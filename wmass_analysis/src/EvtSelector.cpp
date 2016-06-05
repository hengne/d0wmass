#include "wmass_analysis/EvtSelector.hpp"

#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Collection.hpp"

#include "wmass_util/CAFEMObj.hpp"
#include "wmass_util/TriggerManager.hpp"
#include "wmass_util/hist_files.hpp"
#include "wmass_analysis/histograms.hpp"
#include "tmb_tree/TMBMCevtInfo.hpp"
#include <TFile.h>
#include <iostream>
#include <TROOT.h>

using namespace std;
using namespace cafe;

EvtSelector::EvtSelector(const char *name) : Processor(name) {
  Config config(name);

  // debug Level
  _debugLevel = config.get("debugLevel", 0);

  // MC study
  _MCStudy = config.get("MCStudy", false);

  _doZBevent = config.get("doZBevent", false);
  if (_MCStudy && _doZBevent) {
    _ZBfile = config.get("ZBfilename", "");
    _ZBtree = config.get("ZBtreename", "binary_tuple");
    _ZBevent = new CAFZBevent(_ZBfile.Data(), _ZBtree.Data());
    if (!_ZBevent->isOpen()) {
      std::cout << "EvtSelector says ZBevent couldn't get ZB tree. I will not process the ZB information." << std::endl;
      _doZBevent = false;
    }
  }

  // initialize evnet counters
  _events = 0;
  _events_not_in_triggerlists = 0;
  _duplicated_events = 0;

  // remove duplicated events
  _Remove_Duplicated_Events = config.get("Remove_Duplicated_Events", false);

  _global_vars.add("_runno");
  _global_vars.add("_evtno");
  _global_vars.add("_ticknum");
  _global_vars.add("_solpol");
  _global_vars.add("_instlum");
		  
  _MCLumiReweight = config.get("MCLumiReweight", false);
  if (_MCLumiReweight){	
     gROOT->ProcessLine(TString(".x MC_Data_LumiRatio.C"));
     _lumiRatio = (TH1F *)gROOT->FindObject("InstLumiRatio");
  }

  _Use_v16_E1SHT27_Only = config.get("Use_v16_E1SHT27_Only", false);
  _Use_v16_E1SHT25_Only = config.get("Use_v16_E1SHT25_Only", false);
  
}

EvtSelector::~EvtSelector() { }

