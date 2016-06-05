#include "caf_trigger/L2JetTerms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include <sstream>

/*
A class to determine if the L2 term matched to the reco jet has fired.

Mikko Voutilainen 2006/08/28 (Ported 'L2Term' by Camille Belanger-Champagne from trigeff_cafe)
*/

using cafe::Collection;

namespace caf_trigger {

bool L2JetTerms::doL2Term(const Collection<TMBL2Jet> l2jets, Float_t R, const TMBJet &recojet, std::string l2, std::string cut){

  //convert the cut string to a float
  float cutting=0;
  
  std::istringstream stream(cut);
  stream>>cutting;
  
  Float_t rjetdeta=recojet.deta()/10;

  if(l2=="none"){
    
    return true;

  }else if(l2jets.size()==0){
        std::cout<<"The jet size is zero... L2JetTerms returns false"<<std::endl;
    return false;
    
   
  }else if(l2=="JET(0,5)" || l2=="JET(0,7)" ){
    
    double bestmatch=999;
    
    for(int i=0; i<l2jets.size(); i++){
      
      if(l2jets[i].Et()> cutting){
	
	double match=kinem::delta_R(l2jets[i].Eta(), l2jets[i].Phi(), rjetdeta, recojet.Phi());
	
	if(match<bestmatch){
	  bestmatch=match;
	}
      }
    }
    if(bestmatch<R){
      return true;
    }
    
    return false;

  }else{
    std::cout<<"L2 Tool "<<l2<<" was not found in"<<std::endl
	     <<"the L2JetTerms::doL2Term method.  Make sure it is "<<std::endl
	     <<"spelled properly.  It might also not have been"<<std::endl
	     <<"implemented yet to this package.  Please add it"<<std::endl
	     <<"and contact the package authors so it can be put"<<std::endl
	     <<"in the official version."<<std::endl;
    return false;


  }

}

} // namespace caf_trigger
