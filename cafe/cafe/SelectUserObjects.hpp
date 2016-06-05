#ifndef CAFE_SELECTUSEROBJECTS_HPP__
#define CAFE_SELECTUSEROBJECTS_HPP__

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

#include <string>
#include <stdexcept>

namespace cafe {

    /**
     * Select objects based on a user defined cut.
     * 
     * The cut is supplied by the user by overriding the
     * virtual selectObject(const T& obj) method.
     *
     * To use this class, inherit from it, passing the desired
     * object type to the base class:
     *
     * class MySelector : public SelectUserObjects<TMBJet> { 
     *
     * Then override the selectObject(const TMBJet& obj) method.
     * The user can also override two more methods (which do nothing
     * by default):
     *
     *   void before(Collection<T>& from);
     *   void after(Collection<T>& accepted, Collection<T>& rejected);
     *
     * Configuration options:
     *
     * - .From:   OldBranchname [required]
     * - .To:     NewBranchName [required]
     * - .RejectedBranch: NewBranchName for the rejected objects [default none]
     * - .Tree:   OutputTreeName[default: name()]
     * - .Variables: Member variable list [default: all]
     *
     * - .LoadAll: Load whole object before it is copied [default: 1]
     *   You should probably never change this if you don't know exactly
     *   what you are doing.
     *
     * \ingroup cafe
     */

    template<class T> 
    class SelectUserObjects : public Processor {
    public:
	SelectUserObjects(const char *name);
	void inputFileOpened(TFile *file);
	void inputFileClosing(TFile *file);
	bool processEvent(cafe::Event& event);
                 const std::string& treeName() const { return _treeName ;}
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

	std::string  _fromBranch;
        Event const* _event;
	Variables    _vars;

    private:
	std::string  _toBranch;
	std::string  _toRejectedBranch;
	std::string  _treeName;      
        bool         _loadAll;
	TTree        *_tree;
	TClonesArray *_result;
	TClonesArray *_resultRejected;
	TBranch      *_branch;
	TBranch      *_branchRejected;
    public:
	ClassDef(SelectUserObjects, 0);
    };
    
    
    // 
    // Templated implementation must go here...
    // 
    
    template<class T>
    SelectUserObjects<T>::SelectUserObjects(const char *name)
        : Processor(name), 
	  _event(0),
          _loadAll(true),
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
	_vars.add(config.getVString("Variables", " ,"));
        _loadAll    = config.get("LoadAll", 1);

	if(_fromBranch.empty()) {
	    throw std::runtime_error(std::string("SelectUserObject[") + name
				     + "] : From: branch in config file not set");
	}

	if(_toBranch.empty()) {
	    throw std::runtime_error(std::string("SelectUserObject[") + name
				     + "] : To: branch in config file not set");
	}

	if(_fromBranch == _toBranch) {
	    throw std::runtime_error(std::string("SelectUserObject[") + name
				     + "] : From: branch has the same name as To: branch");
	}

	if(_fromBranch == _toRejectedBranch) {
	    throw std::runtime_error(std::string("SelectUserObject[") + name
				     + "] : From: branch has the same name as RejectedBranch: branch");
	}

	out() << "SelectUserObjects[" << name << "] From: " << _fromBranch 
	      << " To: " << _toBranch << std::endl ;
	if (_toRejectedBranch != "") {
	    out () << "  Rejected objects go to branch: " << _toRejectedBranch  << std::endl;
	}
	out() << "SelectUserObjects[" << name << "] Output Tree: " << _treeName << std::endl;
    }

    template<class T>
    void SelectUserObjects<T>::inputFileOpened(TFile *file)
    {
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
		  throw std::runtime_error(std::string("SelectUserObject[") + name()
					   + "] : No such branch [" 
					   + _fromBranch + "]!\n") ;
		}
	    } else {
	      throw std::runtime_error(std::string("SelectUserObject[") + name()
				       + "] : You are trying to create the branch " 
				       + _toBranch + " which already exists!\n") ;
	    }
	} else {
	    err() << "SelectUserObjects[" << name() << "] No TMBTree" << std::endl;
	}
    }

    template<class T>
    void SelectUserObjects<T>::inputFileClosing(TFile *file)
    {
	// See if our tree still exists (it might have been deleted already
	// by another processor).

        if(TTree* oldtree =
	   dynamic_cast<TTree *>(gROOT->Get(_treeName.c_str()))) {

	  // Undeclare our tree as a friend of main tree.
	  // We need to do this before deleting our tree.

	  if(_treeName != "TMBTree") {
	    TTree *tmb_tree = (TTree *)file->Get("TMBTree");
	    if(tmb_tree != 0 && tmb_tree != oldtree) {
	      tmb_tree->RemoveFriend(oldtree);
	    }
	  }

	  // Now we can delete the tree.

	  oldtree->Delete();
	}
	_tree = 0;
	_branch = 0;
	_branchRejected = 0;
    }

    template<class T>
    void SelectUserObjects<T>::before(Collection<T>& from) 
    {
    }
    
    template<class T>
    void SelectUserObjects<T>::after(Collection<T>& accepted, Collection<T>& rejected) 
    {
    }
    
    template<class T>
    bool SelectUserObjects<T>::processEvent(Event& event)
    {
	using namespace cafe;

	if(!_result) return true;
	_result->Delete() ;
	if(_resultRejected) _resultRejected->Delete() ;

	_event = &event;

	Collection<T> from(event.getCollection<T>(_fromBranch.c_str(), _vars));
	
	before(from);

	Int_t next = 0;
	Int_t nextr = 0;

	for(typename Collection<T>::const_iterator it = from.begin();
	    it != from.end();
	    ++it) {
	    if(selectObject(*it)) {
                if(_loadAll) {
                    event.readBranch(_fromBranch);
                }
		new ((*_result)[next++]) T(*it); 
	    } else if (_resultRejected) {
                if(_loadAll) {
                    event.readBranch(_fromBranch);
                }
		new ((*_resultRejected)[nextr++]) T(*it); 
	    }
	}

	Collection<T> accepted(_result);
	Collection<T> rejected(_resultRejected);
	
	after(accepted, rejected);

	return true;
    }
    
}

#endif // CAFE_SELECTUSEROBJECTS_HPP__
