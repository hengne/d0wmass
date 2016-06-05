{


cout<<" WARNING about wtree !!! "<<endl;
cout<<" wutdelphi and metutdelphi are swapped "<<endl;
cout<<" end of WARNING about wtree !!! "<<endl;
 
/*
TFile fW("/prj_root/5670/wmass1/alex/samples/wenu_newoverlay.root");
gDirectory->cd("WCand_Hist");
cout<<WCandElecPt_Spatial_Match_0->Integral()<<endl;
9.79328e+06
cout<<WCandElecPt_0->Integral()<<endl;
1.21963e+07
/prj_root/5670/wmass1/alex/samples/wenu_newoverlay.root
entries=1.219654e+07 (1.21963e+07 integral)
entries=9793444      (9.79328e+06 integral)
TCut ascutone("wut<15 && wut>0 && met>25 && mt>50 && mt<200");
loose
w->Draw("deteta",ascutone && "cc==1 &&  abs(deteta)<2.3 && !(abs(deteta)<1.5 && abs(deteta)>1.05)  && trkspat==1 && pt>25 && iso<0.15 && hm7<12  && (cc!=1 || (cc==1 && ccphifidtrk==1))")
tight
w->Draw("deteta",ascutone && "trkgood==1 && cc==1 &&  abs(deteta)<2.3 && !(abs(deteta)<1.5 && abs(deteta)>1.05)  && trkspat==1 && pt>25 && iso<0.15 && hm7<12  && (cc!=1 || (cc==1 && ccphifidtrk==1))")
(Long64_t)12197427
(Long64_t)9794021
*/
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");
//gStyle->SetOptStat(0);
//-------------------
#define VARIABLEBIN
//#define FIXEDBIN
//------------------
#define PTEBINNING
//#define LUMIBINNING
//#define SETBINNING

Int_t N_variables = 9;
TString name[9];
TString var[9];
Int_t nbins[9];   
Double_t xmin[9]; 
Double_t xmax[9]; 

// name[0]="WEffAnaLoose_vs_PhysEta";xmin[0]=-1.5; xmax[0]=1.5;  nbins[0]=30;var[0]="eta";
// name[1]="WEffAnaLoose_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	
// name[2]="WEffAnaLoose_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";    
// name[3]="WEffAnaLoose_vs_VTXZ";   xmin[3]=-60.0;xmax[3]=60.0; nbins[3]=30;var[3]="vtxz";   
// name[4]="WEffAnaLoose_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";   
// name[5]="WEffAnaLoose_vs_UPARA";  xmin[5]=-15;  xmax[5]=15;   nbins[5]=30;var[5]="upara";  
// name[6]="WEffAnaLoose_vs_UT";     xmin[6]=0;    xmax[6]=15;   nbins[6]=30;var[6]="wut";  	
// name[7]="WEffAnaLoose_vs_delphi"; xmin[7]=0;    xmax[7]=3.5;  nbins[7]=30;var[7]="metdelphi";//this is actually wutdelphi 
// name[8]="WEffAnaLoose_vs_trkpt";  xmin[8]=10.;  xmax[8]=65.;  nbins[8]=30;var[8]="trkpt";  
name[0]="WEffTight_VarBin_vs_PhysEta";xmin[0]=-1.5; xmax[0]=1.5;  nbins[0]=30;var[0]="eta";
//name[1]="WEffTight_VarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	
//name[1]="WTightVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	
name[1]="WLooseVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	

//name[2]="WEffTight_VarBin_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";    
//name[2]="WTightVarBin_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";    
//name[2]="WTLooseVarBin_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";    

name[3]="WEffTight_VarBin_vs_VTXZ";   xmin[3]=-60.0;xmax[3]=60.0; nbins[3]=30;var[3]="vtxz";   
//name[4]="WEffTight_VarBin_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";   
//name[4]="WTightVarBin_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";   
name[4]="WLooseVarBin_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";   

name[5]="WEffTight_VarBin_vs_UPARA";  xmin[5]=-15;  xmax[5]=15;   nbins[5]=30;var[5]="upara";  
name[6]="WEffTight_VarBin_vs_UT";     xmin[6]=0;    xmax[6]=15;   nbins[6]=30;var[6]="wut";  	
name[7]="WEffTight_VarBin_vs_delphi"; xmin[7]=0;    xmax[7]=3.5;  nbins[7]=30;var[7]="metdelphi";//this is actually wutdelphi 
name[8]="WEffTight_VarBin_vs_trkpt";  xmin[8]=10.;  xmax[8]=65.;  nbins[8]=30;var[8]="trkpt";  


TCut ept("pt>25");
TCut ecc("cc==1");
TCut eccfid("(ccphifidcal==1 || (trkspat==1 && ccphifidtrk==1))");
TCut eccfidcal("ccphifidcal==1");
TCut emid("iso<0.15 && hm7<12");
TCut etrkspat("trkspat==1 && ccphifidtrk==1");
TCut etrkgood(etrkspat && "trkgood==1");
TCut etrkgoodbyhand(etrkspat && "trkprob>0.01 && trknsmt>0 && trkpt>10");
TCut etrkgoodbyhandnosmt(etrkspat && "trkprob>0.01 && trkpt>10");

TCut wmt("mt>50. && mt<200.");
TCut wmet("met>25.");
TCut wut("wut<15");

//for(int i=0; i<9; i++){
for(int i=1; i<=1; i++){//pt
//for(int i=4; i<=4; i++){//lumi
//for(int i=2; i<=2; i++){//set


TFile *file = new TFile(name[i]+".root","recreate");
TFile fw("~/samples/wtree_geant072710.root");


#ifdef FIXEDBIN
TH1F *h  = new TH1F("h","",nbins[i],xmin[i],xmax[i]);
TH1F *h0 = new TH1F("h0","",nbins[i],xmin[i],xmax[i]);
TH1F *h1 = new TH1F("h1","",nbins[i],xmin[i],xmax[i]);
TH1F *h2 = new TH1F("h2","",nbins[i],xmin[i],xmax[i]);

TH1F *hnum = new TH1F("hnum","",nbins[i],xmin[i],xmax[i]);
TH1F *hden = new TH1F("hden","",nbins[i],xmin[i],xmax[i]);
TH1F *heff = new TH1F("heff","",nbins[i],xmin[i],xmax[i]);
#endif

#ifdef PTEBINNING
//PTE
int nxbins = 23;
float xbins[24]={0,25,27,29,31,33,35,37,39,41, 43,45,47,49,51,53,57,61,65,70, 75,80,90,100};
#endif

#ifdef LUMIBINNING
//LUMI
int nxbins = 13;
float xbins[14]={0.0, 1.5, 2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,8.0,10.0};
#endif

#ifdef SETBINNING
//LUMI
int nxbins = 15;
float xbins[16]={0,20,30,40,50,60,70,80,90,100,120,140,155,170,180,300};
#endif

#ifdef VARIABLEBIN
TH1F *h  = new TH1F("h","",nxbins,xbins);
TH1F *h0 = new TH1F("h0","",nxbins,xbins);
TH1F *h1 = new TH1F("h1","",nxbins,xbins);
TH1F *h2 = new TH1F("h2","",nxbins,xbins);

TH1F *hnum = new TH1F("hnum","",nxbins,xbins);
TH1F *hden = new TH1F("hden","",nxbins,xbins);
TH1F *heff = new TH1F("heff","",nxbins,xbins);
#endif

//--- tight track match efficiency
TCut base(ept && ecc && eccfid && wmt && wmet && wut && emid && etrkspat);
w->Draw(var[i]+">>hden",   base);
w->Draw(var[i]+">>hnum",   base && etrkgood);
// //--- loose track match efficiency
// TCut base(ept && ecc && eccfid && wmt && wmet && wut && emid);
// w->Draw(var[i]+">>hden",   base);
// w->Draw(var[i]+">>hnum",   base && etrkspat);
// //--- (EffAnalysis definition) loose track match efficiency
// TCut base(ept && ecc && eccfidcal && wmt && wmet && wut && emid);
// w->Draw(var[i]+">>hden",   base);
// w->Draw(var[i]+">>hnum",   base && etrkspat);

heff->Divide(hnum,hden,1,1);
//--------------------------------
#ifdef VARIABLEBIN
SetBinomialErrors(nbins[i] , (TH1F*)hnum, (TH1F*)hden, (TH1F*) heff);
#endif

#ifdef FIXEDBIN
SetBinomialErrors(nxbins , (TH1F*)hnum, (TH1F*)hden, (TH1F*) heff);
#endif

heff->Draw();

file->cd();
hnum->Write();
hden->Write();
heff->Write();
file->Close();

}//for(int i=0; i<9; i++){
}
