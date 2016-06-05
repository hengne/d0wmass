/*
setenv tag MWISFUN;
setenv wendata /prj_root/5670/wmass1/alex/samples/wendata.root
setenv wenpmcs /prj_root/5670/wmass1/alex/samples/wenresbos051410.root

rm wenucomp.o; gmake; mv wenucomp wenucomp.${tag} ; 
./wenucomp.${tag}  ${wendata}    ${wenpmcs}     1 0 0 1 0 81.95  > log.${tag} 
mv fitter_backgrounds.root fitter_backgrounds.${tag}.root; 
root -l fitter_backgrounds.${tag}.root plot.C
*/



{

TCanvas *c1 = new TCanvas("c1","1",50,10,800,250);
c1->Divide(3,1);

_file0->cd();
cout<<"Entries MT PT MET "<<bkgd_signal_wmass->Integral()<<"  "<<bkgd_signal_elecpT->Integral()<<"  "<<bkgd_signal_Met->Integral()<<endl;
cout<<"Nbins   MT PT MET "<<bkgd_signal_wmass->GetNbinsX()<<"  "<<bkgd_signal_elecpT->GetNbinsX()<<"  "<<bkgd_signal_Met->GetNbinsX()<<endl;

//bkgd_signal_wmass->SetLineColor(2);
//bkgd_signal_elecpT->SetLineColor(2);
//bkgd_signal_Met->SetLineColor(2);
// c1->cd(1); bkgd_signal_wmass->DrawCopy();
// c1->cd(2); bkgd_signal_wmass->DrawCopy();//bkgd_signal_elecpT->DrawCopy();
// c1->cd(3); bkgd_signal_wmass->DrawCopy();//bkgd_signal_Met->DrawCopy();

bkgd_signal_wmass->GetXaxis()->SetRangeUser(50,110);
bkgd_signal_elecpT->GetXaxis()->SetRangeUser(20,70);
bkgd_signal_Met->GetXaxis()->SetRangeUser(20,70);

c1->cd(1); bkgd_signal_wmass->DrawCopy();
c1->cd(2); bkgd_signal_elecpT->DrawCopy();//bkgd_signal_elecpT->DrawCopy();
c1->cd(3); bkgd_signal_Met->DrawCopy();//bkgd_signal_Met->DrawCopy();

//  _file1->cd();
// // cout<<"Entries MT PT MET "<<bkgd_signal_wmass->Integral()<<"  "<<bkgd_signal_elecpT->Integral()<<"  "<<bkgd_signal_Met->Integral()<<endl;
// // c1->cd(1); bkgd_signal_wmass->DrawCopy("Sames");
// // c1->cd(2); bkgd_signal_wmass->DrawCopy("Sames");// bkgd_signal_elecpT->DrawCopy("Sames");
// // c1->cd(3); bkgd_signal_wmass->DrawCopy("Sames");//bkgd_signal_Met->DrawCopy("Sames");
// c1->cd(1); bkgd_signal_wmass->DrawCopy("Sames");
// c1->cd(2); bkgd_signal_elecpT->DrawCopy("Sames");// bkgd_signal_elecpT->DrawCopy("Sames");
// c1->cd(3); bkgd_signal_Met->DrawCopy("Sames");//bkgd_signal_Met->DrawCopy("Sames");

}
