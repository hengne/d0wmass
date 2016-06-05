#include "wmass_analysis/WTauStudy.hpp"
#include "cafe/Stat.hpp"
#include "cafe/Config.hpp"

#include <cstdlib>
#include <stdexcept>
#include <sstream>

using namespace cafe;
using namespace std;

namespace caf_mc_util {

  WTauStudy::WTauStudy(const char *name) : Processor(name) {

     Config config(name);
//      _nsample = config.get("NumberOfSample",2);
//      _passsample = config.get("SampleToPass",0);
//      _correctMCweight = config.get("CorrectMCweight",true);  
  }
  
  void WTauStudy::begin() {
      analysis_form = "nevt/I:event_weight/D:mw/D:wpt/D:weta/D:wq/I:elpt/D:eleta/D:eleq/I:nuelept/D:nueleeta/D:taupt/D:taueta/D:tauq/I:nutaupt[2]/D:nutaueta[2]/D:met/D";
     
      _tau_file = new TFile( "result_tau.root" , "recreate" );
      
//       _ana_tree = new TTree("ana_tree","Analysis Tree");
      
//       TBranch * b_ana = _ana_tree->Branch("mc_ana", &_ana.nevt, analysis_form.c_str());
      
      _ewetau = new TH1D("ewetau", "(E_{#nu_{e}}+E_{e})/E_{#tau}", 100, 0, 1);
      _ptwtau = new TH1D("ptwtau", "p_{T}^{e+#nu_{e}}", 150, 0, 150);

      _MW_hist = new TH1D("mw", "M_{W}", 300, 50., 200.);
      _WPT_hist = new TH1D("wpt", "p_T^{W}", 100, 0, 50);
      _WETA_hist = new TH1D("weta", "#eta_{W}", 100, -10., 10.);
      _ELPT_hist = new TH1D("elpt", "p_T^{e}", 200, 0., 100.);
      _ELETA_hist = new TH1D("eleta", "#eta_{e}", 60, -3., 3.);
      _NUELEPT_hist = new TH1D("nuelpt", "p_T^{#nu e}", 200, 0., 100.);
      _NUELETA_hist = new TH1D("nueleta", "#eta_{#nu e}", 60, -3., 3.);
      _TAUPT_hist = new TH1D("taupt", "p_T^{#tau}", 200, 0., 100.);
      _TAUETA_hist = new TH1D("taueta", "#eta_{#tau}", 60, -3., 3.);
      _NUTAUPT_hist = new TH1D("nutaupt", "p_T^{#nu #tau}", 200, 0., 100.);
      _NUTAUETA_hist = new TH1D("nutaueta", "#eta_{#nu #tau}", 60, -3., 3.);
      _PIPT_hist = new TH1D("pipt", "p_T^{#pi}", 200, 0., 100.);
      _MET_hist = new TH1D("mett", "MET", 200, 0., 100.);

      _ewetau->Sumw2();
      _ptwtau->Sumw2();
      _MW_hist->Sumw2();
      _WPT_hist->Sumw2();
      _WETA_hist->Sumw2();
      _ELPT_hist->Sumw2();
      _ELETA_hist->Sumw2();
      _NUELEPT_hist->Sumw2();
      _NUELETA_hist->Sumw2();
      _TAUPT_hist->Sumw2();
      _TAUETA_hist->Sumw2();
      _NUTAUPT_hist->Sumw2();
      _NUTAUETA_hist->Sumw2();
      _PIPT_hist->Sumw2();
      _MET_hist->Sumw2();

  }
	
