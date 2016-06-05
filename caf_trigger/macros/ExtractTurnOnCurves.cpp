#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TSystem.h"
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int main()
{
  std::ifstream infile("fit.txt");

  std::string line;
  double _pi = 3.1415;

  while (getline(infile, line)) {
    std::istringstream info_line(line);
    
    std::string version;
    std::string level;
    std::string type;
    std::string trigger;
    std::string function;
    double ipar,ierrpar;
    std::vector<double> par;
    std::vector<double> errpar;
    info_line >> version;
    info_line >> level;
    info_line >> type;
    info_line >> trigger;
    info_line >> function;
    while (!info_line.eof()) {
      info_line >> ipar;
      par.push_back(ipar);
      info_line >> ierrpar;
      errpar.push_back(ierrpar);
    }

    // Output to screen which turnon is being done.
    std::cout << version << " " << level << " " << type << " " << trigger << " " << function << std::endl;



    //----------------------------------------------------------------
    //
    // Jets
    //
    //----------------------------------------------------------------
    if (type=="JET") {
      //std::string effname = "eff_ptturn_" + level;
      std::string effname = "jetid_"+level;	    
      std::string objtype = "Jet";
      int version_int; 
      int runhigh;
      int runlow;
      if (version=="v13") {
	version_int = 13;
	runhigh = 209104;
	runlow = 194598;
      }
      if (version=="v12") {
	version_int = 12;
	runhigh = 194597;
	runlow = 178722;
      }
      if (version=="v11") {
	version_int = 11;
	runhigh = 178721;
	runlow = 174807;
      }
      if (version=="v10") {
	version_int = 10;
	runhigh = 174807;
	runlow = 170247;
      }
      if (version=="v9") {
	version_int = 9;
	runhigh = 170247;
	runlow = 167016;
      }
      if (version=="v8") {
	version_int = 8;
	runhigh = 167015;
	runlow = 160582;
      }

      // Now for some string manipulation
      typedef std::string::size_type string_size;
      string_size i = 0;
      int index1 = 0;
      int index2 = 0;
      int index3 = 0;
      for (i=0; i<trigger.size(); ++i) {
	if (trigger[i]=='(') index1=i;
	if (trigger[i]==',') index2=i;
	if (trigger[i]==')') index3=i;
      }
      std::string trigger_name = trigger.substr(0,index1) + "_" 
	+ trigger.substr(index1+1,index2-index1-1) + "_" 
	+ trigger.substr(index2+1,index3-index2-1);

      //std::string filename = effname+"_1D_Binned_jet_"+version+"_CC_"+trigger_name+".spc";
      std::string effname1 = effname+trigger_name+"_CC_"+version;
      std::string filename1 = effname1+"_"+objtype+"_matched"+"_1D_pt_Binned.spc";     
      std::ofstream outfile(filename1.c_str());
      outfile << "EffName : " << effname1 << std::endl;
      outfile << "EffType : Binned" << std::endl;
      outfile << "EffVarNames : pt" << std::endl;
      outfile << "EffVersion : " << version_int << std::endl; 
      outfile << "ObjQuality :  matched" << std::endl;
      outfile << "ObjType : " << objtype << std::endl;
      outfile << "ObjVersion : -1 " << std::endl;
      outfile << "ObjFunction : " << function << std::endl;
      outfile << "ObjTrigger : " << trigger << std::endl;
//       outfile << "RunRangeHigh : " << runhigh << std::endl;
//       outfile << "RunRangeLow : " << runlow << std::endl;
      outfile << "BinEdgesX : ";
      for (int i=0; i<100; i++) outfile << i << " ";
      outfile << "2000" << std::endl;
      if (function=="f3") {
	for (int i=0; i<100; i++) {
	  //	  double bin_center = 2000;
	  double bin_center = i;
	  double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	  double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));
	  outfile << "BinVal : " << bin_center << " " << fitval << " " << errpar[2] << " " << errpar[2] << std::endl;
	}
	//fix that nasty bin edge problem
	double bin_center = 2000;		
	double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));
	outfile << "BinVal : " << "100" << " " << fitval << " " << errpar[2] << " " << errpar[2] << std::endl;
      } 
      
      //std::string filename2 = effname + "_1D_Binned_jet_"+version+"_EC_"+trigger_name+".spc";      
      std::string effname2 = effname+trigger_name+"_EC_"+version;
      std::string filename2 = effname2+"_"+objtype+"_matched"+"_1D_pt_Binned.spc";         
      std::ofstream outfile2(filename2.c_str());
      outfile2 << "EffName : " << effname2 << std::endl;
      outfile2 << "EffType : Binned" << std::endl;
      outfile2 << "EffVarNames : pt" << std::endl;
      outfile2 << "EffVersion : " << version_int << std::endl; 
      outfile2 << "ObjQuality :  matched" << std::endl;
      outfile2 << "ObjType : " << objtype << std::endl;
      outfile2 << "ObjVersion : -1 " << std::endl;
      outfile2 << "ObjFunction : " << function << std::endl;
      outfile2 << "ObjTrigger : " << trigger << std::endl;
