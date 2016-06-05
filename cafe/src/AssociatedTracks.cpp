
#include "cafe/AssociatedTracks.hpp"
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"

#include <iostream>
#include <stdexcept>

namespace cafe {

    AssociatedTracks::AssociatedTracks(const char *name)
	: cafe::Processor(name)
    {
	Config config(name);
    
	_trackBranch   = config.get("TrackBranch","Track");
	_trackListName = config.get("TrackList", "KeepTracks");
	_branches      = config.getVString("Branches", " ,");

	out() << "AssociatedTracks[" << name << "] Track Branch = " << _trackBranch << std::endl;
	out() << "AssociatedTracks[" << name << "] Track List   = " << _trackListName << std::endl;
	out() << "AssociatedTracks[" << name << "] Branches     = ";
	for(std::vector<std::string>::const_iterator it = _branches.begin();
	    it != _branches.end();
	    ++it) {
	    out() << *it << " ";
	}
	out() << std::endl;
    }

    bool AssociatedTracks::processEvent(Event& event)
    {
	using namespace std;

	// result
	TObjArray *keepTracks = new TObjArray;
	
	Collection<TMBTrack> tracks(event.getCollection<TMBTrack>(_trackBranch));

	for(Collection<TMBTrack>::iterator it = tracks.begin();
	    it != tracks.end();
	    ++it) {
	    const TMBTrack& track = *it;

	    for(vector<string>::iterator br = _branches.begin();
		br != _branches.end();
		++br) {
		
		if(const TClonesArray *array = event.getClonesArray((*br).c_str())) {
		    if(array->GetClass() == TMBMuon::Class()) {
			// Muons
			Collection<TMBMuon> muons(event.getCollection<TMBMuon>(*br));

			for(size_t i = 0; i < muons.size(); i++) {
			    if(const TMBTrack *p = muons[i].GetChargedTrack()) {
				if(p == &track) {
				    if(keepTracks->FindObject(p) == 0) {
					keepTracks->AddLast((TObject *)p);
				    }
				}
			    }
			}
		    } else if(array->GetClass() == TMBEMCluster::Class()) {
			// EM objects
			Collection<TMBEMCluster> ems(event.getEM(*br));
			
			for(size_t i = 0; i < ems.size(); i++) {
			    if(const TMBTrack *p = ems[i].GetChargedTrack()) {
				if(p == &track) {
				    if(keepTracks->FindObject(p) == 0) {
					keepTracks->AddLast((TObject *)p);
				    }
				}
			    }
			}
		    } else if(array->GetClass() == TMBJet::Class()) {

			// Jets
			Collection<TMBJet> jets(event.getJets(*br));
			for(size_t i = 0; i < jets.size(); i++) {
			    
			    for(Int_t j = 0; j < jets[i].Ntr(); j++) {
				if(const TMBTrack * p = jets[i].GetChargedTrack(j)) {
				    if(p == &track) {
					if(keepTracks->FindObject(p) == 0) {
					    keepTracks->AddLast((TObject *)p);
					}
				    }
				}
			    }	
			}
		    } else if (array->GetClass() == TMBTau::Class()) {
			// Taus
			Collection<TMBTau> taus(event.getCollection<TMBTau>(*br));
			for(size_t i = 0; i < taus.size(); i++) {
			    
			    for(Int_t j = 0; j < taus[i].ntrk(); j++) {
				if(const TMBTrack *p = taus[i].GetChargedTrack(j)) {
				    if(p == &track) {
					if(keepTracks->FindObject(p) == 0) {
					    keepTracks->AddLast((TObject *)p);
					}
				    }
				}
			    }
			}
		    } else {
			throw std::runtime_error(string("AssociatedTracks: cannot handle object type: ") + array->GetClass()->GetName());
		    }
		} else {
			throw std::runtime_error("AssociatedTracks: no such branch: " + *br);
		}
		
	    }
	}

	event.put(_trackListName, keepTracks);
    
	return true;
    }
}

ClassImp(cafe::AssociatedTracks);


