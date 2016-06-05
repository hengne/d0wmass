#include "cafe/Event.hpp"

#include <stdexcept>

namespace cafe {
    
  Event::Event()
  {
  }

  bool Event::isMC() const
  //
  // Purpose: Tell if event is mc.  The algorithm is similar to 
  //          HistorySelector::is_monte_carlo, namely, it checks a) history,
  //          b) TMBMCevtInfo::nchunks() > 0, or c) run number == 1 
  //          (else data).
  //
  {
    bool is_mc = false;

    // First check run number in TMBGlobal.  Assume run 1 is always mc.

    const TMBGlobal* global = getGlobal();
    is_mc = global != 0 && global->runno() == 1;
      
    // Next look for program "d0gstar" in TMBHistory.

    if(!is_mc) {
      const Collection<TMBHistory> history = getHistory();
      for(Collection<TMBHistory>::const_iterator i = history.begin();
	  i != history.end(); ++i) {
	const TMBHistory& hist = *i;
	if(hist.program() == std::string("d0gstar")) {
	  is_mc = true;
	  break;
	}
      }
    }

    // Finally check if TMBMCevtInfo::nchunks() > 0.

    if(!is_mc) {
      const TMBMCevtInfo* mcinfo = getMCEventInfo();
      is_mc = mcinfo != 0 && mcinfo->nchunks() > 0;
    }

    // Done

    return is_mc;
  }

  std::string Event::mcVersion() const {
    if ( !isMC() ) return ""; 
    
    // For mc, the run 2a vs. run 2b determination is based on the 
    // d0gstar program version from TMBHistory. It is a fatal
    // error if a d0gstar TMBHistory object isn't found.

      const TMBHistory* phist = 0;
      const Collection<TMBHistory> history = getHistory();
      for(Collection<TMBHistory>::const_iterator i = history.begin();
	  i != history.end(); ++i) {
	phist = &*i;
	assert(phist != 0);
	if(phist->program() == std::string("d0gstar"))
	  break;
      }
      if(phist == 0) {
	assert(phist != 0);
	abort();
      }
	  
      return phist->version();
  }

  bool Event::isRun2b() const
  {
    bool is_2b = false;

    // Data or mc?

    if(isMC()) {

      // For mc, the run 2a vs. run 2b determination is based on the 
      // d0gstar program version from TMBHistory.  Any version later than
      // t05.09.00 or p20.00.00 is assumed to be run 2b.  It is a fatal
      // error if a d0gstar TMBHistory object isn't found.

      std::string version_tag = mcVersion() ;

      // We only know how to definitively interpret standard 9-character
      // test and production version tags: txx.yy.zz or pxx.yy.zz.  In
      // these cases, do a straight lexical comparison with the cutoff
      // version.  Assume any version tag that doesn't conform to these
      // standard forms is run2a (since there were a few early
      // production releases with weird names), but print an error
      // message.  Don't think anyone should be using them any more, but
      // you never know.

      if(version_tag.size() == 9 && 
	 version_tag.substr(0,1) == std::string("t")) {

	// Check test release.

	is_2b = version_tag >= std::string("t05.09.00");
      }
      else if(version_tag.size() == 9 && 
	      version_tag.substr(0,1) == std::string("p")) {

	// Check production release.

	is_2b = version_tag >= std::string("p20.00.00");
      }
      else {

	// Nonstandard version tag.

	std::cerr << "cafe::Event::isRun2b - Nonstandard d0gstar version "
		  << version_tag << ", assuming run 2a." << std::endl;
      }
    }
    else {

      // For data, the determination whether this is run 2a or run 2b is
      // based on run number, see cafe::DataEpochs

      const TMBGlobal* global = getGlobal();
      if(global == 0) {
	assert(global != 0);
	abort();
      }
      // this cut-off is between CSG data set RunIIa and RunIIb1
      is_2b = global->runno() >= 219000;
    }

    return is_2b;
  }


  bool Event::isRun2b1() const
  {
    
    if ( isRun2a() ) return false ;

    if(isMC()) {

      // For production release any version later than p20.15 
      // is assumed to be run Run2b2.  
      
      std::string version_tag = mcVersion() ;
      
      // We only know how to definitively interpret standard 9-character
      // test and production version tags: txx.yy.zz or pxx.yy.zz.  In
      // these cases, do a straight lexical comparison with the cutoff
      // version.  
      
      
      // test release 
      if(version_tag.size() == 9 && 
	 version_tag.substr(0,1) == std::string("t")) {
	return  version_tag >= std::string("t05.09.00") &&
	  version_tag < std::string("t09.02.00");
      }
      
      // Check production release.
      else if(version_tag.size() == 9 && 
	      version_tag.substr(0,1) == std::string("p")) {
	
	return  version_tag < std::string("p20.15.00");
      }

      
      // Nonstandard version tag.
      
      throw std::runtime_error("cafe::Event::isRun2b1 - Nonstandard d0gstar version "
			  +  version_tag) ;
      
    }

    
    // For data, the determination whether this is run 2b1 is based on run number
    
    const TMBGlobal* global = getGlobal();
    if(global == 0) {
      assert(global != 0);
      abort();
    }
    return  global->runno() <= _epochs.lastRun("RunIIb1");
  }

