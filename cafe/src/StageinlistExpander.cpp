#include "cafe/StageinlistExpander.hpp"
#include "cafe/Config.hpp"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>

namespace cafe {

    StageinlistExpander::StageinlistExpander(const char *url): _localFile("")
    {
	Config config("cafe");

	_stageinCommand = config.get("Stager","cp");
	_stageinDirectory = config.get("StagingDirectory",".");
	_host             = config.get("Host","");
	if(!_host.empty()) {
	    _host += ':';
	}

	const char *ptr = strchr(url, ':') + 1;
	_file.open(ptr);
	if(!_file) {
	    throw std::runtime_error(std::string("StageinlistExpander: cannot find ") + url);
	}
    }

    StageinlistExpander::~StageinlistExpander()
    {
	clean();
	_file.close();
    }

    bool StageinlistExpander::fileExists(const std::string& fileName) const
    {
	// inspired from io_packages/RemoteFileExpander 
	std::ifstream file(fileName.c_str());
	bool result = file.good() && file.is_open();
	return result;
    }

    void StageinlistExpander::clean()
    {
	if ( _localFile.size() > 0 && fileExists(_localFile) ) std::remove(_localFile.c_str());
	_localFile = "";
    }

    std::string StageinlistExpander::nextFile()
    {
	using namespace std;
	clean();

	string url = "";
	if ( _file && _file >> url ) {

	    string::size_type n = url.find(':');
	    string remote_path = "";
	    if (n != string::npos ) remote_path = url.substr(n+1);
	    else remote_path = url;
	    assert(remote_path.size() > 0);
	    string::size_type m = remote_path.rfind('/');
	    if(m < string::npos) {
		++m;
	    } else {
		m = 0;
	    }
	    _localFile = _stageinDirectory + '/' + remote_path.substr(m);

	    if ( fileExists(_localFile) ) std::remove(_localFile.c_str());
	    std::string cmd = _stageinCommand + ' ' + _host + url + ' ' + _localFile;
	    std::cout << cmd << std::endl;

	    int ok = system(cmd.c_str());
	    if ( ok != 0 || !fileExists(_localFile)) {
		clean();
		std::string msg("StageinlistExpander: cannot find ");
		msg+=_localFile;
		throw std::runtime_error(msg);
	    }
	}

	return _localFile;
    }
}

ClassImp(cafe::StageinlistExpander);
