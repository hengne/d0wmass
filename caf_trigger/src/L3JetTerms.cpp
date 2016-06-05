#include "caf_trigger/L3JetTerms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include <sstream>

/*
A class to determine if the L3 term matched to the reco jet has fired.

Mikko Voutilainen 2006/08/28 (Ported 'L3Term' by Camille Belanger-Champagne from trigeff_cafe)
*/

using cafe::Collection;

namespace caf_trigger {

bool L3JetTerms::doL3Term(const Collection<TMBL3Jet> l3jets, Float_t R, const TMBJet &recojet, std::string l3, std::string cut){

  //convert the cut string to a float
  float cutting=0;
  
  std::istringstream stream(cut);
  stream>>cutting;

  Float_t rjetdeta=-99;

  float sign = recojet.deta() / fabs (recojet.deta());
  
  if (fabs (recojet.deta()) <= 32){
    rjetdeta= 0.1*(recojet.deta());
  }else if (fabs (recojet.deta()) <= 33){
    rjetdeta= 0.1*(recojet.deta()) + sign*((fabs(recojet.deta())-32)*0.12);
  }else if (fabs (recojet.deta()) <= 34){
    rjetdeta= 0.1*(recojet.deta()) + sign*(0.12 + (fabs(recojet.deta())-33)*0.18);
  }else if (fabs (recojet.deta()) <= 35){
    rjetdeta= 0.1*(recojet.deta()) + sign*(0.3  + (fabs(recojet.deta())-34)*0.3);
  }else{
    rjetdeta= 0.1*(recojet.deta()) + sign*(0.6 + (fabs(recojet.deta())-35)*0.35);
  }

  if(l3=="none"){
    std::cout<<"L3 is none"<<std::endl;
    return true;

  }else if(l3jets.size()==0){
    //    std::cout<<"The jet size is zero... L3JetTerms returns false"<<std::endl;
    return false;

  }else if(l3=="SCJET_8"){

    //    std::cout<<"Looking for SCJET_8 jets"<<std::endl;
    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
    
      if(l3jets[i].ToolName()=="SCJET_8"){
	
	toolcount++;

	if(l3jets[i].Et()> cutting){
	  
	  //	  double match=kinem::delta_R(l3jets[i].DetEta(), l3jets[i].Phi(), recojet.detEta(), recojet.Phi());
	  double match=kinem::delta_R(l3jets[i].Eta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  if(match<bestmatch){
	    bestmatch=match;
	  }
	  
	}
      }
    }
    //    std::cout<<"The count is at: "<<toolcount<<std::endl;
    if(toolcount==0){
      
      /* std::cerr<<"Warning, no jets where found for tool SCJET_8"<<std::endl
	       <<"in event.  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl; */
    } 
  
    

    if(bestmatch<R){

      return true;
    }
    
    return false;

  }else if(l3=="SC5JET_9_PV3"){
    //    std::cout<<"Looking for SC5JET_9_PV3 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
      
      if(l3jets[i].ToolName()=="SC5JET_9_PV3"){
	toolcount++;

	if(l3jets[i].Et()>cutting){
	  
	  double match=kinem::delta_R(l3jets[i].Eta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  if(match<bestmatch){
	    bestmatch=match;

	  }
	  
	}
	
      }
    }

    if(toolcount==0){
      
      /*std::cout<<"Warning, no jets where found for tool SC5JET_9_PV3"<<std::endl
	       <<"in this event "<< event.getGlobal()->evtno()<<".  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl;*/
      
      
    } 
  
    if(bestmatch<R){
      
      return true;
    }
    
    return false;
  }else if(l3=="SC5JET_9_PV3_TOW"){
    //    std::cout<<"Looking for SC5JET_9_PV3 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
      
      if(l3jets[i].ToolName()=="SC5JET_9_PV3_TOW"){
	toolcount++;

	if(l3jets[i].Et()>cutting){
	  
	  double match=kinem::delta_R(l3jets[i].Eta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  if(match<bestmatch){
	    bestmatch=match;

	  }
	  
	}
	
      }
    }

    if(toolcount==0){
      
      /*std::cout<<"Warning, no jets where found for tool SC5JET_9_PV3"<<std::endl
	       <<"in this event "<< event.getGlobal()->evtno()<<".  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl;*/
      
      
    } 
  
    if(bestmatch<R){
      
      return true;
    }
    
    return false;
  }else if(l3=="SC5JET_9_PV3_SUM"){
    //    std::cout<<"Looking for SC5JET_9_PV3 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
      
      if(l3jets[i].ToolName()=="SC5JET_9_PV3_SUM"){
	toolcount++;

	if(l3jets[i].Et()>cutting){
	  
	  double match=kinem::delta_R(l3jets[i].Eta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  if(match<bestmatch){
	    bestmatch=match;

	  }
	  
	}
	
      }
    }

    if(toolcount==0){
      
      /*std::cout<<"Warning, no jets where found for tool SC5JET_9_PV3"<<std::endl
	       <<"in this event "<< event.getGlobal()->evtno()<<".  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl;*/
      
      
    } 
  
    if(bestmatch<R){
      
      return true;
    }
    
    return false;
}else if(l3=="SC5JET_9_PV1"){
    //    std::cout<<"Looking for SC5JET_9_PV3 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
      
      if(l3jets[i].ToolName()=="SC5JET_9_PV1"){
	toolcount++;

	if(l3jets[i].Et()>cutting){
	  
	  double match=kinem::delta_R(l3jets[i].Eta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  if(match<bestmatch){
	    bestmatch=match;

	  }
	  
	}
	
      }
    }

    if(toolcount==0){
      
      /*std::cout<<"Warning, no jets where found for tool SC5JET_9_PV3"<<std::endl
	       <<"in this event "<< event.getGlobal()->evtno()<<".  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl;*/
      
      
    } 
  
    if(bestmatch<R){
      
      return true;
    }
    
    return false;

  
}else if(l3=="SCJET_9_PVTXZ"){
    //    std::cout<<"Looking for SC5JET_9_PV3 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
      
      if(l3jets[i].ToolName()=="SCJET_9_PVTXZ"){
	toolcount++;

	if(l3jets[i].Et()>cutting){
	  
	  double match=kinem::delta_R(l3jets[i].Eta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  if(match<bestmatch){
	    bestmatch=match;

	  }
	  
	}
	
      }
    }

    if(toolcount==0){
      
      /*std::cout<<"Warning, no jets where found for tool SC5JET_9_PV3"<<std::endl
	       <<"in this event "<< event.getGlobal()->evtno()<<".  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl;*/
      
      
    } 
  
    if(bestmatch<R){
      
      return true;
    }
    
    return false;

  
 }else if(l3=="SCJET_9"){
    //    std::cout<<"Looking for SCJET_9 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for(int i=0; i<l3jets.size(); i++){
      
      if(l3jets[i].ToolName()=="SCJET_9"){
	toolcount++;

	if(l3jets[i].Et()>cutting){
	  
	  double match=kinem::delta_R(l3jets[i].DetEta(), l3jets[i].Phi(), rjetdeta, recojet.Phi());
	  
	  //std::cout<<"Current match value: "<<match<<std::endl;
	  
	  if(match<bestmatch){
	    bestmatch=match;
	    // std::cout<<"Replacing the best match"<<std::endl;
	  }
	  
	}
	
      }
    }

    if(toolcount==0){
      
      /*std::cout<<"Warning, no jets where found for tool SCJET_9"<<std::endl
	       <<"in this event "<< event.getGlobal()->evtno()<<".  This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl;*/
      
      
    } 
  
    if(bestmatch<R){
      
      return true;
    }
    
    return false;

 } else if (l3=="SCJET_15") { // QCD
    //    std::cout<<"Looking for SCJET_9 jets"<<std::endl;

    double bestmatch=999;
    int toolcount=0;

    for (int i = 0; i != l3jets.size(); ++i) {
      
      if (l3jets[i].ToolName()=="SCJET_15") {
	++toolcount;

	if (l3jets[i].Et() > cutting) {
	  
	  double match = kinem::delta_R(l3jets[i].DetEta(), l3jets[i].Phi(),
					rjetdeta, recojet.Phi());
	  
	  //std::cout<<"Current match value: "<<match<<std::endl;
	  
	  if (match < bestmatch) {

	    bestmatch = match;
	    // std::cout<<"Replacing the best match"<<std::endl;
	  }
	  
	}
	
      }
    }

    if (toolcount==0) {
      
      /* std::cerr<<"Warning, no jets where found for tool SCJET_15"<<std::endl
	       <<"in event. This may indicate the tool has"<<std::endl
	       <<"not been run on every event.  If it is the case"<<std::endl
	       <<"you will not be obtaining the correct trigger"<<std::endl
	       <<"efficiency curves."<<std::endl; */
    } 
  
    return (bestmatch < R);
      
  }else{

    std::cerr<<"L3 Tool "<<l3<<" was not found in"<<std::endl
	     <<"the L3JetTerms::doL3Term method.  Make sure it is "<<std::endl
	     <<"spelled properly.  It might also not have been"<<std::endl
	     <<"implemented yet to this package.  Please add it"<<std::endl
	     <<"and contact the package authors so it can be put"<<std::endl
	     <<"in the official version."<<std::endl;
    return false;

  }

}

} // namespace caf_trigger
