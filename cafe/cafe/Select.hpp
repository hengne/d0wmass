#ifndef CAFE_SELECT_HPP__
#define CAFE_SELECT_HPP__

#include "cafe/Formula.hpp"
#include "cafe/Processor.hpp"
#include "cafe/SelectBranches.hpp"

#include <string>

class TFile;

namespace cafe {

    class Event;

    /**
     * Select events based on a user defined cut.
     *
     * If .Tag is specified, events are tagged,
     * otherwise events are rejected, if they don't fulfill
     * the selection criteria.
     *
     * The cut follows the usual TTree::Draw() rules, 
     * e.g. "Muon.pT() > 10.0 && abs(Muon.eta()) < 2.0"
     *
     * Configuration options:
     *
     * - .Select:  Expression [default:"1"]
     * - .Tag:     String     [default: ""]
     * - .Variables: StringList [ default: empty ]
     *
     * The .Variables: entry should be only used for optimization.
     * During the execution of the selection only the designated
     * branches are enabled for reading. For example, if you use only
     * EMscone.Pt() in your expression, and you know that it uses only
     * EMscone.fX and EMscone.fY, you can mention these in the
     * .Variables: configuration entry.
     *
     * \ingroup cafe
     */
    class Select : public Processor, protected Formula {
    public:
        Select(const char *name);
        void inputFileOpened(TFile *file);
        bool processEvent(cafe::Event& event);
    public:
        ClassDef(Select, 0);
    private:
	std::string _tag;
	cafe::BranchNames _branches;
    };
    
}

#endif // CAFE_SELECT_HPP__
