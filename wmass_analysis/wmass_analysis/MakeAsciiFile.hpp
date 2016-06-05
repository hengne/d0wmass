#ifndef MAKE_ASCII_FILE_HPP__
#define MAKE_ASCII_FILE_HPP__

#include <vector>
#include <string>
#include <fstream>

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"
#include "cafe/Event.hpp"
#include "caf_mc_util/CafUtilsMC.hpp"

#include "TH1D.h"

namespace caf_mc_util {

    class MakeAsciiFile : public cafe::Processor {
      std::string analysis_form;
      struct analysis_block {
	 int nevt;
	 double event_weight;
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
//       TH1D *_ewetau;
//       TH1D *_ptwtau;

      TTree * _ana_tree;
      ofstream outasciifile;
      MakeAsciiFile(const char *name);
      bool processEvent(cafe::Event& event);
      void begin() ;	  
      void finish() ;	  
      void inputFileOpened(TFile *file) ;
      int _event_number;
      ClassDef(MakeAsciiFile,0);
    };

}

#endif // MAKE_ASCII_FILE
