
#include "cafe/SelectBranches.hpp"
#include "cafe/Event.hpp"

#include "TBranch.h"
#include "TLeaf.h"
#include "TTree.h"

#include <stdexcept>
#include <algorithm>
#include <set>

namespace cafe {

    BranchNames::BranchNames()
	: _cookie(-1)
    {
    }

    BranchNames::BranchNames(const std::string& name)
	: _branchNames(1, name),
	  _cookie(-1)
    {
    }

    BranchNames::BranchNames(const std::string& name1, const std::string& name2)
	: _cookie(-1)
    {
	_branchNames.push_back(name1);
	_branchNames.push_back(name2);
    }

    BranchNames::BranchNames(const std::string& name1, const std::string& name2, const std::string& name3)
	: _cookie(-1)
    {
	_branchNames.push_back(name1);
	_branchNames.push_back(name2);
	_branchNames.push_back(name3);
    }

    BranchNames::BranchNames(const std::string& name1, const std::string& name2, const std::string& name3, const std::string& name4)
	: _cookie(-1)
    {
	_branchNames.push_back(name1);
	_branchNames.push_back(name2);
	_branchNames.push_back(name3);
	_branchNames.push_back(name4);
    }

    BranchNames::BranchNames(const std::vector<std::string>& names)
	: _branchNames(names),
	  _cookie(-1)
    {
    }

    BranchNames::BranchNames(const BranchNames& other)
	: _branchNames(other._branchNames),
	  _branches(other._branches),
	  _oldStatus(other._oldStatus),
	  _cookie(other._cookie)
    {
    }

    BranchNames& BranchNames::operator=(const BranchNames& other)
    {
	if(this != &other) {
	    _branchNames = other._branchNames;
	    _branches    = other._branches;
	    _oldStatus   = other._oldStatus;
	    _cookie      = other._cookie;
	}
	return *this;
    }

    void BranchNames::disable(TTree *tree, int cookie) const
    {
	using namespace std;

	if(_branchNames.empty()) return;

	if(cookie != _cookie) {
	    // The TTree has changed. This is called once
	    // per input file.

	    _cookie = cookie;

	    // update branches
	    _branches.clear();
	    _oldStatus.clear();

	    set<string>   branchesSeen;
	    set<TBranch*> branchesToDisable;

	    for(vector<string>::const_iterator it = _branchNames.begin();
		it != _branchNames.end();
		++it) {

		// Name is of the form BRANCH.MEMBER
		string::size_type pos = (*it).find('.');
		if(pos != string::npos) {

		    std::string branchName = (*it).substr(0, pos);
		    std::string memberName = (*it).substr(pos + 1);

		    if(TBranch *br = tree->FindBranch(branchName.c_str())) {

			// Disable the whole branch
			// the first time we see it.
			if(branchesSeen.find(branchName) == branchesSeen.end()) {
			    TIter iter(br->GetListOfBranches());
			    while(TBranch *member = (TBranch *)iter.Next()) {
				branchesToDisable.insert(member);
			    }
			    branchesSeen.insert(branchName);
			}
			    
			// Remove the entry we are interested in.
			if(TBranch *member = br->FindBranch(memberName.c_str())) {
			    branchesToDisable.erase(member);
			} else {
			    throw runtime_error("BranchNames: no such member: " + memberName);
			}
			
		    } else {
			throw runtime_error("BranchNames: no such branch: " + branchName);
		    }
		} else {
		    throw runtime_error("BranchNames: no such branch: " + *it);
		}
	    }
	    _branches.assign(branchesToDisable.begin(), branchesToDisable.end());
	    _oldStatus.resize(_branches.size());
	}

	// This is called for every event.
	for(size_t i = 0; i < _branches.size(); ++i) { 
	    _oldStatus[i] = _branches[i]->TestBit(kDoNotProcess);
	    _branches[i]->SetBit(kDoNotProcess);
	}
    }

    void BranchNames::enable() const
    {
	using namespace std;

	for(size_t i = 0; i < _branches.size(); i++) {
	    _branches[i]->SetBit(kDoNotProcess, _oldStatus[i]);
	}
    }

    SelectBranches::SelectBranches(cafe::Event& event, const BranchNames& names)
	: _names(names)
    {
	names.disable(event.getTree(), event.getCookie());
    }

    SelectBranches::~SelectBranches()
    {
	_names.enable();
    }
	
}