  bool Event::isRun2b2() const
  {
    
    if ( isRun2a() ) return false ;

    if(isMC()) {

      // For mc, any version later than t05.09.00 for test release is run2b1.
      // For production release any version later than p20.00.00, but 
      // earlier p20.15 is assumed to be run Run2b1.  
      
      std::string version_tag = mcVersion() ;
      
      // We only know how to definitively interpret standard 9-character
      // test and production version tags: txx.yy.zz or pxx.yy.zz.  In
      // these cases, do a straight lexical comparison with the cutoff
      // version.  
      
      
      // test release 
      if(version_tag.size() == 9 && 
	 version_tag.substr(0,1) == std::string("t")) {
	return  version_tag >= std::string("t09.02.00") &&
	  version_tag < std::string("t10.02.00");
      }
      
      // Check production release.
      else if(version_tag.size() == 9 && 
	      version_tag.substr(0,1) == std::string("p")) {
	
	return  version_tag >= std::string("p20.15.00") &&
	  version_tag < std::string("p20.16.00");
      }

      
      // Nonstandard version tag.
      
      throw std::runtime_error("cafe::Event::isRun2b2 - Nonstandard d0gstar version "
			  +  version_tag) ;
      
    }

    
    // For data, the determination whether this is run 2b2 is  based on run number
    
    const TMBGlobal* global = getGlobal();
    if(global == 0) {
      assert(global != 0);
      abort();
    }
    return  global->runno() >=_epochs.firstRun("RunIIb2") && 
      global->runno() <= _epochs.lastRun("RunIIb2") ;
  }

  bool Event::isRun2b3() const
  {
    
    if ( isRun2a() ) return false ;

    if(isMC()) {

      // For mc, any version later than t05.09.00 for test release is run2b1.
      // For production release any version later than p20.00.00, but 
      // earlier p20.15 is assumed to be run Run2b1.  
      
      std::string version_tag = mcVersion() ;
      
      // We only know how to definitively interpret standard 9-character
      // test and production version tags: txx.yy.zz or pxx.yy.zz.  In
      // these cases, do a straight lexical comparison with the cutoff
      // version.  
      
      
      // test release 
      if(version_tag.size() == 9 && 
	 version_tag.substr(0,1) == std::string("t")) {
	return  version_tag >= std::string("t10.02.00") &&
	  version_tag < std::string("t11.01.00");
      }
      
      // Check production release.
      else if(version_tag.size() == 9 && 
	      version_tag.substr(0,1) == std::string("p")) {
	
	return  version_tag >= std::string("p20.17.00") &&
	  version_tag < std::string("p20.18.00");
      }

      
      // Nonstandard version tag.
      
      throw std::runtime_error("cafe::Event::isRun2b3 - Nonstandard d0gstar version "
			  +  version_tag) ;
      
    }

    
    // For data, the determination whether this is run 2b3 is  based on run number
    
    const TMBGlobal* global = getGlobal();
    if(global == 0) {
      assert(global != 0);
      abort();
    }
    return  global->runno() >=_epochs.firstRun("RunIIb3") && 
      global->runno() <= _epochs.lastRun("RunIIb3") ;
  }

  bool Event::isRun2b4() const
  {
    
    if ( isRun2a() ) return false ;

    if(isMC()) {

      // For mc, any version later than t05.09.00 for test release is run2b1.
      // For production release any version later than p20.00.00, but 
      // earlier p20.15 is assumed to be run Run2b1.  
      
      std::string version_tag = mcVersion() ;
      
      // We only know how to definitively interpret standard 9-character
      // test and production version tags: txx.yy.zz or pxx.yy.zz.  In
      // these cases, do a straight lexical comparison with the cutoff
      // version.  
      
      
      // test release 
      if(version_tag.size() == 9 && 
	 version_tag.substr(0,1) == std::string("t")) {
	return  version_tag >= std::string("t11.01.00");
      }
      
      // Check production release.
      else if(version_tag.size() == 9 && 
	      version_tag.substr(0,1) == std::string("p")) {
	
	return  version_tag >= std::string("p20.19.00") &&
	  version_tag < std::string("p20.20.00");
      
      }

      
      // Nonstandard version tag.
      
      throw std::runtime_error("cafe::Event::isRun2b3 - Nonstandard d0gstar version "
			  +  version_tag) ;
    }

    
    // For data, the determination whether this is runIIb4 is  based on run number
    
    const TMBGlobal* global = getGlobal();
    if(global == 0) {
      assert(global != 0);
      abort();
    }
    return  global->runno() >= _epochs.firstRun("RunIIb4"); ;
  }


