#include "TH1.h"

//code used to calculate the total entries of one histogram

float Entries_Calc(TH1F *his, float cut1 = -1000., float cut2 = 1000.) {

  //count total entries of data histogram
  float num = 0;
  for(int ibin=0; ibin<his->GetNbinsX(); ++ibin) { 
    float center = his->GetBinCenter(ibin);
    if(center >= cut1 && center <= cut2)  num += his->GetBinContent(ibin);
  }//loop over all bins

  return num;
}


