
#include "cafe/Hist2D.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Formula.hpp"

#include <stdexcept>
#include <cstdlib>

#include "TH2F.h"
#include "TFile.h"
#include "TTreeFormula.h"
#include "TTreeFormulaManager.h"

namespace cafe {
    
    Hist2D::Hist2D(const char *name)
        : Processor(name),
          _title(name),
	  _num_binsX(100),
	  _bin_minX(0.0),
	  _bin_maxX(100.0),
	  _num_binsY(100),
	  _bin_minY(0.0),
	  _bin_maxY(100.0),
	  _select(0),
	  _draw1(0),
	  _draw2(0),
	  _mgr(0)
    {
	using namespace std;

        // from configuration get:
        // _expr, _title, _binX_min, _bin_max, _num_bins
        // _draw1, _draw2
	//
        Config config(name);
        _title    = config.get("Title", _title);
	_weight   = config.get("Weight", "");

	vector<string> bins = config.getVString("Bins", " ,");

	if(bins.size() != 6) {
	    err() << "Hist2D[" << name << "] : Expected six parameters for .Bins, got: " << config.get("Bins", "") << endl;
	    throw std::runtime_error("Hist2D: wrong number of Bins parameters");
	} else {
	    _num_binsX = strtol(bins[0].c_str(), 0, 0);
	    _bin_minX  = strtod(bins[1].c_str(), 0);
	    _bin_maxX  = strtod(bins[2].c_str(), 0);
	    _num_binsY = strtol(bins[3].c_str(), 0, 0);
	    _bin_minY  = strtod(bins[4].c_str(), 0);
	    _bin_maxY  = strtod(bins[5].c_str(), 0);
	}

	string sel  = config.get("Select", "1");

        vector<string> draws = config.getVString("Draw", ":");
	string draw1("0");
	string draw2("0");

	if(draws.size() != 2) {
	    err() << "Hist2D[" << name << "]: Expected two dimensions in Draw, got: " 
		  << config.get("Draw","") << endl;
	    throw std::runtime_error("Hist2D: wrong number of Draw dimensions");
	} else {
	    draw1 = replace(draws[0]);
	    if(draw1 == "") {
		err() << "Hist2D[" << name << "]: Replacement failed for first dimension: " 
		      << draws[0] << endl;
	    }
	    draw2 = replace(draws[1]);
	    if(draw2 == "") {
		err() << "Hist2D[" << name << "]: Replacement failed for second dimension: " 
		      << draws[1] << endl;
	    }
	    
	    out() << "Hist2D[" << name << "]: Plotting " << draw1 << " : " << draw2 << endl;
	}

	_select = new Formula(this);
	_select->setFormula(sel);
	
	_draw1 = new Formula(this);
	_draw1->setFormula(draw1);
	
	_draw2 = new Formula(this);
	_draw2->setFormula(draw2);

    }

    Hist2D::~Hist2D()
    {
	delete _select;
	delete _draw1;
	delete _draw2;
    }

    void Hist2D::begin()
    {

        if(TDirectory *dir = getDirectory()) {
            dir->cd();
            _hist = new TH2F(name().c_str(), _title.c_str(), 
			     _num_binsX, _bin_minX, _bin_maxX,
			     _num_binsY, _bin_minY, _bin_maxY
			     );
            if (!_weight.empty())
                _hist->Sumw2();
            out() << "Hist2D: Title: \"" << _title << "\""
		  << " BinsX: " << _num_binsX << " MinX: " << _bin_minX << " MaxX: " << _bin_maxX
		  << " BinsY: " << _num_binsY << " MinY: " << _bin_minY << " MaxY: " << _bin_maxY
		  << std::endl;
        } else {
            err() << fullName() << ": No valid directory" << std::endl;
        }

    }

    void Hist2D::inputFileOpened(TFile *file)
    {
	_select->inputFileOpened(file);
        _draw1->inputFileOpened(file);
        _draw2->inputFileOpened(file);
	if(_mgr == 0) {
	    _mgr = new TTreeFormulaManager();
	    _mgr->Add(_select->getFormula());
	    _mgr->Add(_draw1->getFormula());
	    _mgr->Add(_draw2->getFormula());	    
	    _mgr->Sync();
	}
	_mgr->UpdateFormulaLeaves();
    }

    bool Hist2D::processEvent(Event& event)
    {
	Float_t weight = 1.0;
	if(!_weight.empty()) {
	    event.get(_weight, weight);
	}

	TTreeFormula *sel  = _select->getFormula();
        TTreeFormula *draw1 = _draw1->getFormula();
        TTreeFormula *draw2 = _draw2->getFormula();

	int ndata = _mgr->GetNdata();
	for(int i = 0; i < ndata; i++) {
	    if(sel->EvalInstance(i)) {
		_hist->Fill(draw1->EvalInstance(i), draw2->EvalInstance(i), weight);
	    }
	}
        return true;
    }
    
}

ClassImp(cafe::Hist2D)

