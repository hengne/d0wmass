#include "caf_trigger/L2RecoMatchTest.hpp"

L2RecoMatchTest::L2RecoMatchTest(const char *name) : cafe::Processor(name) {
	cafe::Config config(name);

	_matchname = config.get("Matches", "");
	_toolname = config.get("Toolname","");
};

bool L2RecoMatchTest::processEvent(cafe::Event &event)
{
  // The vector of "Matches" and iterators of it are used with the _old_ interface
  std::vector<Match< TMBL2Base, TMBLorentzVector> > test;
  std::vector<Match< TMBL2Base, TMBLorentzVector> >::iterator match_it;
  //The new interface uses a multimap and iterators thereof.
  std::multimap<Collection<TMBL2Base>::iterator, Collection<TMBLorentzVector>::iterator> L2Reco;
  std::multimap<Collection<TMBL2Base>::iterator, Collection<TMBLorentzVector>::iterator>::iterator L2Reco_it;
  Collection<TMBL2Base>::iterator l2_it;
  Collection<TMBLorentzVector>::iterator reco_it;

  //Uncomment the following section to print a list of all triggers of the event
/*
  Collection<TMBTrigger> triggers = event.getTriggers();
  Collection<TMBTrigger>::iterator trigger_it=triggers.begin();
  for(; trigger_it!=triggers.end(); trigger_it++) {
    std::cout << (*trigger_it).getTrgName() << std::endl;
  };
*/
  //Example to access the matchings, old interface!
  if(event.get(_matchname, test)) {
    match_it=test.begin();
    std::cout << "Found " << test.size() << " match(es) in the event." << std::endl; 
    for(; match_it!=test.end(); match_it++) {
	std::cout << "dr = " << (*match_it).getdR() << std::endl;
	std::cout << "Et = " << (*match_it).getObj1It()->Et() << std::endl;
    };
  }
  
  //Example code to access the matchings, new interface!
  if(event.get(_matchname+"MAP", L2Reco)) {
    std::cout << "Matches in the event: " << L2Reco.size() << std::endl;
    L2Reco_it = L2Reco.begin();

    int i=0;
    for(; L2Reco_it!=L2Reco.end(); L2Reco_it++) {
	l2_it = (*L2Reco_it).first;
	reco_it = (*L2Reco_it).second;
	
	float dphi = kinem::delta_phi((*l2_it).Phi(), (*reco_it).Phi());
	float deta = (*l2_it).Eta() - (*reco_it).Eta();
	float dR   = sqrt(dphi * dphi + deta * deta);
	
	std::cout << "Distance of match: " << dR << std::endl;
	std::cout << "Et of L2 object: " << (*l2_it).Et() << "; and pT of reco object: " << (*reco_it).Pt() << std::endl;
    };
  };
  
  std::cout << "--------------------------------------------------------------------------" << std::endl;
  return true;
};

ClassImp(L2RecoMatchTest)
