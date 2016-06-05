#ifndef EVENTBASE_HPP__
#define EVENTBASE_HPP__

#include <map>
#include <set>
#include <string>

#include "TClonesArray.h"
#include "TIterator.h"
#include "TBranchElement.h"
#include "TTree.h"

#include "cafe/Collection.hpp"
#include "cafe/Variables.hpp"

namespace cafe { 

    namespace detail {
	extern const Variables empty;
    }

    /**
     * CAF tree independent part of Event.
     *
     * This class provides three generic services:
     *
     * -# Access to an arbitrary branch in the associated TTree
     * -# Access to an intermediate store for arbitrary values
     * -# Tagging of events.
     *
     * \ingroup cafe
     */

    class EventBase {
    public:
	EventBase();
	virtual ~EventBase();

	/// @name Access to branches in the tree.
	//@{
	
	/**
	 * Return a pointer to the object corresponding to branch 'branchName'.
	 * If the branch does not exist, return 0.
	 */
	template<typename T>
	const T *get(const std::string& branchName, const Variables& vars = cafe::detail::empty) const;

	/**
	 * Return a Collection<T> corresponding to the TClonesArray in 'branchName'. If the
	 * branch does not exist, return an empty Collection<T>. 
	 */
	template<typename T>
	Collection<T> getCollection(const std::string& branchName, const Variables& vars = cafe::detail::empty) const;

	/**
	 * Return the TClonesArray for the given branch.
	 */
	const TClonesArray *getClonesArray(const std::string& branchName, const Variables& vars = cafe::detail::empty) const;

        /**
	 * Read this branch if not already in memory.
	 */
        bool readBranch(const std::string& branchName);

	/// Called when the tree changes.
	/// Set addresses for reading Branches.
	void setBranchAddresses(TTree *tree);

	/// Allow/Disallow partial reading of objects.
	/// Returns old value. Default is true.
	bool setPartialRead(bool allow);

	/// Get partial read flag
	bool getPartialRead() const;

	//@}

	/// @name Access to intermediate values stored in Event.
	//@{

	/// Store arbitrary value with key.
	///
	/// The value must be copy constructible and assignable.
	/// If you store primitive types, make sure to tell it
	/// exactly which type you mean, e.g.:
	///
	///   event.put("MyValue", (int )5);
	///   int x;
	///   event.get("MyValue", x);
	///
	/// If you store a pointer, the pointer will be deleted
	/// at the end of the current event processing.
	///
	/// If you want the pointer to be preserved, call the
	/// method like this:
	///
	/// SomePointer *ptr = ...;
	/// event.put("MyName", keep(ptr));
	/// 
	/// where 'keep' is defined in the 'cafe' namespace.
	///
	/// Note that the entry "MyName" in the Event is still
	/// cleared at the end of the current event processing.
	///
	
	template<typename T>
	void put(const std::string& key, const T& value);

	void clear (const std::string &key);

	/// Retrieve arbitrary value with key
	template<typename T>
	bool get(const std::string& key, T& value) const;

	/// Clear any values kept in the event store.
	void clear();

        std::vector<std::string> *varnames();
        std::vector<std::string> *vartypes();

	//@}

	/// @name Tagging
	//@{

	/// Tag the event with 'name'
	void tag(const std::string& name);

	/// Tag the event with tags in the range.
	template<typename ITER>
	void tag(ITER from, ITER to);

	/// Check if event is tagged with 'name'
	bool hasTag(const std::string& name) const;

	/// Check if event is tagged with 'name'
	bool hasTag(const char *name) const;

	/// Check if event has any of the tags in the list
	/// 'C' can be any STL container
	template<typename C>
	bool hasTag(const C& c) const;

	/// Remove tag with 'name'
	void untag(const std::string& name);

	/// Remove all of the tags in the range.
	template<typename ITER>
	void untag(ITER from, ITER to);

	/// Print all tags in the event       
	ostream& printTags(ostream& os) const ;

	//@}

	/// Get current TTree
	TTree *getTree() const;

	/// Get current cookie (== tree number)
	int   getCookie() const;
    
    private:
	
	// Internal class for event store
	class BaseHolder {
	public:
	    virtual ~BaseHolder() {}
	    virtual void clear() = 0;
	};

	template<typename T>
	class Holder : public BaseHolder {
	public:
	    Holder(const T& value) : _value(value) {}
	    virtual ~Holder()      {}
	    virtual void clear()   { delete_it(_value); }
	    const T& value() const { return _value; }
	private:
	    template<class U>
	    void delete_it(U *p) { delete p;}

	    template<class U>
	    void delete_it(const U&p) {}
	    T     _value;
	};

	typedef std::map<std::string, BaseHolder*> Map;
	Map _map;

    private:

	// Internal base class for a BranchHolder
	// Only used to keep pointers to it in a map<>
	class BranchHolderBase {
	public:
	    virtual ~BranchHolderBase() {}
	    virtual void setBranchAddress(TTree *tree) = 0;   
	    virtual void readBranch(TTree *tree) = 0;
	};


	// A map of all know branches.
	typedef std::map<std::string,BranchHolderBase*> BranchMap;

	template<typename T>
	class BranchHolder : public BranchHolderBase {
	public:
	    BranchHolder(const std::string& branchName);
	    ~BranchHolder();
	    void setBranchAddress(TTree *tree);
	    T *getObject(TTree *tree, const Variables& vars, int cookie) const;
	    void readBranch(TTree *tree);
	private:
	    std::string _branchName;
	    T           *_branchObject;	// pointer to object
	    TBranch     *_branch;       // pointer to branch
	    mutable Long64_t  _entry;   // cached entry number
	};


