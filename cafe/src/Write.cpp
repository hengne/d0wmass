
#include "cafe/Write.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"

#include <cstdlib>
#include <climits>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cassert>

#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranchRef.h"
#include "TRefTable.h"
#include "TObjArray.h"
#include "TBranchElement.h"
#include "TStreamerInfo.h"

namespace {

    // enable this branch and all sub-branches
    void enableBranch(TBranch *br)
    {
	if(br != 0) {
	    br->ResetBit(kDoNotProcess);
	    TIter iter(br->GetListOfBranches());
	    while(TBranch *sub = (TBranch *)iter.Next()) {
		enableBranch(sub);
	    }
	} 
    }


    void disableBranch(TBranch *br)
    {
	if(br != 0) {
	    br->SetBit(kDoNotProcess);
	    TIter iter(br->GetListOfBranches());
	    while(TBranch *sub = (TBranch *)iter.Next()) {
		disableBranch(sub);
	    }
	}
    }


}

namespace cafe {

    Write::Write(const char *name)
	: Processor(name),
          _oldFileName(""),
	  _input_file(0),
	  _file(0),
	  _tree(0),
	  _fileOwner(false),
	  _isMC(false),
	  _firstEvent(INT_MAX),
	  _lastEvent(0),
	  _vars("_runno", "_evtno"),
	  _updateObjectVersion(true)
    {
	Config config(name);
	_pattern.set(config.get("File", ""));
	_branches = config.getVString("Branches", " ,");
	if(_branches.empty()) _branches = config.getVString("Enable", " ,");
	_disable  = config.getVString("Disable", " ,");
	_treeName = config.get("Tree", "TMBTree");
	_autosave = config.get("AutoSave", -1);
	_destination = config.get("Destination", "");
	_filesPerOutput = config.get("FilesPerOutput", 0);
	_filesPerOutputDone = _filesPerOutput;

	_rootMaxTreeSize = config.get("RootMaxTreeSize", 0);
	if(_rootMaxTreeSize > 0)
	  TTree::SetMaxTreeSize(_rootMaxTreeSize);
	else
	  _rootMaxTreeSize = TTree::GetMaxTreeSize();

	_maxEventsPerFile = config.get("MaxEventsPerFile", 0);
	_maxBytesPerFile = config.get("MaxBytesPerFile", 0);
	_updateObjectVersion = config.get("UpdateObjectVersion", 1);

	Config samConfig("SAM");
	_samFamily      = samConfig.get("Family","");
	_samApplication = samConfig.get("Application","");
	_samVersion     = samConfig.get("Version","");

	_doMetaData = !_samFamily.empty() && !_samApplication.empty() && !_samVersion.empty();

    }

    Write::~Write()
    {
    }


    void Write::finish()
    {
	if(_file && _fileOwner) {
	    check_file();
	    _file->Write();
	    writeMetaData();
	    _file->Close();
	    if(!_destination.empty()) {
		copy_file();
	    }
	    delete _file;
	}
    }


    bool Write::processEvent(Event& event)
    {     
	if(_tree) {

	    // See if we want to advance to the next output file.

	    if(_maxEventsPerFile != 0 && 
	       _tree->GetEntries() >= _maxEventsPerFile ||
	       _maxBytesPerFile != 0 && 
	       _tree->GetCurrentFile()->GetBytesWritten() >= _maxBytesPerFile){

	      // Generate a file open event with force = true.
	      // This will crash if we can't get a new name from the 
	      // output pattern.

	      inputFileOpened(_input_file, true);
	    }

	    // Loop over enabled branches of output tree
	    // Read only if necessary (readBranch keeps track
	    // of the top-level branches).
	    TIter iter(_tree->GetListOfBranches());
	    while(TBranch *br = (TBranch *)iter.Next()) {

		// TODO: this test is no longer necessary ?
		if(!br->TestBit(kDoNotProcess)) {
		    event.readBranch(br->GetName());
		}
	    }

	    if(_fileOwner && _doMetaData) {
		if(const TMBGlobal *global = event.getGlobal(_vars)) {
		    _runs.insert(global->runno());
		    int evt = global->evtno();
		    if(evt < _firstEvent) { 
			_firstEvent = evt;
		    }
		    if(evt > _lastEvent) {
			_lastEvent = evt;
		    }
		}

		_isMC = event.isMC() ;
		if (_isMC) {
		  cafe::Variables mcvar("_reqid");
		  const TMBMCevtInfo* mcevtinfo = event.getMCEventInfo(mcvar) ;
		  _reqids.insert((unsigned int)  mcevtinfo->reqid());
		}

	    }

	    _tree->Fill();

	    if(_autosave > 0 && (eventCount() % _autosave == 0)) {
		_tree->AutoSave();
	    }

	    // Make sure root didn't open a new file behind our backs.

	    check_file();
	}
	return true;
    }

