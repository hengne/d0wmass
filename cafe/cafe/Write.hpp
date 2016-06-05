#ifndef CAFE_WRITE_HPP__
#define CAFE_WRITE_HPP__

#include "cafe/Processor.hpp"
#include "cafe/FilePattern.hpp"
#include "cafe/Variables.hpp"

#include <string>
#include <vector>
#include <set>

class TFile;
class TTree;
class TBranch;

namespace cafe {

    /**
     * Write selected branches for each event into a new
     * output file.
     *
     * Configuration options:
     *
     * - .File:     FileNamePattern [required] (see FilePattern.hpp)
     * - .Tree:     NameOfTree      [default: "TMBTree"]
     * - .Branches: ListOfBranches  [default: "*"] 
     *   .Enable:   ListOfBranches  [default: "*"]  - same as .Branches:
     *   OR
     * - .Disable:  ListOfBranches  [default: ""]
     * - .AutoSave: NumEvents       [default: -1 (no autosave)]
     * - .Destination: [Host:]Path  [default: ""; copy output file after closing to this path]
     * - .FilesPerOutput: NumFiles  [default: 0, i.e. all files if no pattern specified ]
     * - .RootMaxTreeSize: Bytes    [default: root decides.  Uses root methods 
     *                               TTree::{Get|Set}MaxTreeSize.  Global effect on all trees.]
     * - .MaxEventsPerFile: Events  [default: 0 (no limit).]
     * - .MaxBytesPerFile: Bytes    [default: 0 (no limit).]
     * - .UpdateObjectVersion:      [default: 1] - Objects that have a new version number in 
     *                               memory are written out to the file in that new version 
     *                               instead of the file version.
     *
     * To create SAM metadata output, the following options have to be all set:
     *
     * - SAM.Application: Name 
     * - SAM.Version:     Version
     * - SAM.Family:      Name
     *
     * \ingroup cafe
     */

    class Write : public Processor {
    public:
	Write(const char *name);
	~Write();

	// Processor interface
	void finish();
	bool processEvent(Event& event);
        void inputFileOpened(TFile *file) {inputFileOpened(file, false);}
	void inputFileOpened(TFile *file, bool force);
    private:
	void check_file();
	void copy_file();
	void writeMetaData();

	std::string              _treeName;
	std::string              _oldFileName;
	std::vector<std::string> _branches;
	std::vector<std::string> _disable;
	TFile       *_input_file;
	TFile       *_file;
	TTree       *_tree;
	FilePattern _pattern;
	Long64_t    _autosave;
	bool        _fileOwner;
	std::string _destination;
	unsigned int _filesPerOutput;
	unsigned int _filesPerOutputDone;
	Long64_t _rootMaxTreeSize;
	unsigned int _maxEventsPerFile;
	unsigned int _maxBytesPerFile;

	/// SAM parameters

	/// SAM.Family: 
	std::string  _samFamily;
	/// SAM.Application:
	std::string  _samApplication;
	/// SAM.Version: 
	std::string  _samVersion;

	bool  _doMetaData;
        bool _isMC ;

	/// List of parent files
	std::vector<std::string> _parents;
	/// List of runs
	std::set<int> _runs;
	/// Lowest event no
	int _firstEvent;
	/// Highest event no
	int _lastEvent;
        /// List of reqids for MC
        std::set<unsigned int> _reqids;
 
	/// To read event number and run.
	Variables _vars;

	/// Should we re-write branches that contain new versions of objects.
	bool         _updateObjectVersion; 

	/// List of top level branch names that need updating.
	std::vector<std::string> _updatedBranches;
        std::vector<TBranch*> _updatedBranchesPointers;

	/// Does the branch contain a class version to update ?
	bool containsUpdatedClass (TBranch *br);

	/// Update the current output tree with a new version
	/// of this branch.
	void updateBranch(TTree *input_tree, const std::string& branch_name);

    public:
	ClassDef(Write,0);
    };

}

#endif // CAFE_WRITE_HPP__
