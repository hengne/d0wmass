{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");

TString name("regions_w");
TFile *file = new TFile(name+".root","recreate");

TFile fz("~/samples/wtree_geant072710.root");

TH1F *hpeak_pt=new TH1F("hpeak_pt","",80,20,60);
TH1F *h_low_pt=new TH1F("h_low_pt","",80,20,60);
TH1F *hhigh_pt=new TH1F("hhigh_pt","",80,20,60);

TH1F *hpeak_trkprob=new TH1F("hpeak_trkprob","",100,-0.1,0.1);
TH1F *h_low_trkprob=new TH1F("h_low_trkprob","",100,-0.1,0.1);
TH1F *hhigh_trkprob=new TH1F("hhigh_trkprob","",100,-0.1,0.1);

TH1F *hpeak_trknsmt=new TH1F("hpeak_trknsmt","",13,-0.5,12.5);
TH1F *h_low_trknsmt=new TH1F("h_low_trknsmt","",13,-0.5,12.5);
TH1F *hhigh_trknsmt=new TH1F("hhigh_trknsmt","",13,-0.5,12.5);

TH1F *hpeak_mt=new TH1F("hpeak_mt","",80,50,110);
TH1F *h_low_mt=new TH1F("h_low_mt","",80,50,110);
TH1F *hhigh_mt=new TH1F("hhigh_mt","",80,50,110);
                
TH1F *hpeak_ptw=new TH1F("hpeak_ptw","",80,0,30);
TH1F *h_low_ptw=new TH1F("h_low_ptw","",80,0,30);
TH1F *hhigh_ptw=new TH1F("hhigh_ptw","",80,0,30);

TH1F *hpeak_set=new TH1F("hpeak_set","",80,0,200);
TH1F *h_low_set=new TH1F("h_low_set","",80,0,200);
TH1F *hhigh_set=new TH1F("hhigh_set","",80,0,200);

TH1F *hpeak_met=new TH1F("hpeak_met","",80,20,60);
TH1F *h_low_met=new TH1F("h_low_met","",80,20,60);
TH1F *hhigh_met=new TH1F("hhigh_met","",80,20,60);

TH1F *hpeak_wut=new TH1F("hpeak_wut","",80,0,30);
TH1F *h_low_wut=new TH1F("h_low_wut","",80,0,30);
TH1F *hhigh_wut=new TH1F("hhigh_wut","",80,0,30);

TH1F *hpeak_delphi=new TH1F("hpeak_delphi","",80,-7,7);
TH1F *h_low_delphi=new TH1F("h_low_delphi","",80,-7,7);
TH1F *hhigh_delphi=new TH1F("hhigh_delphi","",80,-7,7);

TH1F *hpeak_vtxz=new TH1F("hpeak_vtxz","",80,-60,60);
TH1F *h_low_vtxz=new TH1F("h_low_vtxz","",80,-60,60);
TH1F *hhigh_vtxz=new TH1F("hhigh_vtxz","",80,-60,60);

TH1F *hpeak_e=new TH1F("hpeak_e","",80,20,100);
TH1F *h_low_e=new TH1F("h_low_e","",80,20,100);
TH1F *hhigh_e=new TH1F("hhigh_e","",80,20,100);

TH1F *hpeak_upara=new TH1F("hpeak_upara","",80,-15,15);
TH1F *h_low_upara=new TH1F("h_low_upara","",80,-15,15);
TH1F *hhigh_upara=new TH1F("hhigh_upara","",80,-15,15);

TH1F *hpeak_caloriphi=new TH1F("hpeak_caloriphi","",80,0,7);
TH1F *h_low_caloriphi=new TH1F("h_low_caloriphi","",80,0,7);
TH1F *hhigh_caloriphi=new TH1F("hhigh_caloriphi","",80,0,7);

TH1F *hpeak_trkphidca=new TH1F("hpeak_trkphidca","",80,0,7);
TH1F *h_low_trkphidca=new TH1F("h_low_trkphidca","",80,0,7);
TH1F *hhigh_trkphidca=new TH1F("hhigh_trkphidca","",80,0,7);

TH1F *hpeak_trkphiem3=new TH1F("hpeak_trkphiem3","",80,0,7);
TH1F *h_low_trkphiem3=new TH1F("h_low_trkphiem3","",80,0,7);
TH1F *hhigh_trkphiem3=new TH1F("hhigh_trkphiem3","",80,0,7);

TH1F *hpeak_hm7=new TH1F("hpeak_hm7","",80,0,15);
TH1F *h_low_hm7=new TH1F("h_low_hm7","",80,0,15);
TH1F *hhigh_hm7=new TH1F("hhigh_hm7","",80,0,15);

TH1F *hpeak_iso=new TH1F("hpeak_iso","",150,0,0.15);
TH1F *h_low_iso=new TH1F("h_low_iso","",150,0,0.15);
TH1F *hhigh_iso=new TH1F("hhigh_iso","",150,0,0.15);

TH1F *hpeak_eta=new TH1F("hpeak_eta","",80,-1.5,1.5);
TH1F *h_low_eta=new TH1F("h_low_eta","",80,-1.5,1.5);
TH1F *hhigh_eta=new TH1F("hhigh_eta","",80,-1.5,1.5);

TH1F *hpeak_deteta=new TH1F("hpeak_deteta","",80,-1.5,1.5);
TH1F *h_low_deteta=new TH1F("h_low_deteta","",80,-1.5,1.5);
TH1F *hhigh_deteta=new TH1F("hhigh_deteta","",80,-1.5,1.5);

TH1F *hpeak_trkpt=new TH1F("hpeak_trkpt","",80,0,60);
TH1F *h_low_trkpt=new TH1F("h_low_trkpt","",80,0,60);
TH1F *hhigh_trkpt=new TH1F("hhigh_trkpt","",80,0,60);


TH1F *hpeak_run=new TH1F("hpeak_run","",200,222000,246000);
TH1F *h_low_run=new TH1F("h_low_run","",200,222000,246000);
TH1F *hhigh_run=new TH1F("hhigh_run","",200,222000,246000);

TH1F *hpeak_lumi=new TH1F("hpeak_lumi","",200,0,10);
TH1F *h_low_lumi=new TH1F("h_low_lumi","",200,0,10);
TH1F *hhigh_lumi=new TH1F("hhigh_lumi","",200,0,10);


TCut ept("pt>25");
TCut ecc("cc==1");
TCut eccfid("(ccphifidcal==1 || (trkspat==1 && ccphifidtrk==1))");
TCut eccfidcal("ccphifidcal==1 && ccphifidcal==1");
TCut emid("iso<0.15 && hm7<12");
TCut etrkspat("trkspat==1 && ccphifidtrk==1");
TCut wmt("mt>50. && mt<200.");
TCut wmet("met>25.");
TCut wut("wut<15");


TCut rpeak("pt>44.4 && pt<45.6");
TCut r_low("pt>35 && pt<40");
TCut rhigh("pt>50 && pt<56");

TCut base(ept && ecc && eccfid && emid && etrkspat && wmt && wmet && wut);

TString var="pt";
w->Draw(var+">>hpeak"+"_"+var, base && rpeak);
w->Draw(var+">>h_low"+"_"+var, base && r_low);
w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="trkprob";
w->Draw(var+">>hpeak"+"_"+var, base && rpeak);
w->Draw(var+">>h_low"+"_"+var, base && r_low);
w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="trknsmt";
w->Draw(var+">>hpeak"+"_"+var, base && rpeak);
w->Draw(var+">>h_low"+"_"+var, base && r_low);
w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="delphi";
w->Draw("(wutphi-trkphidca)>>hpeak_delphi", base && rpeak);
w->Draw("(wutphi-trkphidca)>>h_low_delphi", base && r_low);
w->Draw("(wutphi-trkphidca)>>hhigh_delphi", base && rhigh);
var="mt";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="ptw";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="set";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="met";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="wut";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="vtxz";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="e";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="upara";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="caloriphi";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="trkphidca";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="trkphiem3";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="hm7";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="iso";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="eta";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="deteta";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="trkpt";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="run";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
var="lumi";w->Draw(var+">>hpeak"+"_"+var, base && rpeak);w->Draw(var+">>h_low"+"_"+var, base && r_low);w->Draw(var+">>hhigh"+"_"+var, base && rhigh);
 
                 
file->cd();

hpeak_pt->Write();
h_low_pt->Write();
hhigh_pt->Write();

hpeak_trkprob->Write();
h_low_trkprob->Write();
hhigh_trkprob->Write();

hpeak_trknsmt->Write();
h_low_trknsmt->Write();
hhigh_trknsmt->Write();

hpeak_mt->Write();		  
h_low_mt->Write();		  
hhigh_mt->Write();		  
		  
hpeak_ptw->Write();  	  
h_low_ptw->Write();  	  
hhigh_ptw->Write();  	  

hpeak_set->Write(); 		
h_low_set->Write(); 		
hhigh_set->Write(); 		

hpeak_met->Write(); 		
h_low_met->Write(); 		
hhigh_met->Write(); 		

hpeak_wut->Write();  	   
h_low_wut->Write();  	   
hhigh_wut->Write();  	   

hpeak_delphi->Write();  	
h_low_delphi->Write();  	
hhigh_delphi->Write();  	

hpeak_vtxz->Write();		
h_low_vtxz->Write();		
hhigh_vtxz->Write();		

hpeak_e->Write();			
h_low_e->Write();			
hhigh_e->Write();			

hpeak_upara->Write();		
h_low_upara->Write();		
hhigh_upara->Write();		

hpeak_caloriphi->Write();	
h_low_caloriphi->Write();	
hhigh_caloriphi->Write();	

hpeak_trkphidca->Write();	
h_low_trkphidca->Write();	
hhigh_trkphidca->Write();	

hpeak_trkphiem3->Write();	
h_low_trkphiem3->Write();	
hhigh_trkphiem3->Write();	

hpeak_hm7->Write(); 		
h_low_hm7->Write(); 		
hhigh_hm7->Write(); 		

hpeak_iso->Write(); 		
h_low_iso->Write(); 		
hhigh_iso->Write(); 		

hpeak_eta->Write(); 		
h_low_eta->Write(); 		
hhigh_eta->Write(); 		

hpeak_deteta->Write();  	
h_low_deteta->Write();  	
hhigh_deteta->Write();  	

hpeak_trkpt->Write();		
h_low_trkpt->Write();		
hhigh_trkpt->Write();		

hpeak_run->Write(); 		
h_low_run->Write(); 		
hhigh_run->Write(); 		

hpeak_lumi->Write();		
h_low_lumi->Write();		
hhigh_lumi->Write();		

file->Close();

}
