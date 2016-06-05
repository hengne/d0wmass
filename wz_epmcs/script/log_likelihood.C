/////////////////////////////////////////////////////////////
//Code used to calculate the Log-Likelihood
//lnL = sum[x_i * ln(u_i) - u_i - sum ln(x_i)]
//where x_i is number of events in each bin
//u_i is the number of expected events in each bin
/////////////////////////////////////////////////////////////


double Log_Likelihood( TH1F *hdata, TH1F *hmc, 
		      double& min_fit_range, double& max_fit_range) {

  if( hdata->GetNbinsX() != hmc->GetNbinsX() ) {
    cout << "Data and MC histograms have difference bins" << endl;
    return 0;
  }

  double likelihood = 0.;

  for(int ibin=0; ibin<hdata->GetNbinsX(); ++ibin) {
    double data_center = hdata->GetBinCenter(ibin);

    if( (data_center >= min_fit_range) && (data_center <= max_fit_range) ) {
      int data_content = (int)(hdata->GetBinContent(ibin));
      double mc_content = hmc->GetBinContent(ibin);

      if(data_content > 0) {

	//calculate sum{ln(x_i)}
	double sum1 = 0.;
	for(int nn=data_content; nn>0; --nn) sum1 += TMath::Log(nn);

	if(mc_content > 0) 
	  likelihood += data_content*TMath::Log(mc_content) - mc_content - sum1;

      }//data_content > 0


    }//fit range

  }//loop over all bins

  cout << "Log Likelihood = " << (-likelihood) << endl;

  return (-likelihood);
}