//       outfile2 << "RunRangeHigh : " << runhigh << std::endl;
//       outfile2 << "RunRangeLow : " << runlow << std::endl;
      outfile2 << "BinEdgesX : ";
      for (int i=0; i<100; i++) outfile2 << i << " ";
      outfile2 << "2000" << std::endl;
      if (function=="f3") {
	for (int i=0; i<100; i++) {
	  double bin_center = i;
	  //	  double bin_center = 2000;		
	  double arg = (  bin_center - par[3] )/ ( sqrt(bin_center)*par[4] );
	  double fitval = 0.5*par[5]*(1. + TMath::Erf(arg));
	  outfile2 << "BinVal : " << bin_center << " " << fitval << " " << errpar[5] << " " << errpar[5] << std::endl;
	}
	//	int i=100;
	double bin_center = 2000;		
	double arg = (  bin_center - par[3] )/ ( sqrt(bin_center)*par[4] );
	double fitval = 0.5*par[5]*(1. + TMath::Erf(arg));
	outfile2 << "BinVal : " << "100" << " " << fitval << " " << errpar[5] << " " << errpar[5] << std::endl;
      } 
  
      std::string effname3 = effname+trigger_name+"_ICD_"+version;
      //std::string filename3 = effname + "_1D_Binned_jet_"+version+"_ICD_"+trigger_name+".spc";
      std::string filename3 = effname3+"_"+objtype+"_matched"+"_1D_pt_Binned.spc";     
      std::ofstream outfile3(filename3.c_str());
      outfile3 << "EffName : " << effname3 << std::endl;
      outfile3 << "EffType : Binned" << std::endl;
      outfile3 << "EffVarNames : pt" << std::endl;
      outfile3 << "EffVersion : " << version_int << std::endl; 
      outfile3 << "ObjQuality :  matched" << std::endl;
      outfile3 << "ObjType : " << objtype << std::endl;
      outfile3 << "ObjVersion : -1 " << std::endl;
      outfile3 << "ObjFunction : " << function << std::endl;
      outfile3 << "ObjTrigger : " << trigger << std::endl;
