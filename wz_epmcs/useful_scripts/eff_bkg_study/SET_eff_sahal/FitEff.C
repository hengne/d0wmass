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

   TFile *fileout = new TFile("LumStudy_Big.root","RECREATE");
   
   TH1D *ept[8][2];
   TH1D *zMass[8][16][2];
   //   Float_t setbinlow[12];
   //Float_t setbinhigh[12];
   //Float_t ptbinlow[8][20];
   //Float_t ptbinhigh[8][20];
   Long64_t nentries = fChain->GetEntriesFast();
   
   
//    Float_t persetbin = 2*nentries / 4.;
//    Float_t perptbin = persetbin / 20.;
   


//    Float_t slo =0.;
//    Float_t shi =10.;
//    TString *prestring = new TString("(ScalarEt > ");
//    TString *midstring = new TString("0) && ScalarEt < ");
//    for (Int_t setbin=0; setbin < 8; ++setbin){
//      char cut[100];
//      sprintf(cut,"(ScalarEt > %2.0f) && (ScalarEt < %2.0f)",slo,shi);
//      while ((fChain->Draw("em_pt",cut,"goff") < persetbin) && (shi <500.)){
//        shi += 1;
//        sprintf(cut,"(ScalarEt > %2.0f) && (ScalarEt < %2.0f)",slo,shi);
       
//        if (shi > 400)    sprintf(cut,"(ScalarEt > %2.0f)",slo);
//      }
//      //std::cout << setbin << "  " << slo << "   " << shi << std::endl;	
//      setbinlow[setbin] = slo;
//      setbinhigh[setbin] = shi;
//      slo = shi;
//      shi +=1;
//      Float_t ptlo =25.;
//      Float_t pthi =27.;
//      perptbin= fChain->Draw("em_pt",cut,"goff") / 8;
//      for (Int_t ptbin=0; ptbin < 20; ++ptbin){
//        char cut[100];
//        sprintf(cut,"(ScalarEt > %2.0f) && (ScalarEt < %2.0f) && (em_pt > %2.0f) && (em_pt < %2.0f)",setbinlow[setbin],setbinhigh[setbin],ptlo,pthi);
//        while ((fChain->Draw("em_pt",cut,"goff") < perptbin) && (pthi < 200.)){
// 	 pthi += 0.5;
// 	 sprintf(cut,"(ScalarEt > %2.0f) && (ScalarEt < %2.0f) && (em_pt > %2.0f) && (em_pt < %2.0f)",setbinlow[setbin],setbinhigh[setbin],ptlo,pthi);
	 
// 	 if (pthi > 69.)  sprintf(cut,"(ScalarEt > %2.0f) && (ScalarEt < %2.0f) && (em_pt > %2.0f)",setbinlow[setbin],setbinhigh[setbin],ptlo);
//        }
    
//      ptbinlow[setbin][ptbin] = ptlo;
//      ptbinhigh[setbin][ptbin] = pthi;
//      // std::cout << ptbin << "  " << ptlo << "   " << pthi << std::endl;
//      ptlo = pthi;
//      pthi += 0.5;
//      } 
	
//    }
//    for (Int_t setbin=0; setbin < 8; ++setbin){
//      std::cout << setbinlow[setbin] << ",";
//    }
//    std::cout << std::endl;
//    for (Int_t setbin=0; setbin < 8; ++setbin){
//      std::cout << setbinhigh[setbin] << ",";
//    }
//    std::cout << std::endl;
//    for (Int_t setbin=0; setbin < 8; ++setbin){
//      for (Int_t ptbin=0; ptbin < 20; ++ptbin){
//        std::cout << ptbinlow[setbin][ptbin] << ",";
//      }
//     std::cout <<  std::endl;
//    }

//    for (Int_t setbin=0; setbin < 8; ++setbin){
//      for (Int_t ptbin=0; ptbin < 20; ++ptbin){
//        std::cout << ptbinhigh[setbin][ptbin] << ",";
//      }
//    std::cout <<   std::endl;
//    }
   
   
   Double_t setbinlow[] = {0,59,91,134,500};
   Double_t setbinhigh[]= {59,91,134,500};
   Double_t ptbinlow[][7] = {
     {25,35,39,41.5,43.5,45.5,49},
     {25,33.5,37.5,41,43.5,47,51.5},
     {25,33.5,37.5,41,43.5,47,51.5},
     {25,33.5,37.5,41,43.5,47,51.5}
   };
   Double_t ptbinhigh[][7] = {
     {35,39,41.5,43.5,45.5,49,200},
     {33.5,37.5,41,43.5,47,51.5,200},
     {33.5,37.5,41,43.5,47,51.5,200},
     {33.5,37.5,41,43.5,47,51.5,200}
   };
   
   
