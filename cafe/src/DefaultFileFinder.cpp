///
/// DefaultFileFinder.cpp
///
///  
///
#include "cafe/DefaultFileFinder.hpp"

#include "TSystem.h"

namespace cafe {
    
    /// If argument is null, then use the default setup with is ".", 
    /// $SRT_LOCAL_CONTEXT, and $SRT_PUBLIC_CONTEXT.
    DefaultFileFinder::DefaultFileFinder()
    {
        push_back("./");
        if(const char *priv = getenv("SRT_PRIVATE_CONTEXT")) {
            push_back(priv);
        }
        if(const char *pub = getenv("SRT_PUBLIC_CONTEXT")) {
            push_back(pub);
        }
    }
    
    /// Add a new pattern to the end of the list
    void DefaultFileFinder::push_back (const std::string& location)
    {
        _locations.push_back(location);
    }

    /// Add a new pattern to the end of the list
    void DefaultFileFinder::push_front (const std::string& location)
    {
        _locations.push_front(location);
    }
    
    /// Use the stub given to see if the file can be found. If not,
    /// then return an empty string.
    std::string DefaultFileFinder::findFile (const std::string& base_name) const
    {
        using namespace std;

        // return absolute path names unchanged
        if(!base_name.empty() && base_name[0] == '/') return base_name;

        for(list<string>::const_iterator it = _locations.begin();
            it != _locations.end();
            ++it) {
            string path = (*it) + '/' + base_name;
            if(gSystem->AccessPathName(path.c_str(), kReadPermission) == 0) {
                return path;
            }
        }

	return "";
    }
   
}
