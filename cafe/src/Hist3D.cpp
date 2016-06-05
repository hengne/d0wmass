
#include "cafe/Hist3D.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Formula.hpp"

#include <stdexcept>
#include <cstdlib>

#include "TH3F.h"
#include "TFile.h"
#include "TTreeFormula.h"
#include "TTreeFormulaManager.h"

namespace cafe {
    
    Hist3D::Hist3D(const char *name)
        : Processor(name),
          _title(name),
	  _num_binsX(100),
	  _bin_minX(0.0),
	  _bin_maxX(100.0),
	  _num_binsY(100),
	  _bin_minY(0.0),
	  _bin_maxY(100.0),
	  _num_binsZ(100),
	  _bin_minZ(0.0),
	  _bin_maxZ(100.0),
	  _select(0),
	  _draw1(0),
	  _draw2(0),
	  _draw3(0),
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

	if(bins.size() != 9) {
	    err() << "Hist3D[" << name << "] : Expected nine parameters for .Bins, got: " << config.get("Bins", "") << endl;
	    throw std::runtime_error("Hist3D: wrong number of Bins parameters");
	} else {
	    _num_binsX = strtol(bins[0].c_str(), 0, 0);
	    _bin_minX  = strtod(bins[1].c_str(), 0);
	    _bin_maxX  = strtod(bins[2].c_str(), 0);
	    _num_binsY = strtol(bins[3].c_str(), 0, 0);
	    _bin_minY  = strtod(bins[4].c_str(), 0);
	    _bin_maxY  = strtod(bins[5].c_str(), 0);
	    _num_binsZ = strtol(bins[6].c_str(), 0, 0);
	    _bin_minZ  = strtod(bins[7].c_str(), 0);
	    _bin_maxZ  = strtod(bins[8].c_str(), 0);
	}

	string sel  = config.get("Select", "1");

        vector<string> draws = config.getVString("Draw", ":");

	string draw1("0");
	string draw2("0");
	string draw3("0");

	if(draws.size() != 3) {
	    err() << "Hist3D[" << name << "]: Expected three dimensions in Draw, got: " 
		  << config.get("Draw","") << endl;
	    throw std::runtime_error("Hist3D: wrong number of Draw dimensions");
	} else {
	    draw1 = replace(draws[0]);
	    draw2 = replace(draws[1]);
	    draw3 = replace(draws[2]);
	    out() << "Hist3D[" << name << "]: Plotting " << draw1 
		  << " : " << draw2 
		  << " : " << draw3 << endl;
	}
	_select = new Formula(this);
	_select->setFormula(sel);
	
	_draw1 = new Formula(this);
	_draw1->setFormula(draw1);
	
	_draw2 = new Formula(this);
	_draw2->setFormula(draw2);
	
	_draw3 = new Formula(this);
	_draw3->setFormula(draw3);

    }

    Hist3D::~Hist3D()
    {
	delete _select;
	delete _draw1;
	delete _draw2;
	delete _draw3;
	// delete _mgr;
    }

    void Hist3D::begin()
    {
        if(TDirectory *dir = getDirectory()) {
            dir->cd();
            _hist = new TH3F(name().c_str(), _title.c_str(), 
			     _num_binsX, _bin_minX, _bin_maxX,
			     _num_binsY, _bin_minY, _bin_maxY,
			     _num_binsZ, _bin_minZ, _bin_maxZ
			     );
            if (!_weight.empty())
                _hist->Sumw2();
            out() << "Hist3D: Title: \"" << _title << "\""
		  << " BinsX: " << _num_binsX << " MinX: " << _bin_minX << " MaxX: " << _bin_maxX
		  << " BinsY: " << _num_binsY << " MinY: " << _bin_minY << " MaxY: " << _bin_maxY
		  << " BinsZ: " << _num_binsZ << " MinZ: " << _bin_minZ << " MaxZ: " << _bin_maxZ
		  << std::endl;
        } else {
            err() << fullName() << ": No valid directory" << std::endl;
        }

    }

    void Hist3D::inputFileOpened(TFile *file)
    {
	_select->inputFileOpened(file);
        _draw1->inputFileOpened(file);
        _draw2->inputFileOpened(file);
        _draw3->inputFileOpened(file);
	if(_mgr == 0) {
	    _mgr = new TTreeFormulaManager();
	    _mgr->Add(_select->getFormula());
	    _mgr->Add(_draw1->getFormula());
	    _mgr->Add(_draw2->getFormula());	    
	    _mgr->Add(_draw3->getFormula());	    
	    _mgr->Sync();
	}
	_mgr->UpdateFormulaLeaves();
    }

    bool Hist3D::processEvent(Event& event)
    {
	Float_t weight = 1.0;
	if(!_weight.empty()) {
	    event.get(_weight, weight);
	}

	TTreeFormula *sel  = _select->getFormula();
        TTreeFormula *draw1 = _draw1->getFormula();
        TTreeFormula *draw2 = _draw2->getFormula();
        TTreeFormula *draw3 = _draw3->getFormula();

	int ndata = _mgr->GetNdata();
	for(int i = 0; i < ndata; i++) {
	    if(sel->EvalInstance(i)) {
		_hist->Fill(draw1->EvalInstance(i), draw2->EvalInstance(i), draw3->EvalInstance(i), weight);
	    }
	} 
        return true;
    }
    
}

ClassImp(cafe::Hist3D)

