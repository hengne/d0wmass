
///////////////////////////////
// Main Program
///////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>  //atoi
#include <unistd.h>  //getopt
#include "pmcsana.h"
#include "TChain.h"
#ifdef __USE_PDFS__
#include "LHAPDF/LHAPDF.h"
#endif
#include "SAMExpander.hpp"

bool GetNextFile(TString& filename, bool sam, SAMExpander* expander, ifstream& in){
  if(sam) {
    filename=expander->nextFile();    
    std::cout << "Retrieved file " << filename << " from SAM." << std::endl;
    if (filename=="") {
      return false;
    } else {
      return true;
    }
  } else {
    in >> filename;
    std::cout << "Retrieved file " << filename << " from local disk." << std::endl;
    if (in.eof()) {
      return false;
    } else {
      return true;
    }
  }
}

int main(int argc, char** argv) {

  //RCLSA: Modifications to use SAM properly
  //       Creates a SAMExpander
  bool fUseSam = true;  
  int fChainPoint, fTreePoint;

#ifdef __USE_PDFS__
  LHAPDF::setVerbosity( LHAPDF::LOWKEY); // or SILENT, for no banner at all
#endif
  //command line parameter defaults
  int runevt,skipevt;
  int nevt = 0;
  int runoption = -1;  //0 for Zee events, 1 for Wenu events, 2 for Zmumu events, 3 for JPsiMumu events
  int r = 0;  //random seed
  int s = 0;  //skip first s events

  TString filelist("file.list");
  TString parameterfile("parameters.rc");
  TString outputfile;  //if not set, the value in the parameters file is used

  TChain ch("Global");

  //parse command line
  int c;
  while( (c=getopt(argc,argv,"hn:f:c:t:r:s:")) != -1 ){
    switch(c){
    case 'h':
      std::cout << "Usage: " << argv[0] << 
	" [-h] [-f <input_filename>] [-n <number_of_events>] [-s <number of events to skip] [-c parameter_file] " << 
	"[-t 0(for Zee)/1(for Wenu)/2(for Zmumu)/3(for JPsiMumu)/4(for ZNuNu) events] [-r random_seed]" 
		<< std::endl;
      exit(0);
      break;
    case 'n':
      nevt = atoi(optarg);
      if (nevt < 0) nevt = 0;
      break;
    case 'f':
      filelist = TString(optarg);
      if( !filelist.Contains("sam:") )
        fUseSam = false;
      break;
    case 'c':
      parameterfile = TString(optarg);
      break;
    case 't':
      runoption = atoi(optarg);
      break;
    case 'r':
      r = atoi(optarg);
      break;
    case 's':
      s = atoi(optarg);
      if (s < 0) s = 0;
      break;
    }
  }
  
  std::cout << "===========================================" << "\n"
            << "           Reading Files                   " << "\n"
            << "===========================================" << std::endl;

  SAMExpander* fSAMExpander;
  TString input_roottuple;
  pmcsana *sel = new pmcsana;

  sel->setParameterFileName(parameterfile.Data());
  sel->setOutputRootFileName(outputfile.Data());
  sel->setRunOption(runoption);
  sel->setRandomSeed(r);
  sel->Initialize();

  ifstream fin;
  if(fUseSam) {
    std::cout << "Using SAM" << std::endl;
    fSAMExpander = new SAMExpander();
  } else {
    std::cout << "Using filelist " << filelist.Data() << std::endl; 
    fin.open(filelist.Data());
  }
  Int_t sum=0;
  int cummulative_total = 0;

  while(GetNextFile(input_roottuple,fUseSam,fSAMExpander,fin)) {
    
    TFile *newROOTFile= new TFile(input_roottuple);
    TTree *SelEventROOTTree = (TTree *)newROOTFile->Get("Global");
    
    if(!SelEventROOTTree){
      std::cout << "Can not open ROOT file: " << input_roottuple << std::endl;
    } else {
      std::cout << "File: " << input_roottuple << ", Entries = " << SelEventROOTTree->GetEntries() << std::endl;
      fTreePoint = SelEventROOTTree->GetEntries();
      fChainPoint = ch.GetEntries();
      ch.Add(input_roottuple);
      sum++;
    }

    delete SelEventROOTTree;
    delete newROOTFile;

    std::cout << "===========================================" << "\n"
              << "           Analyzing  File " << input_roottuple << "\n"
              << "===========================================" << std::endl;

    if(runoption == -1) {
      std::cout<<"Please tell me which process you want to run: "<<"\n"
               <<"   -t 0 for Z->ee events, -t 1 for W->e nu events, "<<"\n"
               <<"   -t 2 for Z->mumu and -t 3 for JPsi->mumu -t 4 for Z->nunu"<<std::endl;
      std::cout<<"You can use \"./run_pmcs -h\" to find more options"<<std::endl;
    } else {
      std::cout << nevt << " " << s << " " << fTreePoint << " " << runevt << " " << skipevt << std::endl;
      skipevt=0;      
      runevt=0;      
      if (nevt == 0) {  
        runevt = fTreePoint;
      } else if (nevt > fTreePoint) {
        nevt -= fTreePoint;        
        runevt = fTreePoint;      
      } else {        
        runevt = nevt;  
        nevt = -1;
      }
      cummulative_total += runevt;

      if (s > runevt) {
        skipevt += runevt;
        s -= runevt;
      } else {
        skipevt += s;
        s = 0;
      }

      skipevt += fChainPoint;      

      std::cout << nevt << " " << s << " " << fTreePoint << " " << runevt << " " << skipevt << std::endl;
      
      std::cout << "===========================================" << "\n"                
                << "      Running " << runevt << " events from " << input_roottuple << "\n"             
                << "===========================================" << std::endl;            

      sel->setNumEvents(cummulative_total);
      ch.Process(sel, "", runevt, skipevt);
      fChainPoint+=fTreePoint;
      if (nevt < 0) {
        break;
      }
    }
  }
  sel->WriteOut();
  
  // Forces termination
  pid_t pid = getpid();
  TString command;
  command.Form("kill %i", (int)pid);
  system(command.Data());
  return EXIT_SUCCESS;
}

#include "LHAPDF/FortranWrappers.h"
#ifdef FC_DUMMY_MAIN
int FC_DUMMY_MAIN() { return 1; }
#endif



