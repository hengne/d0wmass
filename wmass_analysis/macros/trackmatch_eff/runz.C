{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

//#define TAGANDPROBE
#define COUNTINGTRACKS
//#define WLIKE
//-------------------
#define VARIABLEBIN
//#define FIXEDBIN
//------------------
//#define PTEBINNING
#define LUMIBINNING
//#define SETBINNING

Int_t N_variables = 9;
TString name[9];
TString var[9];
Int_t nbins[9];   
Double_t xmin[9]; 
Double_t xmax[9]; 
bool objectvariable[9];
// name[0]="ZLooseWlike_092710_vs_PhysEta";xmin[0]=-1.5; xmax[0]=1.5;  nbins[0]=30;var[0]="eta";	   objectvariable[0]=true;
// name[1]="ZLooseWlike_092710_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// //name[1]="ZLooseWlike_092710VarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// name[2]="ZLooseWlike_092710_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";      objectvariable[2]=false;	
// name[3]="ZLooseWlike_092710_vs_VTXZ";   xmin[3]=-60.0;xmax[3]=60.0; nbins[3]=30;var[3]="vtxz";     objectvariable[3]=false;	
// name[4]="ZLooseWlike_092710_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";     objectvariable[4]=false;	
// name[5]="ZLooseWlike_092710_vs_UPARA";  xmin[5]=-15;  xmax[5]=15;   nbins[5]=30;var[5]="upara";    objectvariable[5]=true;  
// name[6]="ZLooseWlike_092710_vs_UT";     xmin[6]=0;    xmax[6]=15;   nbins[6]=30;var[6]="zut";  	   objectvariable[6]=false;   
// name[7]="ZLooseWlike_092710_vs_delphi"; xmin[7]=0;    xmax[7]=3.5;  nbins[7]=30;var[7]="zutdelphi";objectvariable[7]=false;
// name[8]="ZLooseWlike_092710_vs_trkpt";  xmin[8]=10.;  xmax[8]=65.;  nbins[8]=30;var[8]="trkpt";    objectvariable[8]=true;  

// // name[0]="ZEffAnaLoose_vs_PhysEta";xmin[0]=-1.5; xmax[0]=1.5;  nbins[0]=30;var[0]="eta";	   objectvariable[0]=true;
// // name[1]="ZEffAnaLoose_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// //name[1]="ZEffAnaLooseVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// name[1]="ZEffAnaLooseVarBin_vs_PT__mass60_130_redef012toaddtoh";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// // name[2]="ZEffAnaLoose_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";      objectvariable[2]=false;	
// // name[3]="ZEffAnaLoose_vs_VTXZ";   xmin[3]=-60.0;xmax[3]=60.0; nbins[3]=30;var[3]="vtxz";     objectvariable[3]=false;	
// // name[4]="ZEffAnaLoose_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";     objectvariable[4]=false;	
// // name[5]="ZEffAnaLoose_vs_UPARA";  xmin[5]=-15;  xmax[5]=15;   nbins[5]=30;var[5]="upara";    objectvariable[5]=true;  
// // name[6]="ZEffAnaLoose_vs_UT";     xmin[6]=0;    xmax[6]=15;   nbins[6]=30;var[6]="zut";  	   objectvariable[6]=false;   
// // name[7]="ZEffAnaLoose_vs_delphi"; xmin[7]=0;    xmax[7]=3.5;  nbins[7]=30;var[7]="zutdelphi";objectvariable[7]=false;
// // name[8]="ZEffAnaLoose_vs_trkpt";  xmin[8]=10.;  xmax[8]=65.;  nbins[8]=30;var[8]="trkpt";    objectvariable[8]=true;  


// name[0]="ZEffTightVarBin_vs_PhysEta";xmin[0]=-1.5; xmax[0]=1.5;  nbins[0]=30;var[0]="eta";	   objectvariable[0]=true;
// //name[1]="ZEffTightVarBin_vs_PT_TP";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// //name[1]="ZEffTightVarBin_vs_PT_TPtag1st";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// //name[1]="ZEffTightVarBin_vs_PT_TPtag2nd";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
// name[1]="ZEffTightVarBin_vs_PT_TPtagboth1stand2nd";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
//name[1]="ZTightVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
//name[1]="ZLooseHengnesfixVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
//name[1]="ZLooseBacktoAlexVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
//name[1]="ZLooseAlaDataVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
//name[1]="ZLooseHengneVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    
//name[1]="ZTightHengneVarBin_vs_PT";     xmin[1]=20.0; xmax[1]=80.0; nbins[1]=30;var[1]="pt";  	   objectvariable[1]=true;    

// name[2]="ZEffTightVarBin_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";      objectvariable[2]=false;	
//name[2]="ZTightVarBin_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";      objectvariable[2]=false;	
//name[2]="ZLoose_092710VarBin_vs_SET";    xmin[2]=0.0;  xmax[2]=300.0;nbins[2]=30;var[2]="set";      objectvariable[2]=false;	

// name[3]="ZEffTightVarBin_vs_VTXZ";   xmin[3]=-60.0;xmax[3]=60.0; nbins[3]=30;var[3]="vtxz";     objectvariable[3]=false;	
// name[4]="ZEffTightVarBin_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";     objectvariable[4]=false;	
//name[4]="ZTightVarBin_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";     objectvariable[4]=false;	
name[4]="ZTightVarBin_vs_LUMI";   xmin[4]=0.0;  xmax[4]=10.0; nbins[4]=30;var[4]="lumi";     objectvariable[4]=false;	

// name[5]="ZEffTightVarBin_vs_UPARA";  xmin[5]=-15;  xmax[5]=15;   nbins[5]=30;var[5]="upara";    objectvariable[5]=true;  
// name[6]="ZEffTightVarBin_vs_UT";     xmin[6]=0;    xmax[6]=15;   nbins[6]=30;var[6]="zut";  	   objectvariable[6]=false;   
// name[7]="ZEffTightVarBin_vs_delphi"; xmin[7]=0;    xmax[7]=3.5;  nbins[7]=30;var[7]="zutdelphi";objectvariable[7]=false;
// name[8]="ZEffTightVarBin_vs_trkpt";  xmin[8]=10.;  xmax[8]=65.;  nbins[8]=30;var[8]="trkpt";    objectvariable[8]=true;  


TCut ept("pt[0]>25 && pt[1]>25");
TCut ecc("cc[0]==1 && cc[1]==1");
TCut eccfid("(ccphifidcal[0]==1 || (trkspat[0]==1 && ccphifidtrk[0]==1)) && (ccphifidcal[1]==1 || (trkspat[1]==1 && ccphifidtrk[1]==1))");
TCut eccfidcal("ccphifidcal[0]==1 && ccphifidcal[1]==1");
TCut emid("iso[0]<0.15 && iso[1]<0.15 && hm7[0]<12 && hm7[1]<12");
TCut etrkspat("trkspat[0]==1 && ccphifidtrk[0]==1 && trkspat[1]==1 && ccphifidtrk[1]==1");
TCut zmeedatasignalrange("mee>70. && mee<110.");
TCut zmeedatafitrange("mee>60. && mee<130.");

TCut zut("zut<15");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//


TCut eccwlike0("cc[0]==1");
TCut eccfidwlike0("(ccphifidcal[0]==1 || (trkspat[0]==1 && ccphifidtrk[0]==1))");
TCut eccfidcalwlike0("ccphifidcal[0]==1");
TCut emidwlike0("iso[0]<0.15 && hm7[0]<12");
TCut etrkspatwlike0("trkspat[0]==1 && ccphifidtrk[0]==1");


TCut trkgoodbyhand0("trkpt[0]>10 && trknsmt[0]>0 && trkprob[0]>0.01");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//
TCut trkgoodbyhand1("trkpt[1]>10 && trknsmt[1]>0 && trkprob[1]>0.01");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//

TCut trknotgoodbyhand0("!(trkpt[0]>10 && trknsmt[0]>0 && trkprob[0]>0.01)");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//
TCut trknotgoodbyhand1("!(trkpt[1]>10 && trknsmt[1]>0 && trkprob[1]>0.01)");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//

TCut trkgoodbyhand0("trkpt[0]>10 && trknsmt[0]>0 && trkprob[0]>0.01");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//
TCut trkgoodbyhand1("trkpt[1]>10 && trknsmt[1]>0 && trkprob[1]>0.01");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//

TCut trknotgoodbyhand0("!(trkpt[0]>10 && trknsmt[0]>0 && trkprob[0]>0.01)");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//
TCut trknotgoodbyhand1("!(trkpt[1]>10 && trknsmt[1]>0 && trkprob[1]>0.01)");//TCut zut("zut<7");//TCut zut("");//TCut zut("zut<15");//


//for(int i=0; i<9; i++){
//for(int i=1; i<=1; i++){//pte
//for(int i=2; i<=2; i++){//set
for(int i=4; i<=4; i++){//lumi


TFile *file = new TFile(name[i]+".root","recreate");
TFile fz("~/samples/ztree_geant072710.root");

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


#ifdef COUNTINGTRACKS
cout<<" using counting tracks method "<<endl;

//--- tight track match efficiency
cout<<" calculating tight track match efficiency "<<endl;
TCut base(ept && ecc && eccfid && emid && etrkspat && zmeedatasignalrange && zut);
TCut basewlike0(ept && eccwlike0 && eccfidwlike0 && emidwlike0 && etrkspatwlike0 && zut);
if(objectvariable[i]==true){
z->Draw(var[i]+"[0]>>hden",  base);
z->Draw(var[i]+"[0]>>hnum",  base && "trkgood[0]==1");
z->Draw(var[i]+"[1]>>+hden",  base);
z->Draw(var[i]+"[1]>>+hnum",  base && "trkgood[1]==1");
} else {
z->Draw(var[i]+">>h",   base);
z->Draw(var[i]+">>h0",  base && "trkgood[0]==0 && trkgood[1]==0");
z->Draw(var[i]+">>h1",  base && "((trkgood[0]==1 && trkgood[1]==0) || (trkgood[0]==0 && trkgood[1]==1))");
z->Draw(var[i]+">>h2",  base && "trkgood[0]==1 && trkgood[1]==1");
}

// //--- loose track match efficiency
// cout<<" calculating loose track match efficiency "<<endl;
// TCut base(ept && ecc && eccfid && emid && zmeedatasignalrange && zut);
// cout<<endl;
// // //--- loose track match efficiency
// if(objectvariable[i]==true){
// z->Draw(var[i]+"[0]>>hden",  base);
// z->Draw(var[i]+"[0]>>hnum",  base && "(trkspat[0]==1 && ccphifidtrk[0]==1)");
// z->Draw(var[i]+"[1]>>+hden",  base);
// z->Draw(var[i]+"[1]>>+hnum",  base && "(trkspat[1]==1 && ccphifidtrk[1]==1)");
// } else {
// z->Draw(var[i]+">>h",  base);
// z->Draw(var[i]+">>h0", base &&  "!(trkspat[0]==1 && ccphifidtrk[0]==1) && !(trkspat[1]==1 && ccphifidtrk[1]==1)");
// z->Draw(var[i]+">>h1", base && "(((trkspat[0]==1 && ccphifidtrk[0]==1) && !(trkspat[1]==1 && ccphifidtrk[1]==1)) || (!(trkspat[0]==1 && ccphifidtrk[0]==1) && (trkspat[1]==1 && ccphifidtrk[1]==1)))");
// z->Draw(var[i]+">>h2", base &&   "(trkspat[0]==1 && ccphifidtrk[0]==1)  && (trkspat[1]==1 && ccphifidtrk[1]==1)");
}
//-----------------------------------


#endif

#ifdef TAGANDPROBE 
cout<<" using tag and probe method "<<endl;
//cout<<" 1st object is used as TAG "<<endl;
//z->Draw(var[i]+"[1]>>hden",  base && "trkgood[0]==1");
//z->Draw(var[i]+"[1]>>hnum",  base && "trkgood[0]==1 && trkgood[1]==1");
//cout<<" 2nd object is used as TAG "<<endl;
//z->Draw(var[i]+"[0]>>hden",  base && "trkgood[1]==1");
//z->Draw(var[i]+"[0]>>hnum",  base && "trkgood[0]==1 && trkgood[1]==1");
cout<<" both objects are used as TAG "<<endl;
z->Draw(var[i]+"[1]>>hden",   base && "trkgood[0]==1");
z->Draw(var[i]+"[1]>>hnum",   base && "trkgood[0]==1 && trkgood[1]==1");
z->Draw(var[i]+"[0]>>+hden",  base && "trkgood[1]==1");
z->Draw(var[i]+"[0]>>+hnum",  base && "trkgood[0]==1 && trkgood[1]==1");
#endif

#ifdef WLIKE 
TCut base(ept && eccwlike0 && eccfidwlike0 && emidwlike0 && zut);
cout<<" using W-like electron selection in for Z->ee electrons "<<endl;
cout<<" calculating loosetrk electron efficiency for W-like Zee electrons "<<endl;
cout<<endl;
z->Draw(var[i]+"[0]>>hden",   base );
z->Draw(var[i]+"[0]>>hnum",   base && "(trkspat[0]==1 && ccphifidtrk[0]==1)");
#endif


if(objectvariable[i]==false) {
hden = (TH1F *)h->Clone();
hden->SetName("hden");
hden->Scale(2.0);

hnum = (TH1F *)h1->Clone();
hnum->SetName("hnum");
hnum->Add(h2,2);

heff = (TH1F *)hnum->Clone();
heff->SetName("heff");
}
heff->Divide(hnum,hden,1,1);

#ifdef VARIABLEBIN
SetBinomialErrors(nxbins , (TH1F*)hnum, (TH1F*)hden, (TH1F*) heff);
#endif
#ifdef FIXEDBIN
SetBinomialErrors(nbins[i], (TH1F*)hnum, (TH1F*)hden, (TH1F*) heff);
#endif

heff->Draw();

file->cd();
h->Write();
h0->Write();
h1->Write();
h2->Write();
hnum->Write();
hden->Write();
heff->Write();
file->Close();

}//for(int i=0; i<9; i++){
}