    void Write::inputFileOpened(TFile *file, bool force)
    {
	TTree *tree = 0;
	if (_treeName=="TMBTree") tree = (TTree *)file->Get("TMBTree");
	if (tree == 0) tree = (TTree *)getDirectory()->Get(_treeName.c_str());
	if (tree == 0) tree = (TTree *)gROOT->Get(_treeName.c_str());
	if (tree == 0) tree = (TTree *)file->Get(_treeName.c_str());
	if (tree == 0) {
	    _tree = 0;
	    err() << "Write[" << name() << "] No tree in file named: " << _treeName << std::endl;
	    return;
	}

	_input_file = file;

	// check this before we generate a new name
	if(!force && _file && _filesPerOutput && (++_filesPerOutputDone < _filesPerOutput)) {
	    // Same output file, just update tree addresses
	    tree->CopyAddresses(_tree);
            _parents.push_back(gSystem->BaseName(file->GetName()));
	    return;
	}

	// Now generate a new name if necessory
	std::string new_name = _pattern.replace(file->GetName());
	if(_file) { 

	    if(new_name == _oldFileName) {
		// Fatal error if we don't get a new name using force flag.
		if(force) {
		  err() << "Write[" << name() << "] Failed to generate new file name.  Got old file name: " << new_name << std::endl;
		  assert(!force);
		  abort();
		}
		// Same output file, just update tree addresses
		tree->CopyAddresses(_tree);
                _parents.push_back(gSystem->BaseName(file->GetName()));
		return;
	    }

	    if(_fileOwner) {
		check_file();
		_file->Write();
		writeMetaData();
		_file->Close();
		if(!_destination.empty()) {
		    copy_file();
		}

		delete _file;
	    }
	    _file = 0;
	}

        _parents.push_back(gSystem->BaseName(file->GetName()));

	_filesPerOutputDone = 0;

        _oldFileName = new_name;

	_file = dynamic_cast<TFile*>(gROOT->GetFile(new_name.c_str()));

	if(_file == 0) {
	    out() << "Write[" << name() << "] Opening new output file: " << new_name << std::endl;
	    _file = new TFile(new_name.c_str(), "RECREATE");
	    _fileOwner = true;
	} else {
	    out() << "Write[" << name() << "] Using existing file: " << new_name << std::endl;
	    _fileOwner = false;
	}

	// We allow to enable/disable top-level branches only.

	if(!_branches.empty()) {
	    // Disable all branches in input tree
	    tree->SetBranchStatus("*",0);

	    for(std::vector<std::string>::iterator it = _branches.begin();
		it != _branches.end();
		++it) {
		out() << "Write[" << name() << "] Enabling branch: " << *it << std::endl;
		if(TBranch *br = tree->GetBranch((*it).c_str())) {
		    enableBranch(br);
		} else {
		    err() << "Write[" << name() << "] Branch not found: " << *it << std::endl;
		    _branches.erase(it--);
		}
	    }

	} else if(!_disable.empty()) {

	    tree->SetBranchStatus("*", 1);

	    // Disable only branches in list
	    for(std::vector<std::string>::iterator it = _disable.begin();
		it != _disable.end();
		++it) {
		out() << "Write[" << name() << "] Disabling branch: " << *it << std::endl;
		if(TBranch *br = tree->GetBranch((*it).c_str())) {
		    disableBranch(br);
		} else {
		    err() << "Write[" << name() << "] Branch not found: " << *it << std::endl;
		    _disable.erase(it--);
		}
	    }
	} 

	//
	// Disable branches in updatedBranches
	// 
	// If requested, look for objects in the original tree 
	// that have old object format versions.
	_updatedBranches.clear();
	_updatedBranchesPointers.clear();

	if (_updateObjectVersion) {
	    TIter branchNext (tree->GetListOfBranches());
	    while (TBranch *br = static_cast<TBranch*>(branchNext.Next())) {
		if (!br->TestBit(kDoNotProcess) && containsUpdatedClass (br)) {
		    _updatedBranches.push_back (br->GetName());
		    _updatedBranchesPointers.push_back (br);
		    disableBranch(br);
		}
	    }
	}

	// Clone all active branches
	_file->cd();
	_tree = tree->CloneTree(0);

	// Return everything to normal
	//tree->SetBranchStatus("*",1);
	for(std::vector<TBranch*>::const_iterator 
	      i = _updatedBranchesPointers.begin();
	    i != _updatedBranchesPointers.end(); ++i) {
	    TBranch* br = *i;
	    enableBranch(br);
	}
	_updatedBranchesPointers.clear();

	for(std::vector<std::string>::iterator it = _updatedBranches.begin();
	    it != _updatedBranches.end();
	    ++it) {
	    out() << "Write[" << name() << "] Updating branch: " << *it << std::endl;
	    updateBranch(tree, *it);
	}

	// This is for buggy ROOT versions
	if(TBranchRef *ref = _tree->GetBranchRef()) {
	    // BranchRef is not properly reset after cloning
	    ref->Reset();
	    if(TRefTable *table = ref->GetRefTable()) {
		// TRefTable is not cleared; crashes when only some branches
		// are written out.
		if(TObjArray *parents = table->GetParents()) {
		    parents->Clear();
		}
	    }
	} else {
	    // Always create a BranchRef in the new tree, even
	    // if it didn't have one before.
	    _tree->BranchRef();
	}

	// Some friends work, others don't, e.g. if they are only
	// in memory.
	// Remove them and have he user write them out explicitly
	// with a separate Write processor (can go in same file).
	if(TList *fr = _tree->GetListOfFriends()) {
	    fr->Clear();
	}

    }

