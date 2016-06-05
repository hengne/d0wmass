/* File RandomSelectUserObjects.hpp
 *
 * Created       : Sun May 31 2007
 * Author        : Amnon Harel (but most of the code is a copy of SelectUserObjects)
 * Purpose       : Base class for cafe object selectors that use random numbers
 * Last modified : 
 * Comments      : Use this instead of a multiplie inheritence from SelectUserObjects and RandomProcessor

    See SelectUserObjects for the main parameters.

    See RandomProcessor for parameters controling the random behavior.

 * Usage :

   In the header file
   ------------------
   class yourProcessor : public cafe::RandomSelectUserObjects<T> { // Do not also inherit from Processor!

     where T is the type of objects you're selecting

   In the source flie
   ------------------
   1) Call the base constructor:

     yourProcessor::yourProcessor (const char *name) : 
       cafe::RandomSelectUserObjects<T>(name)

   2) In your processEvent method, you must call the base class explicitely when you want it to
      loop over the objects and call your selectObject method.

     bool yourProcessor::processEvent(cafe::Event& event)
     {
       cafe::RandomSelectUserObjects<T>::processEvent (event);

       TRandom& rnd = myTRandom();
       ...

     or simply call myRand().Uniform() etc.

   2a) If you need random numbers in your processEvent before looping on the objects, 
       you can call the RandomProcessor::processEvent explicitely, but take care to somehow change
       the resulting seed, otherwise you'll have a nasty correlation when it's reinitialized
       in the later call to RandomSelectUserObjects<T>::processEvent.

   3) if you implement inputFileOpened, you must call the base class explicitely (preferably the first thing
   in your function):

     yourProcessor::inputFileOpened (TFile* file)
     {
       cafe::RandomSelectUserObjects<T>::inputFileOpened (file);
       ...

   4) same for inputFileClosing

     yourProcessor::inputFileClosing (TFile* file)
     {
       cafe::RandomSelectUserObjects<T>::inputFileClosing (file);
       ...

 * Caveats: See 2a) above.

 */

#ifndef RandomSelectUserObjects_HPP_
#define RandomSelectUserObjects_HPP_

#include "cafe/Event.hpp"
#include "cafe/Processor.hpp"
#include "cafe/Config.hpp"
#include "cafe/Variables.hpp"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TDirectory.h"
#include "TClonesArray.h"

#include <stdexcept>

#include "cafe/RandomProcessor.hpp"

namespace cafe {

    template<class T> 
    class RandomSelectUserObjects : public RandomProcessor {
    public:
        RandomSelectUserObjects(const char *name);
        void inputFileOpened(TFile *file);
        void inputFileClosing(TFile *file);
        bool processEvent(cafe::Event& event);
    protected:
        /// Abstract select method to be overridden by user.
        /// Each object for which this method returns true
        /// will be put into the result branch, rejected objected will be 
        /// put in the rejected object branch
        virtual bool selectObject(const T& obj) = 0;
    
        /// Called before the actual selection starts. E.g. the input
	/// can be sorted here.
	virtual void before(Collection<T>& from);
    
        /// Called after the selection is done.
	virtual void after(Collection<T>& accepted, Collection<T>& rejected);
    
        /// Add variables to branch for the partial read
	void addVariable(const std::string& name) {_vars.add(name);}

    private:
        std::string  _fromBranch;
        std::string  _toBranch;
        std::string  _toRejectedBranch;
        std::string  _treeName;      
        TTree        *_tree;
        TClonesArray *_result;
        TClonesArray *_resultRejected;
        TBranch      *_branch;
        TBranch      *_branchRejected;
        Variables     _vars;
    public:
        ClassDef(RandomSelectUserObjects, 0);
    };

    // 
    // Templated implementation must go here...
    // 
    
