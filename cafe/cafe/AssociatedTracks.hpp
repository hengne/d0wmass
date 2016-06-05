#ifndef CAFE_ASSOCIATEDTRACKS_HPP_
#define CAFE_ASSOCIATEDTRACKS_HPP_

#include "cafe/Processor.hpp"

#include <string>

namespace cafe {
    
    /**
     * Find associated tracks for a list of user defined branches.
     *
     * An example on how to use the RemoveObjects processor. This
     * class will find all associated tracks in the given list
     * of branches and store them in a format suitable for
     * the 'RemoveObject' processor.
     *
     * The following example will create a small event where only
     * tracks associated with EMscone, Muon or JCCB branches are stored.
     *
     * cafe.Run: AssociatedTracks(tracks) RemoveObjects(delete) Write(out)
     *
     * tracks.Branches:  EMscone Muon JCCB
     * tracks.TrackList: KeepTracks
     *
     * delete.Branch: Track
     * delete.Keep:   KeepTracks
     *
     * out.File:  new-%f
     * out.Enable: EMscone Muon JCCB Track
     *
     * Configuration options:
     *
     *  - .TrackBranch: branchName        [ default: "Track" ] 
     *  - .Branches:    listOfBranchNames [ default: empty ]
     *  - .TrackList:   nameOfList        [ default: "KeepTracks" ]
     */

    class AssociatedTracks : public cafe::Processor {
    public:
	AssociatedTracks(const char *name);
	bool processEvent(cafe::Event& event);
    private:
	/// Name of track branch (defaults to 'Track').
	std::string              _trackBranch;
	/// Name of TObjArray stored in Event (default 'KeepTracks')
	std::string              _trackListName;
	/// List of branch names to consider.
	/// Objects have to be subclasses of TMBMuon, TMBEMCluster, TMBJet, TMBTau.
	std::vector<std::string> _branches;
    public:
	ClassDef(AssociatedTracks,0);
    };
}

#endif // CAFE_ASSOCIATEDTRACKS_HPP_

