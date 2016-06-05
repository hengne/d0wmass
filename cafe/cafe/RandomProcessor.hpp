/* File RandomProcessor.hpp
 *
 * Created       : Sun May 27 2007
 * Author        : Amnon Harel
 * Purpose       : Base class for cafe processors that use random numbers
 * Last modified : 
 * Comments      : Best not to use this with multiplie inheritence, e.g., use RandomSelectUserObjects

    Optional parameters:
    - .NewEventKey: seed RNG for each event based on Monte Carlo information
       or event and run number for data. This makes the seed independant of
       the order and filename events are stored in. The name of the processor
       is also used to make different processors independant of each other.
       It is a mistake to set EventKey and NewEventKey at the same time.
       This is the new default.

    - .EventKey: make the random numbers given to each event independent (of anything else) [default: false]
                 setting this to false means that seeds will only be initialized at the processor's construction  

    - .Seed:   seed for TRandom3[default: 0]. 
	       When EventKey=true, the default seed=0 takes the seed from the processor's name.
	       When NewEventKey=true, this parameter is ignored.
               When EventKey=false,  the default seed=0 tells ROOT to use the system clock to choose a seed.
	       That should always give correct results, but they will be irreproducible

    - .TableSize: size of hash table used to look up random numbers when EventKey is true [defaut: 10000].

    - .ROOT4patch: how to overcome the ROOT4 TRandom3 initialization bug:
                   0 = don't
                   1 = use the first random number (which is OK) to reseed [default]
                   2 = ignore first thousand numbres

    - .DebugConstructor:   self explanatory

    _ .IgnoreDirectory:  whether to use only the filename (and not the full path) for each input file [default: false]

    - .NFirstCharsToIgnore: how many of the leading filename characters to ignore

    - .NLastCharsToIgnore:  how many of the final filename characters before the .root suffix to ignore

    - .AddPrefix: prefix to add ahead of file name 

    e.g. if you moved file AA.root from directory /BB to /CCC and want the same random seeds, you can use
    ".AddPrefix: /CCC/" and either ".IgnoreDirectory: true" or ".NFirstCharsToIgnore: 4" (for /BB/)


 * Usage :

   In the header file
   ------------------
   class yourProcessor : public cafe::RandomProcessor { // Do not also inherit from Processor!

   In the source flie
   ------------------
   1) Call the base constructor:

     yourProcessor::yourProcessor (const char *name) : 
       cafe::RandomProcessor(name)

   2) if you implement inputFileOpened, you must call the base class explicitely (preferably the first thing
   in your function):

     yourProcessor::inputFileOpened (TFile* file)
     {
       RandomProcessor::inputFileOpened (file);
       ...

   3) In your processEvent method,  you must call the base class explicitely (preferably the first thing
   in your function):

     bool yourProcessor::processEvent(cafe::Event& event)
     {
       RandomProcessor::processEvent (event);

       TRandom& rnd = myTRandom();
       ...

     or simply call myRand().Uniform() etc.

 

 */

#ifndef RandomProcessor_HPP_
#define RandomProcessor_HPP_

#include "cafe/Event.hpp"
#include "cafe/Processor.hpp"
#include <map>

#include "TRandom3.h"

using namespace cafe;

namespace cafe {

  // Utility functions - outside of class since they are also used by RandomSelectUserObjects

  void patchedSetSeed (TRandom3& rnd, const UInt_t seed, 
		       const bool treatZeroAsSpecial = true, const int method = 1, const int debug = 0); 

  inline UInt_t hashString (const register char* p);

  class RandomProcessor : public cafe::Processor {
  
  public:
    
    // Constructor
    RandomProcessor(const char *name);
    // No pointer members: shallow copy and default destructor suffice. But Processor requires a destructor
    
    void inputFileOpened(TFile* file);
    bool processEvent(cafe::Event& event);

    ClassDef(RandomProcessor, 0);

  protected:

    // return a ready to use (seeded when required) TRandom3
    inline TRandom& myRand()    {return _rnd;}
    inline TRandom& myRandom()  {return _rnd;}
    inline TRandom& myTRandom() {return _rnd;}
    
    // needed for producing CINT dictionaries of templated classes that derive from this class. Really.
    RandomProcessor ();
    
  private:

    UInt_t _seed;  //< input seed parameter.
    int _ROOT4patch;   //< how to overcome the TRandom3 bug
    TRandom3 _rnd; //< internal random function
    bool _eventKey;//< whether to seed according to an event based key
    bool _newEventKey;//< seed event by event based only on information about the event, not file name
    bool _ignoreDirectory; //< whether to use only the filename (and not the full path) for each input file
    int _nFirstCharsToIgnore; //< how many of the leading filename characters to ignore
    int _nLastCharsToIgnore; //< how many of the final filename characters before the .root suffix to ignore
    TString _addPrefix; //< prefix to add ahead of file name 
    

    //< (*) = All the following variables are only meaningful when _eventKey == true
    int _mTable;   //< size of table (*)

    std::vector<UInt_t> _seeds; //< table of seeds (*)
    UInt_t _fileHash; //< Hash value calculated from filename (*)
  };

  inline UInt_t hashString (const register char* p)
  {
    register unsigned long hash = 0;
    register unsigned char c; 
    // attributed to sdbm
    while (c = *p++) hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
    //x = 0xd2d84a61;
    //while (c = *p++) x ^= ( (x<<7) + c + (x>>5) );
    //return x;      
  }

} // end namespace

#endif
