#include "cafe/Variables.hpp"

#include "TBranch.h"
#include "TClass.h"
#include "TTree.h"

#include <cassert>
#include <stdexcept>

namespace cafe {

    Variables::Variables()
	: _cookie(-1),
	  _branch(0)
    {
    }

    Variables::Variables(const std::vector<std::string>& names)
	: _names(names),
	  _cookie(-1),
	  _branch(0)
    {
    }

    Variables::Variables(const std::string& name1)
	: _names(1, name1),
	  _cookie(-1),
	  _branch(0)
    {
    }
	
    Variables::Variables(const std::string& name1, const std::string& name2)
	: _cookie(-1),
	  _branch(0)
    {
	add(name1);
	add(name2);
    }

    Variables::Variables(const std::string& name1, const std::string& name2, const std::string& name3)
	: _cookie(-1),
	  _branch(0)
    {
	add(name1);
	add(name2);
	add(name3);
    }

    Variables::Variables(const std::string& name1, const std::string& name2, const std::string& name3, const std::string& name4)
	: _cookie(-1),
	  _branch(0)
    {
	add(name1);
	add(name2);
	add(name3);
	add(name4);
    }

    Variables::Variables(const Variables& other)
	: _names(other._names),
	  _subbranches(other._subbranches),
	  _cookie(other._cookie),
	  _branch(other._branch)
    {
    }
    
    Variables& Variables::operator=(const Variables& other)
    {
	if(this != &other) {
	    _names       = other._names;
	    _subbranches = other._subbranches;
	    _cookie      = other._cookie;
	    _branch      = other._branch;
	}
	return *this;
    }

    Variables& Variables::add(const std::string& name)
    {
	_names.push_back(name);
	_cookie = -1;
	_branch = 0;
	return *this;
    }
    
    Variables& Variables::add(const std::vector<std::string>& names)
    {
	_names.insert(_names.end(), names.begin(), names.end());
	_cookie = -1;
	_branch = 0;
	return *this;
    }
    
    Variables::~Variables()
    {
    }

    bool Variables::empty() const
    {
	return _names.empty();
    }

    void Variables::get(TTree *tree, TBranch *br, int cookie) const
    {
	using namespace std;

	assert(tree != 0);
	assert(br != 0);

	if(cookie != _cookie) {

	    // TTree has changed, update branch pointers
	    // update branch pointers
	    _subbranches.clear();
	    for(vector<string>::const_iterator it = _names.begin();
		it != _names.end();
		++it) {
		if(TBranch *subbr = br->FindBranch((*it).c_str())) {
		    _subbranches.push_back(subbr);
		} else {

		  // Requested variable is missing from branch.  This might
		  // be OK if this is a newly added variable.  Crash if the
		  // requested variable is missing from dictionary.

		  TClass* cls = TClass::GetClass(br->GetClassName());
		  assert(cls != 0);
		  if(cls->GetDataMember(it->c_str()) == 0)
		    throw runtime_error("Variables: non-existing branch name: " + *it);
		}
	    }

	    _cookie = cookie;
	    _branch = br;
	}

	if(_branch != br) {
	    throw std::logic_error(std::string("Variables: using same object for two different branches: ") +
				   _branch->GetName() + " and " + br->GetName());
	}
	
	// Read the variables if they are not yet in memory
	Long64_t current = tree->GetReadEntry();
	for(vector<TBranch*>::iterator it = _subbranches.begin();
	    it != _subbranches.end();
	    ++it) {
	    if((*it)->GetReadEntry() != current) {
		(*it)->GetEntry(current);
	    }
	}
    }

}

