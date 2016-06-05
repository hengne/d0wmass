#ifndef EVENT_HPP__
#define EVENT_HPP__

#include "cafe/EventBase.hpp"
#include "cafe/DataEpochs.hpp"

// Global 
#include "tmb_tree/TMBGlobal.hpp"
#include "tmb_tree/TMBHistory.hpp"
#include "tmb_tree/TMBTrigger.hpp"
#include "tmb_tree/TMBEventFlags.hpp"

// Reco
#include "tmb_tree/TMBMuon.hpp"
#include "tmb_tree/TMBEMCluster.hpp"
#include "tmb_tree/TMBJet.hpp"
#include "tmb_tree/TMBMet.hpp"
#include "tmb_tree/TMBParticleJet.hpp"
#include "tmb_tree/TMBMetEx.hpp"
#include "tmb_tree/TMBTrack.hpp"
#include "tmb_tree/TMBTau.hpp"
#include "tmb_tree/TMBIsoTrack.hpp"
#include "tmb_tree/TMBPrimaryVertex.hpp"
#include "tmb_tree/TMBLeBob.hpp"
#include "tmb_tree/TMBTrackCal.hpp"
#include "tmb_tree/TMBTrackCalJet.hpp"

#include "tmb_tree/TMBCps.hpp"
#include "tmb_tree/TMBFps.hpp"

// B-Tagging
#include "tmb_tree/TMBBTag.hpp"
#include "tmb_tree/TMBBTagSLT.hpp"
#include "tmb_tree/TMBBTagJLIP.hpp"
#include "tmb_tree/TMBBTagSVT.hpp"
#include "tmb_tree/TMBBTagNN.hpp"
#include "tmb_tree/TMBBTagSLTNN.hpp"
#include "tmb_tree/TMBBTagMVA.hpp"

// Compact
#include "tmb_tree/TMBTrigBits.hpp"
#include "tmb_tree/TMBHiPt.hpp"

// MC
#include "tmb_tree/TMBMCpart.hpp"
#include "tmb_tree/TMBMCvtx.hpp"
#include "tmb_tree/TMBMCevtInfo.hpp"

// Trigger

// L1
#include "tmb_tree/TMBL1AndOr.hpp"
#include "tmb_tree/TMBL1Names.hpp"
#include "tmb_tree/TMBL2Names.hpp"
#include "tmb_tree/TMBL1Cal.hpp"
#include "tmb_tree/TMBL1CalTile.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL1CTT.hpp"
#include "tmb_tree/TMBL1Muon.hpp"
#include "tmb_tree/TMBL1Track.hpp"
#include "tmb_tree/TMBL1toL2CTT.hpp"
#include "tmb_tree/TMBL1L2Masks.hpp"

// L2 Preprocessor objects
#include "tmb_tree/TMBL2CPS.hpp"
#include "tmb_tree/TMBL2EM.hpp"
#include "tmb_tree/TMBL2FPS.hpp"
#include "tmb_tree/TMBL2Muon.hpp"
#include "tmb_tree/TMBL2Track.hpp"
#include "tmb_tree/TMBL2Jet.hpp"
#include "tmb_tree/TMBL2MEt.hpp"

// L2 Global objects
#include "tmb_tree/TMBL2GblEM.hpp"
#include "tmb_tree/TMBL2GblHt.hpp"
#include "tmb_tree/TMBL2GblInvMass.hpp"
#include "tmb_tree/TMBL2GblJet.hpp"
#include "tmb_tree/TMBL2GblMEt.hpp"
#include "tmb_tree/TMBL2GblMJt.hpp"
#include "tmb_tree/TMBL2GblMuon.hpp"
#include "tmb_tree/TMBL2GblSphericity.hpp"
#include "tmb_tree/TMBL2GblSTTBtag.hpp"
#include "tmb_tree/TMBL2GblTau.hpp"
#include "tmb_tree/TMBL2GblTrack.hpp"
#include "tmb_tree/TMBL2GblTransMass.hpp"
#include "tmb_tree/TMBL2Script.hpp"

