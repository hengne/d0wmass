#include "wmass_analysis/MetSelector.hpp"
#include "tmb_tree/TMBEMCluster.hpp"

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "wmass_util/CAFMet.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace cafe;

MetSelector::MetSelector(const char *name):Processor(name) {
  Config config(name);

  // debug level
  _debugLevel = config.get("debugLevel", 0);

  // met calculated with em corrections only applied on selected electrons
  _met_only_use_Selected_emobjs = config.get("met_only_use_Selected_emobjs", 1);

  _metex_vars.add("_metEM");
  _metex_vars.add("_metMG");
  _metex_vars.add("_metFH");
  _metex_vars.add("_metICD");

}

MetSelector::~MetSelector() {
}

//
// extract missingET
//
void MetSelector::extract(cafe::Event& event, vector<CAFEMObj*> emobjs) {  
  const TMBMetEx *missingET = event.getMetEx(_metex_vars);
  
  float metX_raw=0., metY_raw=0., met_raw=0., scalarEt_raw=0.;
  float metX_new=0., metY_new=0., met_new=0., scalarEt_new=0.;
  float metX_rawicd=0., metY_rawicd=0., met_rawicd=0., scalarEt_rawicd=0.;
  float metX_newicd=0., metY_newicd=0., met_newicd=0., scalarEt_newicd=0.;

  float SumEx_em=0., SumEy_em=0., SumE_em=0., scalarEt_em=0.;
  float SumEx_mg=0., SumEy_mg=0., SumE_mg=0., scalarEt_mg=0.;
  float SumEx_fh=0., SumEy_fh=0., SumE_fh=0., scalarEt_fh=0.;
  float SumExicd=0., SumEyicd=0., SumEicd=0., scalarEticd=0.; 
  
  // energies measured from EM, massless gap and FH layers
  missingET->getVETEM(scalarEt_em, SumEx_em, SumEy_em, SumE_em);
  missingET->getVETMG(scalarEt_mg, SumEx_mg, SumEy_mg, SumE_mg);
  missingET->getVETFH(scalarEt_fh, SumEx_fh, SumEy_fh, SumE_fh);
  missingET->getVETICD(scalarEticd, SumExicd, SumEyicd, SumEicd);

  metX_rawicd = -(SumEx_em + SumEx_mg + SumEx_fh + SumExicd);
  metY_rawicd = -(SumEy_em + SumEy_mg + SumEy_fh + SumEyicd);
  met_rawicd = sqrt(metX_rawicd*metX_rawicd + metY_rawicd*metY_rawicd);
  scalarEt_rawicd = scalarEt_em + scalarEt_mg + scalarEt_fh + scalarEticd;


  metX_raw = -(SumEx_em + SumEx_mg + SumEx_fh);
  metY_raw = -(SumEy_em + SumEy_mg + SumEy_fh);
  met_raw = sqrt(metX_raw*metX_raw + metY_raw*metY_raw);
  scalarEt_raw = scalarEt_em + scalarEt_mg + scalarEt_fh;

  // make EM corrections
  make_EMCorr(event, emobjs, metX_raw, metY_raw, met_raw, scalarEt_raw,
	      metX_new, metY_new, met_new, scalarEt_new);

  // raw missingEt
  _rawMet.SetMet(metX_raw, metY_raw, met_raw, scalarEt_raw);
  
  // missingEt with EM energy corrections applied
  _corrEMMet.SetMet(metX_new, metY_new, met_new, scalarEt_new);


  // make EM corrections
  make_EMCorr(event, emobjs, metX_rawicd, metY_rawicd, met_rawicd, scalarEt_rawicd,
	      metX_newicd, metY_newicd, met_newicd, scalarEt_newicd);

  // raw missingEt
  _rawMetICD.SetMet(metX_rawicd, metY_rawicd, met_rawicd, scalarEt_rawicd);
  
  // missingEt with EM energy corrections applied
  _corrEMMetICD.SetMet(metX_newicd, metY_newicd, met_newicd, scalarEt_newicd);

}

//
// recalculate missingET for different primary vertex
//
void MetSelector::applyCorrection(cafe::Event& event, vector<CAFEMObj*> emobjs, float vtx_old[3], float vtx_new[3]) {
  
  // revertexing, recalculate missingET for new primary vertex 
  _rawMet.SetMet(event, vtx_new);
  
  // rawMet is now calculated using new primary vertex
  float metX_raw = _rawMet.metx();
  float metY_raw = _rawMet.mety();
  float met_raw = _rawMet.met();
  float scalarEt_raw = _rawMet.scalarEt();
  float metX_new=0., metY_new=0., met_new=0., scalarEt_new=0.;

  // make EM corrections
  make_EMCorr(event, emobjs, metX_raw, metY_raw, met_raw, scalarEt_raw,
	      metX_new, metY_new, met_new, scalarEt_new);

  // now we finally have MET with revertexing and EM energy correction applied
  _corrEMMet.SetMet(metX_new, metY_new, met_new, scalarEt_new);

  // print out information for all missingEt objects
  if(_debugLevel>=5) {
    cout<<"Raw missingEt: ";
    _rawMet.print();
    cout<<"missingEt after EM Correction: ";
    _corrEMMet.print();
  }
}