  bool WTauStudy::processEvent(Event& event)
  {
      TLorentzVector w_vec;
      TLorentzVector el1_vec , el2_vec , nue_vec;
      TLorentzVector tau_vec , nutau1_vec , nutau2_vec;
      int w_id = -100; 
      int el1_id = -100, el2_id = -100, nue_id = -100;
      int tau_id = -100, nutau1_id = -100, nutau2_id = -100;
      vector<TLorentzVector> photon_vecs;

      _ana.wq = 0;
      _ana.mw = -1;
      _ana.wpt = -1;
      _ana.elpt = -1;
      _ana.eleq = 0;
      _ana.nuelept = -1;
      _ana.taupt = -1;
      _ana.tauq = 0;
      _ana.met = -1;

      double metx=0 , mety=0;

      const TMBGlobal * _glob = event.getGlobal();
      _ana.nevt = _glob->evtno();
//       out() << "evtno " << _ana.nevt << endl;
      const TMBMCevtInfo * _mcglob = event.getMCEventInfo();
      _ana.event_weight = _mcglob->weight();
//       out() << "evtwt " << _ana.event_weight << endl;

      int nparts = _mcglob->npart(0);
//       out() << "nparts " << nparts << endl;

//       _ana.event_weight = stat.pointer()->eventWeight();
//       _ana.event_weight = 1.0;
      
//       Collection<TMBMCvtx>  AllMCvtxs  = event.getMCVertices();
//       const TMBMCvtx &PV = AllMCvtxs[0];
      
      cafe::Collection<TMBMCpart> mcparts = event.getMCParticles();
//       out() << "mcparts size " << mcparts.size() << endl;

      TLorentzVector ele , nue , tau , pi;
      int number_of_w = 0;
      for( int i = 0 ; i < nparts ; i++ )
      {
        const TMBMCpart * ptcl = &mcparts[i];
        int absid = ptcl->abspdgid();
        int id = ptcl->pdgid();
        
//         if( ptcl->isStable() != 1 )
//           continue;

        const TMBMCvtx *vtx = ptcl->getDMCvtx();
        
        if( absid != 24 ) continue;
        if( id == 24 ) {
          w_id = 80;
          number_of_w++;
        }
        else if( id == -24 ) {
          w_id = -80;
          number_of_w++;
        }
        else if( id == 23 ) w_id = 90;
        if( !vtx ) continue;
        int ndaughters = vtx->ndaughters();
//         out() << "W ndaughters " << ndaughters << " " << absid << " " << ptcl->isStable() << endl;
        if( ndaughters == 0 ) continue;

        double px = ptcl->Px();
        double py = ptcl->Py();
        double pz = ptcl->Pz();
        double pE = ptcl->E();
        double pT = ptcl->Pt();
        double mass = ptcl->M();
        double eta = ptcl->Eta();

        w_vec.SetPxPyPzE( px , py , pz , pE );

        _ana.mw = mass;
        _ana.wpt = pT;
        _ana.weta = eta;
        _ana.wq = int(ptcl->charge());

        for( int j = 0 ; j < ndaughters ; j++ )
        {
          const TMBMCpart* daught = vtx->getDaughter(j);
          const TMBMCvtx *dvtx = daught->getDMCvtx();
          
//           if( daught->isStable() != 1 )
//             continue;
          
          absid = daught->abspdgid();
          id = daught->pdgid();
          
          px = daught->Px();
          py = daught->Py();
          pz = daught->Pz();
          pE = daught->E();
          pT = daught->Pt();
          eta = daught->Eta();
          
          if( absid == 16 )
          {
            _ana.nutaupt[0] = pT;
            _ana.nutaueta[0] = eta;
            metx -= px;
            mety -= py;
          }
          else if( absid == 15 )
          {
            _ana.taupt = pT;
            _ana.taueta = eta;
            _ana.tauq = int(daught->charge());
            tau.SetPxPyPzE(px,py,pz,pE);
          }

          if( absid != 15 ) continue;
          if( !dvtx ) continue;
          int nddaughters = dvtx->ndaughters();
//           out() << "W ndaughters " << nddaughters << endl;
          if( nddaughters == 0 ) continue;
          for( int k = 0 ; k < nddaughters ; k++ )
          {
            const TMBMCpart* ddaught = dvtx->getDaughter(k);
            
            absid = ddaught->abspdgid();
            id = ddaught->pdgid();
            
            px = ddaught->Px();
            py = ddaught->Py();
            pz = ddaught->Pz();
            pE = ddaught->E();
            pT = ddaught->Pt();
            eta = ddaught->Eta();
            
            if( absid == 11 )
            {
              _ana.elpt = pT;
              _ana.eleta = eta;
              _ana.eleq = int(ddaught->charge());
              ele.SetPxPyPzE(px,py,pz,pE);
            }
            else if( absid == 12 )
            {
              _ana.nuelept = pT;
              _ana.nueleeta = eta;
              metx -= px;
              mety -= py;
              nue.SetPxPyPzE(px,py,pz,pE);
            }
            else if( absid == 16 )
            {
              _ana.nutaupt[1] = pT;
              _ana.nutaueta[1] = eta;
              metx -= px;
              mety -= py;
            }
            else if( absid == 211 )
            {
              pi.SetPxPyPzE(px,py,pz,pE);
            }
          }
          if( _ana.elpt < 0 ) return false;
//           if( !(pi.E() > 0 ) || nddaughters>2 ) return false;
        }
      }
//       cout << " number of w bosons " << number_of_w << endl;
      if( pi.E() > 0 )
      {
        _ewetau->Fill( pi.E()/tau.E() );
        _ptwtau->Fill( pi.Pt() );
      }
      else
      {
        _ewetau->Fill( (ele+nue).E() / tau.E() );
        _ptwtau->Fill( (ele+nue).Pt() );
      }

      _ana.met = TMath::Sqrt( metx*metx + mety*mety );

      _MW_hist->Fill( _ana.mw , _ana.event_weight );
      _WPT_hist->Fill( _ana.wpt , _ana.event_weight );
      _WETA_hist->Fill( _ana.weta , _ana.event_weight );
      _ELPT_hist->Fill( _ana.elpt , _ana.event_weight );
      _ELETA_hist->Fill( _ana.eleta , _ana.event_weight );
      _NUELEPT_hist->Fill( _ana.nuelept , _ana.event_weight );
      _NUELEPT_hist->Fill( _ana.nuelept , _ana.event_weight );
      _NUELETA_hist->Fill( _ana.nueleeta , _ana.event_weight );
      _NUELETA_hist->Fill( _ana.nueleeta , _ana.event_weight );
      _TAUPT_hist->Fill( _ana.taupt , _ana.event_weight );
      _TAUETA_hist->Fill( _ana.taueta , _ana.event_weight );
      _NUTAUPT_hist->Fill( _ana.nutaupt[0] , _ana.event_weight );
      _NUTAUPT_hist->Fill( _ana.nutaupt[1] , _ana.event_weight );
      _NUTAUETA_hist->Fill( _ana.nutaueta[0] , _ana.event_weight );
      _NUTAUETA_hist->Fill( _ana.nutaueta[1] , _ana.event_weight );
      _PIPT_hist->Fill( pi.Pt() , _ana.event_weight );
      _MET_hist->Fill( _ana.met , _ana.event_weight );

//       _ana_tree->Fill();

      return true;

  }

  void WTauStudy::finish() {
    _tau_file->cd();
//     _ana_tree->Write();
    _ewetau->Write();
    _ptwtau->Write();
    _MW_hist->Write();
    _WPT_hist->Write();
    _WETA_hist->Write();
    _ELPT_hist->Write();
    _ELETA_hist->Write();
    _NUELEPT_hist->Write();
    _NUELETA_hist->Write();
    _TAUPT_hist->Write();
    _TAUETA_hist->Write();
    _NUTAUPT_hist->Write();
    _NUTAUETA_hist->Write();
    _PIPT_hist->Write();
    _MET_hist->Write();
    
    _tau_file->Close();
    
    out() << "======= WTauStudy ============" << endl ;
    out() << "================================" << endl ;
  }
  
  void WTauStudy::inputFileOpened(TFile *file) {
     out() << "a new file" << endl;
  }
}

ClassImp(caf_mc_util::WTauStudy)