//    Double_t setbinlow[] = {0,42,59,75,92,111,136,176};
//    Double_t setbinhigh[]= {42,59,75,92,111,136,176,500};

//    Double_t ptbinlow[][16] = {
//      {25,31,33.5,35.5,37.5,39.5,41,41.5,43,43.5,45,45.5,47,49,51.5,59.0},
//      {25,31,33.5,35.5,37.5,39.5,41,41.5,43,43.5,45,45.5,47,49,51.5,59.5},
//      {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47,49,51.5,57.5},
//      {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,61}, 
//      {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59.5},
//      {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59},
//      {25,29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59},
//      {25,29.5,33,35,37,39,41,41.5,43,43.5,45,47,49,51.5,55.5,65}
//    };
   
//    Double_t ptbinhigh[][16] = {
//      {31,33.5,35.5,37.5,39.5,41,41.5,43,43.5,45,45.5,47,49,51.5,59.0,200.}, 
//      {31,33.5,35.5,37.5,39.5,41,41.5,43,43.5,45,45.5,47,49,51.5,59.5,200.},
//      {29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47,49,51.5,57.5,200.},
//      {29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,61,200.},
//      {29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59.5,200.},
//      {29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59,200.},
//      {29.5,33,35,37,39,41,41.5,43,43.5,45,45.5,47.5,49.5,53,59,200.},
//      {29.5,33,35,37,39,41,41.5,43,43.5,45,47,49,51.5,55.5,65,200.}
//    };
   
   
   char name[50];
   char title[50];
   for (Int_t iset=0; iset < 4; ++iset){
     for (Int_t ihist=0; ihist < 2; ++ihist){
       sprintf(name,"ept_%i_%i",iset,ihist);
       sprintf(title,"elec Pt %2.0f < SET < %2.0f, %i trk ", setbinlow[iset],setbinhigh[iset],ihist);
       ept[iset][ihist] = new TH1D(name,title, 500,24.,80.);
       for (Int_t ipt=0; ipt <7; ++ipt){
	 sprintf(name,"zMass_%i_%i_%i",iset,ipt,ihist);
	 sprintf(title,"Z Mass %2.0f < SET < %2.0f, %2.0f < pT < %2.0f, %i trk ", setbinlow[iset],setbinhigh[iset],ptbinlow[iset][ipt],ptbinhigh[iset][ipt],ihist); 
	 zMass[iset][ipt][ihist] = new TH1D(name,title, 75,69.,111.);
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
     Int_t ptBine1 =0;
     Int_t ptBine2 =0;
     while (ScalarEt > setbinhigh[ScalarEtBin]){
       ++ScalarEtBin;
       if (ScalarEtBin==3)
	 break;
     }
     while(em_pt[0] > ptbinhigh[ScalarEtBin][ptBine1]){
       ++ptBine1;
       if (ptBine1==6)
	 break;
     }
     while(em_pt[1] > ptbinhigh[ScalarEtBin][ptBine2]){
       ++ptBine2;
       if (ptBine2==6)
	 break;
     }
     
     zMass[ScalarEtBin][ptBine1][0]->Fill(Mz);
     zMass[ScalarEtBin][ptBine2][0]->Fill(Mz);
     ept[ScalarEtBin][0]->Fill(em_pt[0]);
     ept[ScalarEtBin][0]->Fill(em_pt[1]);
     
     if ((em_trk_prob[0] > 0.01) || ( em_trk_prob[1] > 0.01)){
       for (Int_t iem=0; iem < 2; ++iem){
	 if (em_trk_prob[iem] > 0.01) {
	   if (iem==0){
	     ept[ScalarEtBin][1]->Fill(em_pt[0]);
	     zMass[ScalarEtBin][ptBine1][1]->Fill(Mz);
	   }  
	   if (iem==1){
	     ept[ScalarEtBin][1]->Fill(em_pt[1]);
	     zMass[ScalarEtBin][ptBine2][1]->Fill(Mz);
	   }
	 }
       }
     }
     
     
     // if (Cut(ientry) < 0) continue;
   }
   
  
   
   

   fileout->Write();
   fileout->Close();

}
