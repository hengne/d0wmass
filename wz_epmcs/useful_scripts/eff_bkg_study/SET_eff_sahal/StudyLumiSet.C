#define StudyLumiSet_cxx
#include "StudyLumiSet.h"
#include <TH2.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>

void StudyLumiSet::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L StudyLumiSet.C
//      Root > StudyLumiSet t
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

   TFile *fileout = new TFile("LumStudy.root","RECREATE");
   
   TH1D *lum[2];
   TH1D *set[2];
   TH1D *zPt[2];
   TH1D *zMass[2];
   TH1D *ePt[2];
   TH1D *zUt[2];
   TH1D *eta[2];
   TH1D *deteta[2];
   TH1D *ePtset[2];
   TH1D *setePt[2];

   TH2D *set_ePt2D[2];
   TH2D *ePt_set2D[2];
   TH2D *setePt_ePt2D[2];
   TH2D *ePtset_ePt2D[2];
   
   for (Int_t ihist=0; ihist < 2; ++ihist){
     lum[ihist] = new TH1D(TString("lumi_")+=ihist, "Luminosity", 200,0.,13.);
     set[ihist] = new TH1D(TString("set_")+=ihist, "ScalarEt", 125,0.,700.);
     zPt[ihist] = new TH1D(TString("zPt_")+=ihist, "pT", 500,0.,100.);
     zMass[ihist] = new TH1D(TString("zMass_")+=ihist, "Z Boson Mass", 500,60.,130.);
     std::cout << " Gets here" << std::endl;
     ePt[ihist] = new TH1D(TString("ePt_")+=ihist, "electron Pt", 125,20.,60.);
     zUt[ihist] = new TH1D(TString("zUt_")+=ihist, "Recoil Pt", 500,0.,80.);
     eta[ihist] = new TH1D(TString("physeta_")+=ihist, "eta", 100,-1.5,1.5);
     deteta[ihist] = new TH1D(TString("deteta_")+=ihist, "Det eta", 100,-1.1,1.1); 
     ePtset[ihist] = new TH1D(TString("eptset_")+=ihist, "e Pt over Set", 500, 0., 5.);
     setePt[ihist] = new TH1D(TString("setept_")+=ihist, "e Pt over Set", 500, 0., 25.);
     
     ePt_set2D[ihist] = new TH2D(TString("ept_set_")+=ihist, "e Pt vs. Set", 50,24.,80., 50, 0.,800.);
     set_ePt2D[ihist] = new TH2D(TString("set_ept_")+=ihist, "set vs. ePt", 50,0.,800., 50, 24.,80.);

     setePt_ePt2D[ihist] = new TH2D(TString("setept_ept_")+=ihist, "Set/ ePt vs. ePt", 50,0.,5., 50, 0.,80.);
     ePtset_ePt2D[ihist] = new TH2D(TString("eptset_ept_")+=ihist, "e Pt / Set vs. ePt", 50,0.,20., 50, 0.,80.);
     
     
   }
   std::cout << " Finished Creating Histograms" << std::endl;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     lum[0]->Fill(Luminosity);
     set[0]->Fill(ScalarEt);
     zPt[0]->Fill(Ptz);
     zMass[0]->Fill(Mz);
     zUt[0]->Fill(ZUt);
    
     for (Int_t iem=0; iem < 2; ++iem){
       ePtset[0]->Fill(em_pt[iem]/ScalarEt);
       setePt[0]->Fill(ScalarEt/em_pt[iem]);

       ePt_set2D[0]->Fill(em_pt[iem],ScalarEt);
       set_ePt2D[0]->Fill(ScalarEt,em_pt[iem]);

       ePtset_ePt2D[0]->Fill(em_pt[iem]/ScalarEt,em_pt[iem]);
       setePt_ePt2D[0]->Fill(ScalarEt/em_pt[iem],em_pt[iem]);
	 
       ePt[0]->Fill(em_pt[iem]);
       eta[0]->Fill(em_eta[iem]);
       deteta[0]->Fill(em_deteta[iem]);
       
     }
     
     if ((em_trk_prob[0] > 0.01) && ( em_trk_prob[1] > 0.01)){
       
       lum[1]->Fill(Luminosity);
       set[1]->Fill(ScalarEt);
       zPt[1]->Fill(Ptz);
       zMass[1]->Fill(Mz);
       zUt[1]->Fill(ZUt);

     }
     for (Int_t iem=0; iem < 2; ++iem){
       if (em_trk_prob[iem] > 0.01) {
	 
	 ePtset[1]->Fill(em_pt[iem]/ScalarEt);
	 setePt[1]->Fill(ScalarEt/em_pt[iem]);
	 
	 ePt_set2D[1]->Fill(em_pt[iem],ScalarEt);
	 set_ePt2D[1]->Fill(ScalarEt,em_pt[iem]);
	 
	 ePtset_ePt2D[1]->Fill(em_pt[iem]/ScalarEt,em_pt[iem]);
	 setePt_ePt2D[1]->Fill(ScalarEt/em_pt[iem],em_pt[iem]);
	 
	 ePt[1]->Fill(em_pt[iem]);
	 eta[1]->Fill(em_eta[iem]);
	 deteta[1]->Fill(em_deteta[iem]);
       }
     }
     
   

     // if (Cut(ientry) < 0) continue;
   }

   std::cout << " Gets here" << std::endl;
   TH1D* lumeff = (TH1D*)(lum[1]->Clone("lumeff"));
   lumeff->Divide(lum[1],lum[0],1,1,"B");
   TH1D* seteff = (TH1D*)(set[1]->Clone("seteff"));
   seteff->Divide(set[1],set[0],1,1,"B");
   TH1D* zPteff = (TH1D*)(zPt[1]->Clone("zPteff"));
   zPteff->Divide(zPt[1],zPt[0],1,1,"B");
   TH1D* zMasseff = (TH1D*)(zMass[1]->Clone("Masseff"));
   zMasseff->Divide(zMass[1],zMass[0],1,1,"B");
   TH1D* epteff = (TH1D*)(ePt[1]->Clone("ePteff"));
   epteff->Divide(ePt[1],ePt[0],1,1,"B");

   TH1D* ePtseteff = (TH1D*)(ePtset[0]->Clone("ePtseteff"));
   ePtseteff->Divide(ePtset[1],ePtset[0],1,1,"B");
   TH1D* setePteff = (TH1D*)(setePt[0]->Clone("setePteff"));
   setePteff->Divide(setePt[1],setePt[0],1,1,"B");
   TH2D* ePt_set2Deff = (TH2D*)(ePt_set2D[0]->Clone("ePt_set2Deff"));
   ePt_set2Deff->Divide(ePt_set2D[1],ePt_set2D[0],1,1,"B");
   TH2D* set_ePt2Deff = (TH2D*)(set_ePt2D[0]->Clone("set_ePt2Deff"));
   set_ePt2Deff->Divide(set_ePt2D[1],set_ePt2D[0],1,1,"B");
   TH2D* ePtset_ePt2Deff  = (TH2D*)(ePtset_ePt2D[0]->Clone("ePtset_ePt2Deff"));
   ePtset_ePt2Deff->Divide(ePtset_ePt2D[1],ePtset_ePt2D[0],1,1,"B");
   TH2D* setePt_ePt2Deff = (TH2D*)(setePt_ePt2D[0]->Clone("setePt_ePt2Deff"));
   setePt_ePt2Deff->Divide(setePt_ePt2D[0],setePt_ePt2D[0],1,1,"B");



   //TH1D* zMasseff = (TH1D*)(zMass[1]->Clone("Masseff"));
   //zMasseff->Divide(zMass[1],zMass[0],1,1,"B");
   
   

   fileout->Write();
   fileout->Close();
}
