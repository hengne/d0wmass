#ifndef CAF_TRIGGER_L2JETTERMS_HPP_
#define CAF_TRIGGER_L2JETTERMS_HPP_

/* 
A class to determine if the L2 term matched to the reco jet has fired.

Mikko Voutilainen 2006/08/28 (Ported 'L2Term' by Camille Belanger-Champagne from trigeff_cafe)
*/

#include "cafe/Event.hpp"
#include "tmb_tree/TMBL2Jet.hpp"
#include "tmb_tree/TMBJet.hpp"

#include <string>
#include <vector>

namespace caf_trigger {

class L2JetTerms
{
public:
  L2JetTerms(){;}
  ~L2JetTerms(){;}

  bool doL2Term(const cafe::Collection<TMBL2Jet> l2jets, Float_t R, const TMBJet &recojet, std::string l2, std::string cut);

private:
  
};

} // namespace caf_trigger

#endif // CAF_TRIGGER_L2JETTERMS_HPP_

