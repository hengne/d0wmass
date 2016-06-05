#ifndef CAFE_FRIEND_HPP__
#define CAFE_FRIEND_HPP__

#include <string>
#include "cafe/Processor.hpp"
#include "cafe/FilePattern.hpp"

namespace cafe {

    /**
     * Open a file and add a friend tree to the current input tree.
     *
     * Configuration Options:
     *
     * - .File:  NameOfFileToOpen (see FilePattern)
     * - .Tree:  NameOfTreeToAdd
     *
     * \ingroup cafe
     */
    class Friend : public Processor {
    public:
        Friend(const char *name);
        void inputFileOpened(TFile *file);
    private:
        std::string  _fileName;
        std::string  _treeName;
        FilePattern  _pattern;
    public:
        ClassDef(Friend, 0);
    };
    
}

#endif // CAFE_FRIEND_HPP__
