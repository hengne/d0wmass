{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

Int_t N_variables=5;

TString varnum[5];
varnum[0]="WCandElecPt_Spatial_Match_0";
varnum[1]="WCandElecEta_Spatial_Match_0";					  
varnum[2]="WCandVtx_Spatial_Match_0";					  
varnum[3]="WCandScalarEt_Spatial_Match_0";  						 
varnum[4]="WCandInstLumi_Spatial_Match_0";  				  

TString varden[5];
varden[0]="WCandElecPt_0";
varden[1]="WCandElecEta_0";					  
varden[2]="WCandVtx_0";					  
varden[3]="WCandScalarEt_0";  						 
varden[4]="WCandInstLumi_0"; 

TString vareff[5];
vareff[0]="eff_v_pt";
vareff[1]="eff_v_eta";					  
vareff[2]="eff_v_vtxz";					  
vareff[3]="eff_v_set";  						 
vareff[4]="eff_v_lumi";  				  

TH1 *heff[5];
TH1 *hnum[5];
TH1 *hden[5];

TFile *f = new TFile("/prj_root/5670/wmass1/alex/samples/wenu_newoverlay.root");
gDirectory->cd("WCand_Hist");
for (Int_t i=0; i<N_variables; i++){

  
	hnum[i]=(TH1*)gDirectory->Get(varnum[i]);
	hden[i]=(TH1*)gDirectory->Get(varden[i]);
	heff[i]=(TH1*)gDirectory->Get(varnum[i]);
// 
// if(i==0){hnum[i]->Rebin(6);hden[i]->Rebin(6);heff[i]->Rebin(6);}
// if(i==1){hnum[i]->Rebin(2);hden[i]->Rebin(2);heff[i]->Rebin(2);}
// if(i==2){hnum[i]->Rebin(10);hden[i]->Rebin(10);heff[i]->Rebin(10);}
// if(i==3){hnum[i]->Rebin(10);hden[i]->Rebin(10);heff[i]->Rebin(10);}
// if(i==4){hnum[i]->Rebin(9);hden[i]->Rebin(9);heff[i]->Rebin(9);}


    Int_t nbins = hnum[i]->GetNbinsX();
    cout<<nbins<<endl;
    heff[i]->SetName(vareff[i]);
    heff[i]->SetLineColor(7);

    heff[i]->Divide(hnum[i],hden[i],1,1);

    SetBinomialErrors(nbins , (TH1F*)hnum[i], (TH1F*)hden[i], (TH1F*) heff[i]);

}
}
