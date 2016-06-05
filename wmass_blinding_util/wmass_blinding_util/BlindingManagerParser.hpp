/////////////////////////////////////////////////////////////////////
///     File: BlindingManagerParser.hpp                           ///
///     Created: J. Stark  September 2007                         ///
///     Purpose: Decode the histograms from BlindingManagerData   ///
///              and from BlindingManagerPMCS.                    ///
///     Modified: J.Stark  May 2009                               /// 
///               Add Run IIb features                            /// 
///     Modified: J.Stark  April 2012                             ///
///               Add Run IIb3,4 features                         ///
/////////////////////////////////////////////////////////////////////

#ifndef BLINDINGMANAGERPARSER_HPP__
#define BLINDINGMANAGERPARSER_HPP__

class TH1F;

class BlindingManagerParser {

  public:

   BlindingManagerParser();
   ~BlindingManagerParser();

   void ParseAVerdictData(TH1F* verdict, int& version, int& isThisData, int& isThisRunIIb, int& isThisRunIIb34);
   void ParseAVerdictPMCS(TH1F* verdict, int& version, bool& variedMass, bool& enoughRangeMass);

};
 
#endif // BLINDINGMANAGERPARSER_HPP__