// L3
#include "tmb_tree/TMBL3BTagIP.hpp"
#include "tmb_tree/TMBL3CFTVtx.hpp"
#include "tmb_tree/TMBL3Ele.hpp"
#include "tmb_tree/TMBL3IPTrack.hpp"
#include "tmb_tree/TMBL3Isolation.hpp"
#include "tmb_tree/TMBL3Jet.hpp"
#include "tmb_tree/TMBL3MEt.hpp"
#include "tmb_tree/TMBL3Muon.hpp"
#include "tmb_tree/TMBL3Photon.hpp"
#include "tmb_tree/TMBL3Tau.hpp"
#include "tmb_tree/TMBL3Track.hpp"

// Detector
#include "tmb_tree/TMBCalNada.hpp"
#include "tmb_tree/TMBCalT42.hpp"
#include "tmb_tree/TMBCellContainer.hpp"
#include "tmb_tree/TMBCps.hpp"
#include "tmb_tree/TMBCpsDigi.hpp"
#include "tmb_tree/TMBFps.hpp"
#include "tmb_tree/TMBFpsData.hpp"
#include "tmb_tree/TMBFpd.hpp"
#include "tmb_tree/TMBFPDTrack.hpp"
#include "tmb_tree/TMBTdc.hpp" 



#include "tmb_tree/TMBLum.hpp"
#include "tmb_tree/TMBLumV.hpp"

// L1Cal IIb
#include "tmb_tree/TMBL1Cal2bEM.hpp"
#include "tmb_tree/TMBL1Cal2bTau.hpp"
#include "tmb_tree/TMBL1Cal2bJet.hpp"
#include "tmb_tree/TMBL1Cal2bMET.hpp"
#include "tmb_tree/TMBL1Cal2bSeed.hpp"
#include "tmb_tree/TMBL1Cal2bGAB.hpp"

// Weights
#include "tmb_tree/TMBHiPtWeight.hpp"
#include "cafe/EventWeight.hpp"

namespace cafe {

    /**
     * The D0 specific Event class. 
     *
     * Contains specialized methods to access all common
     * D0 physics objects.
     *
     * \ingroup cafe
     */

    class Event : public EventBase {
      DataEpochs _epochs ;
      
    public:
        Event();

	/// @name Global
	//@{

	/// Get data type.

	bool isMC() const;
        
        /// retun mc version tag txx.yy.zz or pxx.yy.zz. Return empty string for data ;
        std::string mcVersion() const ;

        bool isRun2b() const;
        bool isRun2a() const {return !isRun2b();}

        bool isRun2b1() const;
        bool isRun2b2() const;
        bool isRun2b3() const;
        bool isRun2b4() const;

        /// Return true if run number is inside data epocs limits. 
        /// The name of epochs should match one in cafe::DataEpochs.
        /// For MC  throw an exeption
        bool isEpoch(const std::string& epoch) const ;

        /// Get global event information (like run number, event number, ...)
        const TMBGlobal *getGlobal(const Variables& vars = cafe::detail::empty) const 
        { 
            return get<TMBGlobal>("Global", vars); 
        }

	/// Get history information.
        const Collection<TMBHistory> getHistory(const Variables& vars = cafe::detail::empty) const 
        { 
            return getCollection<TMBHistory>("History"); 
        }

	/// Get event flags.
	const TMBEventFlags *getEventFlags(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBEventFlags>("EventFlags", vars);
	}

	//@}
        

	/// @name Reco Objects.

	//@{ 

	/// Get all muons.
        Collection<TMBMuon> getMuons(const Variables& vars = cafe::detail::empty)    const 
        { 
            return getCollection<TMBMuon>("Muon", vars); 
        }

	/// Get all EM clusters from the given branch.
	/// Default branches stored are EMscone and EMcnn.
        Collection<TMBEMCluster> getEM(const std::string& branchName, const Variables& vars = cafe::detail::empty)    const 
        { 
            return getCollection<TMBEMCluster>(branchName, vars); 
        }

	/// Get simple cone EM clusters.
        Collection<TMBEMCluster> getEMscone(const Variables& vars = cafe::detail::empty) const
        { 
            return getEM("EMscone", vars); 
        }

	/// Get Cell NN EM clusters.
        Collection<TMBEMCluster> getEMcnn(const Variables& vars = cafe::detail::empty) const
        { 
            return getEM("EMcnn", vars);
        }

	/// Get all jets from given branch.
	Collection<TMBJet> getJets(const std::string &branchName, const Variables& vars = cafe::detail::empty) const
	{
            return getCollection<TMBJet>(branchName, vars);
	}

