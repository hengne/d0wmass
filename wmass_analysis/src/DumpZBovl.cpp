#include "wmass_analysis/DumpZBovl.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

using namespace std;
using namespace cafe;

DumpZBovl::DumpZBovl(const char *name)
    : cafe::Processor(name)
{
  Config config(name);
  _prefix=config.get("Prefix","JANOVL");
}

bool DumpZBovl::processEvent(cafe::Event& event)
{
  Long_t OVLrun=event.getMCEventInfo()->overlayrun();
  Long_t OVLevt=event.getMCEventInfo()->overlayevtid();
  Float_t OVLlumi=event.getMCEventInfo()->overlay_instlum();
  cout<<_prefix<<"  "<<OVLrun<<" "<<OVLevt<<"  "<<OVLlumi<<endl;
  return true;
}

void DumpZBovl::begin() {
}

void DumpZBovl::finish() {
}

ClassImp(DumpZBovl);

