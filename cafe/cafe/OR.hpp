#ifndef CAFE_OR_HPP__
#define CAFE_OR_HPP__

#include <list>
#include "cafe/Formula.hpp"
#include "cafe/Controller.hpp"

class TFile;
class TTreeFormula;

namespace cafe {

    /**
     * Retunr true, if any of the specified processors return true
     *
     * Configuration options:
     *
     * - .Run: Processors* 
     * 
     * \ingroup cafe
     */
    class OR : public Controller {
    public:

      OR(const char *name);
      ~OR(){}

        // Processor interface
        virtual bool processEvent(Event& event);
    public:
        ClassDef(OR, 0);
    };

}

#endif // CAFE_IFPR_HPP__
