#ifndef CAFE_CONTROLLER_HPP__
#define CAFE_CONTROLLER_HPP__

#include <list>
#include "cafe/Processor.hpp"

class TFile;

namespace cafe {

    class Event;

    /**
     * Common base class for Controllers, i.e. Processors
     * that have children. This is intended as an internal
     * base class. As a user prefer 'Group' instead.
     *
     * - if '.Output:' is specified, the Controller will open
     * a new output file with the given name.
     *
     * - if '.Directory:' is specified, the Controller will
     * create a new subdirectory in the current directory/file.
     *
     * Configuration options:
     *
     * - .Run:       ProcessorList    [default: ""]
     * - .Output:    OutputFilename   [default: ""]
     * - .Directory: DirectoryName    [default: ""]
     * - .Debug:     DebugLevel       [default: 0]
     *
     * - .Tag: Tag1 Tag2.... [ default: none ]. 
     *    Tag event before invoking the first processor.
     * - .Untag: Tag1 Tag2.... [ default: none ]. 
     *    Remove tags from event before invoking the first processor.
     *                      
     *
     * \ingroup cafe
     */
    class Controller : public Processor {
    public:
        Controller(const char *name);
        Controller(const char *name, const std::list<cafe::Processor*>& procs);
        ~Controller();

	/// @name Processor interface
	/// Calls the corresponding method for every child.
        //@{
        virtual void begin();
        virtual void finish();
        virtual void inputFileOpened(TFile *file);
        virtual void inputFileClosing(TFile *file);
        virtual bool processEvent(Event& event);
	//@}

	virtual void setDebug(unsigned int level);

        /// Add the named Processor to this Controller
        bool add(const std::string& name, const std::string& instance = "");

        /// Add Processor object directly to Controller
        bool add(Processor *proc);

        /// Add function directly to Controller
        bool add(bool (*func)(Event&), const std::string& instance);

    protected:
	/// Only used by subclasses: set the list of children
        bool add(const std::list<Processor*>& procs);

    protected:
        std::list<Processor*> _processors;
	std::vector<std::string> _untag;
	std::vector<std::string> _tag;

    private:
        TFile *_outfile;

    public:
        ClassDef(Controller, 0);
    };

}

#endif // CAFE_CONTROLLER_HPP__