    void Write::writeMetaData()
    {
	using namespace std;

	if(!_fileOwner || !_doMetaData) {
	    _parents.clear();
	    _runs.clear();
	    _firstEvent = INT_MAX;
	    _lastEvent  = 0;
	    return;
	}

	check_file();
	out() << "Write[" << name() << "] Writing metadata for: " << _file->GetName() << std::endl;

	const char *pid = getenv("SAM_PROCESSID");

	string processID = pid ? pid : "0";

	string metaFileName(gSystem->BaseName(_file->GetName()));
	metaFileName += ".metadata.py";
	
	ofstream metaFile(metaFileName.c_str());
	
	if (_isMC) {
	  metaFile << 
	    "from SamFile.SamDataFile import SamDataFile\n" 
	    "from SamFile.SamDataFile import SamTime, SamSize, CRC, ApplicationFamily, DataType\n"
	    "from SamFile.SamDataFile import Params, ParamValue\n"
	    "from SamFile.SamDataFile import LumBlockRange, LumBlockRangeList\n"
	    "from SamFile.SamDataFile import RunDescriptor, RunDescriptorList\n"
	    "from SamFile.SamDataFile import NameOrId, NameOrIdList, SamLongList\n"
	    "from SamFile.SamDataFile import CaseInsensitiveDictionary\n"
	    "from SamFile.SamDataFile import DerivedSimulatedFile\n"
	    
	    "TheFile = DerivedSimulatedFile({\n";
	} else {
	  metaFile << 
	    "from SamFile.SamDataFile import SamDataFile\n" 
	    "from SamFile.SamDataFile import SamTime, SamSize, CRC, ApplicationFamily, DataType\n"
	    "from SamFile.SamDataFile import Params, ParamValue\n"
	    "from SamFile.SamDataFile import LumBlockRange, LumBlockRangeList\n"
	    "from SamFile.SamDataFile import RunDescriptor, RunDescriptorList\n"
	    "from SamFile.SamDataFile import NameOrId, NameOrIdList, SamLongList\n"
	    "from SamFile.SamDataFile import CaseInsensitiveDictionary\n"
	    "from SamFile.SamDataFile import DerivedDetectorFile\n"
	    
	    "TheFile = DerivedDetectorFile({\n";
	}

	metaFile << "      'fileName' : '"  << gSystem->BaseName(_file->GetName()) << "',\n"
		 << "      'fileId' : 0L,\n" ;
	if (_isMC)
	  metaFile << "      'fileType' : 'derivedSimulated',\n" ;
	else 
	  metaFile << "      'fileType' : 'derivedDetector',\n" ;

	metaFile << "      'fileFormat' : 'unknown',\n"
		 << "      'fileSize' : SamSize('" << (_file->GetSize() - 1.0)/(1024.0*1024.0) + 1.0 << "MB'),\n"
		 << "      'crc' : CRC('unknown crc value', 'unknown crc type'),\n"
		 << "      'fileContentStatus' : 'good',\n"
		 << "      'eventCount' : " << _tree->GetEntries() << ",\n"
		 << "      'firstEvent' : " << _firstEvent << ",\n"
		 << "      'lastEvent'  : " << _lastEvent << ",\n"
		 << "      'dataTier' : 'root-tree-bygroup',\n"
		 << "      'applicationFamily' : ApplicationFamily('"
		 << _samFamily << "','" 
		 << _samApplication << "','" 
		 << _samVersion << "'),\n"
		 << "      'group' : 'dzero',\n"
		 << "      'processId' : " << processID << "L,\n"
		 << "      'parents' : NameOrIdList([\n";
	for(vector<string>::const_iterator it = _parents.begin();
	    it != _parents.end(); ) {
	    metaFile << "          '" << *it << "'";
	    if(++it != _parents.end()) {
		metaFile << ",\n";
	    }
	}
	metaFile << "]),\n" ;
	
	if (_isMC) {
	  if (_reqids.size()==1) {
	    metaFile << "      'params' : Params({\n" 
		     << "      'global' : CaseInsensitiveDictionary({'requestid' : '"
		     << *(_reqids.begin()) << "'}),\n"
		     << "       }),\n" ;
	  }
	  metaFile << "      'runDescriptorList' : RunDescriptorList(),\n" ;
	} else {
	  metaFile << "      'runDescriptorList' : [\n";
	  
	  for(set<int>::const_iterator it = _runs.begin();
	      it != _runs.end(); ) {
	    metaFile << "           RunDescriptor('physics data taking'," << *it << ")";
	    if(++it != _runs.end()) {
	      metaFile << ",\n";
	    }
	  }       

	  metaFile << "],\n" ;
	}

	metaFile   << "      'datastream' : 'notstreamed',\n"
		   << "   })\n";
	

	metaFile.close();
	_parents.clear();
	_runs.clear();
	_firstEvent = INT_MAX;
	_lastEvent = 0;
	_reqids.clear() ;
    }

