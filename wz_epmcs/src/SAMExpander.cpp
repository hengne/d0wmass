#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "SAMExpander.hpp"

#ifdef __SETUP_SAM__

#include "sam_cpp_api/SamConsumer.hpp"

using namespace sam;

SAMExpander::SAMExpander()
    : _samConsumer(0)
{

    std::string samProject = "NONE";
    if(const char *project = getenv("SAM_PROJECT")) {
        samProject = project;
    }

    std::string samStation = "clued0";
    if(const char *station = getenv("SAM_STATION")) {
        samStation = station;
    }

    std::string workGroup  = "dzero";
    if(const char *workgroup = getenv("SAM_WORKGROUP")) {
      workGroup = workgroup;
    }

    char command[4096];
    sprintf(command, "echo \"from Sam import sam; print sam.translateConstraints(summaryOnly=True, dim=\'snapshot_id %%d\' %% sam.getProjectInfo(project=\'%s\').getSnapshotId()).getFileCount()\" | sampy", samProject.c_str());
    FILE *one_file_protection = popen(command, "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), one_file_protection);
    pclose(one_file_protection);
    int number_of_files = atoi(buffer);
    if (number_of_files< 10) return;

    std::string appName    = "demo";
    std::string appVersion = "1";
    std::string procDesc   = SamConsumer::DefaultConsumerProcessDescription;
    int maxFiles           = static_cast<int>(SamConsumer::UnlimitedNumberOfInputFiles);
    int  timeOut           = SamConsumer::DefaultProjectMasterTimeOut;

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

#else

SAMExpander::SAMExpander()
{

}

SAMExpander::~SAMExpander()
{

}

std::string SAMExpander::nextFile()
{

}

#endif
