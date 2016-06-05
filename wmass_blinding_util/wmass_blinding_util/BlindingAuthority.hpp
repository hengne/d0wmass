//////////////////////////////////////////////////////////////
///     File: BlindingAuthority.hpp                        ///
///     Created: J. Stark  September 2007                  ///
///     Purpose: Know everything about blinding strategy   ///
///     Modified: J.Stark  May 2009                        /// 
///               Add Run IIb features                     /// 
//////////////////////////////////////////////////////////////

#ifndef BLINDINGAUTHORITY_HPP__
#define BLINDINGAUTHORITY_HPP__

#include "wmass_blinding_util/BlindingManagerParser.hpp"

class TFile;
class TH1;
class TH1F;
class TProfile;
class TObject;

class OffsetMass;
class OffsetWidth;

class BlindingAuthority {

  public:

   BlindingAuthority(int IntendedPeriod=0);   // 0 = Run IIa, 1 = RunIIb, until Summer 2009 shutdown, ...
   ~BlindingAuthority();

   void SetConfiguration(TFile* f1, TFile* f2, int compmode);
   void SetBlindMass(double m);

   bool isConfigured();

   void SetDebug(bool debug=true);
 
   TH1F* Get_mass(TFile* f, const char* wo);
   TH1F* Get_elecpt(TFile* f, const char* wo);
   TH1F* Get_met(TFile* f, const char* wo);

   TH1* Get_hWcandMtUpara(TFile* f, const char* wo);
   TH1* Get_hWcandElecPtUpara(TFile* f, const char* wo);
   TH1* Get_hWcandMetUpara(TFile* f, const char* wo);

   TH1F* Get_mtoverlay(TFile* f, int bin, const char* wo);
   TH1F* Get_eptoverlay(TFile* f, int bin, const char* wo);
   TH1F* Get_metoverlay(TFile* f, int bin, const char* wo);

   TH1F* Get_utbinoverlay(TFile* f, int bin, const char* wo);

   // blinding offset factory 
   OffsetMass* Get_Offset_Mass();
   OffsetWidth* Get_Offset_Width();

  private:

   void CheckConsistency();

   bool knowMass();

   TH1F* Get_TH1F(TFile* f, const char* wo, const char* basename, const char* nominal);
   TH1* Get_TProfile(TFile* f, const char* wo, const char* basename, const char* nominal);

   void BuildTemplateMasses(TFile* f, double masses[100]);
   void GrabTemplates(TFile* f, const char* basename, TObject* temps[100]);
   TH1F* InterpolateTemplatesTH1F(double theBlindMass, double masses[100], TObject* temps[100]);
   TH1F* InterpolateTemplatesTProfile(double theBlindMass, double masses[100], TObject* temps[100]);

   void VerifySeeding();

   int _IntendedPeriod;

   TFile* _f1;
   TFile* _f2;
   int _compmode;

   double _BlindMass;

   // parsed information
   int _origin1;
   TH1F* _BMhist1;
   int _origin2;
   TH1F* _BMhist2;

   BlindingManagerParser _BMP;

   bool _TreatFastMCblind;

   bool _debug;

   OffsetMass* _theMassOffset;
   OffsetWidth* _theWidthOffset;

};
 
#endif // BLINDINGAUTHORITY_HPP__
