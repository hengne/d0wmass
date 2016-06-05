#ifndef CAFE_HIST3D_HPP__
#define CAFE_HIST3D_HPP__

#include <string>
#include "cafe/Processor.hpp"

class TFile;
class TH3F;
class TTreeFormula;
class TTreeFormulaManager;


namespace cafe {

    class Formula;

    /**
     * Create a 3D Histogram (TH2F) and fill it for
     * each event. The histogram is stored in the
     * current directory. You can set the current file
     * and directory in any of the parents of this Processor
     * or the top-level 'Cafe' controller via the
     * .Output: or .Directory: parameters.
     *
     * Configuration options:
     *
     * - .Title:  title [default: name]
     * - .Bins:   NumberBinsX MinBinX MaxBinX 
     *            NumberBinsY MinBinY MaxBinY 
                  NumberBinsZ MinBinZ MaxBinZ [ default: 100 0.0 100.0 ...]
     * - .Draw:   DrawExpression1:DrawExpression2:DrawExpression3  [default:""]
     * - .Select: SelectExpression [ default: "1" ]
     * - .Weight: WeightName [ default: "", ie. weight 1.0 ]
     *
     * \ingroup cafe
     */
    class Hist3D : public Processor {
    public:
        Hist3D(const char *name);
	~Hist3D();
        void begin();
        void inputFileOpened(TFile *file);
        bool processEvent(Event& event);
    private:
        std::string  _title;
        int          _num_binsX;
        double       _bin_minX, _bin_maxX;
        int          _num_binsY;
        double       _bin_minY, _bin_maxY;
        int          _num_binsZ;
        double       _bin_minZ, _bin_maxZ;
        TH3F         *_hist;
	Formula      *_select;
	Formula      *_draw1;
	Formula      *_draw2;
	Formula      *_draw3;
	TTreeFormulaManager *_mgr;
	std::string  _weight;
    public:
        ClassDef(Hist3D, 0);
    };

}


#endif // CAFE_HIST3D_HPP__
