#ifndef CAFE_SELECTOBJECTS_HPP__
#define CAFE_SELECTOBJECTS_HPP__

#include "cafe/Event.hpp"
#include "cafe/Formula.hpp"
#include "cafe/Processor.hpp"

#include <string>

class TFile;
class TTree;
class TBranch;
class TClonesArray;

namespace cafe {

    /**
     * Select objects based on a user defined cut.
     *
     * The cut follows the usual TTree::Draw() rules, 
     * e.g. "Muon.pT() > 10.0 && Muon.eta() < 2.0"
     *
     * The selection is applied to all objects.
     *
     * Configuration options:
     *
     * - .From:   OldBranchname [required]
     * - .To:     NewBranchName [required]
     * - .Select: Expression    [default:"1"], i.e. all objects
     * - .Tree:   OutputTreeName[default: name()]
     * 
     * \ingroup cafe
     */
    class SelectObjects : public Processor, protected Formula {
    public:
        SelectObjects(const char *name);
        void inputFileOpened(TFile *file);
        void inputFileClosing(TFile *file);
        bool processEvent(cafe::Event& event);
    private:
	std::string  _fromBranch;
	std::string  _toBranch;
	std::string  _treeName;
	TTree        *_tree;
	TClonesArray *_result;
	TBranch      *_branch;
    public:
        ClassDef(SelectObjects, 0);
    };
    
}

#endif // CAFE_SELECTOBJECTS_HPP__
