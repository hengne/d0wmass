
#include "cafe/SelectUserObjects.hpp"
#include "cafe/Config.hpp"

#include "tmb_tree/TMBMuon.hpp"
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBJet.hpp"
#include "tmb_tree/TMBTrack.hpp"
#include "tmb_tree/TMBIsoTrack.hpp"
#include "tmb_tree/TMBVertex.hpp"
#include "tmb_tree/TMBPrimaryVertex.hpp"
#include "tmb_tree/TMBTrackCal.hpp"
#include "tmb_tree/TMBTrackCalJet.hpp"

#include "tmb_tree/TMBCps.hpp"
#include "tmb_tree/TMBFps.hpp"

#include "tmb_tree/TMBMCvtx.hpp"
#include "tmb_tree/TMBMCpart.hpp"


namespace cafe {}

ClassImp(cafe::SelectUserObjects<TMBHistory>);
ClassImp(cafe::SelectUserObjects<TMBTrigger>);

ClassImp(cafe::SelectUserObjects<TMBLorentzVector>);
ClassImp(cafe::SelectUserObjects<TMBMuon>);
ClassImp(cafe::SelectUserObjects<TMBEMCluster>);
ClassImp(cafe::SelectUserObjects<TMBJet>);
ClassImp(cafe::SelectUserObjects<TMBTrack>);
ClassImp(cafe::SelectUserObjects<TMBIsoTrack>);
ClassImp(cafe::SelectUserObjects<TMBVertex>);
ClassImp(cafe::SelectUserObjects<TMBPrimaryVertex>);
ClassImp(cafe::SelectUserObjects<TMBTrackCal>);
ClassImp(cafe::SelectUserObjects<TMBTrackCalJet>);
ClassImp(cafe::SelectUserObjects<TMBTau>);

ClassImp(cafe::SelectUserObjects<TMBCps>);
ClassImp(cafe::SelectUserObjects<TMBFps>);

ClassImp(cafe::SelectUserObjects<TMBMCvtx>);
ClassImp(cafe::SelectUserObjects<TMBMCpart>);

ClassImp(cafe::SelectUserObjects<TMBL1CalTile>);
ClassImp(cafe::SelectUserObjects<TMBL1CalTower>);
ClassImp(cafe::SelectUserObjects<TMBL1Track>);
ClassImp(cafe::SelectUserObjects<TMBL1toL2CTT>);
ClassImp(cafe::SelectUserObjects<TMBL2Base>);
ClassImp(cafe::SelectUserObjects<TMBL2CPS>);
ClassImp(cafe::SelectUserObjects<TMBL2EM>);
ClassImp(cafe::SelectUserObjects<TMBL2Muon>);
ClassImp(cafe::SelectUserObjects<TMBL2Jet>);
ClassImp(cafe::SelectUserObjects<TMBL2Track>);
ClassImp(cafe::SelectUserObjects<TMBL2GblJet>);
ClassImp(cafe::SelectUserObjects<TMBL2GblMuon>);
ClassImp(cafe::SelectUserObjects<TMBL2GblEM>);
ClassImp(cafe::SelectUserObjects<TMBL2GblTrack>);
ClassImp(cafe::SelectUserObjects<TMBL2GblInvMass>);
ClassImp(cafe::SelectUserObjects<TMBL2GblMJt>);
ClassImp(cafe::SelectUserObjects<TMBL2GblHt>);

ClassImp(cafe::SelectUserObjects<TMBL3Base>);
ClassImp(cafe::SelectUserObjects<TMBL3BTagIP>);
ClassImp(cafe::SelectUserObjects<TMBL3CFTVtx>);
ClassImp(cafe::SelectUserObjects<TMBL3Ele>);
ClassImp(cafe::SelectUserObjects<TMBL3IPTrack>);
ClassImp(cafe::SelectUserObjects<TMBL3Isolation>);
ClassImp(cafe::SelectUserObjects<TMBL3Jet>);
ClassImp(cafe::SelectUserObjects<TMBL3Muon>);
ClassImp(cafe::SelectUserObjects<TMBL3Photon>);
ClassImp(cafe::SelectUserObjects<TMBL3Tau>);
ClassImp(cafe::SelectUserObjects<TMBL3Track>);
ClassImp(cafe::SelectUserObjects<TMBL3MEt>);

ClassImp(cafe::SelectUserObjects<TMBLum>);
ClassImp(cafe::SelectUserObjects<TMBLumV>);
