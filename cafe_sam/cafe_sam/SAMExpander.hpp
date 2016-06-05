#ifndef CAFE_SAMEXPANDER_HPP__
#define CAFE_SAMEXPANDER_HPP__

#include "cafe/Expander.hpp"

namespace sam {
    class SamConsumer;
}

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
    class SAMExpander : public Expander {
    public:
        SAMExpander(const char *url);
        ~SAMExpander();
        std::string nextFile();
    private:
        sam::SamConsumer *_samConsumer;
	std::string       _currentFile;
    public:
        ClassDef(SAMExpander, 0);
    };
}

#endif // CAFE_SAMEXPANDER_HPP__
