#ifndef CAFE_DEFAULTFILEFINDER_HPP__
#define CAFE_DEFAULTFILEFINDER_HPP_

#include <string>
#include <list>

namespace cafe {

    /// Find a particular file in a possible list of locations. 
    /// The default locations are ./, ${SRT_PRIVATE_CONTEXT}/ and ${SRT_PUBLIC_CONTEXT}/
    /// You can prepend or append other locations.
    class DefaultFileFinder  {
    public:
	DefaultFileFinder ();
	
	/// Add a new pattern to the end of the list.
	void push_back (const std::string& location);

	/// Add a new pattern to the beginning of the list.
	void push_front (const std::string& location);
	
	/// Use the stub given to see if the file can be found. If not,
	/// then return an empty string. Absolute pathnames are returned
        /// unchanged.
	std::string findFile (const std::string &base_name) const;

    private:
        std::list<std::string> _locations;
    };

}

#endif // CAFE_DEFAULTFILEFINDER_HPP_
