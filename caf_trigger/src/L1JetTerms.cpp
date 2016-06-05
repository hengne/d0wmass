#include "caf_trigger/L1JetTerms.hpp"
#include "kinem_util/AnglesUtil.hpp"
#include <iostream>

/*
A class to determine if the L1 term matched to the reco jet has fired.

Mikko Voutilainen 2006/08/28 (Ported 'L1Term' by Camille Belanger-Champagne from trigeff_cafe)
*/

using cafe::Collection;

namespace caf_trigger {

bool L1JetTerms::doL1Term(const Collection<TMBL1CalTower> l1jet, const Collection<TMBL1Cal2bJet> l1cal2b, Float_t R, const TMBJet &recojet, std::string l1){

  Float_t rjetdeta=recojet.deta()/10;

  if (l1=="none"){
    
    return true;
    
  }else if(l1jet.size()==0){
    std::cout<<"Could not access the L1 calorimeter info... L1JetTerms returns false"<<std::endl;
    return false;

  }else if(l1=="CJT(1,3)_ncu"){

    bool match=false;

    for(int h=0; h<l1jet.size(); h++){
     
      if(l1jet[h].Et()>3 && abs(l1jet[h].iEta()) < 19 ){

	double matching=kinem::delta_R(l1jet[h].Eta(), l1jet[h].Phi(), rjetdeta, recojet.Phi());

	if(matching<R) {
	  match=true;
	  break;
	}
      }
    }

    if(match==true){
      
      return true;
    }else{

      return false;
    }

  }else if (l1=="CJT(1,5)_ncu"){

    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>5 && abs(l1jet[i].iEta()) < 19 ){

	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  break;
	}
      }
    }

    if(match==true){

      return true;
    }else{

      return false;
    }

  }else if (l1=="CJT(2,3)_ncu"){
    int count=0;
    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>3 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  count++;
	}
      }
    }
    if(count>1 && match==true){
      
      return true;
    }else{
      
      return false;
    }
  } else if (l1=="CJT(2,3)CJT(1,5)") { // QCD

    int count1 = 0, count2 = 0;
    for (int i = 0; i != l1jet.size(); ++i) {

      if (l1jet[i].Et() > 3 && abs(l1jet[i].iEta()) < 19 ) {
	
	double matching = kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(),
					 rjetdeta, recojet.Phi());
	if (matching < R) {
	  ++count1;
	  if (l1jet[i].Et() > 5)
	    ++count2;
	}
      }
    }
    return (count1 > 1 && count2 > 0);

  }else if (l1=="CJT(2,5)_ncu"){
    int count=0;
    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>5 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  count++;
	  match=true;
	}
      }
    }
    if(count>1 && match==true){
     
      return true;
    }else{
     
      return false;
    }
  } else if (l1=="CJT(2,5)") { // QCD

    int count = 0;
    for (int i = 0; i != l1jet.size(); ++i) {

      if (l1jet[i].Et() > 5 && abs(l1jet[i].iEta()) < 19) {
	
	double matching = kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(),
					 rjetdeta, recojet.Phi());
	if (matching < R)
	  ++count;
      }
    }
    return (count > 1);
    
  }else if (l1=="CJT(3,5)_ncu"){
    int count=0;
    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>5 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  count++;
	}
      }
    }
    if(count>2 && match==true){
     
      return true;
    }else{
     
      return false;
    }

  } else if (l1=="CJT(3,5)") { // QCD

    int count = 0;
    for (int i = 0; i != l1jet.size(); ++i) {

      if (l1jet[i].Et() > 5 && abs(l1jet[i].iEta()) < 19 ) {
	
	double matching = kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(),
					 rjetdeta, recojet.Phi());
	if (matching < R)
	  ++count;
      }
    }
    return (count > 2);
    
  }else if (l1=="CJT(4,5)_ncu"){
    int count=0;
    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>5 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  count++;
	}
      }
    }
    if(count>3 && match==true){
      
      return true;
    }else{
      
      return false;
    }
  } else if (l1=="CJT(4,5)") {  // QCD

    int count = 0;
    for (int i = 0; i != l1jet.size(); ++i) {

      if (l1jet[i].Et() > 5 && abs(l1jet[i].iEta()) < 19 ) {
	
	double matching = kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(),
					 rjetdeta, recojet.Phi());
	if (matching < R)
	  ++count;
      }
    }
    return (count > 3);

  } else if (l1=="CJT(4,7)_ncu") { // QCD

    int count = 0;
    for (int i = 0; i != l1jet.size(); ++i) {

      if (l1jet[i].Et() > 7 && abs(l1jet[i].iEta()) < 19) {
	
	double matching = kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(),
					 rjetdeta, recojet.Phi());
	if (matching < R)
	  ++count;
      }
    }
    return (count > 3);

  } else if (l1=="CJT(4,7)") { // QCD

    int count = 0;
    for (int i = 0; i != l1jet.size(); ++i) {

      if (l1jet[i].Et() > 7 && abs(l1jet[i].iEta()) < 19) {
	
	double matching = kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(),
					 rjetdeta, recojet.Phi());
	if (matching < R)
	  ++count;
      }
    }
    return (count > 3);

  }else if (l1=="CJT(3,4eta2.6)_ncu"){
    int count=0;
    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>4 && l1jet[i].Eta()<2.6 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  count++;
	}
      }
    }
    if(count>2 && match==true){
     
      return true;
    }else{
     
      return false;
    }
  }else if (l1=="CJT(2,4eta2.6)_ncu"){
    int count=0;
    bool match=false;
    
    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>4 && l1jet[i].Eta()<2.6 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());
	
	if(matching<R){
	  match=true;
	  count++;
	}
      }
    }
    if(count>1 && match==true){
      
      return true;
    }else{
      
      return false;
    }
  }else if (l1=="CJT(1,4eta2.6)_ncu"){
    int count=0;
    bool match=false;
    
    for(int i=0; i<l1jet.size(); i++){
      
      if(l1jet[i].Et()>4 && l1jet[i].Eta()<2.6 && abs(l1jet[i].iEta()) < 19 ){
	
	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  break;
	
	}
      }
    }
    if( match==true){
    
      return true;
    }else{
    
      return false;
    }
    
  }else if (l1=="CJT(1,7eta1.8)_ncu"){
    int count=0;
    bool match=false;

    for(int i=0; i<l1jet.size(); i++){

      if(l1jet[i].Et()>7&& l1jet[i].Eta()<1.8 && abs(l1jet[i].iEta()) < 19 ){

	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());

	if(matching<R){
	  match=true;
	  break;
	}
      }
    }
    
    if(match==true){
      return true;
    }else{
      return false;
    }

  }else if (l1=="CJT(1,7)_ncu"){
    int count=0;
    bool match=false;
    
    for(int i=0; i<l1jet.size(); i++){
      
      if(l1jet[i].Et()>7&& l1jet[i].Eta()<1.8 && abs(l1jet[i].iEta()) < 19 ){

	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());
	
	if(matching<R){
	  match=true;
	  break;
	}
      }
    }
    
    if(match==true){
      return true;
    }else{
      return false;
    }
  }else if (l1=="CJT(2,7)_ncu"){
    int count=0;
    bool match=false;
    
    for(int i=0; i<l1jet.size(); i++){
      
      if(l1jet[i].Et()>7&& l1jet[i].Eta()<1.8 && abs(l1jet[i].iEta()) < 19 ){

	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());
	
	if(matching<R){
	  match=true;
	  count++;
	  break;
	}
      }
    }
    
    if(count>1&&match==true){
      return true;
    }else{
      return false;
    }
  }else if (l1=="CJT(3,7)_ncu"){
    int count=0;
    bool match=false;
    
    for(int i=0; i<l1jet.size(); i++){
      
      if(l1jet[i].Et()>7&& l1jet[i].Eta()<1.8 && abs(l1jet[i].iEta()) < 19 ){

	double matching=kinem::delta_R(l1jet[i].Eta(), l1jet[i].Phi(), rjetdeta, recojet.Phi());
	
	if(matching<R){
	  match=true;
	  count++;
	  break;
	}
      }
    }
    
    if(count>2 && match==true){
      return true;
    }else{
      return false;
    }

  }else if (TString(l1).Contains("CSWJT")){ //QCD

    const char* l1term = l1.c_str();
    int n_thr;
    float et_thr, eta_thr;
    sscanf(l1term,"CSWJT(%d,%f,%f)",&n_thr,&et_thr,&eta_thr);
    int n = 0;
    for (int i=0; i<l1cal2b.size(); i++){
      if (l1cal2b[i].Et()>et_thr && l1cal2b[i].Eta()<eta_thr){
        double matching=kinem::delta_R(l1cal2b[i].Eta(), l1cal2b[i].Phi(), rjetdeta, recojet.Phi());
	
        if(matching<R){
          ++n;
        }
      }

    }
    return (n >= n_thr);
    
  }else if(l1 == "none") { //no L1 jet requirement
    return true;
  }else{
    
    std::cout<<"L1 Term "<<l1<<" was not found in"<<std::endl
	     <<"the L1JetTerms::doL1Term method.  Make sure it is "<<std::endl
	     <<"spelled properly.  It might also not have been"<<std::endl
	     <<"implemented yet to this package.  Please add it"<<std::endl
	     <<"and contact the package authors so it can be put"<<std::endl
	     <<"in the official version."<<std::endl;
    return false;

  }
  
}

} // namespace caf_trigger
