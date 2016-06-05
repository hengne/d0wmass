/********************************************************************************** 
 *
 *  Author : Jan Stark
 *
 *  PURPOSE : Correct EM energy in Jan's fancy calibration  
 *
 **********************************************************************************/


#ifndef CorrEemcaloJan_h
#define CorrEemcaloJan_h

class CorrEemcaloJan 
{
 public:
    
    // ---> constructor; destructor
  CorrEemcaloJan();
  ~CorrEemcaloJan(){;}    

  double correvsphi_S(float E, const float phid, const float etad, bool is_data);

  double correvseta_S(float E, const float etap, const float etad);
  double Jan_Eloss(double e, double etap, const double params[36]);

  double corretaga_IC_S(const float e);

 private:

  double _params000[36];
  double _params017[36];
  double _params036[36];
  double _nX0;

};

#endif
