#ifndef CAFE_PERMUTE_HPP__
#define CAFE_PERMUTE_HPP__

#include "cafe/Controller.hpp"

namespace cafe {

    /**
     * Execute all permutations of its children (N!)
     *
     * Internally creates a Controller for each permutation.
     * and fills each with a possible sequence. For each
     * sub-Controller it creates a separate directory, 
     * named after the permuted sequence of names of the children.
     *
     * Example:
     *
     * - .Run: Permute[Cuts]
     * - Cuts.Run: Cut1 Cut2 Cut3
     *
     * is equivalent to:
     *
     * - Cuts.Run: Fork[groups]
     * - groups.Run: Group[Cut1_Cut2_Cut3] Group[Cut1_Cut3_Cut2] Group[Cut2_Cut1_Cut3] ...
     *
     * Cut1_Cut2_Cut3.Directory: Cut1_Cut2_Cut3
     * Cut1_Cut3_Cut2.Directory: Cut1_Cut3_Cut2
     * ...
     *
     * \ingroup cafe
     */
    class Permute : public Controller {
    public:
        Permute(const char *name);
        ~Permute();

	// process interface
	virtual bool processEvent(cafe::Event& event);
    public:
	ClassDef(Permute,1);
    };
    
}

#endif // CAFE_PERMUTE_HPP__
