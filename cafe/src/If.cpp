

#include "cafe/If.hpp"
#include "cafe/ParseRun.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include "TFile.h"
#include "TTreeFormula.h"

#include <iostream>
#include <vector>

namespace cafe {

    If::If(const char *name) 
        : Controller(name, std::list<Processor*>()),
          Formula(this)
    {
	using namespace std;

        Config config(name);

	// Get selection expression
        std::string expr = config.get("Select", "1");
        setFormula(expr);

	// Get then/else branches
	ParseRun parser;
	add(new Controller((string(name) + "_Then").c_str(), parser.parse(config.get("Then", ""))));
	add(new Controller((string(name) + "_Else").c_str(), parser.parse(config.get("Else", "")))); 

	// Be nice and tell user if he specified the .Run: entry
	if(config.get("Run","") != "") {
	    err() << "If[" << name << "]: .Run not used in If[]. .Use 'Then:' and '.Else:' instead" << endl;
	}
    }

    If::~If() {}

    void If::inputFileOpened(TFile *file)
    {
        Formula::inputFileOpened(file);
        Controller::inputFileOpened(file);
    }

    // Processor interface
    bool If::processEvent(Event& event)
    {
        event.untag(_untag.begin(), _untag.end());
        event.tag(_tag.begin(), _tag.end());
        TTreeFormula *formula = getFormula();

        if(_processors.size() > 0) {
            std::list<Processor*>::iterator it = _processors.begin();
            // if (!formula->GetNdim()) return true ? 
            int ndata = formula->GetNdata();
            for(int i = 0; i < ndata; i++) {
                if(formula->EvalInstance(i) > 0.0) {
                    // call first subprocessor
                    (*it)->incEventCount();
                    return (*it)->processEvent(event) ;
                }
            }
            // call any other subprocessor, abort if
            // any of them returns false.
            ++it;
            while(it != _processors.end()) {
                (*it)->incEventCount();
                if(!(*it)->processEvent(event)) return false;
                ++it;
            }
            // else fall through
        }
        return true;
    }
}

ClassImp(cafe::If);

