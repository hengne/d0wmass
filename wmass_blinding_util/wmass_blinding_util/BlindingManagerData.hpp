/////////////////////////////////////////////////////
///     File: BlindingManagerData.hpp             ///
///     Created: J. Stark  September 2007         ///
///     Purpose: Manage blinding information      ///
///              for data and full MC             ///
///     Modified: J.Stark  May 2009               ///
///               Add Run IIb features            ///
///     Modified: J.Stark  April 2012             ///
///               Add Run IIb3,4 features         ///
/////////////////////////////////////////////////////

#ifndef BLINDINGMANAGERDATA_HPP__
#define BLINDINGMANAGERDATA_HPP__

#include "cafe/Event.hpp"

class TFile;

class BlindingManagerData {

  public:

   BlindingManagerData();
   ~BlindingManagerData();

   void ExamineEvent(cafe::Event* evt);
   void WriteVerdict(TFile* file);

  private:

   int _nSeen;
   int _nMClike;
   int _nDATAlike;
   int _nRunIIblike;
   int _nRunIIb34like;

};
 
#endif // BLINDINGMANAGERDATA_HPP__