//       outfile3 << "RunRangeHigh : " << runhigh << std::endl;
//       outfile3 << "RunRangeLow : " << runlow << std::endl;
      outfile3 << "BinEdgesX : ";
      for (int i=0; i<100; i++) outfile3 << i << " ";
      outfile3 << "2000" << std::endl;
      if (function=="f3") {
	for (int i=0; i<100; i++) {	  
	  double bin_center = i;
	  //	  double bin_center = 2000;		
	  double arg = (  bin_center - par[6] )/ ( sqrt(bin_center)*par[7] );
	  double fitval = 0.5*par[8]*(1. + TMath::Erf(arg));
	  outfile3 << "BinVal : " << bin_center << " " << fitval << " " << errpar[8] << " " << errpar[8] << std::endl;
	}
	double bin_center = 2000;		
	double arg = (  bin_center - par[6] )/ ( sqrt(bin_center)*par[7] );
	double fitval = 0.5*par[8]*(1. + TMath::Erf(arg));
	outfile3 << "BinVal : " << "100" << " " << fitval << " " << errpar[8] << " " << errpar[8] << std::endl;	
      } 
 
    } // End of jet condition




    //----------------------------------------------------------------
    //
    // Electrons
    //
    //----------------------------------------------------------------
    if (type=="EM") {
      //std::string effname = "eff_ptturn_" + level;
      std::string effname = "emid_"+level;	 
      std::string objtype = "Electron";
      int version_int;
      int runhigh;
      int runlow;
      if (version=="v13") {
	version_int = 13;
	runhigh = 209104;
	runlow = 194598;
      }
      if (version=="v12") {
	version_int = 12;
	runhigh = 194597;
	runlow = 178722;
      }
      if (version=="v11") {
	version_int = 11;
	runhigh = 178721;
	runlow = 174807;
      }
      if (version=="v10") {
	version_int = 10;
	runhigh = 174807;
	runlow = 170247;
      }
      if (version=="v9") {
	version_int = 9;
	runhigh = 170247;
	runlow = 167016;
      }
      if (version=="v8") {
	version_int = 8;
	runhigh = 167015;
	runlow = 160582;
      }

      // Now for some string manipulation
      typedef std::string::size_type string_size;
      string_size i = 0;
      int index1 = 0;
      int index2 = 0;
      int index3 = 0;
      for (i=0; i<trigger.size(); ++i) {
	if (trigger[i]=='(') index1=i;
	if (trigger[i]==',') index2=i;
	if (trigger[i]==')') index3=i;
      }
      std::string trigger_name = trigger.substr(0,index1) + "_" 
	+ trigger.substr(index1+1,index2-index1-1) + "_" 
	+ trigger.substr(index2+1,index3-index2-1);

      //std::string filename = effname+"_1D_Binned_electron_"+version+"_CC_"+trigger_name+".spc";
      std::string effname1 = effname+trigger_name+"_CC_"+version;
      std::string filename1 = effname1+"_"+objtype+"_matched"+"_1D_pt_Binned.spc";     
      std::ofstream outfile(filename1.c_str());
      outfile << "EffName : " << effname1 << std::endl;
      outfile << "EffType : Binned" << std::endl;
      outfile << "EffVarNames : pt" << std::endl;
      outfile << "EffVersion : " << version_int << std::endl; 
      outfile << "ObjQuality :  matched" << std::endl;
      outfile << "ObjType : " << objtype << std::endl;
      outfile << "ObjVersion : -1 " << std::endl;
      outfile << "ObjFunction : " << function << std::endl;
      outfile << "ObjTrigger : " << trigger << std::endl;
//       outfile << "RunRangeHigh : " << runhigh << std::endl;
//       outfile << "RunRangeLow : " << runlow << std::endl;
      outfile << "BinEdgesX : ";
      for (int i=0; i<100; i++) outfile << i << " ";
      outfile << "2000" << std::endl;
      if (function=="f0") {
	for (int i=0; i<100; i++) {	  
	  double bin_center = i;
	  outfile << "BinVal : " << bin_center << " " << par[0] << " " << par[1] << " " << par[1] << std::endl;
	}
	double bin_center = 2000;
	outfile << "BinVal : " << "100" << " " << par[0] << " " << par[1] << " " << par[1] << std::endl;
      } 
      if (function=="f1") {
	for (int i=0; i<100; i++) {	  
	  double bin_center = i;		
	  double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	  double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));
	  double d0 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[1]);
	  double d1 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[0])/(sqrt(2.)*par[1]*par[1]);
	  double d2 = 0.5*(1.+TMath::Erf(arg));
	  double sigma = (d0*d0) * (errpar[0]*errpar[0]) + (d1*d1) * (errpar[1]*errpar[1]) +  (d2*d2) * (errpar[2]*errpar[2]);
	  if (sigma>0.0) {
	    sigma = sqrt(sigma);
	  } else {
	    sigma = 0;
	  }
	  outfile << "BinVal : " << bin_center << " " << fitval << " " << sigma << " " << sigma << std::endl;
	}
	double bin_center = 2000;		
	double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));
	double d0 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[1]);
	double d1 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[0])/(sqrt(2.)*par[1]*par[1]);
	double d2 = 0.5*(1.+TMath::Erf(arg));
	double sigma = (d0*d0) * (errpar[0]*errpar[0]) + (d1*d1) * (errpar[1]*errpar[1]) +  (d2*d2) * (errpar[2]*errpar[2]);
	if (sigma>0.0) {
	  sigma = sqrt(sigma);
	} else {
	  sigma = 0;
	}
	outfile << "BinVal : " << "100" << " " << fitval << " " << sigma << " " << sigma << std::endl;
      } 
      
      if (function=="f2") {
	for (int i=0; i<100; i++) {	  
	  double bin_center = i;		
	  double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	  double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));	  
	  double d0 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[1]);
	  double d1 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[0])/(sqrt(2.)*par[1]*par[1]);
	  double d2 = 0.5*(1.+TMath::Erf(arg));
	  double sigma = (d0*d0) * (errpar[0]*errpar[0]) + (d1*d1) * (errpar[1]*errpar[1]) +  (d2*d2) * (errpar[2]*errpar[2]);
	  if (sigma>0.0) {
	    sigma = sqrt(sigma);
	  } else {
	    sigma = 0;
	  }
	  outfile << "BinVal : " << bin_center << " " << fitval << " " << sigma << " " << sigma << std::endl;
	}
	double bin_center = 2000;		
	double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));	  
	double d0 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[1]);
	double d1 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[0])/(sqrt(2.)*par[1]*par[1]);
	double d2 = 0.5*(1.+TMath::Erf(arg));
	double sigma = (d0*d0) * (errpar[0]*errpar[0]) + (d1*d1) * (errpar[1]*errpar[1]) +  (d2*d2) * (errpar[2]*errpar[2]);
	if (sigma>0.0) {
	  sigma = sqrt(sigma);
	} else {
	  sigma = 0;
	}
	outfile << "BinVal : " << "100" << " " << fitval << " " << sigma << " " << sigma << std::endl;	
      } 
  
      
      bool _electron_ec = true;
      
      if ( _electron_ec ) {
	std::string effname2 = effname+trigger_name+"_EC_"+version;
	std::string filename2 = effname2+"_"+objtype+"_matched"+"_1D_pt_Binned.spc";     
	std::ofstream outfile2(filename2.c_str());
	outfile2 << "EffName : " << effname2 << std::endl;
	outfile2 << "EffType : Binned" << std::endl;
	outfile2 << "EffVarNames : pt" << std::endl;
	outfile2 << "EffVersion : " << version_int << std::endl; 
	outfile2 << "ObjQuality :  matched" << std::endl;
	outfile2 << "ObjType : " << objtype << std::endl;
	outfile2 << "ObjVersion : -1 " << std::endl;
	outfile2 << "ObjFunction : " << function << std::endl;
	outfile2 << "ObjTrigger : " << trigger << std::endl;
	//       outfile2 << "RunRangeHigh : " << runhigh << std::endl;
	//       outfile2 << "RunRangeLow : " << runlow << std::endl;
	outfile2 << "BinEdgesX : ";
	for (int i=0; i<100; i++) outfile2 << i << " ";
	outfile2 << "2000" << std::endl;
	if (function=="f0") {
	  for (int i=0; i<100; i++) {	  
	    double bin_center = i;
	    outfile2 << "BinVal : " << bin_center << " " << par[0] << " " << par[1] << " " << par[1] << std::endl;
	  }	  
	  double bin_center = 2000;
	  outfile2 << "BinVal : " << "100" << " " << par[0] << " " << par[1] << " " << par[1] << std::endl;
	} 
	if (function=="f1") {
	  for (int i=0; i<100; i++) {	  
	    double bin_center = i;
	    double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	    double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));
	    double d0 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[1]);
	    double d1 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[0])/(sqrt(2.)*par[1]*par[1]);
	    double d2 = 0.5*(1.+TMath::Erf(arg));
	    double sigma = (d0*d0) * (errpar[0]*errpar[0]) + (d1*d1) * (errpar[1]*errpar[1]) +  (d2*d2) * (errpar[2]*errpar[2]);
	    if (sigma>0.0) {
	      sigma = sqrt(sigma);
	    } else {
	      sigma = 0;
	    }
	    outfile2 << "BinVal : " << bin_center << " " << fitval << " " << sigma << " " << sigma << std::endl;
	  }
	  double bin_center = 2000;		
	  double arg = (  bin_center - par[0] )/ ( sqrt(bin_center)*par[1] );
	  double fitval = 0.5*par[2]*(1. + TMath::Erf(arg));
	  double d0 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[1]);
	  double d1 = par[2]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[0])/(sqrt(2.)*par[1]*par[1]);
	  double d2 = 0.5*(1.+TMath::Erf(arg));
	  double sigma = (d0*d0) * (errpar[0]*errpar[0]) + (d1*d1) * (errpar[1]*errpar[1]) +  (d2*d2) * (errpar[2]*errpar[2]);
	  if (sigma>0.0) {
	    sigma = sqrt(sigma);
	  } else {
	    sigma = 0;
	  }
	  outfile2 << "BinVal : " << "100" << " " << fitval << " " << sigma << " " << sigma << std::endl;
	} 
      
	if (function=="f2") {	  
	  for (int i=0; i<100; i++) {	  
	    double bin_center = i;		
	    double arg = (  bin_center - par[3] )/ ( sqrt(bin_center)*par[4] );
	    double fitval = 0.5*par[5]*(1. + TMath::Erf(arg));	  
	    double d0 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[4]);
	    double d1 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[3])/(sqrt(2.)*par[4]*par[4]);
	    double d2 = 0.5*(1.+TMath::Erf(arg));
	    double sigma = (d0*d0) * (errpar[3]*errpar[3]) + (d1*d1) * (errpar[4]*errpar[4]) +  (d2*d2) * (errpar[5]*errpar[5]);
	    if (sigma>0.0) {
	      sigma = sqrt(sigma);
	    } else {
	      sigma = 0;
	    }
	    cout << "I'm Here" << endl;
	    //	    exit(1);
	    outfile2 << "BinVal : " << bin_center << " " << fitval << " " << sigma << " " << sigma << std::endl;
	  }
	  double bin_center = 2000;		
	  double arg = (  bin_center - par[3] )/ ( sqrt(bin_center)*par[4] );
	  double fitval = 0.5*par[5]*(1. + TMath::Erf(arg));	  
	  double d0 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[4]);
	  double d1 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[3])/(sqrt(2.)*par[4]*par[4]);
	  double d2 = 0.5*(1.+TMath::Erf(arg));
	  double sigma = (d0*d0) * (errpar[3]*errpar[3]) + (d1*d1) * (errpar[4]*errpar[4]) +  (d2*d2) * (errpar[5]*errpar[5]);
	  if (sigma>0.0) {
	    sigma = sqrt(sigma);
	  } else {
	    sigma = 0;
	  }
	  outfile2 << "BinVal : " << "100" << " " << fitval << " " << sigma << " " << sigma << std::endl;	
	} 
	
	if (function=="f3") {
	  for (int i=0; i<100; i++) {	  
	    double bin_center = i;		
	    double arg = (  bin_center - par[3] )/ ( sqrt(bin_center)*par[4] );
	    double fitval = 0.5*par[5]*(1. + TMath::Erf(arg));
	    double d0 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[4]);
	    double d1 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[3])/(sqrt(2.)*par[4]*par[4]);
	    double d2 = 0.5*(1.+TMath::Erf(arg));
	    double sigma = (d0*d0) * (errpar[3]*errpar[3]) + (d1*d1) * (errpar[4]*errpar[4]) +  (d2*d2) * (errpar[5]*errpar[5]);
	    if (sigma>0.0) {
	      sigma = sqrt(sigma);
	    } else {
	      sigma = 0;
	    }
	    outfile2 << "BinVal : " << bin_center << " " << fitval << " " << sigma << " " << sigma << std::endl;
	  }
	  double bin_center = 2000;		
	  double arg = (  bin_center - par[3] )/ ( sqrt(bin_center)*par[4] );
	  double fitval = 0.5*par[5]*(1. + TMath::Erf(arg));
	  double d0 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) / (sqrt(2.)*par[4]);
	  double d1 = par[5]/TMath::Sqrt(_pi) * TMath::Exp(-1.*arg*arg) * (bin_center-par[3])/(sqrt(2.)*par[4]*par[4]);
	  double d2 = 0.5*(1.+TMath::Erf(arg));
	  double sigma = (d0*d0) * (errpar[3]*errpar[3]) + (d1*d1) * (errpar[4]*errpar[4]) +  (d2*d2) * (errpar[5]*errpar[5]);
	  if (sigma>0.0) {
	    sigma = sqrt(sigma);
	  } else {
	    sigma = 0;
	  }
	  outfile2 << "BinVal : " << "100" << " " << fitval << " " << sigma << " " << sigma << std::endl;
	} 
      }
  
    } // End of em condition



    //----------------------------------------------------------------
    //
    // Muons
    //
    //----------------------------------------------------------------
    if (type=="MU") {
      std::string effname = "muonid_"+level;  
      std::string objtype = "Muon";
      int version_int;
      int runhigh;
      int runlow;
      if (version=="v13") {
	version_int = 13;
	runhigh = 209104;
	runlow = 194598;
      }
      if (version=="v12") {
	version_int = 12;
	runhigh = 194597;
	runlow = 178722;
      }
      if (version=="v11") {
	version_int = 11;
	runhigh = 178721;
	runlow = 174807;
      }
      if (version=="v10") {
	version_int = 10;
	runhigh = 174807;
	runlow = 170247;
      }
      if (version=="v9") {
	version_int = 9;
	runhigh = 170247;
	runlow = 167016;
      }
      if (version=="v8") {
	version_int = 8;
	runhigh = 167015;
	runlow = 160582;
      }

      // Now for some string manipulation
      typedef std::string::size_type string_size;
      string_size i = 0;
      int index1 = 0;
      int index2 = 0;
      int index3 = 0;
      std::string trigger_name; 
      if (trigger[0]=='m') {
	trigger_name = trigger;
      } else {
	for (i=0; i<trigger.size(); ++i) {
	  if (trigger[i]=='(') index1=i;
	  if (trigger[i]==',') index2=i;
	  if (trigger[i]==')') index3=i;
	}
	trigger_name = trigger.substr(0,index1) + "_" 
	  + trigger.substr(index1+1,index2-index1-1) + "_" 
	  + trigger.substr(index2+1,index3-index2-1);
      }

      effname = effname + trigger_name+"_CC_"+version;
      std::string filename = effname+"_"+objtype+"_loose"+"_1D_deteta_Binned.spc";
      std::ofstream outfile(filename.c_str());
      outfile << "EffMethod : TagAndProbe" << std::endl;
      outfile << "EffName : " << effname << std::endl;
      outfile << "EffType : Binned" << std::endl;
      outfile << "EffVarNames : deteta" << std::endl;
      outfile << "EffVersion : " << version_int << std::endl; 
      outfile << "ObjQuality : loose" << std::endl;
      outfile << "ObjType : " << objtype << std::endl;
      outfile << "ObjVersion : -1 " << std::endl;
      outfile << "ObjFunction : " << function << std::endl;
      outfile << "ObjTrigger : " << trigger << std::endl;
//       outfile << "RunRangeHigh : " << runhigh << std::endl;
//       outfile << "RunRangeLow : " << runlow << std::endl;
      outfile << "BinEdgesX : ";
      for (double i=-2.5; i<2.6; i=i+0.1) outfile << i << " ";
      outfile << std::endl;
      if (function=="f4") {
	int bin_count = 0;
	for (double i=-2.5; i<2.6; i=i+0.1) {
	  double arg=(i*i - par[2]);
	  double fitval= par[3] + par[0]*TMath::Exp(-par[1]*arg)*TMath::Sin(arg);
 	  double d0 = TMath::Exp(-par[1]*arg)*TMath::Sin(arg);
	  double d1 = par[0]*TMath::Exp(-par[1]*arg)*TMath::Sin(arg)*arg;
	  double d2 = par[0]*par[1]*TMath::Exp(-par[1]*arg)*TMath::Sin(arg)-par[0]*TMath::Exp(-par[1]*arg)*TMath::Cos(arg);
	  double d3 = 1.;	
	  double sigma = TMath::Sqrt( d0*d0*errpar[0]*errpar[0] +
				      d1*d1*errpar[1]*errpar[1] +
				      d2*d2*errpar[2]*errpar[2] +
				      d3*d3*errpar[3]*errpar[3]  );
	  if (sigma>0.0) {
	    sigma = sqrt(sigma);
	  } else {
	    sigma = 0;
	  }
	  outfile << "BinVal : " << bin_count << " " << fitval << " " << sigma << " " << sigma << std::endl;
	  bin_count++;
	}
      }
    } // End of mu condition

  }

  return 0;
}
