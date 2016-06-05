#include "caf_trigger/MatchL1CalTileReco.hpp"

MatchL1CalTileReco::MatchL1CalTileReco(const char *name) : cafe::Processor(name) {
    cafe::Config config(name);

    _L1Name = config.get("CalTiles", "L1CalTile");
    _RecoName = config.get("RecoBranch", "EMscone");
    _matchname = config.get("Result", "");
    _maxdR = config.get("dR", .5);
    _maxdEt = config.get("dEt", 10.); // GeV
    _minItems = config.get("nMatches", 0);
    _maxItems = config.get("nMatchesMax", 0);
};

bool MatchL1CalTileReco::processEvent(cafe::Event &event) 
{
    Collection<TMBL1CalTile> objs1 = event.getCollection<TMBL1CalTile>(_L1Name);
    Collection<TMBL1CalTile>::iterator obj1_it=objs1.begin();

    Collection<TMBLorentzVector> objs2 = event.getCollection<TMBLorentzVector>(_RecoName);
    Collection<TMBLorentzVector>::iterator obj2_it=objs2.begin(), best_it=objs2.end();

    int nmatches=0;

    _matchmmap.clear();

    for(obj1_it=objs1.begin(); obj1_it!=objs1.end(); obj1_it++) {
	  best_it=objs2.end();
	  float bestdR=_maxdR;
	  for(obj2_it=objs2.begin(); obj2_it!=objs2.end(); obj2_it++) {
		float dphi = kinem::delta_phi((*obj1_it).Phi(), (*obj2_it).Phi());
		//			std::cout << "Obj1 eta: " << (*obj1_it).Eta() << ", Obj2 eta: " << /*(*obj2_it).Eta() <<*/ std::endl;
		float deta = (*obj1_it).Eta() - (*obj2_it).Eta();
		float dR   = sqrt(dphi * dphi + deta * deta);
		if( dR < bestdR ) {
		    bestdR = dR;
		    best_it = obj2_it;
		};
	  };
	  if(best_it!=objs2.end()) {
		_matchmmap.insert(std::pair<Collection<TMBL1CalTile>::iterator, Collection<TMBLorentzVector>::iterator>(obj1_it, best_it));
		nmatches++;
		if(debug()>0) {
		    std::cout << "An object match was found!" << std::endl;
		    std::cout << "dR: " << bestdR << std::endl << "Eta (best obj2): " << (*best_it).Eta() << ", Phi (best obj2): " << (*best_it).Phi() << std::endl;
		    std::cout << "Eta (obj1): " << (*obj1_it).Eta() << ", Phi (obj1): " << (*obj1_it).Phi() << std::endl;
		    /*std::cout << "Tool name: " << (*obj1_it).ToolName() << std::endl;*/
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

ClassImp(MatchL1CalTileReco);