// process event
bool EvtSelector::processEvent(Event& event) {
  
  if(_events%20000 == 0) cout<<"Processing event "<<_events<<endl;  
  _events ++;
  
  // get run number, event number and solenoid polarity information
  int runNo = event.getGlobal(_global_vars)->runno();
  int evtNo = event.getGlobal(_global_vars)->evtno();
  int solpol = event.getGlobal(_global_vars)->solpol();
  int tickNo = event.getGlobal(_global_vars)->ticknum();

  // get luminosity information for data and MC separately
  double instlumi = 0., mc_data_lumi_ratio = 0.; 
  if(_MCStudy) {
    runNo = event.getMCEventInfo()->overlayrun();
    evtNo = event.getMCEventInfo()->overlayevtid();
    tickNo = event.getMCEventInfo()->overlaytick();
    
    instlumi = event.getMCEventInfo()->overlay_instlum();
    if (_MCLumiReweight){
    	Int_t bin = _lumiRatio->FindBin(instlumi);
    	mc_data_lumi_ratio = _lumiRatio->GetBinContent(bin);
    }
    else{
	 mc_data_lumi_ratio = 1.;
    }
  } else {
    mc_data_lumi_ratio = 1.;
    instlumi = event.getGlobal(_global_vars)->instlum();
  }

  if(_debugLevel>=5) {
    cout << "-------------------------------" << endl;
    cout << "run="<<runNo << ",event=" << evtNo << endl;
  }

  // remove duplicated events, this one only works if you run ONLY ONE JOB
  // and will not work for MULTIPLE JOBS
  if(_Remove_Duplicated_Events) {
    if(_event_set.find(make_pair(runNo, evtNo)) == _event_set.end())
      _event_set.insert(make_pair(runNo, evtNo));
    else {
      _duplicated_events++;
      cout << "found duplicate event: " << runNo << " " << evtNo << " will remove it"<<endl;
      return false;
    }
  }//remove duplicated events



  // find which trigger list is used
  // triglist: 0 for v8-10, 1 for v11, 2 for v12, 3 for v13, 4 for v14
  int triglist_flag;
  // for MC studies, triglist_flag does not matter since we will not measure trigger efficiency
  if(_MCStudy) triglist_flag = 1;

  else if( (runNo>=161973) && (runNo<=174807) ) triglist_flag = 0;
  else if ( (runNo>=174896 && runNo<=177312) || 
            (runNo>=177315 && runNo<=177684) ||
	    (runNo>=177744 && runNo<=178096) ||
	    (runNo>=178104 && runNo<=178721) ) 
    triglist_flag = 1;
  else if ( (runNo>=178098 && runNo<=178103) ||
            (runNo>=177689 && runNo<=177690) ||
            (runNo==177314) ||
            (runNo>=178722 && runNo<=194597))         
    triglist_flag = 2;
  else if ( (runNo>=194598 && runNo<=207216) )
    triglist_flag = 3; 
  else if ( runNo>=207218 and runNo <= 215670  ) triglist_flag = 4;
  else if ((runNo>=221989 and runNo <= 240438) ||  
	   (runNo>=240576 and runNo <= 240743))
    triglist_flag = 5;
  else if ( (runNo>= 240762 ) ||
	    (runNo>=240476 and runNo <= 240566)){
    TriggerManager *trigmanager = TriggerManager::get_instance();
    trigmanager->TrigsUsed(event);
    triglist_flag = 6;
    if (!(trigmanager->Uses_Trig("E1_SHT25"))){
      triglist_flag = 7;
      if  (!(trigmanager->Uses_Trig("E1_SHT27"))){
	std::cerr << "Logic Error " << std::endl;
	abort();
      }
    }
  }
  else triglist_flag = -1;
  if(triglist_flag == -1) {   // not in any trigger list
    _events_not_in_triggerlists ++;
    return false;  
  } else {                    // save some information into event for future use
    if (_Use_v16_E1SHT27_Only && !(triglist_flag ==7)  ){
      _events_not_in_triggerlists ++;
      return false;
      
    }
    if (_Use_v16_E1SHT25_Only && !(triglist_flag==6)  ){
      _events_not_in_triggerlists ++;
      return false;
    }
    event.put("run number", runNo);
    event.put("event number", evtNo);
    event.put("tick number", tickNo);
    event.put("triglist flag", triglist_flag);
    event.put("solenoid polarity", solpol);    
    event.put("InstLumi", instlumi);    
    event.put("MC Data LumiRatio", mc_data_lumi_ratio);

    // Gets the ZB information, if requested
    if (_MCStudy && _doZBevent) {
      _ZBevent->getZBevent(runNo, evtNo);
      event.put("ZBevent nPVS", _ZBevent->getnPVS());
      event.put("ZBevent HKset", _ZBevent->getHKset());
      event.put("ZBevent HKmetx", _ZBevent->getHKmetx());
      event.put("ZBevent HKmety", _ZBevent->getHKmety());
      event.put("ZBevent TickNum", _ZBevent->getTickNum());
      event.put("ZBevent TimeLastL1Accept", _ZBevent->getTimeLastL1Accept());
    }

    return true;
  }
  
}

void EvtSelector::begin() {}

void EvtSelector::finish() {

  TFile *file = histfiles::initializeTFile( this );
  if(file==NULL) return;

  string directory_name("General_Hist");
  file->mkdir(directory_name.c_str());
  _histos.save(file, directory_name);
  
  if(_events_not_in_triggerlists>0) 
    cout<<"WARNING: # of events thrown aways by EvtSelector since they are not in trigger lists is "
	<<_events_not_in_triggerlists<<endl;  
  if(_duplicated_events>0)
    cout<<"WARNING: # of duplicated events removed is "<<_duplicated_events<<endl;

  cout<<"Events processed by EvtSelector "<<_events<<endl;  
  
  file -> Close();
}

ClassImp(EvtSelector)
