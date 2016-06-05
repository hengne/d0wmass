#include "caf_trigger/L3RecoMatchTest.hpp"

L3RecoMatchTest::L3RecoMatchTest(const char *name) : cafe::Processor(name) {
	cafe::Config config(name);

	_matchname = config.get("Matches", "");
	_toolname = config.get("Toolname","");
};

bool L3RecoMatchTest::processEvent(cafe::Event &event)
{
  // The vector of "Matches" and iterators of it are used with the _old_ interface
  std::vector<Match< TMBL3Base, TMBLorentzVector> > test;
  std::vector<Match< TMBL3Base, TMBLorentzVector> >::iterator match_it;
  //The new interface uses a multimap and iterators thereof.
  std::multimap<Collection<TMBL3Base>::iterator, Collection<TMBLorentzVector>::iterator> L3Reco;
  std::multimap<Collection<TMBL3Base>::iterator, Collection<TMBLorentzVector>::iterator>::iterator L3Reco_it;
  Collection<TMBL3Base>::iterator l3_it;
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
  if(event.get(_matchname+"MAP", L3Reco)) {
    std::cout << "Matches in the event: " << L3Reco.size() << std::endl;
    L3Reco_it = L3Reco.begin();

    int i=0;
    for(; L3Reco_it!=L3Reco.end(); L3Reco_it++) {
	l3_it = (*L3Reco_it).first;
	reco_it = (*L3Reco_it).second;
	
	float dphi = kinem::delta_phi((*l3_it).Phi(), (*reco_it).Phi());
	float deta = (*l3_it).Eta() - (*reco_it).Eta();
	float dR   = sqrt(dphi * dphi + deta * deta);
	
	std::cout << "Tool name: " << (*l3_it).ToolName() << std::endl;
	std::cout << "Distance of match: " << dR << std::endl;
	std::cout << "Et of L3 object: " << (*l3_it).Et() << "; and pT of reco object: " << (*reco_it).Pt() << std::endl;
    };
  };
  
  std::cout << "--------------------------------------------------------------------------" << std::endl;
  return true;
};

ClassImp(L3RecoMatchTest)
