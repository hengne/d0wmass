#ifndef CAFE_FORMULA_HPP__
#define CAFE_FORMULA_HPP__

#include "TObject.h"
#include <string>

class TFile;
class TTreeFormula;

namespace cafe {

    class Processor;

    /**
     *
     * Inherit from this if you need to use TTreeFormular
     * and call Formula::inputFileOpened() at the appropriate time.
     *
     * Due to problems with rootcint, always use protected inheritance
     * and put this class after any other Processor, Controller:
     *
     * class Example : public Processor, protected Formula {}
     *
     * This is used internally by several cafe classes.
     *
     * \ingroup cafe
     */
    class Formula {
    public:
        Formula(cafe::Processor *owner);
        virtual ~Formula();
    public:
        void inputFileOpened(TFile *file);

        void          setFormula(const std::string& formula);
        TTreeFormula *getFormula();

    private:
        std::string      _expr;
        cafe::Processor *_owner;
        TTreeFormula    *_formula;
    public:
        ClassDef(Formula, 0);
    };

}

#endif // CAFE_FORMULA_HPP__