  bool Event::isEpoch(const std::string& epoch) const {    

    if(isMC()) 
      throw std::runtime_error("cafe::Event:isEpoch cann't be used for MC events"); 
    
    const TMBGlobal* global = getGlobal();
    if(global == 0) {
      assert(global != 0);
      abort();
    }
    return  global->runno() >=_epochs.firstRun(epoch) && 
      global->runno() <= _epochs.lastRun(epoch) ;
  }

}

ClassImp(cafe::Event);

ClassImp(cafe::Collection<TMBHistory>);
ClassImp(cafe::Collection<TMBTrigger>);

ClassImp(cafe::Collection<TMBLorentzVector>);
ClassImp(cafe::Collection<TMBMuon>);
ClassImp(cafe::Collection<TMBEMCluster>);
ClassImp(cafe::Collection<TMBJet>);
ClassImp(cafe::Collection<TMBParticleJet>);
ClassImp(cafe::Collection<TMBTrack>);
ClassImp(cafe::Collection<TMBIsoTrack>);
ClassImp(cafe::Collection<TMBVertex>);
ClassImp(cafe::Collection<TMBPrimaryVertex>);
ClassImp(cafe::Collection<TMBTrackCal>);
ClassImp(cafe::Collection<TMBTrackCalJet>);
ClassImp(cafe::Collection<TMBTau>);

ClassImp(cafe::Collection<TMBCps>);
ClassImp(cafe::Collection<TMBCpsDigi>);
ClassImp(cafe::Collection<TMBFps>);
ClassImp(cafe::Collection<TMBFpsData>);
ClassImp(cafe::Collection<TMBFpd>);

ClassImp(cafe::Collection<TMBMCvtx>);
ClassImp(cafe::Collection<TMBMCpart>);

ClassImp(cafe::Collection<TMBL1CalTile>);
ClassImp(cafe::Collection<TMBL1CalTower>);
ClassImp(cafe::Collection<TMBL1Track>);
ClassImp(cafe::Collection<TMBL1toL2CTT>);
ClassImp(cafe::Collection<TMBL1L2Masks>);
ClassImp(cafe::Collection<TMBL2Base>);
ClassImp(cafe::Collection<TMBL2CPS>);
ClassImp(cafe::Collection<TMBL2EM>);
ClassImp(cafe::Collection<TMBL2Muon>);
ClassImp(cafe::Collection<TMBL2Jet>);
ClassImp(cafe::Collection<TMBL2Track>);

ClassImp(cafe::Collection<TMBL2GblJet>);
ClassImp(cafe::Collection<TMBL2GblMuon>);
ClassImp(cafe::Collection<TMBL2GblEM>);
ClassImp(cafe::Collection<TMBL2GblTrack>);
ClassImp(cafe::Collection<TMBL2GblInvMass>);
ClassImp(cafe::Collection<TMBL2GblMJt>);
ClassImp(cafe::Collection<TMBL2GblHt>);
ClassImp(cafe::Collection<TMBL2GblTau>);
ClassImp(cafe::Collection<TMBL2GblSphericity>);
ClassImp(cafe::Collection<TMBL2GblSTTBtag>);
ClassImp(cafe::Collection<TMBL2Script>);

ClassImp(cafe::Collection<TMBL3Base>);
ClassImp(cafe::Collection<TMBL3BTagIP>);
ClassImp(cafe::Collection<TMBL3CFTVtx>);
ClassImp(cafe::Collection<TMBL3Ele>);
ClassImp(cafe::Collection<TMBL3IPTrack>);
ClassImp(cafe::Collection<TMBL3Isolation>);
ClassImp(cafe::Collection<TMBL3Jet>);
ClassImp(cafe::Collection<TMBL3Muon>);
ClassImp(cafe::Collection<TMBL3Photon>);
ClassImp(cafe::Collection<TMBL3Tau>);
ClassImp(cafe::Collection<TMBL3Track>);
ClassImp(cafe::Collection<TMBL3MEt>);

ClassImp(cafe::Collection<TMBLum>);
ClassImp(cafe::Collection<TMBLumV>);
ClassImp(cafe::Collection<EventWeight>);

ClassImp(cafe::Collection<TMBBTag>);
ClassImp(cafe::Collection<TMBBTagSLT>);
ClassImp(cafe::Collection<TMBBTagJLIP>);
ClassImp(cafe::Collection<TMBBTagSVT>);
ClassImp(cafe::Collection<TMBBTagNN>);
ClassImp(cafe::Collection<TMBBTagSLTNN>);
ClassImp(cafe::Collection<TMBBTagMVA>);

ClassImp(cafe::Collection<TMBL1Cal2bEM>);
ClassImp(cafe::Collection<TMBL1Cal2bJet>);
ClassImp(cafe::Collection<TMBL1Cal2bTau>);
ClassImp(cafe::Collection<TMBL1Cal2bSeed>);
ClassImp(cafe::Collection<TMBL1Cal2bGAB>);

ClassImp(cafe::Collection<TMBLeBob>);
ClassImp(cafe::Collection<TMBHiPt>);

ClassImp(cafe::Collection<TMBTdc>);
ClassImp(cafe::Collection<TMBFPDTrack>);

