#include "caf_trigger/MatchObjectsL2Reco.hpp"

MatchObjectsL2Reco::MatchObjectsL2Reco(const char *name) : cafe::Processor(name) {
    cafe::Config config(name);

    _l2branch = config.get("L2Branch", "");
    _recobranch = config.get("RecoBranch", "");
    _matchname = config.get("Result", "");
    _maxdR = config.get("dR", .5);
    _minItems = config.get("nMatches", 0);
    _maxItems = config.get("nMatchesMax", 0);
};

bool MatchObjectsL2Reco::processEvent(cafe::Event &event)
{
    bool obj1_L2=false, obj1_L3=false, obj2_L3=false, obj2_Reco=false;
	
    Collection<TMBL2Base> objs1 = event.getCollection<TMBL2Base>(_l2branch);
    Collection<TMBL2Base>::iterator obj1_it=objs1.begin();

    Collection<TMBLorentzVector> objs2 = event.getCollection<TMBLorentzVector>(_recobranch);
    Collection<TMBLorentzVector>::iterator obj2_it=objs2.begin(), best_it=objs2.end();

    int nmatches=0;

    // 	if(typeid(T1)==typeid(TMBL2Base)) obj1_L2 = true;
    // 	if(typeid(T1)==typeid(TMBL3Base)) obj1_L3 = true;

    // 	if(typeid(T2)==typeid(TMBL3Base)) obj2_L3 = true;
    // 	if(typeid(T2)==typeid(TMBLorentzVector)) obj2_Reco = true;
	
    if(debug()>0) {
	  std::cout << "Trying to find a match!" << std::endl;
	  std::cout << "Size of obj1 collection: " << objs1.size() << std::endl;
	  std::cout << "Size of obj2 collection: " << objs2.size() << std::endl;
    };
	
    //_matches.clear();
    _matchmap.clear();

    for(obj1_it=objs1.begin(); obj1_it!=objs1.end(); obj1_it++) {
	  best_it=objs2.end();
	  float bestdR=_maxdR;
	  for(obj2_it=objs2.begin(); obj2_it!=objs2.end(); obj2_it++) {
		float dphi = kinem::delta_phi((*obj2_it).Phi(), (*obj2_it).Phi());
		if(debug()>0) std::cout << "Obj1 eta: " << (*obj1_it).Eta() << ", Obj2 eta: " << /*(*obj2_it).Eta() <<*/ std::endl;
		float deta = (*obj1_it).Eta() - (*obj2_it).Eta();
		float dR   = sqrt(dphi * dphi + deta * deta);
		if( dR < bestdR ) {
		    bestdR = dR;
		    best_it = obj2_it;
		};
	  };
	  if(best_it!=objs2.end()) {
		//_matches.push_back(Match<TMBL2Base,TMBLorentzVector>(obj1_it, _l2branch, best_it, _recobranch, bestdR));
		_matchmap.insert(std::pair<Collection<TMBL2Base>::iterator, Collection<TMBLorentzVector>::iterator>(obj1_it, best_it));
		nmatches++;
		if(debug()>0) {
		    std::cout << "An object match was found!" << std::endl;
		    std::cout << "dR: " << bestdR << std::endl << "Eta (best obj2): " << (*best_it).Eta() << ", Phi (best obj2): " << (*best_it).Phi() << std::endl;
		    std::cout << "Eta (obj1): " << (*obj1_it).Eta() << ", Phi (obj1): " << (*obj1_it).Phi() << std::endl;
		    /*std::cout << "Tool name: " << (*obj1_it).ToolName() << std::endl;*/
		};
	  };
    };
    if(debug()>0) std::cout << std::endl << "---------------------------------------------------------------------------------" << std::endl;
    if((_minItems<=0 || nmatches>=_minItems) && 
       (_maxItems<=0 || nmatches<=_maxItems)) {
		event.put(_matchname, _matchmap);
		return true;
    }
    return false;
};

ClassImp(MatchObjectsL2Reco)
