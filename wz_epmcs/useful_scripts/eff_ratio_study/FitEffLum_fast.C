#define FitEff_cxx
#include "FitEff.h"
#include <TH2.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <string>

void FitEff::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L FitEff.C
//      Root > FitEff t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Int_t NSET = 7;
   Int_t NLUM = 6;
   Int_t NPT  = 4;

   TFile *fileout = new TFile("LumStudy_BigLumi_a.root","RECREATE");
   
   TH1D *ept[NSET][4];
   TH1D *zMass[NSET][NPT][4][NLUM+1];
  

   Long64_t nentries = fChain->GetEntriesFast();
   

   
   
   Double_t setbins[] = {0, 20., 50., 80., 110., 140., 200., 300.};
   Double_t ptbins[] = {25.,35.,45.5,55.,100.};
   Double_t lumibins[] = {0, 1.5, 3.0, 4.5, 6.0, 7.5, 10. };   
   
   char name[100];
   char title[100];
   for (Int_t iset=0; iset < NSET; ++iset){
     for (Int_t ihist=0; ihist < 4; ++ihist){
       std::cout << ihist << "  " << iset << std::endl;
       sprintf(name,"ept_%i_%i",iset,ihist);
       sprintf(title,"elec Pt %2.0f < SET < %2.0f, %i trk ", setbins[iset],setbins[iset+1],ihist);
       ept[iset][ihist] = new TH1D(name,title, 500,24.,80.);
       for (Int_t ipt=0; ipt <NPT; ++ipt){
	 for (Int_t ilumi =0; ilumi < NLUM+1; ++ilumi){
	   if (ilumi==NLUM){
	     sprintf(name,"zMass_%i_%i_%i_%i",iset,ipt,ihist, ilumi);
	     sprintf(title,"Z Mass %2.0f < SET < %2.0f, %2.0f < pT < %2.0f, %i trk, nolumi cut", setbins[iset],setbins[iset+1],ptbins[ipt],ptbins[ipt+1],ihist); 
	   }
	   else {
	     sprintf(name,"zMass_%i_%i_%i_%i",iset,ipt,ihist, ilumi);
	     sprintf(title,"Z Mass %2.0f < SET < %2.0f, %2.0f < pT < %2.0f, %i trk, %2.0f < lumi < %2.0f ", setbins[iset],sets[iset+1],ptbins[ipt],ptbins[ipt+1],ihist, lumibins[ilumi], lumibins[ilumi+1]); 
	   }
	   zMass[iset][ipt][ihist][ilumi] = new TH1D(name,title, 75,69.,111.);
	 }
       }
     }
   }
   
   std::cout << " Finished Creating Histograms" << std::endl;
  
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     Int_t ScalarEtBin = 0;
     Int_t LumiBin =0;
     Int_t ptBine1 =0;
     Int_t ptBine2 =0;
     if (ScalarEt > 300.)
       continue;
      if (ZUt > 30.)
       continue;
     while (ScalarEt > setbins[ScalarEtBin+1]){
       ++ScalarEtBin;
       if (ScalarEtBin==NSET)
	 break;
     }
     
      while (Luminosity > lumibins[LumiBin+1]){
       ++LumiBin;
       if (LumiBin==NLUM)
	 break;
     }

     while(em_pt[0] > ptbinhigh[ptBine1+1]){
       ++ptBine1;
       if (ptBine1==NPT)
	 break;
     }
     while(em_pt[1] > ptbinhigh[ptBine2+1]){
       ++ptBine2;
       if (ptBine2==NPT)
	 break;
     }
     //Float_t weight = 1.;
     zMass[ScalarEtBin][ptBine1][0][LumiBin]->Fill(Mz,weight);
     zMass[ScalarEtBin][ptBine2][0][LumiBin]->Fill(Mz,weight);
     zMass[ScalarEtBin][ptBine1][0][4]->Fill(Mz,weight);
     zMass[ScalarEtBin][ptBine2][0][4]->Fill(Mz,weight);
     ept[ScalarEtBin][0]->Fill(em_pt[0],weight);
     ept[ScalarEtBin][0]->Fill(em_pt[1],weight);
     
     if ((em_trk_prob[0] > 0.5) || ( em_trk_prob[1] > 0.5)){
       for (Int_t iem=0; iem < 2; ++iem){
       if (em_trk_prob[iem] > 0.5) {
	   if (iem==0){
	     ept[ScalarEtBin][1]->Fill(em_pt[0],weight);
	     zMass[ScalarEtBin][ptBine1][1][LumiBin]->Fill(Mz,weight);
	     zMass[ScalarEtBin][ptBine1][1][4]->Fill(Mz,weight);
	     ept[ScalarEtBin][2]->Fill(em_pt[1],weight);
	     zMass[ScalarEtBin][ptBine2][2][LumiBin]->Fill(Mz,weight);
	     zMass[ScalarEtBin][ptBine2][2][4]->Fill(Mz,weight);
	     if (em_trk_prob[1] > 0.5) {
	       ept[ScalarEtBin][3]->Fill(em_pt[1],weight);
	       zMass[ScalarEtBin][ptBine2][3][LumiBin]->Fill(Mz,weight);
	       zMass[ScalarEtBin][ptBine2][3][4]->Fill(Mz,weight);
	       
	     }
	   }  
	   if (iem==1){
	     ept[ScalarEtBin][1]->Fill(em_pt[1],weight);
	     zMass[ScalarEtBin][ptBine2][1][LumiBin]->Fill(Mz,weight);
	     zMass[ScalarEtBin][ptBine2][1][4]->Fill(Mz,weight);
	     ept[ScalarEtBin][2]->Fill(em_pt[0],weight);
	     zMass[ScalarEtBin][ptBine1][2][LumiBin]->Fill(Mz,weight);
	     zMass[ScalarEtBin][ptBine1][2][4]->Fill(Mz,weight);
	     if (em_trk_prob[0] > 0.5) {
	       ept[ScalarEtBin][3]->Fill(em_pt[0],weight);
	       zMass[ScalarEtBin][ptBine1][3][LumiBin]->Fill(Mz,weight);
	       zMass[ScalarEtBin][ptBine1][3][4]->Fill(Mz,weight);
	     }
	   }
	 }
       }
     }
     
     
     // if (Cut(ientry) < 0) continue;
   }
   
  
   
   

   fileout->Write();
   fileout->Close();

}
