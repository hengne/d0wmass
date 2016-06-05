

#ifndef FAKEANALYSIS_HPP
#define FAKEANALYSIS_HPP

#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"
#include "wmass_util/CAFWCand.hpp"
#include "wmass_util/EMClusterPosCorr.hpp"


#include "tmb_tree/TMBJet.hpp"
#include "wmass_util/hist_files.hpp"

class FakeAnalysis : public cafe::Processor {
 public:
  FakeAnalysis(const char *name);
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();

  bool GoodJet(const TMBJet& jet);

  ClassDef(FakeAnalysis, 0);
  
 private:
  // debug level
  int _debugLevel;
  
  // detector eta cuts for EM objects
  float _DetEtaCC, _DetEtaEC1, _DetEtaEC2;

  // emfrac, isolation and hmatrix cuts
  float _EMFracCut, _IsoCut, _HM7Cut, _HM8Cut;

  // definition of good jets
  float _jetpTCut, _jetEMFracCut1, _jetEMFracCut2, _jetCHFracCut, _jetHCRatioCut;
  int _jetN90Cut,  _jetTrackCut;

  // detector eta cuts for jets
  float _DetEtaCC_Jet, _DetEtaEC1_Jet, _DetEtaEC2_Jet;

  // angle and phi seperation between EM and Jet
  float _Angle_Jet_EM_Cut, _DPhi_Jet_EM_Cut;

  // met cut to determine fake rate
  float _MetCut_FakeRate;

  double _InstLumi_lowcut, _InstLumi_highcut;

  bool _dorawCellsRecoil ;
  bool _useConsistentMET ;


  // histograms
  hist_files _histos;

  //variables to use
  cafe::Variables _met_vars;
  cafe::Variables _jccb_vars;
};

#endif
