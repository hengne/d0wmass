#ifndef CAFE_IFPR_HPP__
#define CAFE_IFPR_HPP__

#include <list>
#include "cafe/Formula.hpp"
#include "cafe/Controller.hpp"

class TFile;
class TTreeFormula;

namespace cafe {

    /**
     * For each event, if the Select processors evaluates
     * to true, execute the .Then: children of this Controller.
     * Otherwise execute the .Else: children.
     *
     * Configuration options:
     *
     * - .Select: Processors* 
     * - .Then:  Processors*
     * - .Else:  Processors*
     * 
     * \ingroup cafe
     */
    class IfPr : public Controller {
    public:

        IfPr(const char *name);
        ~IfPr();

        // Processor interface
        virtual bool processEvent(Event& event);
    public:
        ClassDef(IfPr, 0);
    };

}

#endif // CAFE_IFPR_HPP__
