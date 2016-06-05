{
gROOT->Reset(); 
gROOT->LoadMacro("/home/melnit/Library_Alex/Statistics_Kinematics/Functions.hpp");


//Define histograms

 Int_t nbins = 100; 
 Int_t xmin = 0;
 Int_t xmax = 200;

 TH1F *ejmass = new TH1F("ejmass","",nbins,xmin,xmax);
 TH1F* etmass = new TH1F("etmass","",nbins,xmin,xmax);

 TH1F* ejmass_final = new TH1F("ejmass_final","",nbins,xmin,xmax);
 TH1F* etmass_final = new TH1F("etmass_final","",nbins,xmin,xmax);



 TH1F *dr = new TH1F("dr","",100,0,0.6);

 TCut jquality("j_n90>2 && j_n90<25 && j_emf<0.5 && j_chf<0.15 && j_trks<10 && j_trks<10 && (abs(j_deta)>11 && abs(j_deta)<15) && j_hcr<6 && j_n>0 && j_n<4");

 TCut wenu("wcandut<15 && wcandmt<200 && wcandmt>50 && abs(e_deta)<1.1 && e_goodspmtch==1");

 TCut trackselection("t_pt>25 && abs(t_deta)>1.1 && abs(t_deta)<1.5");

 TCut vertex("abs(t_z-vtxz)<1");

 TCut charge("(t_charge*e_charge)<0");

 //et->Draw("ej_m>>ejmass",wenu && jquality && "j_pt>20 && ej_m<110 && ej_m>60");
 //et->Draw("ej_m>>ejmass",wenu && "ej_m<200 && ej_m>0");
 //et->Draw("ej_m>>ejmass",wenu && "ej_m<200 && ej_m>0 && abs(j_deta)>11 && abs(j_deta)<15 && ej_deltaphi>2.5 " && jquality);
 // et->Draw("ej_m>>ejmass",wenu && "ej_m<200 && ej_m>0 && abs(j_deta)>11 && abs(j_deta)<15 && ej_deltaphi>2.5 " && jquality && "j_pt>20");

 et->Draw("ej_m>>ejmass_final",wenu && "ej_m>60 && ej_m<110 && ej_deltaphi>2.5 " && jquality && "j_pt >20" && trackselection && vertex && charge && "et_m<110 && et_m>70");
 et->Draw("et_m>>etmass_final",wenu && trackselection && vertex && charge && " et_m<110 && et_m>70 && et_deltaphi>2.5"  );

 
 et->Draw("ej_m>>ejmass",wenu && "ej_m<110 && ej_m>60 &&  ej_deltaphi>2.5 " && jquality && "j_pt >20");

 // et->Draw("et_m>>etmass",wenu && trackselection && vertex && charge && "et_m<110 && et_m>70 && et_deltaphi>2.5"  );
  et->Draw("et_m>>etmass",wenu && trackselection && vertex && charge && "et_deltaphi>2.5"  );

	 //et->Draw("et_m>>etmass",wenu && trackselection && vertex && charge &&"sqrt((j_eta-t_eta)*(j_eta-t_eta)+(j_phi-t_phi)*(j_phi-t_phi))<0.3" );
 // et->Draw("ej_m>>ejmass",wenu  && "ej_m<110 && ej_m>60 && abs(j_deta)>11 && abs(j_deta)<15 && ej_deltaphi>2.5 " && jquality && "j_pt>20");

 // et->Draw("sqrt((j_eta-t_eta)*(j_eta-t_eta)+(j_phi-t_phi)*(j_phi-t_phi)) >> dr","{((((((sqrt((j_eta-t_eta)*(j_eta-t_eta)+(j_phi-t_phi)*(j_phi-t_phi))<5)&&((((((abs(e_deta)<1.1 && abs(t_deta)>1.1 && abs(t_deta)<1.5)&&(abs(t_z-vtxz)<1.0))&&((e_charge*t_charge)<0))&&(et_m>70 && et_m<110))&&(wcandmt>50 && wcandmt<200 && wcandut<15))&&(e_goodspmtch==1)))&&(abs(e_deta)<1.1 && e_goodspmtch==1 && wcandmt>50 && wcandmt<200 && wcandut<15))&&(abs(j_deta)>11 && abs(j_deta)<15))&&(j_emf<0.5 && j_chf<0.15 && j_trks<10 && j_n>0 && j_n<4 && j_n90>2 && j_n90<25 && j_hcr<6))&&(ej_deltaphi>2.5 && j_pt>20))&&(ej_m>60 && ej_m<110)}");

 
 et->Draw("sqrt((j_eta-t_eta)*(j_eta-t_eta)+(j_phi-t_phi)*(j_phi-t_phi)) >> dr",wenu && trackselection && vertex && charge && jquality  &&"j_pt>20  && ej_m<110 && ej_m>60 && et_m<110 && et_m>70 && et_deltaphi>2.5 && abs(j_deta)>11 && abs(j_deta)<15 && ej_deltaphi>2.5" );

 etmass->Draw();
 ejmass->SetLineColor(2);
 ejmass->Draw("Same");


}
