
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>

#include "cafe_sam/SAMGridExpander.hpp"
#include "cafe/Config.hpp"

//#include "sam_client_cpplib/SamConsumer.hpp"

namespace cafe {

//    using namespace sam;

    SAMGridExpander::SAMGridExpander(const char *url)
//        : _samConsumer(0)
    {
	Config config("SAM");

	_samProject = config.get("Project", "NONE");
        if(const char *project = getenv("SAM_PROJECT")) {
	    _samProject = project;
	}

	if(_samProject == "NONE") {
	    std::cerr << "SAMGridExpander: no SAM_PROJECT defined" << std::endl;
	}

	_samStation = config.get("Station", "clued0");
	if(const char *station = getenv("SAM_STATION")) {
	    _samStation = station;
	}

	std::string samHost = config.get("Host", "NONE");
	if(const char *host = getenv("SAM_HOST_NAME")) {
	    samHost = host;
	}
        _samHost = samHost;
	if(!_samHost.empty()) {
	    _samHost += ':';
	}
	std::cout << "Host name is " << _samHost << std::endl;

	std::string appName    = config.get("Application", "demo");
	std::string appVersion = config.get("Version", "1");
	std::string workGroup  = config.get("Workgroup", "dzero");
	//int  timeOut           = config.get("Timeout", SamConsumer::DefaultProjectMasterTimeOut);

	_samcmdout = "samcmd.out";
	
        _samConsumerOK = true;
        // ... Establish a consumer and obtain the consumer ID
        _samcmd = "sam establish consumer --appname="+appName+" --appversion="
                  +appVersion+" --project="+_samProject+" --station="+_samStation
                  +" --group="+workGroup;
        _cmd = "echo `"+_samcmd+"` | grep CID | cut -f2 -d' ' > samcmd.out";
	_ok = system(_cmd.c_str());
	if(_ok!=0){
          _samConsumerOK = false;
	  std::string msg("SAMGridExpander: failed to establish consumer");
	  throw std::runtime_error(msg);
	}
        _fin.open(_samcmdout.c_str());
        _fin>>_cid;
        _fin.close();
	std::cout << " ... SAMGridExpander: successfully established consumer with CID: " << _cid << std::endl;
        
        // ... Now establish a consumer process with the CID from previous step
        _samcmd = "sam establish process --project="+_samProject
                  +" --station="+_samStation+" --cid="+_cid+" --nodeName="+samHost;
        _cmd = "echo `"+_samcmd+"` | grep CPID | cut -f2 -d' ' > samcmd.out";
	_ok = system(_cmd.c_str());
	if(_ok!=0){
          _samConsumerOK = false;
	  std::string msg("SAMGridExpander: failed to establish consumer process");
	  throw std::runtime_error(msg);
	}
        _fin.open(_samcmdout.c_str());
        _fin>>_cpid;
        _fin.close();
        
        _samcpid="SAM_PROCESSID="+_cpid;
        static char *pid = strdup(_samcpid.c_str());
        putenv(pid);
	std::cout << " ... SAMGridExpander: successfully established consumer process with CPID: "
	          << _cpid << std::endl;
    }

    SAMGridExpander::~SAMGridExpander()
    {
        clean();
        //delete _samConsumer;
    }

    bool SAMGridExpander::fileExists(const std::string& fileName) const
    {
        // inspired from io_packages/RemoteFileExpander
        std::ifstream file(fileName.c_str());
        bool result = file.good() && file.is_open();
        return result;
    }

    void SAMGridExpander::clean()
    {
        if ( _localFile.size() > 0 && fileExists(_localFile) ) std::remove(_localFile.c_str());
        _localFile = "";
    }

    std::string SAMGridExpander::nextFile()
    {
	// ... couldn't establish consumer, return end of list
	std::cout << " ... SAMGridExpander: attempting to get the next file" << std::endl;
	if(!_samConsumerOK) return "";
	clean();
	
	// ... if we opened a file before, release it
	if(_currentFile != "") {
            _samcmd = "sam release --file="+_currentFile+" --cpid="+_cpid+" --project="
                      +_samProject+" --station="+_samStation+" --status=ok";
            _ok = system(_samcmd.c_str());
            if(_ok!=0){
                std::string msg("SAMGridExpander: failed to release file");
                throw std::runtime_error(msg);
            }
	}

        // ... now get the next file
        _samcmd = "sam get next file --cpid="+_cpid+" --project="
                  +_samProject+" --station="+_samStation;
        _cmd = "echo `"+_samcmd+"` | grep File | cut -f2-4 -d' ' > samcmd.out";
        _ok = system(_cmd.c_str());
        if(_ok!=0){
            std::string msg("SAMGridExpander: failed to get next file");
            throw std::runtime_error(msg);
        }
        _fin.open(_samcmdout.c_str());
	getline(_fin,_currentFile);
        _fin.close();
        if(_currentFile=="END OF STREAM"){
            std::cout << " ... SAMGridExpander: no more files left to process " << std::endl;
            return "";
        }
	// ... make sure host name not included in full path                
	std::string::size_type loc = _currentFile.find(':');
	std::string filePath = "";
	if(loc!=std::string::npos) {
	  filePath = _currentFile.substr(loc+1);
	} else {
	  filePath = _currentFile;
	}
	_remoteFile = _samHost + filePath;

	// ... strip off the file name
	loc = filePath.rfind('/');
	if(loc!=std::string::npos) {
	  loc++;
	} else {
	  loc = 0;
	}
	_localFile = filePath.substr(loc); 
	//std::cout << "_currentFile: " << _currentFile << std::endl;
	//std::cout << "filePath: "     << filePath << std::endl;
	//std::cout << "_remoteFile: "  << _remoteFile << std::endl;
	//std::cout << "_localFile: "   << _localFile << std::endl;
	  
	// ... construct the samcp command  
	_samcmd = "samcp";
	_cmd = _samcmd + ' ' + _remoteFile + ' ' + _localFile; 
	std::cout << "Command is: " << _cmd << std::endl;
	
	int ok = system(_cmd.c_str());
	if(ok!=0 || !fileExists(_localFile)){
	  clean();
	  std::string msg("SAMGridExpander: cannot find ");
	  msg+=_localFile;
	  throw std::runtime_error(msg);
	}

	return _localFile;
    }
}

ClassImp(cafe::SAMGridExpander);
