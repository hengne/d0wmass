
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "cafe_sam/SAMExpander.hpp"
#include "cafe/Config.hpp"

#include "sam_cpp_api/SamConsumer.hpp"

namespace cafe {

    using namespace sam;

    SAMExpander::SAMExpander(const char *url)
        : _samConsumer(0)
    {
	Config config("SAM");

	std::string samProject = config.get("Project", "NONE");

        if(const char *project = getenv("SAM_PROJECT")) {
	    samProject = project;
	}

	if(samProject == "NONE") {
	    std::cerr << "SAMExpander: no SAM_PROJECT defined" << std::endl;
	}

	std::string samStation = config.get("Station", "clued0");
	if(const char *station = getenv("SAM_STATION")) {
	    samStation = station;
	}

	std::string appName    = config.get("Application", "demo");
	std::string appVersion = config.get("Version", "1");
	std::string workGroup  = config.get("Workgroup", "dzero");
	std::string procDesc   = config.get("ProcessDescription", SamConsumer::DefaultConsumerProcessDescription);
	int maxFiles = config.get("MaxFiles", static_cast<int>(SamConsumer::UnlimitedNumberOfInputFiles));
	int  timeOut           = config.get("Timeout", SamConsumer::DefaultProjectMasterTimeOut);

	try {
	    _samConsumer = new SamConsumer(samProject,
					   samStation,
					   workGroup,
					   appName,
					   appVersion,
					   procDesc,
					   maxFiles,
					   timeOut);
	    std::stringstream ss;
	    ss << "SAM_PROCESSID=" <<_samConsumer->getConsumerProcessID();
	    static char *pid = strdup(ss.str().c_str());
	    putenv(pid);
 
	} catch (SamConsumer::Exception& ex) {
            std::cerr << "SAMExpander:" << ex.error() << std::endl;
        } catch (std::exception& ex) {
            std::cerr << "SAMExpander: std exception: " << ex.what() << std::endl;
	} catch (...) {
	    std::cerr << "SAMExpander: constructor: unknown exception" << std::endl;
	}
    }

    SAMExpander::~SAMExpander()
    {
        delete _samConsumer;
    }

    std::string SAMExpander::nextFile()
    {
	// couldn't establish consumer, return end of list
	if(_samConsumer == 0) return "";

        try {
	    // if we opened a file before, release it
	    if(_currentFile != "") {
		_samConsumer->releaseFile();
	    }

	    File file = _samConsumer->getFile();
	    _currentFile = file.getFullFileName();
	    return _currentFile;

	} catch(SamConsumer::EndOfFileStreamReached& ) {
	    // ok, no more files
	    return "";
        } catch(SamConsumer::Exception& ex) {
            std::cerr << "SAMExpander:" << ex.error() << std::endl;
        } catch(...) {
	    std::cerr << "SAMExpander: caught unknown exception" << std::endl;
        }

        return "";
    }
}

ClassImp(cafe::SAMExpander);
