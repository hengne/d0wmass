#ifndef CAFE_VARIABLES_HPP_
#define CAFE_VARIABLES_HPP_

#include <string>
#include <vector>

class TBranch;
class TTree;

namespace cafe {

    class EventBase;

    /**
     * Utility class to access only selected variables in a TBranch.
     * By default the Event methods return the full object/array. Often
     * only a few variables are used out of a given branch.
     *
     * This helper class can be used to restrict access to only a subset
     * of the variables in a branch. It should be initialized (either via
     * the constructor or the add() methods) with a list of variable names
     * in the branch. Then the Variables should be passed as a parameter
     * to the Event::getNNN() method. All other variables in the branch
     * are undefined:
     *
     * <pre>
     *  Variables vars("_evtno");
     *  const TMBGlobal *global = event.getGlobal(vars);
     *  int event_number = global->evtno();
     *  int run_number   = global->runno(); // UNDEFINED !!
     * </pre>
     *
     *
     */
    class Variables {
    public:
	Variables();
	explicit Variables(const std::vector<std::string>& names);
	explicit Variables(const std::string& name1);
	Variables(const std::string& name1, const std::string& name2);
	Variables(const std::string& name1, const std::string& name2, const std::string& name3);
	Variables(const std::string& name1, const std::string& name2, const std::string& name3, const std::string& name4);
	Variables(const Variables& other);
	Variables& operator=(const Variables& other);
	Variables& add(const std::string& name);
	Variables& add(const std::vector<std::string>& name);
	~Variables();
	bool empty() const;
    public:
	// Used only internally to do the work.
	void get(TTree *, TBranch *br, int cookie) const;
    private:
	/// List of variable names.
	std::vector<std::string>  _names;
	/// Cached list of TBranch pointers. Invalidated by a new TTree.
	mutable std::vector<TBranch*> _subbranches;
	/// Used to invalidate a new TTree and re-read the TBranch pointers.
	mutable int                   _cookie;
	/// Used internally to check for user error when using same Variables for
	/// different branches.
	mutable TBranch               *_branch;
    };

}

#endif // CAFE_VARIABLES_HPP_
