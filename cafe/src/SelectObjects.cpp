

#include "cafe/SelectObjects.hpp"
#include "cafe/Config.hpp"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TDirectory.h"
#include "TClonesArray.h"
#include "TTreeFormula.h"
#include "TBufferFile.h"

namespace cafe {

    SelectObjects::SelectObjects(const char *name)
        : Processor(name), 
          Formula(this),
	  _tree(0),
	  _result(0),
	  _branch(0)
    {
        // read this from configuration file
        Config config(name);
        std::string expr = config.get("Select","1");
        setFormula(expr);

	_fromBranch = config.get("From", "");
	_toBranch   = config.get("To", _fromBranch);
	_treeName   = config.get("Tree", name);
        out() << "SelectObjects[" << name << "]: " << expr << std::endl;
	out() << "SelectObjects[" << name << "] From: " << _fromBranch << " to: " << _toBranch << std::endl;
        out() << "SelectObjects[" << name << "]: Output Tree: " << _treeName << std::endl;
    }

    void SelectObjects::inputFileOpened(TFile *file)
    {
	if(TTree *tmb_tree = (TTree *)file->Get("TMBTree")) {

	    if ( _treeName=="TMBTree" ) _tree = dynamic_cast<TTree*>(file->Get("TMBTree"));
	    else _tree = dynamic_cast<TTree *>(gROOT->Get(_treeName.c_str()));

	    if (_tree == 0) {
		gROOT->cd();
		_tree = new TTree(_treeName.c_str(), fullName().c_str());
		tmb_tree->AddFriend(_tree);
	    }

	    _branch = _tree->GetBranch(_toBranch.c_str()) ;
	    if (_branch == 0) {
		if(TBranchElement *br = (TBranchElement *)tmb_tree->GetBranch(_fromBranch.c_str())) {
		    _result = new TClonesArray(br->GetClonesName());
		    _branch = _tree->Branch(_toBranch.c_str(), &_result, 4096);
		} else {
		    err() << "SelectObjects[" << name() << "] No such branch: " 
			  << _fromBranch << std::endl;
		}
	    }
	    Formula::inputFileOpened(file);
	} else {
	    err() << "SelectObjects[" << name() << "] No TMBTree" << std::endl;
	}
    }

    void SelectObjects::inputFileClosing(TFile *file)
    {
        if ( TTree* tree = (TTree *)gROOT->Get(_treeName.c_str()) )
            tree->Delete();

	_tree = 0;
	_branch = 0;
	_result = 0;
    }

    bool SelectObjects::processEvent(Event& event)
    {
	if(!_result) return true;
	_result->Clear();

	if(const TClonesArray *from = event.get<TClonesArray>(_fromBranch.c_str())) {
	    TTreeFormula *formula = getFormula();
	    int ndata = formula->GetNdata();
	    int next = 0;
	    for(int i = 0; i < ndata; i++) {
		if(formula->EvalInstance(i)) {
		    TBufferFile buf(TBuffer::kWrite);
		    from->At(i)->Streamer(buf);
		    buf.SetBufferOffset(0);
		    buf.SetReadMode();
		    TObject *newobj = _result->New(next);
		    (*_result)[next++]->Streamer(buf);
		    newobj->ResetBit(kIsReferenced);
		    newobj->SetUniqueID(0);
		}
	    }
	}

	_tree->Fill();

	TTree *tmb_tree = event.getTree();
	_tree->LoadTree(tmb_tree->GetReadEntry());

	return true;
    }

}

ClassImp(cafe::SelectObjects)
