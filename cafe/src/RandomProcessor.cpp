/* Documentation is in header file. */

#include <stdexcept>

#include "cafe/Config.hpp"
#include "cafe/RandomProcessor.hpp"
#include "TFile.h"
#include "TSystem.h"

#include <iomanip>

using std::endl;

namespace cafe {

  // avoid ROOT v4 bug in TRandom3 (thanks to Henrik for testing performances)
  void patchedSetSeed (TRandom3& rnd, const UInt_t seed, 
		       const bool treatZeroAsSpecial, const int method, const int debug)
  {
    // Low numbers are bad, make it hard to get them. But don't spoil/fake the special value 0.
    // This logic will only use the nonreproducible 0 seed (time stamp) if it's explicitely asked for!
    int anInt  = 20060925;
    bool usedTimeStamp = false;
    if (seed == anInt) {
      rnd.SetSeed (seed);
    } else {
      if (treatZeroAsSpecial && seed == 0) {
	rnd.SetSeed (0);
	usedTimeStamp = true;
      } else {
	rnd.SetSeed (seed ^ anInt);
      }
    }
    if (debug) std::cout<<"DBG patchedSetSeed Input: "<<seed
			<<" --> timestamp? "<<usedTimeStamp<<", seed: "<<rnd.GetSeed()<<endl;

    if (usedTimeStamp) {
      // Now avoid the ROOT v4 bug (if needed)
      if (method == 1) { // first number happens to be OK
	//             aaBBccDD                  aaBBccDD - 4 bytes each. UInt_t hardwired to be 4 bytes.
	UInt_t myRandomSeed = rnd.Integer (0xFFffFFff);
	time_t now;
	time(&now);
	UInt_t myRandomSeedWithTime = myRandomSeed + (UInt_t) now; // add the time
	if (myRandomSeedWithTime < 10000) myRandomSeedWithTime ^= 20050823; // protect against small numbers (in particular, 0)
	if (debug) std::cout<<"DBG patchedSetSeed avoiding v4 bug. myRandomSeed: "<<myRandomSeed<<" ^ I(time): "<<UInt_t (now)
			    <<" --> myRandomSeedWithTime: "<<myRandomSeedWithTime<<endl;
	rnd.SetSeed (myRandomSeedWithTime);
	
      } else if (method == 2) { // after 624 numbers, the rest are OK
	for (int it=0; it<700; ++it) rnd.Uniform();
	if (debug) std::cout<<"DBG patchedSetSeed, after discarding some numbers RandomSeed: "<<rnd.GetSeed()<<endl;
      }
    }
  }

  
  // Fake constructor (see header)
  RandomProcessor::RandomProcessor () : 
    Processor()
  {
    // this should never happen, but to have sensible values, these force only one timestamp seeding
    _eventKey = false;
    _rnd.SetSeed (0);
  }

  // Normal Constructor 
  RandomProcessor::RandomProcessor(const char *name) : 
    Processor(name)
  {
    // Read the config
    // ===============
    Config config(name);
    _eventKey            = config.get("EventKey", false);
    _newEventKey         = config.get("NewEventKey", true);
    _seed                = config.get("Seed", 0);
    _mTable              = config.get("TableSize", 10000);
    _ROOT4patch          = config.get("ROOT4patch", 1);
    int debug            = config.get("DebugConstructor", 0);
    _ignoreDirectory     = config.get("IgnoreDirectory", false);
    _nFirstCharsToIgnore = config.get("NFirstCharsToIgnore", 0);
    _nLastCharsToIgnore  = config.get("NLastCharsToIgnore", 0);
    _addPrefix           = config.get("AddPrefix", "");

    if (_eventKey && _newEventKey) throw std::runtime_error("RandomProcessor: Do not set .NewEventKey and .EventKey at the same time.");
    if (_eventKey && _mTable <= 100) throw std::runtime_error("RandomProcessor: table size too small");

    // Initialize the seed
    // ===================
    if (_seed == 0 && _eventKey) {// need reproducible results with eventKey --> use processor name as seed
      patchedSetSeed (_rnd, hashString (name), false, 1, debug); // if it comes out 0, it's just a number
      out()<<" RandomProcessor["<<name<<"]: Seed==0, so took it from processor name ("
	   <<name<<" --> "<<_rnd.GetSeed()<<")"<<endl;
    } else {
      patchedSetSeed (_rnd, _seed, true, 1, debug); // if _seed is 0, _eventKey must be false and the user really means it 
    }

    // Print the parameters
    if (_eventKey) {
      out()<<" RandomProcessor["<<name<<"]: Will reseed random generator per event, based on filename and event #"<<endl;
      if (_ignoreDirectory || _nFirstCharsToIgnore || _nLastCharsToIgnore || _addPrefix.Length()) {
	out()<<" Each file's path will be processes as follows:"<<endl;
	if (_ignoreDirectory) out()<<"  Ignoring directories"<<endl;
	if (_nFirstCharsToIgnore) out()<<"  Ignoring the first "<<_nFirstCharsToIgnore<<" characters"<<endl;
	if (_nLastCharsToIgnore) out()<<"  Ignoring the last "<<_nFirstCharsToIgnore<<" characters"<<endl;
	if (_addPrefix.Length()) out()<<"  Adding the prefix: "<<_addPrefix<<endl;
      }
    } else if (_newEventKey) {
      out()<<" RandomProcessor["<<name<<"]: Will reseed random generator per event, based on MC information or run and event number for data."<<endl;
    } else {
      out()<<" RandomProcessor["<<name<<"]: Seed is "<<_rnd.GetSeed()<<" (from input "<<_seed<<"), it will not be reinitialized."<<endl; 
    }

    // initialize table
    if (_eventKey) {
      if (debug) out()<<"Debugging constructor. Pre-table we have seed: "<<_rnd.GetSeed()<<" (from input "<<_seed<<"), and"
		      <<" _mTable: "<<_mTable<<endl;
      for (int i=0; i<_mTable; ++i) {
	_seeds.push_back (_rnd.Integer (0xffFFffFFu)); // UInt_t is guaranteed to be 4 bytes.
	if (debug > 9) out()<<"i: "<<i<<", l: "<<_seeds.size()<<", s: "<<_seeds[i]<<endl;
      }
    }
  }

