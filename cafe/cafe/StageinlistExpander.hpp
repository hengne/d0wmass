#ifndef CAFESTAGEINLISTEXPANDER_HPP__
#define CAFESTAGEINLISTEXPANDER_HPP__


#include "cafe/Expander.hpp"

#include <string>
#include <fstream>

namespace cafe {

    /**
     *
     * Copy file from remote server to local disk before
     * processing.
     *
     * - .Stager: STAGE_COMMAND       [ default: "cp" ]
     * - .Host:   SERVER_HOSTNAME     [ default: "" ]
     * - .StagingDirectory: DIRECTORY [ default: "." ]
     *
     * For usage on the ClueD0 batch system, use the defaults.
     *
     * For usage on CAB, use "/usr/krb5/bin/kbatch; rcp" for the
     * .Stager: option, and "host-clued0" for the .Host: option.
     *
     * \ingroup cafe
     */

    class StageinlistExpander : public Expander {
    public:
	StageinlistExpander(const char *url);
	~StageinlistExpander();
	virtual std::string nextFile();

    private:
	void clean();
	bool fileExists(const std::string & fileName) const;

	std::string _stageinCommand;
	std::string _stageinDirectory;
	std::string _localFile;
	std::string _host;
	std::ifstream _file;

	ClassDef(StageinlistExpander, 0);
    };
}


#endif
