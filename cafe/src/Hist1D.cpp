
#include "cafe/Hist1D.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/HistoGetter.hpp"

#include <cstdlib>
#include <stdexcept>

#include "TH1F.h"
#include "TFile.h"
#include "TTreeFormula.h"
#include "TTreeFormulaManager.h"

namespace cafe {
    
    Hist1D::Hist1D(const char *name)
        : Processor(name),
          _title(name),
	  _num_bins(100),
	  _bin_min(0.0),
	  _bin_max(100.0),
	  _select(0),
	  _draw(0),
	  _mgr(0),
	  _getter(0),
	  _branch(""),
	  _method("")
    {
	using namespace std;

        // from configuration get:
        // _expr, _title, _bin_min, _bin_max, _num_bins
        //
        Config config(name);
        _title    = config.get("Title", _title);
	_weight   = config.get("Weight", "");

	std::vector<std::string> bins = config.getVString("Bins", " ,");

	if(bins.size() != 3) {
	    err() << "Hist1D[" << name << "] : Expected three parameters for .Bins, got: " << config.get("Bins", "") << std::endl;
	    throw std::runtime_error("Hist1D: wrong number of Bins parameters");
	} else {
	    _num_bins = strtol(bins[0].c_str(), 0, 0);
	    _bin_min  = strtod(bins[1].c_str(), 0);
	    _bin_max  = strtod(bins[2].c_str(), 0);
	}
    }

    Hist1D::~Hist1D()
    {
	delete _select;
	delete _draw;
    }

    void Hist1D::begin()
    {

	using namespace std;

	Config config(name());

	std::string sel  = config.get("Select", "1");
        std::string expr = config.get("Draw", "");

	sel = replace(sel);
	if(sel == "") {
	    err() << fullName() << " : replacement failed for " << config.get("Select", "") << endl;
	}

	_select = new Formula(this);
	_select->setFormula(sel);

	expr = replace(expr);
	if(expr == "") {
	    err() << fullName() << " : replacement failed for " << config.get("Draw", "") << endl;
	}

	_draw = new Formula(this);
        _draw->setFormula(expr);

	if(sel == "1") {
	    HistoGetter::parse(expr, _branch, _method);
	}

	//        _title    = config.get("Title", expr);

	if ( _title == name() )
	  _title = expr;
	else
	  _title = replace(_title);
	  
	if( _title == "")
	    err() << fullName() << " : replacement failed for " << config.get("Title", "") << endl;

        if(TDirectory *dir = getDirectory()) {
            dir->cd();
            _hist = new TH1F(name().c_str(), _title.c_str(), _num_bins, _bin_min, _bin_max);
            if (!_weight.empty())
                _hist->Sumw2();
            out() << "Hist1D: Title: \"" << _title << "\" Bins: " << _num_bins << " Min: " << _bin_min << " Max: " << _bin_max << std::endl;
        } else {
            err() << fullName() << ": No valid directory" << std::endl;
        }

    }

    void Hist1D::inputFileOpened(TFile *file)
    {
	// otherwise check if we can optimize
	if(_getter == 0 && !_branch.empty()) {
	    if(TTree *tree = dynamic_cast<TTree*>(file->Get("TMBTree"))) {
		_getter = HistoGetter::create(tree, _branch, _method);
		if(_getter == 0) _branch = ""; 
	    }
	}

	_select->inputFileOpened(file);
        _draw->inputFileOpened(file);

	if(_mgr == 0) {
	    _mgr = new TTreeFormulaManager();
	    _mgr->Add(_select->getFormula());
	    _mgr->Add(_draw->getFormula());
	    _mgr->Sync();
	}
	_mgr->UpdateFormulaLeaves();
    }

    bool Hist1D::processEvent(Event& event)
    {
	Float_t weight = 1.0;
	if(!_weight.empty()) {
	    event.get(_weight, weight);
	}

	TTreeFormula *sel  = _select->getFormula();
        TTreeFormula *draw = _draw->getFormula();

	const TClonesArray *values = 0;
	if(_getter && (values = event.getClonesArray(_branch, _getter->vars()))) {
	    for(int i = 0; i < values->GetLast() + 1; i++) {
		_hist->Fill(_getter->get(values->At(i)), weight);
	    }
	} else {
	    
	    int ndata = _mgr->GetNdata();
	    for(int i = 0; i < ndata; i++) {
		if(sel->EvalInstance(i)) {
		    _hist->Fill(draw->EvalInstance(i), weight);
		}
	    } 
	}
        return true;
    }
    
}

ClassImp(cafe::Hist1D)