//
// put pointers to event class
//
void MetSelector::putPointers(cafe::Event& event) {
  event.put("Raw Met", _rawMet);
  event.put("EMCorr Met", _corrEMMet);

  event.put("Raw MetICD", _rawMetICD);
  event.put("EMCorr MetICD", _corrEMMetICD);

}

//
// make EM corrected MET
//
void MetSelector::make_EMCorr(cafe::Event& event, vector<CAFEMObj*> emobjs, float metX_raw, float metY_raw, float met_raw, float scalarEt_raw,
			      float& metX_new, float& metY_new, float& met_new, float& scalarEt_new) {  

  // apply EM corrections
  float Ex_EMObjs_raw = 0., Ey_EMObjs_raw = 0., scalarEt_EMObjs_raw = 0.;
  float Ex_EMObjs_corr = 0., Ey_EMObjs_corr = 0., scalarEt_EMObjs_corr = 0.;
  
  // met calculated with em correction only applied on selected em objects
  if(_met_only_use_Selected_emobjs) {
    for(int iem = 0; iem < emobjs.size(); iem ++) {
      float rawE = emobjs[iem]->uncorrE();
      float corrE = emobjs[iem]->E();
      // calculated used positive cells, EM corrections not applied
      float rawScalarEt = emobjs[iem]->EMScalarEt(); 
      
      float theta = emobjs[iem]->Theta();
      float phi = emobjs[iem]->Phi();
      Ex_EMObjs_corr += corrE * sin(theta) * cos(phi);
      Ey_EMObjs_corr += corrE * sin(theta) * sin(phi);
      
      Ex_EMObjs_raw += rawE * sin(theta) * cos(phi);
      Ey_EMObjs_raw += rawE * sin(theta) * sin(phi);
      
      // because EM corrections are applied on EM cluster, not individual cells
      // the corrected scalarEt = rawScalarEt * correction factor
      scalarEt_EMObjs_raw += rawScalarEt;
      scalarEt_EMObjs_corr += rawScalarEt * corrE/rawE; 
    } // only apply EM correction for selected em objects
  } else {
    //met calculated with em correction only applied on almost all possible em objects
    // numbers used below are taken from em_evt/rcp/GoodEMParticle.rcp
    cafe::Collection<TMBEMCluster> em = event.getEMscone();
    for (Collection<TMBEMCluster>::iterator it = em.begin(); it!= em.end(); ++it) {
      
      if ((abs((*it).id())==10 || abs((*it).id())==11) && ((*it).Pt()>5.)) {
	if((*it).emfrac()>0.9 && (*it).iso()<0.2 && fabs((*it).CalDetectorEta())<2.5) {
	  float rawE = (*it).uncorrE();
	  float corrE = (*it).E();
	  // calculated used positive cells, EM corrections not applied
	  float rawScalarEt = (*it).EMScalarEt(); 
	  
	  float theta = (*it).Theta();
	  float phi = (*it).Phi();
	  Ex_EMObjs_corr += corrE * sin(theta) * cos(phi);
	  Ey_EMObjs_corr += corrE * sin(theta) * sin(phi);
	  
	  Ex_EMObjs_raw += rawE * sin(theta) * cos(phi);
	  Ey_EMObjs_raw += rawE * sin(theta) * sin(phi);
	  
	  // because EM corrections are applied on EM cluster, not individual cells
	  // the corrected scalarEt = rawScalarEt * correction factor
	  scalarEt_EMObjs_raw += rawScalarEt;
	  scalarEt_EMObjs_corr += rawScalarEt * corrE/rawE; 
	}
      }
    } // loop over all EM particles
  }

  metX_new = metX_raw + (Ex_EMObjs_raw - Ex_EMObjs_corr);
  metY_new = metY_raw + (Ey_EMObjs_raw - Ey_EMObjs_corr);
  met_new = sqrt(metX_new*metX_new + metY_new*metY_new);
  scalarEt_new = scalarEt_raw - (scalarEt_EMObjs_raw - scalarEt_EMObjs_corr);
}

ClassImp(MetSelector)
  
