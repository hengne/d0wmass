#ifndef CAFE_HIST1D_HPP__
#define CAFE_HIST1D_HPP__

#include <string>
#include "cafe/Formula.hpp"
#include "cafe/Processor.hpp"

class TFile;
class TH1F;
class TTreeFormula;
class TTreeFormulaManager;

namespace cafe {

    class HistoGetter;

    /**
     * Create a 1D Histogram (TH1F) and fill it for
     * each event. The histogram is stored in the
     * current directory. You can set the current file
     * and directory in any of the parents of this Processor
     * or the top-level 'Cafe' controller via the
     * .Output: or .Directory: parameters.
     *
     * Configuration options:
     
     * - .Title:  title [default: name]
     * - .Bins:   NumberOfBins MinBin MaxBin [ default: 100 0.0 100.0 ]
     * - .Draw:   DrawExpression  [default:""]
     * - .Select: SelectExpression [ default: "1" ]
     * - .Weight: WeightName [ default: "" (which means we use 1.0 as weight) ]
     *
     * \ingroup cafe
     */
    class Hist1D : public Processor {
    public:
        Hist1D(const char *name);
	~Hist1D();
        void begin();
        void inputFileOpened(TFile *file);
        bool processEvent(Event& event);
    private:
        std::string  _title;
        int          _num_bins;
        double       _bin_min, _bin_max;
        TH1F         *_hist;
	Formula      *_select;
	Formula      *_draw;
	TTreeFormulaManager *_mgr;
	std::string  _weight;
	HistoGetter  *_getter;
	std::string  _branch;
	std::string  _method;
    public:
        ClassDef(Hist1D, 0);
    };

}


#endif // CAFE_HIST1D_HPP__
