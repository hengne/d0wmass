/********************************************************************************** 
 *
 *  Authors : Sabine Crepe-Renaudin (LPSC Grenoble)
 *            Jan Stark (LPSC Grenoble)
 *
 *  PURPOSE : Correct EM energy   
 *
 *  APPLICATION CONDITIONS : Scone and CellNN, > p10.08.01, no preshower, CC and EC (Scone only)
 *                           Note that CellNN corrections are no longer updated and very
 *                           crude approximations
 * 
 *  DOCUMENTATION : http://isnwww.in2p3.fr/d0/elid/elreco/fit.html
 *                  (this describes the idea and the method, but not recent updates)
 *
 * 01/17/2002 : created
 * 01/24/2002 : bug (-1<etap<1) in correvseta corrected
 * 01/25/2002 : add CellNN eta correction
 * 04/17/2002 : add Scone EC correction
 * 08/12/2002 : add scone IC correction
 * 09/24/2005 : updated for p17 d0gstar geometry
 * 01/05/2007 : updated for Run IIb
 *
 ********************************************************************************** 
 *
 *    FUNCTION correvseta_S(float E, const float etap, const float etad, bool isRunIIb)
 *    ------------------------------------------------------------------
 *
 *       PURPOSE : Correct EM energy variation vs eta for Scone algorithm
 *
 *       INPUT   :  E = EM Scone energy without preshower in CC (|eta|<1) or EC (|eta|>1.5).
 *                  etap = physical eta from EM-block calculated from cluster 
 *                         position in third calorimeter floor.
 *                  etad = detector eta from EM-block calculated from cluster 
 *                         position in third calorimeter floor.
 *
 *       OUTPUT :   E = E corrected
 *
 ********************************************************************************** 
 *
 *    FUNCTION correvseta_Z(float E, const float etap)
 *    --------------------------------------------------
 *
 *       PURPOSE : Correct EM energy variation vs eta for CellNN algorithm
 *
 *       INPUT   :  E = EM CellNN energy without preshower in CC (|eta|<1).
 *                  etap = physical eta from EM-block calculated from cluster 
 *                         position in third calorimeter floor.
 *
 *       OUTPUT :   E = E corrected
 *
 **********************************************************************************/


#ifndef CorrEemcalo_h
#define CorrEemcalo_h

class CorrEemcalo 
{
 public:
    
    // ---> constructor; destructor
  CorrEemcalo();
    ~CorrEemcalo(){;}    

    double correvsphi_S(float E, const float phid, const float etad, bool is_data);
    double correvsphi_Z(float E, const float phid, const float etad, bool is_data);

    double correvseta_S(float E, const float etap, const float etad, bool isRunIIb, bool isMC);
    double corretaa_CC_S(const float e);
    double corretab_CC_S(const float e);
    double corretac_CC_S(const float e);
    double Eloss_Jan_CC(float e, float etap, const double params[36]);
    double Eloss_Jan_CC_regularised(float e, float etap, const double params[36]);
    double Tim_Eloss(const float e, const float etap, const double params[28]);
    double Eloss_Jan_EC(float e, float etad, const double lookup[80]);
    double diffic(const float e);	
    double corretaga_IC_S(const float e);
    double corretada_IC_S(const float e);

    double correvseta_Z(float E, const float etap);
    double corretaa_CC_Z(const float e);
    double corretab_CC_Z(const float e);
    double corretac_CC_Z(const float e);

 private:

  // This is for p17 (Run IIa)
  // EC
  double _params_North[28];
  double _params_South[28];

  // This is for p20 data (Run IIb)
  // CC
  double _params_p20fulljan[36];
  // EC
  double _lookup_p20ECNfulljan[80];
  double _lookup_p20ECSfulljan[80];

  // This is for p20 Monte Carlo (Run IIb)
  // CC
  double _params_p20plaind0g[36];
  // EC
  double _lookup_p20ECNplaind0g[80];
  double _lookup_p20ECSplaind0g[80];

};

#endif
