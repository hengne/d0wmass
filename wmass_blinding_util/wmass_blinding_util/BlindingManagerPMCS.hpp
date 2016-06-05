/////////////////////////////////////////////////////
///     File: BlindingManagerPMCS.hpp             ///
///     Created: J. Stark  September 2007         ///
///     Purpose: Manage blinding information      ///
//               for fast MC                      ///
/////////////////////////////////////////////////////

#ifndef BLINDINGMANAGERPMCS_HPP__
#define BLINDINGMANAGERPMCS_HPP__

class TH1F;

class BlindingManagerPMCS {

  public:

   BlindingManagerPMCS();
   ~BlindingManagerPMCS();

   void SetInfo(bool wmass_reweight, 
		float wmass_default, float wmass_step, int wmass_nstep,
		bool wwidth_reweight,
                float wwidth_default, float wwidth_step, int wwidth_nstep);
   TH1F* GetVerdict();

  private:

   bool _wmass_reweight;
   float _wmass_default;
   float _wmass_step;
   int _wmass_nstep;
   bool _wwidth_reweight;
   float _wwidth_default;
   float _wwidth_step;
   int _wwidth_nstep;

};
 
#endif // BLINDINGMANAGERPMCS_HPP__