    /// Returns true if the branch references a class of some sort that
    /// has a class version different from the one we currently have loaded
    /// in memory.
    bool Write::containsUpdatedClass (TBranch *br)
    {
	TBranchElement *be = dynamic_cast<TBranchElement*>(br);
        if(be == 0) return false;

	int tree_version = be->GetInfo()->GetClassVersion();
	int class_version = TClass::GetClass(be->GetClassName())->GetStreamerInfo()->GetClassVersion();
	if (tree_version < class_version) {
	    return true;
	}

	TIter branchNext (be->GetListOfBranches());
	while (TBranchElement *be = static_cast<TBranchElement*>(branchNext.Next())) {
	    if (containsUpdatedClass(be)) {
		return true;
	    }
	}
	return false;
    }

    void Write::updateBranch(TTree *input_tree, const std::string& branch_name)
    {
	TBranch *br = input_tree->GetBranch(branch_name.c_str());
	assert(br != 0);

	// We want to store this data anyway, so let's load the first
	// entry to set the address of the various objects.
	br->GetEntry(0);

	/// Get the address and use that
	void* obj = br->GetAddress();
	if (obj != 0) {
	    if (std::string(br->GetClassName()) == "TClonesArray") {
		_tree->Branch(branch_name.c_str(), "TClonesArray", obj);
	    } else {
		_tree->Branch(branch_name.c_str(), br->GetClassName(), obj);
	    }
	} // else what ??
    }

    /// This method checks that the file object embedded in _tree matches _file.
    /// If the file objects don't match, crash.
    void Write::check_file()
    {
      if(_fileOwner) {
	assert(_tree);
	assert(_file);
	const TFile* tree_file = _tree->GetCurrentFile();
	if(tree_file != _file || tree_file->GetName() != _oldFileName) {
	  err() << "Write[" << name() << "] File mismatch." << std::endl;
	  err() << "Write[" << name() << "] Write file = " 
		<< _file->GetName() << std::endl;
	  err() << "Write[" << name() << "] TTree file = " 
		<< tree_file->GetName() << std::endl;
	  assert(tree_file == _file && tree_file->GetName() == _oldFileName);
	  abort();
	}
      }
    }

    void Write::copy_file()
    {
	std::ostringstream s;

	if(_destination.find(':') != std::string::npos) {
	    s << "/usr/krb5/bin/kbatch && /usr/krb5/bin/rcp " 
	      << _file->GetName() <<  " "
	      << _destination;
	} else {
	    s << "cp " 
	      << _file->GetName() <<  " "
	      << _destination;
	}
	out() << "Write[" << name() << "] : Copied " << _file->GetName() 
	      << " to " << _destination << std::endl;

	if(system(s.str().c_str()) == 0) {
	    remove(_file->GetName());
	    out() << "Write[" << name() << "] : Removed " << _file->GetName() << std::endl;
	} else {
	    err() << "Write[" << name() << "] : Cannot copy " << _file->GetName() 
		  << "to" << _destination << std::endl;
	}
    }


}

ClassImp(cafe::Write)