	/// Get JCCA jets.
	Collection<TMBJet> getJCCA(const Variables& vars = cafe::detail::empty) const
	{
            return getJets("JCCA", vars);
	}

	/// Get JCCB jets.
	Collection<TMBJet> getJCCB(const Variables& vars = cafe::detail::empty) const
	{
            return getJets("JCCB", vars);
	}

      /// Get all LeBobs
        Collection<TMBLeBob> getLeBob(const Variables& vars = cafe::detail::empty)   const 
        { 
            return getCollection<TMBLeBob>("LeBob", vars); 
        }
	/// Get LeBob from given branch.
	const TMBLeBob* getTMBLeBob(const std::string &branchName, const Variables& vars = cafe::detail::empty) const
	{
            Collection<TMBLeBob> lebobs=getLeBob(vars);
	    int nsize=lebobs.size();
	    for(int i=0; i<nsize; ++i){
	      if(std::string(lebobs[i].algoname())==branchName) return &lebobs[i];
	    }
	    return 0;
	}
	/// Get JCCA LeBob.
	const TMBLeBob* getJCCALeBob(const Variables& vars = cafe::detail::empty) const
	{
            return getTMBLeBob("JCCA", vars);
	}

	/// Get JCCB jets.
	const TMBLeBob* getJCCBLeBob(const Variables& vars = cafe::detail::empty) const
	{
            return getTMBLeBob("JCCB", vars);
	}

	/// Get all particle jets from given branch.
	Collection<TMBParticleJet> 
	getParticleJets(const std::string &branchName, const Variables& vars = cafe::detail::empty) const
	{
            return getCollection<TMBParticleJet>(branchName, vars);
	}
	
	/// Get JCCA particle jets.
	Collection<TMBParticleJet> getParticlesJCCA(const Variables& vars = cafe::detail::empty) const
	{
            return getParticleJets("particlesJCCA", vars);
	}
	
	/// Get JCCB particle jets.
	Collection<TMBParticleJet> getParticlesJCCB(const Variables& vars = cafe::detail::empty) const
	{
            return getParticleJets("particlesJCCB", vars);
	}
	
	/// Get all tracks.
        Collection<TMBTrack> getTracks(const Variables& vars = cafe::detail::empty)   const 
        { 
            return getCollection<TMBTrack>("Track", vars); 
        }

	/// Get all isolated tracks.
        Collection<TMBIsoTrack> getIsoTracks(const Variables& vars = cafe::detail::empty)   const 
        { 
            return getCollection<TMBIsoTrack>("IsoTrack", vars); 
        }

	/// Get all taus.
	Collection<TMBTau> getTaus(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBTau>("Tau", vars);
	}

	/// Get all primary vertices.
        Collection<TMBPrimaryVertex> getPrimaryVertices(const Variables& vars = cafe::detail::empty) const 
        { 
            return getCollection<TMBPrimaryVertex>("PrimaryVertex", vars); 
        }


	/// Get all primayr vertices of a given type.
        Collection<TMBPrimaryVertex> getPrimaryVertices(const std::string& type, const Variables& vars = cafe::detail::empty) const 
        { 
            return getCollection<TMBPrimaryVertex>("PrimaryVertex_" + type, vars); 
        }
	

	/// Get TrackCal .
	Collection<TMBTrackCal> getTrackCals(const Variables& vars = cafe::detail::empty) const
	{
            return  getCollection<TMBTrackCal>("TrackCal", vars);
	}

	/// Get TrackCalJets for 0.7 cone jets.
	Collection<TMBTrackCalJet> getTrackCalJCCA(const Variables& vars = cafe::detail::empty) const
	{
            return  getCollection<TMBTrackCalJet>("TrackCalJet_JCCA", vars);
	}

	/// Get TrackCalJets  for 0.5 cone jets.
	Collection<TMBTrackCalJet> getTrackCalJCCB(const Variables& vars = cafe::detail::empty) const
	{
            return  getCollection<TMBTrackCalJet>("TrackCalJet_JCCB", vars);
	}

	/// Get missing ET object.
        const TMBMet  *getMet(const Variables& vars = cafe::detail::empty) const     
        { 
            return  get<TMBMet>("Met", vars); 
        }

	/// Get expert missing ET object.
        const TMBMetEx  *getMetEx(const Variables& vars = cafe::detail::empty) const     
        { 
            return  get<TMBMetEx>("MetEx", vars); 
        }

