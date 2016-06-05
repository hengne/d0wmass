#include "wmass_analysis/MakeAsciiFile.hpp"
#include "cafe/Stat.hpp"
#include "cafe/Config.hpp"

#include <cstdlib>
#include <stdexcept>
#include <sstream>

using namespace cafe;
using namespace std;

namespace caf_mc_util {

  MakeAsciiFile::MakeAsciiFile(const char *name) : Processor(name) {

     Config config(name);
//      _nsample = config.get("NumberOfSample",2);
//      _passsample = config.get("SampleToPass",0);
//      _correctMCweight = config.get("CorrectMCweight",true);  
  }
  
  void MakeAsciiFile::begin() {
      analysis_form = "nevt/I:event_weight/D:wpt/D:weta/D:wq/I:elpt/D:eleta/D:eleq/I:nuelept/D:nueleeta/D:taupt/D:taueta/D:tauq/I:nutaupt[2]/D:nutaueta[2]/D:met/D";
     
//       _ana_tree = new TTree("ana_tree","Analysis Tree");
      
//       TBranch * b_ana = _ana_tree->Branch("mc_ana", &_ana.nevt, analysis_form.c_str());
      
//       _ewetau = new TH1D("ewetau", "(E_{#nu_{e}}+E_{e})/E_{#tau}", 100, 0, 1);
//       _ewetau->Sumw2();
//       _ptwtau = new TH1D("ptwtau", "p_{T}^{e+#nu_{e}}", 150, 0, 150);
//       _ptwtau->Sumw2();
      _event_number = 1;
      outasciifile.open( "bosons.txt" );
  }
	
  bool MakeAsciiFile::processEvent(Event& event)
  {
      TLorentzVector w_vec;
      TLorentzVector el1_vec , el2_vec , nue_vec;
      TLorentzVector tau_vec , nutau1_vec , nutau2_vec;
      int w_id = -100; 
      int el1_id = -100, el2_id = -100, nue_id = -100;
      int tau_id = -100, nutau1_id = -100, nutau2_id = -100;
      vector<TLorentzVector> photon_vecs;
      
      _ana.wq = 0;
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
        
        if( absid != 24 && absid != 23 ) continue;
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
        double eta = ptcl->Eta();
        
        w_vec.SetPxPyPzE( px , py , pz , pE );

        _ana.wpt = pT;
        _ana.weta = eta;
        _ana.wq = int(ptcl->charge());

        for( int j = 0 ; j < ndaughters ; j++ )
        {
          const TMBMCpart* daught = vtx->getDaughter(j);
          const TMBMCvtx *dvtx = daught->getDMCvtx();

          if( daught->isStable() != 1 )
            continue;
          
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
            if( nutau1_id == -100 )
            {
              if( id == 16  ) nutau1_id = 15;
              if( id == -16 ) nutau1_id = -15;
              nutau1_vec.SetPxPyPzE( px , py , pz , pE );
            }
            else if( nutau2_id == -100 )
            {
              if( id == 16  ) nutau2_id = 15;
              if( id == -16 ) nutau2_id = -15;
              nutau2_vec.SetPxPyPzE( px , py , pz , pE );
            }
          }
          else if( absid == 15 )
          {
            _ana.taupt = pT;
            _ana.taueta = eta;
            _ana.tauq = int(daught->charge());
            tau.SetPxPyPzE(px,py,pz,pE);
            if( tau_id == -100 )
            {
              if( id == 15 ) tau_id = 16;
              if( id == -15 ) tau_id = -16;
              tau_vec = tau;
            }
          }
          else if( absid == 11 )
          {
            _ana.elpt = pT;
            _ana.eleta = eta;
            _ana.eleq = int(daught->charge());
            ele.SetPxPyPzE(px,py,pz,pE);
            if( el1_id == -100 )
            {
              if( id == 11 ) el1_id = 12;
              if( id == -11 ) el1_id = -12;
              el1_vec = ele;
            }
            else if( el2_id == -100 && ( w_id == 90 ) )
            {
              if( id == 11 ) el2_id = 12;
              if( id == -11 ) el2_id = -12;
              el2_vec = ele;
            }
          }
          else if( absid == 12 )
          {
            _ana.nuelept = pT;
            _ana.nueleeta = eta;
            metx -= px;
            mety -= py;
            nue.SetPxPyPzE(px,py,pz,pE);
            if( nue_id == -100 )
            {
              if( id == 12 ) nue_id = 11;
              if( id == -12 ) nue_id = -11;
              nue_vec = nue;
            }
          }
          else if( absid == 22 )
          {
            TLorentzVector phot;
            phot.SetPxPyPzE( px , py , pz , pE );
            photon_vecs.push_back( phot );
          }

          if( absid != 15 ) continue;
          if( !dvtx ) continue;
          int nddaughters = dvtx->ndaughters();
//           out() << "W ndaughters " << nddaughters << endl;
          if( nddaughters == 0 ) continue;
          for( int k = 0 ; k < nddaughters ; k++ )
          {
            const TMBMCpart* ddaught = dvtx->getDaughter(k);
           
            if( ddaught->isStable() != 1 )
              continue;
            
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
              if( el1_id == -100 )
              {
                if( id == 11 ) el1_id = 12;
                if( id == -11 ) el1_id = -12;
                el1_vec = ele;
              }
            }
            else if( absid == 12 )
            {
              _ana.nuelept = pT;
              _ana.nueleeta = eta;
              metx -= px;
              mety -= py;
              nue.SetPxPyPzE(px,py,pz,pE);
              if( nue_id == -100 )
              {
                if( id == 12 ) nue_id = 11;
                if( id == -12 ) nue_id = -11;
                nue_vec = nue;
              }
            }
            else if( absid == 16 )
            {
              _ana.nutaupt[1] = pT;
              _ana.nutaueta[1] = eta;
              metx -= px;
              mety -= py;
              if( nutau1_id == -100 )
              {
                if( id == 16  ) nutau1_id = 15;
                if( id == -16 ) nutau1_id = -15;
                nutau1_vec.SetPxPyPzE( px , py , pz , pE );
              }
              else if( nutau2_id == -100 )
              {
                if( id == 16  ) nutau2_id = 15;
                if( id == -16 ) nutau2_id = -15;
                nutau2_vec.SetPxPyPzE( px , py , pz , pE );
              }
            }
            else if( absid == 211 )
            {
              pi.SetPxPyPzE(px,py,pz,pE);
            }
            else if( absid == 22 )
            {
              TLorentzVector phot;
              phot.SetPxPyPzE( px , py , pz , pE );
              photon_vecs.push_back( phot );
            }
          }
          if( _ana.elpt < 0 ) return false;
//           if( !(pi.E() > 0 ) || nddaughters>2 ) return false;
        }
      }
