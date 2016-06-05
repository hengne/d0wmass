#include <math.h>

void matrix (double eff,
	     double efferr,
	     double fake,
	     double fakeerr,
	     double Ntot,
	     double Ntrk,
	     double & Nsig,
	     double & Nsigtrk,
	     double & Nbg,
	     double & Nbgtrk,
	     double & NsigErr,
	     double & NsigtrkErr,
	     double & NbgErr,
	     double & NbgtrkErr) {

  Double_t emf   ;
  Double_t emfsq   ;
  Double_t Nnot   ;
  Double_t NtrkErr;
  Double_t NnotErr;
  
  //Signal
  if ( (eff - fake) > 0.01 ) {
    Nsig = ( Ntrk - fake * Ntot ) / ( eff - fake ) ;
    Nsigtrk = Nsig*eff;
    // dummies for error calculation
    emf     = ( eff - fake );
    emfsq   = emf * emf ;
    Nnot    = Ntot - Ntrk ;
    NtrkErr = sqrt( Ntrk );
    NnotErr = sqrt( Nnot );
    
    // error calculation
    //check error propogation and fix small bugs
    Double_t NtrkTerm = ( (1.-fake) / emf )            * NtrkErr ;
    Double_t NnotTerm = -( fake / emf )          * NnotErr ;
    Double_t NfTerm   = ( ( Ntrk - eff * Ntot ) / emfsq )  * fakeerr ;
    Double_t NeTerm   = ( ( Ntrk - fake * Ntot ) / emfsq ) * efferr ;
    Double_t NetrkTerm =(fake*(fake*Ntot-Ntrk)/emfsq)* efferr ; 
    // sum them up
    NsigErr = sqrt ( NtrkTerm * NtrkTerm +
		     NnotTerm * NnotTerm +
		     NfTerm   * NfTerm   +
  		     NeTerm   * NeTerm   ) ;
    NsigtrkErr = sqrt ( NtrkTerm * NtrkTerm * eff * eff+
		     NnotTerm * NnotTerm * eff * eff+
		     NfTerm   * NfTerm * eff * eff +
  		     NetrkTerm   * NetrkTerm   ) ;
  } else {
    Nsig = 0.;
    Nsigtrk=0.;
    NsigErr = 0.;
    NsigtrkErr = 0.;
  }
  
  // Bkgd
  
  if ( (eff - fake) > 0.01 ){
    // dummies for error calculation
    //     Double_t emf_BKGD     = ( eff - fake );
    //     Double_t emfsq_BKGD   = emf * emf ;
    //     Double_t Nnot_BKGD    = Ntot - Ntrk ;
    //     Double_t NtrkErr_BKGD = sqrt( Ntrk );
    //     Double_t NnotErr = sqrt( Nnot );
    
    // error calculation
    //check error propogation and fix small bugs
    Double_t NtrkTerm  = ( (eff-1.) / emf ) * NtrkErr ;
    Double_t NnotTerm = ( eff / emf )          * NnotErr ;
    Double_t NfTerm   = ( ( Ntrk - eff * Ntot ) / emfsq )  * fakeerr ;
    Double_t NeTerm   = ( ( Ntrk - fake * Ntot ) / emfsq ) * efferr ;
    Double_t NftrkTerm =(eff*(eff*Ntot-Ntrk)/emfsq) * fakeerr ; 
    
    Nbg = ( eff * Ntot - Ntrk ) / ( eff - fake ) ;
    Nbgtrk = Nbg * fake;

    // AM commented out original error calculation
    /////////////////NbgErr=sqrt ( NtrkTerm * NtrkTerm +
	/////////////////	  NnotTerm * NnotTerm +
	/////////////////	  NfTerm   * NfTerm   +
	/////////////////	  NeTerm   * NeTerm   ) ;
    /////////////////    NbgtrkErr= sqrt ( NtrkTerm * NtrkTerm * fake * fake+
    /////////////////		      NnotTerm * NnotTerm * fake * fake+
    /////////////////		      NeTerm   * NeTerm * fake * fake +
    ////////////////		      NftrkTerm   * NftrkTerm  ) ;
    //-----------------------------------------------------
    //implement error propagation for matrix method,
    //following prescription from D0Note 4564
    //calculate only NbgtrkErr
	double d0note_N1 =  Ntot - Ntrk;
	double d0note_N2 =  Ntrk;
	double d0note_N1_Error = sqrt(d0note_N1);
	double d0note_N2_Error = sqrt(d0note_N2);

	double d0note_d_deff  =  fake*(d0note_N2-fake*(d0note_N1+d0note_N2))/(eff-fake)/(eff-fake);
	double d0note_d_dfake =  eff*(eff*(d0note_N1+d0note_N2)-d0note_N2)/(eff-fake)/(eff-fake);
	double d0note_d_dN1 = eff*fake/(eff-fake);
	double d0note_d_dN2 = fake*(eff-1)/(eff-fake);

    NbgtrkErr=sqrt(d0note_d_deff *d0note_d_deff *efferr *efferr +
			       d0note_d_dfake*d0note_d_dfake*fakeerr*fakeerr +
			       d0note_d_dN1 * d0note_d_dN1 * d0note_N1_Error*d0note_N1_Error +
			       d0note_d_dN2 * d0note_d_dN2 * d0note_N2_Error*d0note_N2_Error);

  } else {
    Nbg = 0.;
    Nbgtrk = 0.;
    NbgErr = 0.;
    NbgtrkErr = 0.;
  }

  return ;
}
