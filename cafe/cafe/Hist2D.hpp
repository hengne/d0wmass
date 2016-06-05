#ifndef CAFE_HIST2D_HPP__
#define CAFE_HIST2D_HPP__

#include <string>
#include "cafe/Processor.hpp"

class TFile;
class TH2F;
class TTreeFormula;
class TTreeFormulaManager;

namespace cafe {

    class Formula;

    /**
     * Create a 2D Histogram (TH2F) and fill it for
     * each event. The histogram is stored in the
     * current directory. You can set the current file
     * and directory in any of the parents of this Processor
     * or the top-level 'Cafe' controller via the
     * .Output: or .Directory: parameters.
     *
     * Configuration options:
     *
     * - .Title:  title [default: name]
     * - .Bins:   NumberBinsX MinBinX MaxBinX NumberBinsY MinBinY MaxBinY [ default: 100 0.0 100.0 100 0. 100. ]
     * - .Draw:   DrawExpression1:DrawExpression2  [default:""]
     * - .Select: SelectExpression [ default: "1" ]
     * - .Weight: WeightName [ default: "", ie. weight is 1.0 ]
     *
     * \ingroup cafe
     */
    class Hist2D : public Processor {
    public:
        Hist2D(const char *name);
	~Hist2D();
        void begin();
        void inputFileOpened(TFile *file);
        bool processEvent(Event& event);
    private:
        std::string  _title;
        int          _num_binsX;
        double       _bin_minX, _bin_maxX;
        int          _num_binsY;
        double       _bin_minY, _bin_maxY;
        TH2F         *_hist;
	Formula      *_select;
	Formula      *_draw1;
	Formula      *_draw2;
	TTreeFormulaManager *_mgr;
	std::string  _weight;
    public:
        ClassDef(Hist2D, 0);
    };

}


#endif // CAFE_HIST1D_HPP__