	/// Get CPS information
	Collection<TMBCps> getCPS(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBCps>("Cps", vars);
        }

        /// Get FPS information
        Collection<TMBFps> getFPS(const Variables& vars = cafe::detail::empty) const
        {
            return getCollection<TMBFps>("Fps", vars);
        }

        /// Get FPD information
        Collection<TMBFpd> getFPD(const Variables& vars = cafe::detail::empty) const
        {
            return getCollection<TMBFpd>("Fpd", vars);
        }

	//@}

	/// @name B-ID
	///
	/// - jetAlgo should be one of corrJCCA or corrJCCB
	/// - qual should be one of LOOSE, MEDIUM, TIGHT

	//@{


	Collection<TMBBTag> getCSIP(const std::string& jetAlgo,
				     const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTag>("BTag_" + jetAlgo + 
					  "_CSIP_" + qual, vars);
	}
				    

	Collection<TMBBTagSLT> getSLT(const std::string& jetAlgo,
				      const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTagSLT>("BTag_" + jetAlgo + 
					  "_SLT_" + qual, vars);
	}
				    

	Collection<TMBBTagJLIP> getJLIP(const std::string& jetAlgo,
					const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTagJLIP>("BTag_" + jetAlgo + 
					      "_JLIP_" + qual, vars);
	}

	Collection<TMBBTagSVT> getSVT(const std::string& jetAlgo,
				      const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTagSVT>("BTag_" + jetAlgo + 
					     "_SVT_" + qual, vars);
	}

        Collection<TMBBTagNN> getNN(const std::string& jetAlgo,
				      const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTagNN>("BTag_" + jetAlgo + 
					     "_NN_" + qual, vars);
	}

        Collection<TMBBTagSLTNN> getSLTNN(const std::string& jetAlgo,
					  const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTagSLTNN>("BTag_" + jetAlgo + 
					     "_SLTNN_" + qual, vars);
	}

        Collection<TMBBTagMVA> getMVA(const std::string& jetAlgo,
				      const std::string& qual, const Variables& vars = cafe::detail::empty)
	{
	    return getCollection<TMBBTagMVA>("BTag_" + jetAlgo + 
					     "_MVA_" + qual, vars);
	}

	//@}

	/// @name Monte Carlo
	//@{

	/// Get MC Event information.
	const TMBMCevtInfo *getMCEventInfo(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBMCevtInfo>("MCevtInfo", vars);
	}

	/// Get all MC vertices.
	Collection<TMBMCvtx> getMCVertices(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBMCvtx> ("MCvtx", vars);
	}
	
	/// Get all MC particles.
	Collection<TMBMCpart> getMCParticles(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBMCpart> ("MCpart", vars);
	}

	//@}

	/// @name Trigger
	
	//@{

	/// Get all triggers.
	Collection<TMBTrigger> getTriggers(const Variables& vars = cafe::detail::empty) const
	{
            return  getCollection<TMBTrigger>("Trigger", vars);
	}


	/// Get Trigger Bits
	const TMBTrigBits *getTrigBits(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBTrigBits>("TrigBits", vars);
	}

	/// Get L1 AndOr terms.
	const TMBL1AndOr *getL1AndOr(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1AndOr>("L1AndOr", vars);
	}

	/// Get L1 terms.
	const TMBL1Names *getL1Names(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1Names>("L1Names", vars);
	}
	
	/// Get L2 terms.
	const TMBL2Names *getL2Names(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL2Names>("L2Names", vars);
	}

	/// Get L1 Calorimeter information.
	const TMBL1Cal *getL1Cal(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1Cal>("L1Cal", vars);
	}


	/// Get L1Cal Tiles.
	Collection<TMBL1CalTile> getL1CalTiles(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL1CalTile> ("L1CalTiles", vars);
	}

	/// Get L1Cal Towers.
	Collection<TMBL1CalTower> getL1CalTotalTowers(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL1CalTower> ("L1CalTotalTowers", vars);
	}

        /// Get L1Cal Towers.
        Collection<TMBL1CalTower> getL1CalEMTowers(const Variables& vars = cafe::detail::empty) const
        {
            return getCollection<TMBL1CalTower> ("L1CalEMTowers", vars);
        }

