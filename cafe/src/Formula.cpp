

#include "cafe/Formula.hpp"
#include "cafe/Processor.hpp"
#include "TTreeFormula.h"
#include "TFile.h"

#include <iostream>

namespace cafe {

    Formula::Formula(cafe::Processor *owner)
        : _owner(owner),
          _formula(0)
    {}

    Formula::~Formula()
    {
        delete _formula;
    }

    void Formula::inputFileOpened(TFile *file)
    {
        if(_formula == 0) {
            // first time
            _formula = new TTreeFormula(_owner->name().c_str(), _expr.c_str(), (TTree *)file->Get("TMBTree"));
        } else {
            _formula->SetTree((TTree *)file->Get("TMBTree"));
            _formula->UpdateFormulaLeaves();
        }
    }

    void Formula::setFormula(const std::string& formula)
    {
        _expr = formula;
    }

    TTreeFormula *Formula::getFormula()
    {
        return _formula;
    }

}

ClassImp(cafe::Formula)