//       cout << " number of w bosons " << number_of_w << endl;
//       if( pi.E() > 0 )
//       {
//         _ewetau->Fill( pi.E()/tau.E() );
//         _ptwtau->Fill( pi.Pt() );
//       }
//       else
//       {
//         _ewetau->Fill( (ele+nue).E() / tau.E() );
//         _ptwtau->Fill( (ele+nue).Pt() );
//       }

      _ana.met = TMath::Sqrt( metx*metx + mety*mety );

//       _ana_tree->Fill();

      outasciifile << " " << _event_number++ << "  1." << endl;
      outasciifile << "  0.  0.  0." << endl;
      outasciifile << " " << w_id << " " << w_vec.Px() << " " << w_vec.Py() << " " << w_vec.Pz() << " " << w_vec.E() << " 0 0" << endl;
      if( nutau1_id != -100 )
        outasciifile << " " << nutau1_id << " " << nutau1_vec.Px() << " " << nutau1_vec.Py() << " " << nutau1_vec.Pz() << " " << nutau1_vec.E() << " 1 0" << endl;
      if( tau_id != -100 )
        outasciifile << " " << tau_id << " " << tau_vec.Px() << " " << tau_vec.Py() << " " << tau_vec.Pz() << " " << tau_vec.E() << " 0 0" << endl;
      if( nutau2_id != -100 )
        outasciifile << " " << nutau2_id << " " << nutau2_vec.Px() << " " << nutau2_vec.Py() << " " << nutau2_vec.Pz() << " " << nutau2_vec.E() << " 1 0" << endl;
      if( el1_id != -100 )
        outasciifile << " " << el1_id << " " << el1_vec.Px() << " " << el1_vec.Py() << " " << el1_vec.Pz() << " " << el1_vec.E() << " 1 0" << endl;
      if( el2_id != -100 )
        outasciifile << " " << el2_id << " " << el2_vec.Px() << " " << el2_vec.Py() << " " << el2_vec.Pz() << " " << el2_vec.E() << " 1 0" << endl;
      if( nue_id != -100 )
        outasciifile << " " << nue_id << " " << nue_vec.Px() << " " << nue_vec.Py() << " " << nue_vec.Pz() << " " << nue_vec.E() << " 1 0" << endl;
      for( int nphot = 0 ; nphot < photon_vecs.size() ; nphot++ )
      {
        outasciifile << " 10 " << photon_vecs[nphot].Px() << " " << photon_vecs[nphot].Py() << " " << photon_vecs[nphot].Pz() << " " << photon_vecs[nphot].E() << " 1 0" << endl;
      }
      outasciifile << " 0" << endl;
      
      return true;
  }

  void MakeAsciiFile::finish() {
    outasciifile << " 0 0" << endl;
    outasciifile.close();
    out() << "======= MakeAsciiFile ============" << endl ;
    out() << "================================" << endl ;
  }
  
  void MakeAsciiFile::inputFileOpened(TFile *file) {
     out() << "a new file" << endl;
  }
}

ClassImp(caf_mc_util::MakeAsciiFile)

