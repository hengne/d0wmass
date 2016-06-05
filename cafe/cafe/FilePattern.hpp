#ifndef CAFE_FILEPATTERN_HPP__
#define CAFE_FILEPATTERN_HPP__

#include <string>

namespace cafe {

    /**
     * Expand a % pattern in a file name, given another
     * filename as input.
     *
     * - replace \%f with original base file name (i.e. without directory part)
     * - replace \%r with original base file withouth suffix and directory
     * - replace \%d with original directory name (without file name)
     * - replace \%n with incrementing counter (starting with 0)
     * - replace \%T with current time (HHMMSS)
     * - replace \%D with current data (DDMMYYYY)
     * - replace \%j with the value of ${PBS_JOBID} if available, else same as \%u
     * - replace \%u with a 128-bit UUID string (see TUUID.h)
     *
     * Examples:
     *
     * %d/myvars/%s-myvariables.root
     * myfile-%n.root
     * 
     * \ingroup cafe
     *
     */

    class FilePattern {
    public:
        FilePattern();
        FilePattern(const std::string& pattern);
        void set(const std::string& pattern);
        std::string replace(const std::string& input);
    private:
        std::string  _pattern;
        unsigned int _counter;
    };
    
}

#endif // CAFE_FILEPATTERN_HPP__
