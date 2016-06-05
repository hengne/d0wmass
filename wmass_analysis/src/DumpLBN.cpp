#include "wmass_analysis/DumpLBN.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

using namespace std;
using namespace cafe;

DumpLBN::DumpLBN(const char *name)
    : cafe::Processor(name)
{
  Config config(name);
  _prefix=config.get("Prefix","JANOVL");
}

bool DumpLBN::processEvent(cafe::Event& event)
{
  if( event.isMC() )
  {
    Long_t OVLrun=event.getMCEventInfo()->overlayrun();
    Long_t OVLlbn=event.getMCEventInfo()->overlaylumblk();
    
    if( _run_lbn_map.find(OVLlbn) == _run_lbn_map.end() ){ // Make sure not already mapped
      _run_lbn_map[OVLlbn] = OVLrun;
    }
    if( _lbn_map.find(OVLlbn) == _lbn_map.end() ){ // Already have lbn
      _lbn_map[OVLlbn] = 1;
    }
    else {
      _lbn_map[OVLlbn] += 1;
    }
    
    _lbn_list.insert( OVLlbn );
  }
  else 
  {
    Long_t OVLrun = event.getGlobal()->runno();
    Long_t OVLlbn = event.getGlobal()->lumblk();

    if( _run_lbn_map.find(OVLlbn) == _run_lbn_map.end() ){ // Make sure not already mapped
      _run_lbn_map[OVLlbn] = OVLrun;
    }
    if( _lbn_map.find(OVLlbn) == _lbn_map.end() ){ // Already have lbn
      _lbn_map[OVLlbn] = 0;
    }
    else {
      _lbn_map[OVLlbn] += 1;
    }
    
    _lbn_list.insert( OVLlbn );
  }
  
  return true;
}

void DumpLBN::begin() {
}

void DumpLBN::finish() {
  std::set<int>::const_iterator it;
  for( it = _lbn_list.begin() ; it != _lbn_list.end() ; it++ )
  {
    int lbn = *it;
    cout << " run " << _run_lbn_map[lbn] << " lbn " << lbn << " N " << _lbn_map[lbn] << endl;
  } 
}

ClassImp(DumpLBN);

