/* File TriggerORProbability.hpp
 *
 * Created       : Wed Aug 16 07:46:01 CDT 2006
 * Author        : filthaut
 * Purpose       : 
 * Last modified : 
 * Comments      : 
 */

#ifndef TriggerORProbability_HPP_
#define TriggerORProbability_HPP_

#include "cafe/Event.hpp"
#include "caf_trigger/probProcessor.hpp"

using namespace cafe;


class TriggerORProbability : public probProcessor {
  
 public:

 // Constructor, destructor: 
  TriggerORProbability(const char *name);
  ~TriggerORProbability();
  
  //Calculate the event weight (override the base class method)
  void eventWeight(std::map<std::string, double> &mRefEvtw);

  // The following two methods are pure virtual in the base class, and
  // hence need to be defined. However, we don't need them.
  void defineEffInfo(std::map< std::string, eff_utils::EffInfo > &effInfo) {};
  double calcProb(std::string version) { return 1; }

  ClassDef(TriggerORProbability, 0);
  
 private:

  // information needed to perform the computations
  std::vector<std::string> _inputChannels;
  std::map<std::string, std::map<std::string, double> > _prescaleFractions;
  std::map<std::string, std::string> _lumiRefTrigger;
  
};

#endif
