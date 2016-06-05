#ifndef CAF_TRIGGER_L3JETTERMS_HPP_
#define CAF_TRIGGER_L3JETTERMS_HPP_

/* 
A class to determine if the L3 term matched to the reco jet has fired.

Mikko Voutilainen 2006/08/28 (Ported 'L3Term' by Camille Belanger-Champagne from trigeff_cafe)
*/

#include "cafe/Event.hpp"
#include "tmb_tree/TMBL3Jet.hpp"
#include "tmb_tree/TMBJet.hpp"

#include <string>
#include <vector>

namespace caf_trigger {

class L3JetTerms
{
public:
  L3JetTerms(){;}
  ~L3JetTerms(){;}

  bool doL3Term(const cafe::Collection<TMBL3Jet> l3jets, Float_t R, const TMBJet &recojet, std::string l3, std::string cut);

private:
  
};

} // namespace caf_trigger

#endif // CAF_TRIGGER_L3JETTERMS_HPP_

