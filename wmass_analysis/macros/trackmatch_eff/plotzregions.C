{
gStyle->SetOptStat(0);

gStyle->SetTitleW(0.5);
gStyle->SetTitleH(0.07);
gStyle->SetTitleX(0.25);
	
Int_t N_variables=22;
TString var[22];
var[0]= "pt";
var[1]= "trkprob";  						
var[2]= "trknsmt";  						
var[3]= "delphi";						   
var[4]= "mee";  					
var[5]= "ptee"; 					
var[6]= "set";  					
var[7]= "met";  					
var[8]= "zut";  					
var[9]= "vtxz"; 					
var[10]="e";						
var[11]="upara";					
var[12]="caloriphi";				
var[13]="trkphidca";				
var[14]="trkphiem3";				
var[15]="hm7";  					
var[16]="iso";  					
var[17]="eta";  					
var[18]="deteta";					
var[19]="trkpt";					
var[20]="run";  					
var[21]="lumi";
  
TH1 *h_low[22];
TH1 *hpeak[22];
TH1 *hhigh[22];
 
TFile *f = new TFile("regions_z.root");
for (Int_t i=0; i<N_variables; i++){
//for (Int_t i=16; i<=17; i++){

	h_low[i]=(TH1*)gDirectory->Get("h_low_"+var[i]);
	hpeak[i]=(TH1*)gDirectory->Get("hpeak_"+var[i]);
	hhigh[i]=(TH1*)gDirectory->Get("hhigh_"+var[i]);

    h_low[i]->SetTitle(var[i]);
    hpeak[i]->SetTitle(var[i]);
    hhigh[i]->SetTitle(var[i]);

    h_low[i]->SetLineStyle(2);
    hhigh[i]->SetLineStyle(3);

//     if ( ((h_low[i]->GetMaximum()) > (hpeak[i]->GetMaximum())) &&
//          ((h_low[i]->GetMaximum()) > (hhigh[i]->GetMaximum())) ){
//        h_low[i]->Draw();
//        hhigh[i]->Draw("Same");
//        hpeak[i]->Draw("Same");
//     }
// 
//     if ( ((hhigh[i]->GetMaximum()) > (hpeak[i]->GetMaximum())) &&
//          ((hhigh[i]->GetMaximum()) > (h_low[i]->GetMaximum())) ){
//        hhigh[i]->Draw();
//        h_low[i]->Draw("Same");
//        hpeak[i]->Draw("Same");
//     }
// 
//     if ( ((hpeak[i]->GetMaximum()) > (hhigh[i]->GetMaximum())) &&
//          ((hpeak[i]->GetMaximum()) > (h_low[i]->GetMaximum())) ){
//        hpeak[i]->Draw();
//        h_low[i]->Draw("Same");
//        hhigh[i]->Draw("Same");
//     }

    hpeak[i]->Draw();
    Double_t normSample = hpeak[i]->Integral(); 
    h_low[i]->DrawNormalized("Same",normSample);
    hhigh[i]->DrawNormalized("Same",normSample);


	TLegend *leg1 = new TLegend(0.8,0.7,0.95,0.99,NULL,"brNDC");
	leg1->SetBorderSize(0);
	leg1->SetTextSize(0.035);

	leg1->AddEntry(h_low[i],"Low PT(e1)","l");
	leg1->AddEntry(hpeak[i],"Peak PT(e1)","l");
	leg1->AddEntry(hhigh[i],"High PT(e1)","l");
	leg1->Draw();
    c1->Print("threeregions_"+var[i]+".eps");
    c1->Print("threeregions_"+var[i]+".gif");

// 	hSample1_Var[i]->Rebin(Rebin_hSample1);
// 	hSample1_Var[i]->GetYaxis()->SetLabelSize(0.07);
// 	hSample1_Var[i]->GetXaxis()->SetTitle(HorizontalAxisTitle);  hSample1_Var[i]->GetXaxis()->SetTitleSize(0.095);hSample1_Var[i]->GetXaxis()->SetTitleOffset(0.7);hSample1_Var[i]->GetXaxis()->SetLabelSize(0.07);
//     hSample1_Var[i]->SetLineColor(LineColor_Var[i]); hSample1_Var[i]->SetLineStyle(LineStyle_Var[i]);hSample1_Var[i]->SetLineWidth(LineWidth_Var[i]);
// 	hSample1_Var[i]->SetTitle(HistogramTitle_Common+HistogramTitle_Sample1);
}

cout<<"now do:"<<endl;
cout<<".q"<<endl;
cout<<"cp threeregions_* ~/next/"<<endl;


}
