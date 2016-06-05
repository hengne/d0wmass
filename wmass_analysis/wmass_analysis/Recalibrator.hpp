#ifndef RECALIBRATOR_HPP
#define RECALIBRATOR_HPP
#include "cafe/SelectUserObjects.hpp"
#include "cafe/Event.hpp"
#include "wmass_analysis/EMScaleChangerRunIIbJan.hpp"
#include "wmass_analysis/CorrEemcalo.hpp"
#include "wmass_analysis/CorrEemcaloJan.hpp"

class Recalibrator : public cafe::SelectUserObjects<TMBEMCluster> {

public:
  Recalibrator(const char * name);
  ~Recalibrator();
  bool processEvent(cafe::Event& event);
  void after(cafe::Collection<TMBEMCluster>&, cafe::Collection<TMBEMCluster>&);
  bool selectObject(const TMBEMCluster &emCluster);

private:

  void ScaleEM(TMBEMCluster &,const float scalefactor); //scale the energy and calE in TMBEMCluster
  
  std::string _epoch;
  std::string _mode;
  EMScaleChangerRunIIbJan _scalechangerIIbJan;
  CorrEemcalo _geocorr;
  CorrEemcaloJan _geocorrJan;

  cafe::Event* _event;

  Bool_t _MClikeData;

  ClassDef(Recalibrator,0) ;
};
#endif