  void RandomProcessor::inputFileOpened(TFile* file)
  {
    if (_eventKey) {
      TString filename = file->GetName();

      if (debug() > 40) out()<<"RandomProcessor::inputFileOpened name from ROOT: "<<filename<<endl;

      if (_ignoreDirectory) {
	filename = gSystem->BaseName(filename);
      }
      if (_nFirstCharsToIgnore) {
	filename.Remove (0, _nFirstCharsToIgnore);
      }
      if (_nLastCharsToIgnore) {
	if (!filename.EndsWith (".root")) throw std::runtime_error ("RandomProcessor::inputFileOpened ["+name()
								    +"] when using the NLastCharsToIgnore option, all "
								    +"input file names must end with \".root\".");
	filename.Remove (TMath::Max(0, filename.Length() - 5 - _nLastCharsToIgnore), _nLastCharsToIgnore);
      }
      filename.Prepend (_addPrefix);

      _fileHash = hashString (filename);
      if (debug() > 5) out()<<"_fileHash: "<<_fileHash<<" <--- "<<filename<<endl;
    }
  }

  bool RandomProcessor::processEvent(cafe::Event& event)
  {
    if (_eventKey) {
      // get the event's number in the tree
      TTree* ptree = event.getTree();
      if (ptree == 0) throw std::runtime_error ("event's tree pointer is NULL!");
      Long64_t iEvent = ptree->GetReadEntry();

      UInt_t rawindex = (UInt_t (iEvent) ^ _fileHash);
      if (debug() > 99) out()<<"iEvent: "<<iEvent<<", rawindex: "<<rawindex<<" -> ["<<(rawindex % _mTable)<<"]"<<endl;
      UInt_t newseed = _seeds [rawindex % _mTable];
      patchedSetSeed (_rnd, newseed, false, 1, debug()); // if it comes out 0, it's just a number
      if (debug() > 29) out()<<"iEvent: "<<iEvent<<", newseed: "<<newseed<<" -> "<<_rnd.GetSeed()<<endl;
    
    }
    else if (_newEventKey) {
      // Make sure to also use the processor name so different
      // processors do not end up with the same random numbers
      TString id(name());
      if (event.isMC()) {
	const TMBMCevtInfo* mcinfo = event.getMCEventInfo();
	id += mcinfo->shat()  + mcinfo->that()+mcinfo->uhat()
	  +  mcinfo->flav1() + mcinfo->x1()
	  +  mcinfo->flav2() + mcinfo->x2()
	  +  mcinfo->weight();
      }
      else {
	const TMBGlobal* global = event.getGlobal();
	id += global->runno();
	id += global->evtno();
      }
      _rnd.SetSeed(id.Hash());
      if (debug() > 29) out()<<"Newseed: "<<_rnd.GetSeed()<<endl;
    }
    // else we simply don't reseed
    return true;
  }
}

ClassImp(cafe::RandomProcessor)
