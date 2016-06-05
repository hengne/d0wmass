#ifndef CAFE_SELECTBRANCHES_HPP_
#define CAFE_SELECTBRANCHES_HPP_

#include <string>
#include <vector>

class TBranch;
class TTree;

namespace cafe {

    class Event;
    class SelectBranches;

    /// Helper class to maintain a list of branch names and corresponding
    /// TBranch pointers.
    ///
    /// All names should be of the form 'BRANCH.MEMBER' or 
    /// just 'BRANCH'.
    ///
    /// Examples:
    /// BranchNames names("EMscone.fX", "EMscone.fY");
    ///
    class BranchNames {
    public:
	BranchNames();
	BranchNames(const std::string& name);
	BranchNames(const std::string& name1, const std::string& name2);
	BranchNames(const std::string& name1, const std::string& name2, const std::string& name3);
	BranchNames(const std::string& name1, const std::string& name2, const std::string& name3, const std::string& name4);
	BranchNames(const std::vector<std::string>& names);

	BranchNames(const BranchNames& other);
	BranchNames& operator=(const BranchNames& other);

    private:
	friend class SelectBranches;
	void disable(TTree *tree, int cookie) const;
	void enable() const;
	
	std::vector<std::string>      _branchNames;
	mutable std::vector<TBranch*> _branches;
	mutable std::vector<bool>     _oldStatus;
	mutable int                   _cookie;
    };

    /// Helper class to temporarily disable branches.
    ///
    /// An instance of this class should be instantiated
    /// around a code block where certain TMBTree branches
    /// should not be read. The destructor will automatically
    /// enable all disabled branches again.
    ///
    /// Example:
    ///
    /// BranchNames names("EMscone.fX", "EMscone.fY");
    ///
    /// SelectBranches enable(event, names);
    ///
    ///   // only the two branches above are enabled now
    ///

    class SelectBranches {
    public:
	SelectBranches(cafe::Event& event, const BranchNames& names);
	~SelectBranches();
    private:
	// not implemented
	SelectBranches(const SelectBranches& );
	SelectBranches operator=(const SelectBranches& );

	const BranchNames& _names;
    };
    

}

#endif // CAFE_SELECTBRANCHES_HPP_