	/// Get L1 Muon information.
	const TMBL1Muon *getL1Muon(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1Muon>("L1Muon", vars);
	}

	/// Get L1 CTT.
	const TMBL1CTT *getL1CTT(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1CTT>("L1CTT", vars);
	}

	/// Get L1toL2CTT.
	Collection<TMBL1toL2CTT> getL1toL2CTT(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL1toL2CTT>("L1toL2CTT", vars);
	}

	/// Get L1 Tracks.
	Collection<TMBL1Track> getL1Tracks(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL1Track> ("L1Track", vars);
	}

	/// Get L1 and L2 bitmasks
	const TMBL1L2Masks *getL1L2Masks(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1L2Masks>("L1L2Masks", vars);
	}

	/// Get L2 CPS.
	Collection<TMBL2CPS> getL2CPSs(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2CPS> ("L2CPS", vars);
	}

	/// Get L2 Preprocessor EM.
	Collection<TMBL2EM> getL2EMs(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2EM> ("L2EM", vars);
	}

	/// Get L2 Preprocessor Muon.
	Collection<TMBL2Muon> getL2Muons(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2Muon> ("L2Muon", vars);
	}

	/// Get L2 Preprocessor Jet.
	Collection<TMBL2Jet> getL2Jets(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2Jet> ("L2Jet", vars);
	}

	/// Get L2 STTPT Tracks.
	Collection<TMBL2Track> getL2STTPT(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2Track> ("STTPT", vars);
	}

	/// Get L2 STTIP Tracks.
	Collection<TMBL2Track> getL2STTIP(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2Track> ("STTIP", vars);
	}

	/// Get L2 CTT Tracks.
	Collection<TMBL2Track> getL2CTT(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2Track> ("CTT", vars);
	}

	/// Get L2 GblJet.
	Collection<TMBL2GblJet> getL2GblJets(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblJet> ("L2GblJet", vars);
	}

	/// Get L2 GblEM.
	Collection<TMBL2GblEM> getL2GblEMs(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblEM> ("L2GblEM", vars);
	}

	/// Get L2 GblMuon.
	Collection<TMBL2GblMuon> getL2GblMuons(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblMuon> ("L2GblMuon", vars);
	}

	/// Get L2 GblTrack.
	Collection<TMBL2GblTrack> getL2GblTracks(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblTrack> ("L2GblTrack", vars);
	}

	/// Get L2 GblInvMass.
	Collection<TMBL2GblInvMass> getL2GblInvMass(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblInvMass> ("L2GblInvMass", vars);
	}

	/// Get L2 GblMJt.
	Collection<TMBL2GblMJt> getL2GblMJts(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblMJt> ("L2GblMJt", vars);
	}

	/// Get L2 GblHt.
	Collection<TMBL2GblHt> getL2GblHts(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblHt> ("L2GblHt", vars);
	}

	/// Get L2 GblTau.
	Collection<TMBL2GblTau> getL2GblTaus(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblTau> ("L2GblTau", vars);
	}
	/// Get L2 GblSphericity.
	Collection<TMBL2GblSphericity> getL2GblSphericitys(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblSphericity> ("L2GblSphericity", vars);
	}

	/// Get L2 GblSTTBtags.
	Collection<TMBL2GblSTTBtag> getL2GblSTTBtags(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2GblSTTBtag> ("L2GblSTTBtag", vars);
	}

	/// Get L2 scripts.
	Collection<TMBL2Script> getL2Scripts(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL2Script> ("L2GblScript", vars);
	}

	/// Get L3 BTagIP.
	Collection<TMBL3BTagIP> getL3BTagIPs(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3BTagIP> ("L3BTagIP", vars);
	}

	/// Get L3 CFTVtx.
	Collection<TMBL3CFTVtx> getL3CFTVtxs(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3CFTVtx> ("L3CFTVertex", vars);
	}

	/// Get L3 Ele.
	Collection<TMBL3Ele> getL3Eles(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Ele> ("L3Electron", vars);
	}

	/// Get L3 IPTrack.
	Collection<TMBL3IPTrack> getL3IPTracks(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3IPTrack> ("L3IPTrack", vars);
	}

	/// Get L3 Isolation.
	Collection<TMBL3Isolation> getL3Isolations(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Isolation> ("L3Isolation", vars);
	}

