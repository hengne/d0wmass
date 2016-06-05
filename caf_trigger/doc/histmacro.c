{
    TFile::Open("d0evtwt.root");
    
    Hist1DBefore->SetTitle("TopDiem Weights With Sigmas");

    Hist1DAfter->SetTitle("TopDiem Weights With Sigmas");
    Hist1DAfter->SetFillColor(102);

    Hist1DAftersig1->SetTitle("TopDiem Weights With Sigmas");
    Hist1DAftersig1->SetMarkerStyle(22);
    Hist1DAftersig1->SetMarkerSize(0.8);
    Hist1DAftersig1->SetMarkerColor(103);
    Hist1DAftersig1->SetFillColor(103);

    Hist1DAftersig2->SetTitle("TopDiem Weights With Sigmas");
    Hist1DAftersig2->SetMarkerStyle(23);
    Hist1DAftersig2->SetMarkerSize(0.8);
    Hist1DAftersig2->SetMarkerColor(104);
    Hist1DAftersig2->SetFillColor(104);

    Hist1DBefore->SetXTitle("EMscone Pt()");
    Hist1DBefore->SetYTitle("Num Events");
    Hist1DBefore->SetTitle("Z->ee MC, EMscone Pt(), TopDiem trigger weights");
    Hist1DBefore->SetName("caf_trigger out");
        
    Hist1DBefore->Draw();
    Hist1DAftersig1->Draw("same");
    Hist1DAfter->Draw("same");
    Hist1DAftersig2->Draw("same");


    leg = new TLegend(0.4,0.6,0.89,0.89);
    leg->AddEntry(Hist1DBefore,"Before Weights","f");
    leg->AddEntry(Hist1DAfter,"With Weights 0 Sigma","f");
    leg->AddEntry(Hist1DAftersig1,"With Weights +1 Sigma","f");
    leg->AddEntry(Hist1DAftersig2,"With Weights -1 Sigma","f");
    // oops we forgot the blue line... add it after
    // and add a header (or "title") for the legend
    leg->SetHeader("Legend");
    leg->Draw();
}
