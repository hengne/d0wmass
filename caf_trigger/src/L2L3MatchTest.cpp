#include "caf_trigger/L2L3MatchTest.hpp"

L2L3MatchTest::L2L3MatchTest(const char *name) : cafe::Processor(name) {
	cafe::Config config(name);

	_matchname = config.get("Matches", "");
	_toolname = config.get("Toolname","");
};

bool L2L3MatchTest::processEvent(cafe::Event &event)
{
  // The vector of "Matches" and iterators of it are used with the _old_ interface
  std::vector<Match< TMBL2Base, TMBL3Base> > test;
  std::vector<Match< TMBL2Base, TMBL3Base> >::iterator match_it;
  //The new interface uses a multimap and iterators thereof.
  std::multimap<Collection<TMBL2Base>::iterator, Collection<TMBL3Base>::iterator> L2L3;
  std::multimap<Collection<TMBL2Base>::iterator, Collection<TMBL3Base>::iterator>::iterator L2L3_it;
  Collection<TMBL2Base>::iterator l2_it;
  Collection<TMBL3Base>::iterator l3_it;

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
	if(typeid((*match_it).getObj2It())==typeid(Collection<TMBL3Base>::iterator)) std::cout << (*(*match_it).getObj2It()).ToolName() << std::endl;
    };
  }
  
  //Example code to access the matchings, new interface!
  if(event.get(_matchname+"MAP", L2L3)) {
    std::cout << "Matches in the event: " << L2L3.size() << std::endl;
    L2L3_it = L2L3.begin();

    int i=0;
    for(; L2L3_it!=L2L3.end(); L2L3_it++) {
	l2_it = (*L2L3_it).first;
	l3_it = (*L2L3_it).second;
	
	float dphi = kinem::delta_phi((*l2_it).Phi(), (*l3_it).Phi());
	float deta = (*l2_it).Eta() - (*l3_it).Eta();
	float dR   = sqrt(dphi * dphi + deta * deta);
	
	std::cout << "L3 tool name: " << (*l3_it).ToolName() << std::endl;
	std::cout << "Distance of match: " << dR << std::endl;
	std::cout << "Et of L2 object: " << (*l2_it).Et() << "; and Et of L3 object: " << (*l3_it).Et() << std::endl;
    };
  };
  
  std::cout << "--------------------------------------------------------------------------" << std::endl;
  return true;
};

ClassImp(L2L3MatchTest)
