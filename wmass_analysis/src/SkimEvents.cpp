
#include "wmass_analysis/SkimEvents.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace cafe;

SkimEvents::SkimEvents(const char *name) : Processor(name) {
  // read this from configuration file
  Config config(name);

  // skim MC events
  _MCSkim = config.get("MCStudy", false);
  
  // read in the table
  string temp = config.get("eventlist", "events.txt");
  ifstream RunEvtNoFile(temp.c_str());

  if ( ! RunEvtNoFile ) {
    cout << "Please provide a text file that contains (run # and event #) on each line" << endl;
    return;
  }
  
  Int_t runno, evtno;
  Int_t nlines=0;
  
  cout << "Reading event list" << endl;
  while ( !RunEvtNoFile.eof() ) { // loop over all lines
    RunEvtNoFile >> runno >> evtno;
    event_set.insert( make_pair(runno, evtno) );
    nlines++;
  }  
  RunEvtNoFile.close();
  
  _skimedEvents = 0;

  cout << "Will skim " << nlines-1 << " events." << endl;
}

bool SkimEvents::processEvent(Event& event)
{
  // read the run, event number table
  int runno = event.getGlobal()->runno();
  int evtno = event.getGlobal()->evtno();
  
  // if we want to do with MC events, will read overlay run number and event number
  if(_MCSkim) {
    runno = event.getMCEventInfo()->overlayrun();
    evtno = event.getMCEventInfo()->overlayevtid();
  }
  
  if(_skimedEvents>0 && _skimedEvents%1000==0) cout <<_skimedEvents << " events skimmed so far" << endl;

  if(event_set.find(make_pair(runno, evtno)) == event_set.end())  {
   if(_MCSkim) cout<<"Throw away event: "<<runno<<" "<<evtno<<endl;
   return false;
  } else {
    _skimedEvents ++;;   
    return true;
  }
}
	
void SkimEvents::finish() {
  cout << "Total number of events skimmed: " << _skimedEvents << endl;
}
	     
ClassImp(SkimEvents)
