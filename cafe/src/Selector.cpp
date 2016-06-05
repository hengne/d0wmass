
#include "cafe/Selector.hpp"

namespace cafe {


    Selector::Selector(const char *name)
	: Controller(name),
	  TSelector(),
	  _tree(0)
    {
    }

    void Selector::Begin(TTree *tree)
    {
	begin();
    }

    void Selector::Init(TTree *tree)
    {
	_tree = tree;
	_event.setBranchAddresses(tree);
	inputFileOpened(tree->GetCurrentFile());
    }

    void Selector::Terminate()
    {
	finish();
    }


    Bool_t Selector::Process(Entry_t entry)
    {
	_tree->LoadTree(entry);
	return processEvent(_event);
    }

    Int_t Selector::Version() const
    {
	return 1;
    }

}

ClassImp(cafe::Selector)
