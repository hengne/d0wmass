#ifndef CAFE_RUNCONTROLLER_HPP__
#define CAFE_RUNCONTROLLER_HPP__

#include <string>
#include <set>
#include "cafe/Controller.hpp"

class TTree;
class TFile;

namespace cafe {

    class Processor;

    /**
     * A special version of a Controller.
     *
     * This opens the input files and loops over the events.
     *
     * Input specifications can be of the form:
     *
     * -  file:pathname/to/file
     * -  listfile:pathname/to/listfile
     * -  sam:datadefinition
     *
     * and any other root prefix (rootd:, rootk:, http:, rfio:, dcache:)
     *
     * If '.Events' is greater than 0, only that many events will be processed.
     *
     * Configuration options:
     *
     * - .Input:    InputSpecification (see above) [default: file:input.root]
     * - .Events:   MaxEvents [default: 0, i.e. no limit]
     * - .Files:    MaxFiles  [default: 0, i.e. no limit]
     * - .Skip:     NumEvents [default: 0]
     * - .SkipFiles: NumFiles [default: 0]
     * - .Progress: Number (print progress after 'Number' events)
     * - .EventList: Filename [ default: "", no event list ]
     * - .PartialReads: false | true [ default: false, don't allow partial reads of objects]
     * - .RootDebug: DebugLevel [ default: 0 ]
     * - .TreeDebug: DebugLevel [ default: 0 ]
     * - .TreeName:  Name [ default: "TMBTree", use non-standard tree ]
     * - .Friends:   NameList [ default: "", list of friend trees to add ]
     * - .LoadAll:   0|1      [ default: 0, force load of whole event ]
     *
     * @see Controller 
     *
     * \ingroup cafe
     */
    class RunController : public Controller {
    public:
        RunController(const char *name);
        ~RunController();
        
        void processTree(TTree *tree, Event& event);
        bool Run(unsigned int max_events = 0);
    private:
        std::string              _input;
        unsigned int             _num_events;
        unsigned int             _max_events;   
	unsigned int             _max_files;
	unsigned int             _num_files;
	unsigned int             _progress;
	int                      _skip;
        int                      _skip_files;
	std::set<std::string>    _friends;
	bool                     _partialReads;
	int                      _rootDebug;
	int                      _treeDebug;
	bool                     _loadAll;
	TFile                    *_eventList;
	std::string              _treeName;
    public:
        ClassDef(RunController, 0);
    };
}

#endif // CAFE_RUNCONTROLLER_HPP__
