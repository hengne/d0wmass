#include "caf_trigger/MatchL1MuonReco.hpp"

MatchL1MuonReco::MatchL1MuonReco(const char *name) : cafe::Processor(name) {
    cafe::Config config(name);

    _RecoName = config.get("RecoBranch", "Muon");
    _matchname = config.get("Result", "");
    _minItems = config.get("nMatches", 0);
    _maxItems = config.get("nMatchesMax", 0);
};

bool MatchL1MuonReco::processEvent(cafe::Event &event) 
{
    const TMBL1Muon *obj1 = event.getL1Muon();
  
    Collection<TMBMuon> objs2 = event.getCollection<TMBMuon>(_RecoName);
    Collection<TMBMuon>::iterator obj2_it=objs2.begin(), best_it=objs2.end();
  
    int nmatches=0;

    _matchmmap.clear();
  
    for(obj2_it=objs2.begin(); obj2_it!=objs2.end(); obj2_it++) {
	  int muon_oct = int(obj2_it->Phi()*4./TMath::Pi());
	  /*for(obj1_it=objs1.begin(); obj1_it!=objs1.end(); obj1_it++)*/ {
		bool match = false;
		if(obj2_it->region()==0) { // Central muon
		    match = (obj1->Central(muon_oct, 9)!=0 || obj1->Central(muon_oct, 10)!=0);
		} else { // Forward muon
		    if(obj2_it->region()==1) { // North muon
			  match = (obj1->North(muon_oct, 9)!=0 || obj1->North(muon_oct, 10)!=0);
		    } else { // South muon
			  match = (obj1->South(muon_oct, 9)!=0 || obj1->South(muon_oct, 10)!=0);
		    };
		};
		if(match) {
		  nmatches++ ;
		    _matchmmap.insert(std::pair<const TMBL1Muon*, Collection<TMBMuon>::iterator>(obj1, obj2_it));
		    if(debug()>0) {
			  std::cout << "An object match was found!" << std::endl;
		    };
		};
	  };
    };

    if((_minItems<=0 || nmatches>=_minItems) && 
       (_maxItems<=0 || nmatches<=_maxItems)) {
		event.put(_matchname, _matchmmap);
		return true;
    } 
    return false;
};

ClassImp(MatchL1MuonReco)
