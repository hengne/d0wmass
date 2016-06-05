
#include "TTree.h"
#include "TFile.h"
#include "TEventList.h"
#include "TSystem.h"

#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Expander.hpp"
#include "cafe/RunController.hpp"

#include <vector>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace cafe {

    RunController::RunController(const char *name)
        : Controller(name),
          _num_events(0),
          _max_events(0),
	  _max_files(0),
	  _num_files(0),
	  _progress(0),
          _skip(0),
          _skip_files(0),
          _partialReads(false),
          _rootDebug(-1),
          _treeDebug(-1),
	  _eventList(0),
          _treeName("TMBTree")
    {
        Config config(name);
        _max_events = config.get("Events", 0);
	_max_files  = config.get("Files", 0);
        _input      = config.get("Input", "file:input.root");
	_progress   = config.get("Progress", 0);
	_skip       = config.get("Skip", 0);
        _skip_files = config.get("SkipFiles",0);
        assert(_skip_files >= 0);

	_partialReads = config.get("PartialReads", false);
	_treeName   = config.get("TreeName", "TMBTree");

	_rootDebug = config.get("RootDebug", -1);
	_treeDebug = config.get("TreeDebug", -1);
	_loadAll   = config.get("LoadAll", 0);

	if(_rootDebug >= 0) {
	    gDebug = _rootDebug;
	}

	std::vector<std::string> friends = config.getVString("Friends", " ,");
	_friends.insert(friends.begin(), friends.end());

	std::string eventList = config.get("EventList", "");
	if(!eventList.empty()) {
	    _eventList = new TFile(eventList.c_str(), "READ");
	    if(_eventList->IsZombie()) {
		throw std::runtime_error("EventList file not readable: " + eventList);
	    }
	}
    }


    RunController::~RunController()
    {
    }

    void RunController::processTree(TTree *tree, Event& event)
    {

	if(_treeDebug >= 0) {
	    tree->SetDebug(_treeDebug);
	}

        event.setBranchAddresses(tree);

        Long64_t index = 0;
	Long64_t entry = -1;

	if(_skip > 0) {
	    index = _skip;
	    out() << "RunController[cafe]: Skipped events = " << _skip << std::endl;
	}

        while((_max_events == 0 || _num_events < _max_events) && 
	      (entry = tree->GetEntryNumber(index++)) >= 0 &&
	      (tree->LoadTree(entry) != -2)) {
            incEventCount();
            _num_events++;
	    if(_progress && (_num_events % _progress == 0)) {
		out() << "cafe: Processed events = " << _num_events << std::endl;
	    }

	    if(_loadAll) {
		// load whole event instead of loading on demand
		tree->GetEntry(entry);
	    }

            processEvent(event);
	    event.clear();
        }

	// Adjust skip event value.
	_skip = _skip - (int)tree->GetEntries();
        if(_skip < 0 ) _skip = 0; 
    }

    bool RunController::Run(unsigned int max_events)
    {
        if(_max_events == 0) {
            _max_events = max_events;
        }

        out() << "RunController[" << name() << "] Input: " << _input << std::endl;
        if(_max_events > 0) {
            out() << "RunController[" << name() << "] MaxEvents: " << _max_events << std::endl;
        }

        if(_max_files > 0) {
            out() << "RunController[" << name() << "] MaxFiles: " << _max_files << std::endl;
        }

	if(_eventList != 0) {
            out() << "RunController[" << name() << "] Using event list: " << _eventList->GetName() << std::endl;
	}

	std::auto_ptr<Expander> exp(Expander::create(_input));
        if(exp.get()) {

            Event event;
	    event.setPartialRead(_partialReads);

            _num_events = 0;

            begin();

	    // check for unused config variables
	    std::vector<std::string> unused = Config::checkConfiguration();

	    if(unused.size() > 0) {
		err() << "-----------------" << std::endl;
		err() << "ERROR: Unused (mispelled?) configuration variables:" << std::endl;
		for(std::vector<std::string>::iterator it = unused.begin();
		    it != unused.end();
		    ++it) {
		    err() << *it << std::endl;
		}
		err() << "-----------------" << std::endl;
	    }
            
            std::string nextFile = exp->nextFile();
            while(nextFile.size() > 0 &&
		  ((_max_files == 0) || (_num_files++ < _max_files)) &&
		  ((_max_events == 0) || (_num_events < _max_events))) {

                // Check if we should skip first N files, if no, open file
                if(_skip_files == 0) {
                    
                    TFile *file = TFile::Open(nextFile.c_str(), "READ");
                    
                    if(file && !file->IsZombie()) {
                        
                        
                        if(TTree *tree = (TTree *)file->Get(_treeName.c_str())) {
                            
                            out() << "RunController[" << name() 
                                  << "]: Input file opened: " << nextFile << std::endl;
                            
                            for(std::set<std::string>::const_iterator it = _friends.begin();
                                it != _friends.end(); 
                                ++it) {
                                if(TTree *fr = dynamic_cast<TTree*>(file->Get((*it).c_str()))) {
                                    tree->AddFriend(fr);
                                    out() << "RunController: Added friend tree:  " << *it << std::endl;
                                } else {
                                    err() << "RunController: Friend tree not found: " << *it << std::endl;
                                }
                            }
                            
                            if(_eventList) {
                                if(TEventList *evts = dynamic_cast<TEventList*>(_eventList->Get((std::string("EVTS-") + gSystem->BaseName(file->GetName())).c_str()))) {
                                    tree->SetEventList(evts);
                                } else {
                                    throw std::runtime_error("RunController: Cannot find event list for:" + 
                                                             std::string(file->GetName()));
                                } 
                            }
                            
                            inputFileOpened(file);
                            
                            processTree(tree, event);
                            
                            inputFileClosing(file);
                            
                        } else {
                            err() << "RunController: No tree object in file: " << nextFile << std::endl;
                            // not TMBTree object
                            return false;
                        }
                        
                        file->Close();
                        delete file;
                    } else {
                        // cannot open file
                        err() << "RunController: Cannot open file: " << nextFile << std::endl;
                        return false;
                    }
                } else { // if(_skip_files == 0)
                    _num_files--;
                    _skip_files--;
                }

                // try to get next file
                nextFile = exp->nextFile();
            }

            out() << fullName() << " : " << eventCount() << std::endl;
            finish();
            
            return true;

        } else {
            // Invalid URL
            err() << "RunController: Cannot open input: " << _input << std::endl;
            return false;
        }
    }
}

ClassImp(cafe::RunController)


    
