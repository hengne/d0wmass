#ifndef INC_MUSMEAR
#define INC_MUSMEAR

#include "PMCSMuon.hpp"
#include "PParameterReader.hpp"
#include <string>
#include "TRandom3.h"
#include <vector>
#include <algorithm>

class MuSmear {
  
 public:

  //constructor: read in parameters
  MuSmear(TString parameter_filename);

  // destructor
  ~MuSmear(){;}

  // smear PMCSMuon
  PMCSMuon SmearMuon(PMCSMuon& muon, TRandom3 *dummy);

  // smear a list of PMCSMuons
  std::vector<PMCSMuon> SmearMuons(std::vector<PMCSMuon> muons, TRandom3 *dummy);
  
  // smear muon momentum and eta, phi
  PMCSMuon Smear(PMCSMuon& part_gen, 
	         double etares_phy, double phires_phy,
	         double A, double B, double C, TRandom3 *dummy);
  
  // smear muon eta, phi
  void SmearPhysEtaPhi(PMCSMuon& part_gen, 
		       double etares_phy, double phires_phy,
		       TRandom3 *dummy, double& phyeta_smeared, double& phyphi_smeared);
  
  // smear muon momentum
  void SmearMomentum(PMCSMuon& part_gen, 
                     double A, double B, double C, TRandom3 *dummy, double& momentum_smeared);
  
  // set smearing parameters
  void SetSmearParameters(double etares_phy, double phires_phy, double A, double B, double C);

  // return smearing parameters
  double EtaRes_Phy() const;
  double PhiRes_Phy() const;
  double A() const;
  double B() const;
  double C() const;
 
  private:
  
  double _etares_phy, _phires_phy;
  double _A, _B, _C;
};

inline double MuSmear::EtaRes_Phy() const {return _etares_phy;}
inline double MuSmear::PhiRes_Phy() const {return _phires_phy;}
inline double MuSmear::A() const {return _A;}
inline double MuSmear::B() const {return _B;}
inline double MuSmear::C() const {return _C;}

#endif
