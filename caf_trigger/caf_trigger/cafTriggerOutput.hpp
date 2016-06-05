//file: cafTriggerOutput.hpp {cafTriggerOutput.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for cafTriggerOutput.cpp

//CAFe include files
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Processor.hpp"

#include "TH1F.h"
#include "TFile.h"
#include "TLorentzVector.h"

//C++ Objects and interfaces
#include <string>
#include <vector>
#include <map>

#include <stdlib.h>

class TH1F;

using namespace cafe;

class cafTriggerOutput : public cafe::Processor
{
public:
    cafTriggerOutput(const char *name);

    void begin();
    void finish();

    void inputFileOpened(TFile *file);
    void inputFileClosing(TFile *file);

    bool processEvent(cafe::Event &event);

    ClassDef(cafTriggerOutput, 0);
private:
    std::vector<std::string>        _branchNames;
    std::map<std::string, float>    _mapVersionLumi;
    bool                            _passedToProc;

    std::map<std::string, double>   _wsum;
    std::map<std::string, int>      _wint;

    bool    _histosCheck;
    int     _histosBins;
    bool    _debug;

    std::vector<std::string>        _histosString;
    std::vector<std::string>        _trigList;

    std::string                     _globalWeightKey;

    std::map<std::string, TH1*>     _evtwChanVer_h;
    
};
