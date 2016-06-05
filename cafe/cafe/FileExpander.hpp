#ifndef CAFE_FILEEXPANDER_HPP__
#define CAFE_FILEEXPANDER_HPP__

#include "cafe/Expander.hpp"

namespace cafe {

    /**
     * Expands a single file:/path/to/file.root specification.
     *
     * Used internally by cafe.
     *
     * \ingroup cafe
     */
    class FileExpander : public Expander {
    public:
        FileExpander(const char *url);
        virtual std::string nextFile();
    private:
        std::string _url;

        ClassDef(FileExpander, 0);
    };
}

#endif // CAFE_FILEEXPANDER_HPP__
