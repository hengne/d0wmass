#ifndef CAFE_IF_HPP__
#define CAFE_IF_HPP__

#include <list>
#include "cafe/Formula.hpp"
#include "cafe/Controller.hpp"

class TFile;
class TTreeFormula;

namespace cafe {

    /**
     * For each event, if the Select expression evaluates
     * to true, execute the .Then: children of this Controller.
     * Otherwise execute the .Else: children.
     *
     * Configuration options:
     *
     * - .Select: Expression [default: "1"]
     * - .Then:  Processors*
     * - .Else:  Processors*
     * 
     * \ingroup cafe
     */
    class If : public Controller, protected Formula {
    public:

        If(const char *name);
        ~If();

        // Processor interface
        virtual void inputFileOpened(TFile *file);
        virtual bool processEvent(Event& event);
    public:
        ClassDef(If, 0);
    };

}

#endif // CAFE_IF_HPP__
