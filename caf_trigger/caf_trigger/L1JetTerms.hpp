#ifndef CAF_TRIGGER_L1JETTERMS_HPP_
#define CAF_TRIGGER_L1JETTERMS_HPP_

/*
A class to determine if the L1 term matched to the reco jet has fired.

Mikko Voutilainen 2006/08/28 (Ported 'L1Term' by Camille Belanger-Champagne from trigeff_cafe)
*/

#include "cafe/Event.hpp"
#include "tmb_tree/TMBL1CalTower.hpp"
#include "tmb_tree/TMBL1Cal2bJet.hpp"
#include "tmb_tree/TMBJet.hpp"

#include <string>
#include <vector>

namespace caf_trigger {

class L1JetTerms
{
public:
  L1JetTerms(){;}
  ~L1JetTerms(){;}

  bool doL1Term(const cafe::Collection<TMBL1CalTower> l1jet, const cafe::Collection<TMBL1Cal2bJet> l1cal2b, Float_t R, const TMBJet &recojet, std::string l1);

private:
  
};

} // namespace caf_trigger

#endif // CAF_TRIGGER_L1JETTERMS_HPP_
