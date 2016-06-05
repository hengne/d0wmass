#include <iostream>
#include <fstream>
#include "math.h"
#include "TFile.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TTree.h"

struct OutputStruct {
  int zpt;
  double eta_imbalance_mean;
  double eta_imbalance_mean_error;
  double eta_imbalance_rms;
  double eta_imbalance_rms_error;
  double delta_phi_rms;
  double delta_phi_rms_error;
  double scale_a;
  double scale_b;
  double tau_had;
  double resolution_a;
  double resolution_b;
  double alpha_mb;
  double phi_a;
  double phi_b;
};

struct ReadingStruct {
  int zpt;
  double eta_imbalance_mean;
  double eta_imbalance_rms;
  double delta_phi_mean;
  double delta_phi_rms;
  double scale_a;
  double scale_b;
  double tau_had;
  double resolution_a;
  double resolution_b;
  double alpha_mb;
  double phi_a;
  double phi_b;
  double evt_weight;
  double evt_weight_2;
};

void hadd_recoil(TString file, TString outfile) {


  TString root_name("/recoil_tree.root");
  TString log_name("/pmcs.log");

  ReadingStruct PointerData;
  ReadingStruct ReadingData;
  OutputStruct OutputData;
  
  TTree* PointerTree;

  TFile* OutputFile = new TFile(outfile,"RECREATE");
  TTree* OutputTree = new TTree("OutputTree","Recoil Study Output");
  OutputTree->Branch("zpt",&OutputData.zpt,"zpt/I");
  OutputTree->Branch("eta_imbalance_mean",&OutputData.eta_imbalance_mean,"eta_imbalance_mean/D");
  OutputTree->Branch("eta_imbalance_mean_error",&OutputData.eta_imbalance_mean_error,"eta_imbalance_mean_error/D");
  OutputTree->Branch("eta_imbalance_rms",&OutputData.eta_imbalance_rms,"eta_imbalance_rms/D");
  OutputTree->Branch("eta_imbalance_rms_error",&OutputData.eta_imbalance_rms_error,"eta_imbalance_rms_error/D");
  OutputTree->Branch("delta_phi_rms",&OutputData.delta_phi_rms,"delta_phi_rms/D");
  OutputTree->Branch("delta_phi_rms_error",&OutputData.delta_phi_rms_error,"delta_phi_rms_error/D");
  OutputTree->Branch("scale_a",&OutputData.scale_a,"scale_a/D");
  OutputTree->Branch("scale_b",&OutputData.scale_b,"scale_b/D");
  OutputTree->Branch("tau_had",&OutputData.tau_had,"tau_had/D");
  OutputTree->Branch("resolution_a",&OutputData.resolution_a,"resolution_a/D");
  OutputTree->Branch("resolution_b",&OutputData.resolution_b,"resolution_b/D");
  OutputTree->Branch("alpha_mb",&OutputData.alpha_mb,"alpha_mb/D");
  OutputTree->Branch("phi_a",&OutputData.phi_a,"phi_a/D");
  OutputTree->Branch("phi_b",&OutputData.phi_b,"phi_b/D");

  // Opens the file with the directory list
  ifstream dir_list(file, ifstream::in);
  TString dir_name;

  int n=0;
  // Get a Pointer Tree
  while(n == 0 && !dir_list.eof()){

    // Read the files until find a tree with more than zero entries.
    // This is to avois SAM and CAB confusions.
    dir_name.ReadLine(dir_list);
    cout << "Reading directory " << dir_name << endl;
    ifstream log_file(dir_name + log_name, ifstream::in);
    n=0;
    while(n==0 && !log_file.eof()) {
      TString temp_line;
      temp_line.ReadLine(log_file);
      if (temp_line.Contains("number of events processed")) {
	TObjArray* temp_tokens = temp_line.Tokenize(' ');
	TObjString* temp_os = (TObjString*)temp_tokens->At(temp_tokens->GetLast()); 
	TString n_string = temp_os->GetString();
	if(n_string.Atoi()) {
	  n=n_string.Atoi();
	  cout << "Found " << n << " events!" << endl;
	}
      }
    }
    log_file.close();

    if (n==0) {
      cout << "No events found!" << endl;
      continue;
    }

    //Ok, found a tree, now uses it as pointer
    TFile* root_file = new TFile(dir_name + root_name,"READ");
    if (!root_file->IsOpen()) continue;
    TTree* temp_tree = (TTree*) gROOT->FindObject("ZRecoilBifurcateOutputTree");

    OutputFile->cd();
    PointerTree = temp_tree->CloneTree();
    delete temp_tree;
    PointerTree->SetBranchAddress("zpt",&PointerData.zpt);
    PointerTree->SetBranchAddress("eta_imbalance_mean",&PointerData.eta_imbalance_mean);
    PointerTree->SetBranchAddress("eta_imbalance_rms",&PointerData.eta_imbalance_rms);
    PointerTree->SetBranchAddress("delta_phi_mean",&PointerData.delta_phi_mean);
    PointerTree->SetBranchAddress("delta_phi_rms",&PointerData.delta_phi_rms);
    PointerTree->SetBranchAddress("scale_a",&PointerData.scale_a);
    PointerTree->SetBranchAddress("scale_b",&PointerData.scale_b);
    PointerTree->SetBranchAddress("tau_had",&PointerData.tau_had);
    PointerTree->SetBranchAddress("resolution_a",&PointerData.resolution_a);
    PointerTree->SetBranchAddress("resolution_b",&PointerData.resolution_b);
    PointerTree->SetBranchAddress("alpha_mb",&PointerData.alpha_mb);
    PointerTree->SetBranchAddress("phi_a",&PointerData.phi_a);
    PointerTree->SetBranchAddress("phi_b",&PointerData.phi_b);
    PointerTree->SetBranchAddress("evt_weight",&PointerData.evt_weight);
    PointerTree->SetBranchAddress("evt_weight_2",&PointerData.evt_weight_2);
    root_file->Close();


    cout << "Using " << dir_name + root_name << " as reference." << endl;

  }// Finish the pointer search.
  
  double final_eta_imbalance_mean;
  double final_eta_imbalance_mean_error;
  double final_eta_imbalance_rms;
  double final_eta_imbalance_rms_error;
  double final_delta_phi_mean;
  double final_delta_phi_rms;
  double final_delta_phi_rms_error;
  double final_evt_weight;
  double final_evt_weight_2;

  int nentries = PointerTree->GetEntries();
  // Get each point in parameter space...
  for(int i=0; i<nentries; i++){
    if ((i%100)==0) cout << "Processing parameter space " << i << "/" << nentries << endl;
    PointerTree->GetEntry(i);    
    final_eta_imbalance_mean = PointerData.eta_imbalance_mean;
    final_eta_imbalance_rms = PointerData.eta_imbalance_rms;
    if (isnan(final_eta_imbalance_rms)) final_eta_imbalance_rms = 0;
    final_delta_phi_mean = PointerData.delta_phi_rms;
    final_delta_phi_rms = PointerData.delta_phi_rms;
    final_evt_weight = PointerData.evt_weight;
    final_evt_weight_2 = PointerData.evt_weight_2;

//      cout << "Initial values" << endl;
//      cout << "--------------------" << endl;
//      cout << "Eta Imbalance Mean: " << final_eta_imbalance_mean << endl;
//      cout << "Eta Imbalance RMS : " << final_eta_imbalance_rms << endl;
//      cout << "Delta Phi Mean    : " << final_delta_phi_mean << endl;
//      cout << "Delta Phi RMS     : " << final_delta_phi_rms << endl;
//      cout << "Event weight      : " << final_evt_weight << endl;
//      cout << "--------------------" << endl;


    // and loop over files to find the values.
    streampos lenght = dir_list.tellg();
    while(!dir_list.eof()){
      dir_name.ReadLine(dir_list);
      if(dir_name.Contains('#')) break;

      TFile* temp_root_file = new TFile(dir_name + root_name,"READ");
      if (!temp_root_file->IsOpen()) continue;
      TTree* temp_tree = (TTree*) gROOT->FindObject("ZRecoilBifurcateOutputTree");

      temp_tree->SetBranchAddress("zpt",&ReadingData.zpt);
      temp_tree->SetBranchAddress("eta_imbalance_mean",&ReadingData.eta_imbalance_mean);
      temp_tree->SetBranchAddress("eta_imbalance_rms",&ReadingData.eta_imbalance_rms);
      temp_tree->SetBranchAddress("delta_phi_mean",&ReadingData.delta_phi_mean);
      temp_tree->SetBranchAddress("delta_phi_rms",&ReadingData.delta_phi_rms);
      temp_tree->SetBranchAddress("scale_a",&ReadingData.scale_a);
      temp_tree->SetBranchAddress("scale_b",&ReadingData.scale_b);
      temp_tree->SetBranchAddress("tau_had",&ReadingData.tau_had);
      temp_tree->SetBranchAddress("resolution_a",&ReadingData.resolution_a);
      temp_tree->SetBranchAddress("resolution_b",&ReadingData.resolution_b);
      temp_tree->SetBranchAddress("alpha_mb",&ReadingData.alpha_mb);
      temp_tree->SetBranchAddress("phi_a",&ReadingData.phi_a);
      temp_tree->SetBranchAddress("phi_b",&ReadingData.phi_b);
      temp_tree->SetBranchAddress("evt_weight",&ReadingData.evt_weight);
      temp_tree->SetBranchAddress("evt_weight_2",&ReadingData.evt_weight_2);

      int temp_nentries = temp_tree->GetEntries(); 
      bool found = false;
      for (int j=0; (!found && j<temp_nentries); j++){

	temp_tree->GetEntry(j);
	bool selection = ((PointerData.scale_a == ReadingData.scale_a) &&
			  (PointerData.scale_b == ReadingData.scale_b) &&
			  (PointerData.tau_had == ReadingData.tau_had) &&
			  (PointerData.resolution_a == ReadingData.resolution_a) &&
			  (PointerData.resolution_b == ReadingData.resolution_b) &&
			  (PointerData.alpha_mb == ReadingData.alpha_mb) &&
			  (PointerData.phi_a == ReadingData.phi_a) &&
			  (PointerData.phi_b == ReadingData.phi_b) &&
			  (PointerData.zpt == ReadingData.zpt));

	// Do the calculation
	if(selection && !(ReadingData.evt_weight==0)) {
	  double temp_evt_weight = ReadingData.evt_weight;
	  double temp_eta_imbalance_rms;
	  if (isnan(ReadingData.eta_imbalance_rms)) {
	    temp_eta_imbalance_rms = 0;
	  } else {
	    temp_eta_imbalance_rms = ReadingData.eta_imbalance_rms;
	  }
	  double temp_delta_phi_rms;
	  if (isnan(ReadingData.delta_phi_rms)) {
	    temp_delta_phi_rms = 0;
	  } else {
	    temp_delta_phi_rms = ReadingData.delta_phi_rms;
	  }

//  	  cout << "Found entry in "  << dir_name << endl;
//  	  cout << "--------------------" << endl;
//  	  cout << "Eta Imbalance Mean: " << ReadingData.eta_imbalance_mean << endl;
//  	  cout << "Eta Imbalance RMS : " << temp_eta_imbalance_rms << endl;
//  	  cout << "Delta Phi Mean    : " << ReadingData.delta_phi_mean << endl;
//  	  cout << "Delta Phi RMS     : " << ReadingData.delta_phi_rms << endl;
//  	  cout << "Event weight      : " << temp_evt_weight << endl;
//  	  cout << "--------------------" << endl;

    
	  final_eta_imbalance_rms = sqrt((((final_eta_imbalance_rms * final_eta_imbalance_rms +
					    final_eta_imbalance_mean * final_eta_imbalance_mean)*
					   final_evt_weight +
					   (temp_eta_imbalance_rms * temp_eta_imbalance_rms +
					    ReadingData.eta_imbalance_mean * ReadingData.eta_imbalance_mean)*
					   temp_evt_weight)/
					  (final_evt_weight + temp_evt_weight))-
					 (((final_evt_weight * final_eta_imbalance_mean +
					   temp_evt_weight * ReadingData.eta_imbalance_mean)/
					  (final_evt_weight + temp_evt_weight)) *
					 ((final_evt_weight * final_eta_imbalance_mean +
					   temp_evt_weight * ReadingData.eta_imbalance_mean)/
					  (final_evt_weight + temp_evt_weight)))); 
	  final_eta_imbalance_mean = ((final_evt_weight * final_eta_imbalance_mean +
				      temp_evt_weight * ReadingData.eta_imbalance_mean)/
				      (final_evt_weight + temp_evt_weight));

	  final_delta_phi_rms = sqrt((((final_delta_phi_rms * final_delta_phi_rms +
					    final_delta_phi_mean * final_delta_phi_mean)*
					   final_evt_weight +
					   (temp_delta_phi_rms * temp_delta_phi_rms +
					    ReadingData.delta_phi_mean * ReadingData.delta_phi_mean)*
					   temp_evt_weight)/
					  (final_evt_weight + temp_evt_weight))-
					 (((final_evt_weight * final_delta_phi_mean +
					   temp_evt_weight * ReadingData.delta_phi_mean)/
					  (final_evt_weight + temp_evt_weight)) *
					 ((final_evt_weight * final_delta_phi_mean +
					   temp_evt_weight * ReadingData.delta_phi_mean)/
					  (final_evt_weight + temp_evt_weight)))); 
	  final_delta_phi_mean = ((final_evt_weight * final_delta_phi_mean +
				      temp_evt_weight * ReadingData.delta_phi_mean)/
				      (final_evt_weight + temp_evt_weight));


// 	  double old_sumsquares_phi = ((final_delta_phi_rms * final_delta_phi_rms +
// 					2*TMath::Pi()*final_delta_phi_mean)*final_evt_weight - 
// 				       TMath::Pi()*TMath::Pi());
// 	  double new_sumsquares_phi = ((ReadingData.delta_phi_rms * ReadingData.delta_phi_rms +
// 					2*TMath::Pi()*ReadingData.delta_phi_mean)*temp_evt_weight - 
// 				       TMath::Pi()*TMath::Pi());
// 	  double old_sum_phi = final_delta_phi_mean * final_evt_weight;
	  
// 	  double new_sum_phi = ReadingData.delta_phi_mean * temp_evt_weight;

// 	  final_delta_phi_rms = TMath::Sqrt((old_sumsquares_phi + new_sumsquares_phi - 
// 					     2*old_sum_phi*TMath::Pi() - 2*new_sum_phi*TMath::Pi() +
// 					     TMath::Pi()*TMath::Pi())/(final_evt_weight+temp_evt_weight));

// 	  final_delta_phi_mean = (new_sum_phi + old_sum_phi)/(final_evt_weight + temp_evt_weight);

	  final_evt_weight += temp_evt_weight;

	  final_evt_weight_2 += ReadingData.evt_weight_2;

	  found = true;
	}
      }

      delete temp_tree;
      temp_root_file->Close();

//      cout << "Recalculated values" << endl;
//      cout << "--------------------" << endl;
//      cout << "Eta Imbalance Mean: " << final_eta_imbalance_mean << endl;
//      cout << "Eta Imbalance RMS : " << final_eta_imbalance_rms << endl;
//      cout << "Delta Phi Mean    : " << final_delta_phi_mean << endl;
//      cout << "Delta Phi RMS     : " << final_delta_phi_rms << endl;
//      cout << "Event weight      : " << final_evt_weight << endl;
//      cout << "--------------------" << endl;


    } // Read next file

    // Calculate the errors that matters
    double final_statistical_power = (final_evt_weight*final_evt_weight)/final_evt_weight_2;
    final_eta_imbalance_mean_error = final_eta_imbalance_rms/sqrt(final_statistical_power);
    final_eta_imbalance_rms_error = final_eta_imbalance_rms/sqrt(2*final_statistical_power);
    final_delta_phi_rms_error = final_delta_phi_rms/sqrt(2*final_statistical_power);

    // Writes the result    
    OutputData.zpt = PointerData.zpt;
    OutputData.eta_imbalance_mean = final_eta_imbalance_mean;
    OutputData.eta_imbalance_mean_error = final_eta_imbalance_mean_error;
    OutputData.eta_imbalance_rms = final_eta_imbalance_rms;
    OutputData.eta_imbalance_rms_error = final_eta_imbalance_rms_error;
    OutputData.delta_phi_rms = final_delta_phi_rms;
    OutputData.delta_phi_rms_error = final_delta_phi_rms_error;
    OutputData.scale_a = PointerData.scale_a;
    OutputData.scale_b = PointerData.scale_b;
    OutputData.tau_had = PointerData.tau_had;
    OutputData.resolution_a = PointerData.resolution_a;
    OutputData.resolution_b = PointerData.resolution_b;
    OutputData.alpha_mb = PointerData.alpha_mb;
    OutputData.phi_a = PointerData.phi_a;
    OutputData.phi_b = PointerData.phi_b;
    OutputTree->Fill();

    // Put the list back where it was
    dir_list.seekg(lenght);

  } // Read next parameter space point
  delete PointerTree; // Free memory;

  // Writes the output file
  cout << "Writing " << outfile << endl;
  dir_list.close();
  OutputFile->cd();
  OutputTree->Write();
  OutputFile->Close();

} // End of hadd_recoil.C

	

