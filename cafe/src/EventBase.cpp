
#include "TObject.h"

#include "cafe/EventBase.hpp"
#include "cafe/Stat.hpp"

#include "TProcessID.h"

#include <stdexcept>

extern cafe::Stat* STAT ; 

namespace cafe {

    namespace detail {
	const Variables empty;
    }

    EventBase::EventBase()
	: _tree (0),
	  _cookie(0),
	  _partial_read(true),
	  _objectCount(TProcessID::GetObjectCount())
    {
    }
    
    EventBase::~EventBase()
    {
    }

    // Called when the tree changes.
    // Set addresses for reading Branches.
    void EventBase::setBranchAddresses(TTree *tree)
    {
	_tree = tree;
	for(BranchMap::iterator it = _branches.begin();
	    it != _branches.end();
	    ++it) {
	    (*it).second->setBranchAddress(tree);
	}
	_cookie++;
    }

    bool EventBase::readBranch(const std::string& branchName) 
    {
	if(_branches.find(branchName) != _branches.end()) {
	    BranchHolderBase *branch = _branches[branchName];
	    branch->readBranch(_tree);
	    return true;
	} else if(TBranch *br = _tree->FindBranch(branchName.c_str())) {
	    return br->GetEntry(_tree->GetReadEntry()) >= 0;
	} else {
	    return false;
	}
    }

    bool EventBase::setPartialRead(bool allow)
    {
	bool ret = _partial_read;
	_partial_read = allow;
	return ret;
    }

    bool EventBase::getPartialRead() const
    {
	return _partial_read;
    }

    void EventBase::clear()
    {
	for(Map::iterator it = _map.begin();
	    it != _map.end();
	    ++it) {
	    (*it).second->clear();
	    delete (*it).second;
	}
	_map.clear();
	_tags.clear();
	if (STAT) STAT->eventEnd() ;

	//
	// The real limit is > 83000000 million objects, but there
	// is something seriously wrong if you created more than
	// 100000 objects per event.
	//
	
	if(TProcessID::GetObjectCount() - _objectCount > 100000) {
	    throw std::runtime_error("EventBase::clear(): TProcessID object count too large");
	}

	TProcessID::SetObjectCount(_objectCount);
    }

    void EventBase::clear(const std::string& key)
    {
	Map::iterator it = _map.find(key);
	if(it != _map.end()) {
	    (*it).second->clear();
	    delete (*it).second;
	    _map.erase (it);
	}
    }

    std::vector<std::string> *EventBase::varnames() 
    {
      Map::iterator it = _map.begin();
      std::vector<std::string> *varnamelist = new std::vector<std::string>;
      for(; it!=_map.end(); it++) varnamelist->push_back(it->first);
      return varnamelist;
    };
  
    std::vector<std::string> *EventBase::vartypes()
    {
      Map::iterator it = _map.begin();
      std::vector<std::string> *vartypelist = new std::vector<std::string>;
      for(; it!=_map.end(); it++) vartypelist->push_back(std::string( (typeid(it->second)).name()) );
      return vartypelist;
    };

    void EventBase::tag(const std::string& tag)
    {
	_tags.insert(tag);
    }

    bool EventBase::hasTag(const std::string& tag) const
    {
	return _tags.find(tag) != _tags.end();
    }

    bool EventBase::hasTag(const char *tag) const
    {
	return _tags.find(std::string(tag)) != _tags.end();
    }

    void EventBase::untag(const std::string& tag)
    {
      _tags.erase(tag);
    }    
  
   ostream& EventBase::printTags(ostream& os) const {
     for(std::set<std::string>::const_iterator it = _tags.begin() ;
	 it != _tags.end() ; it++) 
       os << "[" << *it  << "] " ;
     return os ;
   }


    TTree *EventBase::getTree() const
    {
	return _tree;
    }

    int   EventBase::getCookie() const
    {
	return _cookie;
    }

    const TClonesArray *EventBase::getClonesArray(const std::string& branchName, const Variables& vars) const
    {
	BranchHolder<TClonesArray> *branch = dynamic_cast<BranchHolder<TClonesArray>*>(_branches[branchName]);
	if(branch == 0) {
	    _branches[branchName] = branch = new BranchHolder<TClonesArray>(branchName);
	    branch->setBranchAddress(_tree);
	}
	return branch->getObject(_tree, _partial_read ? vars : cafe::detail::empty, _cookie);
    }



}

ClassImp(cafe::EventBase);

