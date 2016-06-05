
#include "cafe/FilePattern.hpp"

#include "TSystem.h"
#include "TUUID.h"
#include "TDatime.h"

#include <iomanip>
#include <sstream>

namespace cafe {


    FilePattern::FilePattern(const std::string& pattern)
        : _pattern(pattern),
          _counter(0)
    {
    }

    FilePattern::FilePattern()
        : _pattern(""),
          _counter(0)
    {}

    void FilePattern::set(const std::string& pattern)
    {
        _pattern = pattern;
    }
    
    std::string FilePattern::replace(const std::string& input)
    {
	using namespace std;

        std::string new_name = _pattern;
        std::string::size_type next = 0;
        std::string::size_type pos = 0;
        while((pos = new_name.find('%', next)) != std::string::npos) {

            // assert(new_name.size() > pos);

            std::string input_name = input;

            switch(new_name[pos+1]) {
            case 'f':
                new_name.replace(pos, 2, gSystem->BaseName((char *)input_name.c_str()));
                break;
            case 'd':
                new_name.replace(pos, 2, gSystem->DirName((char *)input_name.c_str()));
                break;
            case 'r':
                {
                    std::string base = gSystem->BaseName((char *)input_name.c_str());
                    base.erase(base.rfind('.'));
                    new_name.replace(pos, 2, base);
                }
                break;
            case 'n':
                {
                    std::ostringstream os;
                    os << _counter++;
                    new_name.replace(pos, 2, os.str());
                }
                break;
	    case 'D':
		{
		    TDatime date;
		    std::ostringstream os;
		    os << setw(2) << setfill('0') << date.GetDay()
		       << setw(2) << setfill('0') << date.GetMonth()
		       << setw(4) << setfill('0') << date.GetYear();
		    new_name.replace(pos, 2, os.str());
		}
		break;
	    case 'T':
		{
		    TDatime date;
		    std::ostringstream os;
		    os << setw(2) << setfill('0') << date.GetHour()
		       << setw(2) << setfill('0') << date.GetMinute()
		       << setw(2) << setfill('0') << date.GetSecond();
		    new_name.replace(pos, 2, os.str());
		}
		break;
	    case 'j':
		if(const char *pbs = getenv("PBS_JOBID")) {
		    new_name.replace(pos, 2, pbs);
		    break;
		}
		// fall through
	    case 'u':
		{
		    TUUID uuid;
		    new_name.replace(pos, 2, uuid.AsString());
		}
		break;
            default:
                pos++;
                break;
            }

            next = pos;
        }

        return new_name;

    }
    
}

