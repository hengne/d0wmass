
#include "cafe/Friend.hpp"
#include "cafe/Config.hpp"

#include <iostream>
#include "TFile.h"
#include "TTree.h"


namespace cafe {

    Friend::Friend(const char *name)
        : Processor(name)
    {
        Config config(name);
        _fileName = config.get("File", "");
        _treeName = config.get("Tree", "");
        if(_fileName.size() > 0) {
            _pattern = _fileName;
        }
    }

    void Friend::inputFileOpened(TFile *file)
    {
        using namespace std;

        if(_fileName.size() == 0 || _treeName.size() == 0) return;

        std::string new_name = _pattern.replace(file->GetName());

        out() << "Friend[" << name() << "] Adding " 
              << _treeName << " from file: " 
              << new_name  << std::endl;

        if(TTree *tree = static_cast<TTree*>(file->Get("TMBTree"))) {
            tree->AddFriend(_treeName.c_str(), new_name.c_str());
        }
        
    }

}
