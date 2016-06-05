
#include "cafe/Select.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/SelectBranches.hpp"

#include "TTreeFormula.h"

namespace cafe {

    Select::Select(const char *name)
        : Processor(name), 
          Formula(this)
    {
        // read this from configuration file
        Config config(name);
        std::string expr = config.get("Select","1");

	_tag      = config.get("Tag","");
	_branches = config.getVString("Variables", " ,");

        setFormula(expr);
        out() << "Select[" << name << "]: " << expr << std::endl;
	if(_tag != "") {
	    out() << "Select[" << name << "]: Tag = " << _tag << std::endl;
	}
    }

    void Select::inputFileOpened(TFile *file)
    {
        Formula::inputFileOpened(file);
	getFormula()->SetQuickLoad(kTRUE);
    }

    bool Select::processEvent(Event& event)
    {
	SelectBranches enable(event, _branches);

        // if (!formula->GetNdim()) return true ? 
        TTreeFormula *formula = getFormula();
        int ndata = formula->GetNdata();
        for(int i = 0; i < ndata; i++) {
            if(formula->EvalInstance(i) > 0.0) {
		if(_tag != "") {
		    event.tag(_tag);
		}
		return true;
	    }
        }
        return _tag != "" ? true : false;
    }

}

ClassImp(cafe::Select)