    template<class T>
    RandomSelectUserObjects<T>::RandomSelectUserObjects(const char *name)
        : RandomProcessor(name), 
	  _tree(0),
	  _result(0),
	  _resultRejected(0),
	  _branch(0),
	  _branchRejected(0)
    {
	using namespace cafe;

        // read this from configuration file
	Config config(name);

	_fromBranch = config.get("From", "");
	_toBranch   = config.get("To", "");
	_toRejectedBranch   = config.get("RejectedBranch", "");
	_treeName   = config.get("Tree", "TMBTree");
	// need to explicitely convert from std::vector<std::string> to Variables before copy constructor
	_vars       = Variables (config.getVString("Variables", " ,"));
	if(_fromBranch.empty()) {
	    throw std::runtime_error(std::string("RandomSelectUserObjects[") + name
				     + "] : From: branch in config file not set");
	}

	if(_toBranch.empty()) {
	    throw std::runtime_error(std::string("RandomSelectUserObjects[") + name
				     + "] : To: branch in config file not set");
	}

	if(_fromBranch == _toBranch) {
	    throw std::runtime_error(std::string("RandomSelectUserObjects[") + name
				     + "] : From: branch has the same name as To: branch");
	}

	if(_fromBranch == _toRejectedBranch) {
	    throw std::runtime_error(std::string("RandomSelectUserObjects[") + name
				     + "] : From: branch has the same name as RejectedBranch: branch");
	}

	out() << "RandomSelectUserObjects[" << name << "] From: " << _fromBranch 
	      << " To: " << _toBranch << std::endl ;
	if (_toRejectedBranch != "") {
	    out () << "  Rejected objects go to branch: " << _toRejectedBranch  << std::endl;
	}
	out() << "RandomSelectUserObjects[" << name << "] Output Tree: " << _treeName << std::endl;
    }

    template<class T>
    void RandomSelectUserObjects<T>::inputFileOpened(TFile *file)
    {
	RandomProcessor::inputFileOpened (file); // the timing of this call is immaterial
	if(TTree *tmb_tree = (TTree *)file->Get("TMBTree")) {

	    if ( _treeName=="TMBTree" ) _tree = dynamic_cast<TTree*>(file->Get("TMBTree"));
	    else _tree = dynamic_cast<TTree *>(gROOT->Get(_treeName.c_str()));

	    if (_tree == 0) {
		gROOT->cd();
		_tree = new TTree(_treeName.c_str(), fullName().c_str());
		tmb_tree->AddFriend(_tree);
	    }
	    
	    _branch = _tree->GetBranch(_toBranch.c_str()) ;
	    if (_branch == 0) {
		if(TBranchElement *br = (TBranchElement *)tmb_tree->GetBranch(_fromBranch.c_str())) {
		    _result = new TClonesArray(br->GetClonesName());
		    _branch = _tree->Branch(_toBranch.c_str(), &_result, 4096);
		    if (_toRejectedBranch != "" && !_branchRejected) {
			_resultRejected = new TClonesArray(br->GetClonesName());
			_branchRejected = _tree->Branch(_toRejectedBranch.c_str(), &_resultRejected, 4096);		  		}
		} else {
		    err() << "RandomSelectUserObjects[" << name() << "] No such branch: " 
			  << _fromBranch << std::endl;
		}
	    }
	} else {
	    err() << "RandomSelectUserObjects[" << name() << "] No TMBTree" << std::endl;
	}
    }

    template<class T>
    void RandomSelectUserObjects<T>::inputFileClosing(TFile *file)
    {
	
        if(TTree* oldtree =
	   dynamic_cast<TTree *>(gROOT->Get(_treeName.c_str()))) {
            oldtree->Delete();
	}
	_tree = 0;
	_branch = 0;
	_branchRejected = 0;
    }

    template<class T>
    void RandomSelectUserObjects<T>::before(Collection<T>& from) 
    {
    }
    
    template<class T>
    void RandomSelectUserObjects<T>::after(Collection<T>& accepted, Collection<T>& rejected) 
    {
    }
    
    template<class T>
    bool RandomSelectUserObjects<T>::processEvent(cafe::Event& event)
    {
	using namespace cafe;

	RandomProcessor::processEvent (event); // done first, so PRNs are available in the user's selectObject method

	if(!_result) return true;
	_result->Delete() ;
	if(_resultRejected) _resultRejected->Delete() ;

	Collection<T> from(event.getCollection<T>(_fromBranch.c_str(), _vars));
	
	before(from);

	Int_t next = 0;
	Int_t nextr = 0;

	for(typename Collection<T>::const_iterator it = from.begin();
	    it != from.end();
	    ++it) {
	    if(selectObject(*it)) {
		event.readBranch(_fromBranch);
		new ((*_result)[next++]) T(*it); 
	    } else if (_resultRejected) {
		event.readBranch(_fromBranch);
		new ((*_resultRejected)[nextr++]) T(*it); 
	    }
	}

	Collection<T> accepted(_result);
	Collection<T> rejected(_resultRejected);
	
	after(accepted, rejected);

	return true;
    }
 
} // end namespace

#endif
