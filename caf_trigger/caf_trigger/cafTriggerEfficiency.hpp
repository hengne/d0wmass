//file: cafTriggerEfficiency.hpp {cafTriggerEfficiency.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for cafTriggerEfficiency.cpp

//CAFe include files
#include "cafe/Event.hpp"
#include "cafe/Config.hpp"
#include "cafe/Processor.hpp"
#include "cafe/Variables.hpp"


#include "TH1F.h"
#include "TFile.h"
class TRandom2;

//C++ Objects and interfaces
#include <string>
#include <vector>
#include <map>

#include <stdlib.h>

using namespace cafe;

class cafTriggerEfficiency : public cafe::Processor
{

public:
    cafTriggerEfficiency(const char *name);



// data member to keep track of the last process MC request ID



    void begin();
    void finish();

  void inputFileOpened(TFile *file);
  void inputFileClosing(TFile *file);
  
  bool processEvent(cafe::Event &event);
  
 
  
 
private:
    std::map<std::string, float>    _mapVersionLumi;
    std::map<std::string, float>    _mapVersionLumi1;
    std::map<std::string, float>    _mapVersionLumi2;
    bool                    _dqLumi;
    bool                    _passedToProc;
    bool                    _weightPeriods;
    float                   _lumi_tot;
    TRandom2*               _rand;

    //For the TMBObject branch names
    std::vector<std::string> branchNames;

  //Switch to switch off met branch if you don't need it for your calculations
  bool _met_on;


  unsigned int _reqid ;
  
  //bool for switching on speed ups 
  // the individual switches overide the all switch
  //bool _all_speedups; //switch on all the speed ups
  bool _em_speedups; //switch on just em speed ups
  bool _jet_speedups; //switch on just jet speed ups
  bool _mu_speedups; //switch on just mu speed ups
  bool _met_speedups; //switch on just met speed ups

  //Variables used for speed ups
  cafe::Variables _mu_vars;
  cafe::Variables _em_vars;
  cafe::Variables _jet_vars;
  cafe::Variables _met_vars;

 void change_request(cafe::Event &event);
 ClassDef(cafTriggerEfficiency, 0);
};

