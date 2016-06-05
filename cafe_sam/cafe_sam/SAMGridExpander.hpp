#ifndef CAFE_SAMGRIDEXPANDER_HPP__
#define CAFE_SAMGRIDEXPANDER_HPP__

#include "cafe/Expander.hpp"
#include <fstream>

//namespace sam {
//    class SamConsumer;
//}

namespace cafe {

    /**
     * Expand file names from a SAM dataset
     * definition. This only works inside
     * a running SAM project.
     *
     * This is used internally to expand a SAM definition
     * into a list of file names.
     *
     * \ingroup cafe
     */
    class SAMGridExpander : public Expander {
    public:
        SAMGridExpander(const char *url);
        ~SAMGridExpander();
        std::string nextFile();
    private:
	void clean();
	bool fileExists(const std::string & fileName) const;
        
        //sam::SamConsumer *_samConsumer;
	std::string       _samProject;
	std::string       _samStation;
	std::string       _samHost;
	std::string       _currentFile;
	std::string       _remoteFile;
	std::string       _localFile;
        std::string       _samcmdout;
        std::string       _samcmd;
        std::string       _cmd;
        std::string       _pid;
	std::string       _cid;
        std::string       _cpid;
        std::string       _samcpid;
        int _ok;
        bool _samConsumerOK;
        std::ifstream _fin;
    public:
        ClassDef(SAMGridExpander, 0);
    };
}

#endif // CAFE_SAMGRIDEXPANDER_HPP__
