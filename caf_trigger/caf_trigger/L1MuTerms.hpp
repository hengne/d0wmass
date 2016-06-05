#ifndef L1MuTerms_h
#define L1MuTerms_h

/*
A class to reduce the l1muon regional octant counters into more directly
usable quantities

Stefan Anderson 6/05 (Adapted from 'MuTerms' by Noah Wallace)
*/

#include <bitset>
#include <string>
#include <map>
#include "tmb_tree/TMBL1Muon.hpp"

class L1MuTermsClass 
{
  
   public :

      L1MuTermsClass();

      // Pass in pointer to TMB/CAF object with l1muon info
      L1MuTermsClass(const TMBL1Muon *l1muon, const bool& isRun2B); 

      ~L1MuTermsClass();

      // The following three methods are simple accessors for the 
      // crate manager terms for each region
      int get_mtcm_central(int term){ 
	 if(term >-1 && term <36) {
	    return(_MTCCCounters[term]);
	 } else {
	    return(-1);
	 }
      };
  
      int get_mtcm_north(int term){ 
	 if(term >-1 && term <36) {
	    return(_MTCNCounters[term]);
	 } else {
	    return(-1);
	 }
      };
  
      int get_mtcm_south(int term){
	 if(term >-1 && term <36) { 
	    return(_MTCSCounters[term]);
	 } else {
	    return(-1);
	 }
      };

      // An accessor method for the trigger manager terms 
      int get_mtm(int term){
	 if(term<256 && term > -1){
	    return(_muoManagTerms.test(term));
	 }else{
	    return(-1);
	 }
      };

      // this method provides TM term # given a name
      int get_mtm_number(const std::string& termName){
	 std::map<std::string, int>::const_iterator it = 
	    _TMTermMap.find(termName);
	 if (it != _TMTermMap.end()) {
	    return it->second;
	 } else {
	    return 0;
	 }
      };

      // this method returns trigger manager term given a name
      int get_mtm_named(const std::string& termName);

      // this method allows for octant/region matching given a trigger name
      bool match_trigger_named(int region, int octant, std::string name);

      // this method allows for octant/region matching given a
      // specific set of requirements
      bool match_trigger_requirements(
	 int region, int octant, int eta, int track, int scint, int wire);
      
      // these methods will refill the terms for a new event
      void update_terms(const TMBL1Muon *l1muon, const bool& isRun2B); 

      // clears the terms to zero
      void reset();

   private:
  
      // MTCxx counters
      int _MTCxxCentral[8][18];
      int _MTCxxNorth[8][18];
      int _MTCxxSouth[8][18];

      // 'Combined' counters formed by regional trigger crates
      int _MTCCCounters[36];
      int _MTCNCounters[36];
      int _MTCSCounters[36];

      // 256 terms formed by Trigger Manager
      std::bitset<256> _muoManagTerms;

      // map to go from trigger name to TM term 
      std::map<std::string,int> _TMTermMap;

      // a simple trigger term combination truth table
      int OctantCounterCombine(int counter1, int counter2);

      // Fills the mtcxx counter arrays
      void fill_mtcxx(const TMBL1Muon *l1muon); 

      // makes the crate manager terms from the octant terms
      void fill_mtcmRun2A(); 
      void fill_mtcmRun2B(); 

      // maps the trigger manager terms
      void map_mtmRun2A();
      void map_mtmRun2B();

      // makes the trigger manager terms
      void fill_mtmRun2A();
      void fill_mtmRun2B();

      // Remaining members used to match MTCxx counters to oct/region 
      // trigger requirements

      // Enumerate requirements by detector
      enum _cttRequirements { _ctt_x, _ctt_1, _ctt_2, _ctt_3, _ctt_4, _ctt_5, _ctt_6 };
      enum _etaRequirements { _eta_c, _eta_w, _eta_a, _eta_b};
      enum _scintRequirements { _scint_x, _scint_l, _scint_t, _scint_c };
      enum _wireRequirements { _wire_x, _wire_l, _wire_t };

      // Maps from strings to enumerated ints
      std::map<std::string,_cttRequirements> _cttReqMap;
      std::map<std::string,_etaRequirements> _etaReqMap;
      std::map<std::string,_scintRequirements> _scintReqMap;
      std::map<std::string,_wireRequirements> _wireReqMap;

      // Central MTC05 Counter Map (use a mulitmap, since it is
      // possible for some scint/track combos to have more than
      // one corresponding counter
      std::multimap< std::pair<int, int>, int > _mtc05CentralMap;

      // Central MTC10 Counter Map
      std::map< int, int > _mtc10CentralMap;

      // Forward (i.e., 1.0 < |eta| < 1.5) MTC05 Counter Map
      std::multimap< std::pair<int, int>, int > _mtc05ForwardMap;

      // Forward (i.e., 1.0 < |eta| < 1.5) MTC10 Counter Map
      std::map< int, int > _mtc10ForwardMap;

      // Far Forward (i.e., 1.5 < |eta| < 2.0) MTC05 Counter Map
      std::multimap< std::pair<int, int>, int > _mtc05FarMap;

      // Far Forward (i.e., 1.5 < |eta| < 2.0) MTC10 Counter Map
      std::map< int, int > _mtc10FarMap;

      // Fill mtcxx maps
      void map_mtcxxRun2A();
      void map_mtcxxRun2B();

      // Fetch 05 counters given a key
      void fetch_Counters( std::vector<int> &counters,
			   const std::multimap< std::pair<int, int>, int > &mtcxxMap,
			   const std::pair<int, int> &key);

      // Fetch 10 counters given a key
      void fetch_Counters( std::vector<int> &counters, 
			   const std::map< int, int > &mtcxxMap,
			   int key);

}; // end of class description

#endif