	/// Get L3 Jet.
	Collection<TMBL3Jet> getL3Jets(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Jet> ("L3Jet", vars);
	}

	/// Get L3 Muon.
	Collection<TMBL3Muon> getL3Muons(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Muon> ("L3Muon", vars);
	}

	/// Get L3 Photon.
	Collection<TMBL3Photon> getL3Photons(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Photon> ("L3Photon", vars);
	}

	/// Get L3 Tau.
	Collection<TMBL3Tau> getL3Taus(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Tau> ("L3Tau", vars);
	}

	/// Get L3 Track.
	Collection<TMBL3Track> getL3Tracks(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3Track> ("L3Track", vars);
	}

	/// Get L3 MEt.
	Collection<TMBL3MEt> getL3MEts(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL3MEt> ("L3MEt", vars);
	}

	/// Get L1Cal2B Jet
	Collection<TMBL1Cal2bJet> getL1Cal2bJets() const
	{
	    return getCollection<TMBL1Cal2bJet> ("L1Cal2bJet");
	}
	
	
	/// Get L1Cal2B EM
	Collection<TMBL1Cal2bEM> getL1Cal2bEMs() const
	{
	    return getCollection<TMBL1Cal2bEM> ("L1Cal2bEM");
	}
	
	/// Get L1Cal2B Taus
	Collection<TMBL1Cal2bTau> getL1Cal2bTaus() const
	{
	    return getCollection<TMBL1Cal2bTau> ("L1Cal2bTau");
	}
	
	/// Get L1Cal Towers.
	Collection<TMBL1CalTower> getL1CalHADTowers(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBL1CalTower> ("L1CalHADTowers", vars);
	}
	
	/// Get L1 Cal2bGAB information.
	const TMBL1Cal2bGAB *getL1Cal2bGAB(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1Cal2bGAB>("L1Cal2bGAB", vars);
	}
	
	/// Get L1Cal2B MET
         const TMBL1Cal2bMET *getL1Cal2bMET(const Variables& vars = cafe::detail::empty) const
	{
	    return get<TMBL1Cal2bMET>("L1Cal2bMET", vars);
	}
	
	/// Get L1Cal2B Jet Seeds
        Collection<TMBL1Cal2bSeed> getL1Cal2bJetSeeds() const
	{
	    return getCollection<TMBL1Cal2bSeed> ("L1Cal2bJetSeed");
	}
	
	/// Get L1Cal2B EM Seeds
	Collection<TMBL1Cal2bSeed> getL1Cal2bEMSeeds() const
	{
	    return getCollection<TMBL1Cal2bSeed> ("L1Cal2bEMSeed");
	}
	
	/// Get L1Cal2B Tau Seeds
         Collection<TMBL1Cal2bSeed> getL1Cal2bTauSeeds() const
	{
	    return getCollection<TMBL1Cal2bSeed> ("L1Cal2bTauSeed");
	}
		
        //@}

        /// Get container with all calorimeter cells.
        const TMBCellContainer *getCaloCells(const Variables& vars = cafe::detail::empty) const
        {
            return get<TMBCellContainer>("CaloCells", vars);
        }
	
	/// Luminosity chunk.
	Collection<TMBLum> getLum(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBLum>("Lum", vars);
	}
	
	/// Luminosity chunk.
	Collection<TMBLumV> getLumV(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<TMBLumV>("LumV", vars);
	}
	
	/// Event weights
	Collection<EventWeight> getEventWeights(const Variables& vars = cafe::detail::empty) const
	{
	    return getCollection<EventWeight>("EventWeight", vars);
	}

        /// Get TMBHiPt information
	        Collection<TMBHiPt> getHiPt(const Variables& vars = cafe::detail::empty) const
        {
            return getCollection<TMBHiPt>("HiPt", vars);
        }

        /// Get FPDTrack information  ( relevant  for  FPD analysis )
        Collection<TMBFPDTrack> getFPDTrack(const Variables& vars = cafe::detail::empty) const
        {
            return getCollection<TMBFPDTrack>("FPDTrack", vars);
        }


        /// Get Tdc information  ( relevant  for  FPD analysis )
        Collection<TMBTdc> getTdc(const Variables& vars = cafe::detail::empty) const
        {
            return getCollection<TMBTdc>("FPDTdc", vars);
        }

    public:
        ClassDef(Event, 0);
    };

}

#endif // EVENT_HPP__
