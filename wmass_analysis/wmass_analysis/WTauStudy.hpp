#ifndef TT_EMU_WTAUSTUDY_HPP__
#define TT_EMU_WTAUSTUDY_HPP__

#include <vector>
#include <string>

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"
#include "cafe/Event.hpp"
#include "caf_mc_util/CafUtilsMC.hpp"

#include "TH1D.h"
#include "TFile.h"

namespace caf_mc_util {

    class WTauStudy : public cafe::Processor {
      std::string analysis_form;
      struct analysis_block {
	 int nevt;
	 double event_weight;
    double mw;
	 double wpt;
	 double weta;
	 int wq;
	 double elpt;
	 double eleta;
	 int eleq;
	 double nuelept;
	 double nueleeta;
	 double taupt;
	 double taueta;
	 int tauq;
	 double nutaupt[2];
	 double nutaueta[2];
	 double met;
      } _ana;

    public:
      TH1D *_ewetau;
      TH1D *_ptwtau;

      TH1D *_MW_hist;
      TH1D *_WPT_hist;
      TH1D *_WETA_hist;
      TH1D *_ELPT_hist;
      TH1D *_ELETA_hist;
      TH1D *_NUELEPT_hist;
      TH1D *_NUELETA_hist;
      TH1D *_TAUPT_hist;
      TH1D *_TAUETA_hist;
      TH1D *_NUTAUPT_hist;
      TH1D *_NUTAUETA_hist;
      TH1D *_PIPT_hist;
      TH1D *_MET_hist;

      TFile * _tau_file;
      TTree * _ana_tree;
      WTauStudy(const char *name);
      bool processEvent(cafe::Event& event);
      void begin() ;	  
      void finish() ;	  
      void inputFileOpened(TFile *file) ;
      ClassDef(WTauStudy,0);
    };

}

#endif // TT_EMU_CAF_MCHists_HPP__