	TTree                *_tree;         // the current tree
	mutable BranchMap     _branches;     // a map of branches we know about
	std::set<std::string> _tags;
	int                   _cookie;       // increment for every new tree
	bool                  _partial_read; // if false, no optimized reading by member variable
	UInt_t                _objectCount;  // TProcessID::GetObjectCount()

    public:
	ClassDef(EventBase, 0);
    };

    /// Helper class to avoid that a pointer stored in the
    /// Event is deleted. Use it like this:
    ///
    /// SomeObject *ptr = ...;
    /// event.put("MyName", keep(ptr));
    ///
    /// and retrieve as usual:
    /// SomeObject *ptr = 0;
    /// if(event.get("MyName", ptr)) { ... }

    namespace detail {
	template<class T>
	struct keeper {
	    keeper(T *ptr) : _ptr(ptr) {}
	    T *_ptr;
	};
    }

    template<class T>
    detail::keeper<T> keep(T *ptr) 
    {
	return detail::keeper<T>(ptr);
    }


#ifndef __CINT__

    /*
     * Implementation of templated methods and classes.
     */
    template<typename T>
    const T *EventBase::get(const std::string& branchName, const Variables& vars) const
    {
	BranchHolder<T> *branch = dynamic_cast<BranchHolder<T>*>(_branches[branchName]);
	if(branch == 0) {
	    _branches[branchName] = branch = new BranchHolder<T>(branchName);
	    branch->setBranchAddress(_tree);
	}
	return branch->getObject(_tree, _partial_read ? vars : cafe::detail::empty, _cookie);
    }


    template<typename T>
    Collection<T> EventBase::getCollection(const std::string& branchName, const Variables& vars) const
    {
	BranchHolder<TClonesArray> *branch = dynamic_cast<BranchHolder<TClonesArray>*>(_branches[branchName]);
	if(branch == 0) {
	    _branches[branchName] = branch = new BranchHolder<TClonesArray>(branchName);
	    branch->setBranchAddress(_tree);
	}
	return Collection<T>(branch->getObject(_tree, _partial_read ? vars : cafe::detail::empty, _cookie));
    }

    template<typename T>
    EventBase::BranchHolder<T>::BranchHolder(const std::string& branchName)
	: _branchName(branchName),
	  _branchObject(0),
	  _branch(0),
	  _entry(-1)
    {}

    template<typename T>
    EventBase::BranchHolder<T>::~BranchHolder() 
    { 
	// do we have to delete it ?  
	delete _branchObject;
    }

    template<typename T>
    void EventBase::BranchHolder<T>::setBranchAddress(TTree *tree)
    {
        _branch = tree->GetBranch(_branchName.c_str());
	if(_branch != 0) {
	    char **addr = reinterpret_cast<char **>(_branch->GetAddress());
	    if(addr != 0 && *addr != 0) {
	        _branchObject = reinterpret_cast<T*>(*addr);
		// Take ownership of the object.
		_branch->ResetBit(TBranchElement::kDeleteObject);
	    }
	    // Always pass the address of our pointer so that we are
	    // informed if the branch deletes the object.
	    tree->SetBranchAddress(_branchName.c_str(), &_branchObject);
	}
	_entry = -1;
    }

    template<typename T>
    T *EventBase::BranchHolder<T>::getObject(TTree *tree, const Variables& vars, int cookie) const
    {
	if(!_branch) return 0;

	Long64_t current = tree->GetReadEntry();

	if(vars.empty()) {
	    if(current != _entry) {
                TIter iter(_branch->GetListOfBranches());
                while(TBranch *br = (TBranch *)iter.Next()) {
                    if(current != br->GetReadEntry()) {
                        br->GetEntry(current);
                    }
                }
		_entry = current;
	    }
	} else {
	    vars.get(tree, _branch, cookie);
	}

	return _branchObject;
    }

    template<typename T>
    void EventBase::BranchHolder<T>::readBranch(TTree *tree)
    {
	Long64_t current = tree->GetReadEntry();

	if(current != _entry) {
	    _branch->GetEntry(current);
	    _entry = current;
	}
    }

    template<typename T>
    void EventBase::put(const std::string& key, const T& value)
    {
	Map::iterator it = _map.find(key);
	if(it != _map.end()) {
	    (*it).second->clear();
	    delete (*it).second;
	}
	_map[key] = new Holder<T>(value);
    }

    template<typename T>
    bool EventBase::get(const std::string& key, T& value) const
    {
	Map::const_iterator it = _map.find(key);
	if(it != _map.end()) {
	    if(Holder<T>* p = dynamic_cast<Holder<T>*>((*it).second)) {
		value = p->value();
                return true;
            }
	    if (Holder<detail::keeper<T> >* p = 
	       dynamic_cast<Holder<detail::keeper<T> >*>((*it).second)) {
		value = *(p->value()._ptr);
                return true;
	    }
	}
	return false;
    }

    template<typename C>
    bool EventBase::hasTag(const C& c) const
    {
	for(typename C::const_iterator it = c.begin();
	    it != c.end();
	    ++it) {
	    if(_tags.count(*it) > 0) return true;
	}
	return false;
    }

    /// Tag the events with all tags in the list
    /// 'C' can be any STL container
    template<typename ITER>
    void EventBase::tag(ITER from, ITER to)
    {
	for(;from != to; ++from) {
	    tag(*from);
	}
    }

    /// Remove all of the tags in the list
    /// 'C' can be any STL container
    template<typename ITER>
    void EventBase::untag(ITER from, ITER to)
    {
	for(;from != to; ++from) {
	    untag(*from);
	}
    }
        
#endif // __CINT__

}

#endif // EVENTBASE_HPP__
