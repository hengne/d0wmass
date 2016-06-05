#include "cafe/StatSample.hpp"
#include <string>

using namespace std ;

namespace cafe {

  StatSample::StatSample(const string& sample) : _name(sample)
  {
    _events.push_back(new StatWeight("Initial")) ;
    _weight = new StatWeight("Efficiency correction") ;
  }

  StatSample::~StatSample() {
  }

  void StatSample::AddTags(const vector<string>& tags) {
    for (vector<string>::const_iterator it = tags.begin() ;
	 it != tags.end(); it++) {
      string s = *it ;
      while (s.size() > 0 && s.substr(0,1) == " ") s.erase(0,1) ;
      while (s.size() > 0 && s.substr(s.size()-1,1) == " ") s.erase(s.size()-1,1) ;      
      if (s.size() ==0 ) continue ;      
      _tags.push_back(s) ;
    }
    return ;
  }


  void StatSample::AddAndTags(const vector<string>& tags) {
    for (vector<string>::const_iterator it = tags.begin() ;
	 it != tags.end(); it++) {
      string s = *it ;
      while (s.size() > 0 && s.substr(0,1) == " ") s.erase(0,1) ;
      while (s.size() > 0 && s.substr(s.size()-1,1) == " ") s.erase(s.size()-1,1) ;      
      if (s.size() ==0 ) continue ;      
      _tags_and.push_back(s) ;
    }
    return ;
  }

  unsigned long StatSample::add(cafe::Event* event, const std::string& name) {
    if (!event) {
      cerr << "StatSample ERROR!. Event pointer == 0." << endl ;
      return 0;
    }    

    if (!tagged(event)) return 0 ;

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      _events.push_back(new StatWeight(name, true)) ;  
      it = _events.end()-1 ;
    }

    (*it) ->applyWeight(_weight->weight(), _weight->weight_pos(), _weight->weight_neg()) ;
    return (*it)->nevents() ;
  }

  double StatSample::applyWeight(cafe::Event* event, const std::string& name, 
				 double weight, double weight_pos, double weight_neg) {    
    if (!event) {
      cerr << "StatSample ERROR!. Event pointer == 0." << endl ;
      return 0;
    }    

    if (!tagged(event)) return 0.0 ;

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      _events.push_back(new StatWeight(name)) ;
      it = _events.end()-1 ;
    }

    // update global weight
    _weight->applyWeight(weight, weight_pos, weight_neg) ;

    // update specified weight
    return (*it) ->applyWeight(weight, weight_pos, weight_neg) ;
  }



   unsigned long StatSample::nevents(unsigned int n ) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSample \"" << _name << "\": selection number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }
    return _events[n]->nevents() ;
  }


   unsigned long StatSample::nevents(const string& name) const {

     vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      cout << "cafe::StatSample: \"" << _name << "\": No weight with name \"" << name 
	   << "\" found in the Stat class" << endl ; 
      return 0 ;
    }
    return (*it)->nevents() ;
  }

  void StatSample::Clear() {
    for (vector<StatWeight*>::iterator it = _events.begin() ;
	 it != _events.end(); it++) 
      (*it)->Clear() ;

    _weight->Clear() ;
    return ;
  }

  const StatWeight* StatSample::eventWeight(const std::string& name) const {

    if (name == "global") return _weight ;

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end())   throw StatWeightNotFoundException(name) ;

    return *it ;
  }

  Collection<EventWeight> StatSample::ListEventWeights() const {
    /// nee a trick to be owner of the weights
    Collection<EventWeight> weightlist(0,true);
    EventWeight *weight;
    // Save the global weight first
    weight = new EventWeight("Global weight",_weight->weight(),
			     _weight->weight_pos(),_weight->weight_neg());
   weightlist.push_back(weight);
   vector<StatWeight*>::const_iterator it = _events.begin();
   for (; it != _events.end(); it++) {
      // Do not save "Initial" or the efficiency correction, it is computed automatically
      if ((*it)->isWeight() && (*it)->name() != "Efficiency correction"
	  && (*it)->name() != "Initial") {
         weight = new EventWeight((*it)->name(),((StatWeight*)(*it))->weight(),
                                  ((StatWeight*)(*it))->weight_pos(),((StatWeight*)(*it))->weight_neg());
         weightlist.push_back(weight);
      }
   }
   return weightlist;
  }
   
  const StatWeight* StatSample::eventWeight(unsigned int n) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSample: \"" << _name << "\": weight number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }

    return _events[n] ;
  }

  const StatWeight* StatSample::eventSelection(unsigned int n) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSample \"" << _name << "\": Selection number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }
    return  _events[n];
  }

  const StatWeight* StatSample::eventSelection(const string& name) const {
    
    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      cout << "cafe::StatSample \"" << _name << "\": No selection with name \"" << name 
	   << "\" found in the Stat class" << endl ; 
      return 0 ;
    }

    return (*it) ;
  }

  double StatSample::eff(unsigned int n) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSamplec\"" << _name << "\": Selection number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }

    if (_events[n]->isWeight()) return _events[n]->weight_average() ;

    if ( n > 0) 
      return ((double)_events[n]->nevents())/_events[n-1]->nevents() ;

    return -1.0 ;
  }


  double StatSample::eff(const std::string& name) const {

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      cout << "cafe::StatSample \"" << _name << "\": No selection with name \"" << name 
	   << "\" found in the Stat class" << endl ; 
      return 0 ;
    }

    if (it == _events.begin()) return 0 ;

    return ((double) (*it)->nevents())/(*(it-1))->nevents() ;
  }


  double StatSample::effErr(unsigned int n) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSample \"" << _name << "\": Selection number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }

    if (_events[n]->isWeight()) return  (_events[n])->err() ;

    if ( n >0) 
      return _events[n]->err(*_events[n-1]) ;

    return -1.0 ;
  }

  double StatSample::effErr(const std::string& name) const {

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      cout << "cafe::StatSample \"" << _name << "\": No selection with name \"" << name 
	   << "\" found in the Stat class" << endl ; 
      return 0 ;
    }

    if (it == _events.begin()) return 0 ;

    return (*it)->err(**(it-1)) ;
  }


  double StatSample::effGlob(unsigned int n) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSample \"" << _name << "\": Selection number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }

    if ( _events.front()->nevents() == 0 ) return -1.0 ; 

    if (n == 0) 
      return ((double)_events.back()->nevents())/_events.front()->nevents() ;
    
    return ((double)_events[n]->nevents())/_events.front()->nevents() ;
  }


  double StatSample::effGlob(const std::string& name) const {

    if ( _events.front()->nevents() == 0 ) return -1.0 ; 

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      cout << "cafe::StatSample \"" << _name << "\": No selection with name \"" << name 
	   << "\" found in the Stat class" << endl ; 
      return -1.0 ;
    }

    if (it == _events.begin()) return -1.0 ;

    return ((double) (*it)->nevents())/_events.front()->nevents() ;
  }


  double StatSample::effErrGlob(unsigned int n) const {
    if (n >= _events.size()) {
      cerr << "ERROR! StatSample \"" << _name << "\": Selection number " << n 
	   << " greater than selection size " << _events.size() << endl ;
      exit(1) ;
    }

    if ( _events.front()->nevents() == 0)  return -1.0 ;
    
    if ( n == 0) 
      return _events.back()->err(*_events.front()); 

    return _events[n]->err(*_events.front());
  }

  double StatSample::effErrGlob(const std::string& name) const {

    if ( _events.front()->nevents() == 0 ) return -1.0 ; 

    vector<StatWeight*>::const_iterator it = _events.begin();
    for (; it != _events.end(); it++) if ((*it)->name() == name ) break ;

    if (it == _events.end()) {
      cout << "cafe::StatSample \"" << _name << "\": No selection with name \"" << name 
	   << "\" found in the Stat class" << endl ; 
      return -1.0 ;
    }

    if (it == _events.begin()) return -1.0 ;

    return (*it)->err(*_events.front());
  }

  double StatSample::correctedEfficiency(unsigned int n) const {
    return effGlob(n) * eventWeight(n)->weight_average() ;
  }

  double StatSample::correctedEffErr(unsigned int n) const {
    const StatWeight* w = eventWeight(n) ;
    return sqrt(pow(w->weight_average()*effErrGlob(n),2) 
		+ pow(effGlob(n)*w->err(),2)) ;
  }

  double StatSample::correctedEfficiency(const std::string& name) const {
    return effGlob(name) * eventWeight(name)->weight_average() ;
  }

  double StatSample::correctedEffErr(const std::string& name) const {
    const StatWeight* w = eventWeight(name) ;
    return sqrt(pow(w->weight_average()*effErrGlob(name),2) 
		+ pow(effGlob(name)*w->err(),2)) ;
  }

  bool StatSample::compareNames(const StatSample& sample) const {
    
    if (_events.size() != sample._events.size()) return false ;

    for (unsigned int n = 0 ; n < _events.size() ; n++)
      if (_events[n]->name() != sample._events[n]->name() ) return false ;

    return true ;
  }

  bool StatSample::tagged(const cafe::Event* event) const {

    if (_tags.size()  == 0 &&  _tags_and.size()  == 0 ) return true ;

    for (vector<string>::const_iterator it = _tags_and.begin() ; 
	 it != _tags_and.end(); it++) {
       if (!event->hasTag(*it)) return false ;
    }

    return _tags.size()  == 0 || event->hasTag(_tags) ; 
  }


  ostream& StatSample::HtmlTable(ostream& os) const {
    
    bool weightMode = _weight->nevents() > 0 ?  true : false ;

    os << "<TABLE BORDERCOLORDARK=\"996633\"  BORDERCOLOR=\"CC9966\"    BORDERCOLORLIGHT=\"FFCC99\"   border=3 cellPadding=5 width=\"99%\">" << endl ;
    os << "<TBODY align=right>" << endl ;
    
    os << "<TR>" << endl ;
    os << "<TH align=left>" << endl ;
    os << "SELECTION"   ;
    os << " </TH>" << endl ;
    if (weightMode) 
      os << "<TH align=center colspan=4>" << endl ; 
    else 
      os << "<TH align=center colspan=3>" << endl ; 
    os <<  name() << endl ;
    os << "</TH>" << endl ; 
    os << "</TR>" << endl ;
      
    bool color = false ;
    
    for (unsigned int n = 0; n < size() ; n++) {
      
      if (color) {
	os << "<TR BGCOLOR=#bfefff>" << endl ; 
	color = !color ;
      } else { 
	os << "<TR>" << endl ; 
	color = !color ;
      }      
     
      os << "<TD align=left>" << endl ; 
      os <<  eventSelection(n)->name() << endl ;
      os << "</TD>" << endl ; 

      os << "<TD TITLE=\"Number of events\">" << endl ; 
      os <<  nevents(n) << endl ;
      if (n==0) {
	os << "<TD>&#160;</TD> <TD>&#160;</TD>" ;
	if (weightMode) os << "<TD>&#160;</TD> " ;
	os << endl ; 
	continue ;
      }
	
      if (eventSelection(n)->isWeight()) {
	  if (eventSelection(n)->name() == eventWeight()->name()) 
	    os << "</TD> <TD TITLE=\"Global event weight\">" << endl ; 
	  else 
	    os << "</TD> <TD TITLE=\"Average weight\">" << endl ; 
	  os << eff(n) << "&#177;" << effErr(n)<< endl ;
	  os << "</TD> <TD> &#160;</TD>";
	  if (weightMode) os << "<TD> &#160;</TD>";	  
	  os << endl ;
	  continue ;
      } 
      
      os << "</TD><TD TITLE=\"Selection efficiency\">"<< endl ;
      os << 100.0*eff(n) << "&#177;" << 100.0*effErr(n) << "%" << endl ;
      os << "</TD><TD TITLE=\"Global efficiency\">"<< endl ;
      os << 100.0*effGlob(n) << "&#177;" << 100.0*effErrGlob(n) << "%" 
	 << endl ;
      os << "</TD>" << endl ;       
      if (weightMode) {
	os << "</TD><TD TITLE=\"Global efficiency corrected by the event weight\">"<< endl ;
	os << 100.0*correctedEfficiency(n) << "&#177;" << 100.0*correctedEffErr(n) << "%" 
	   << endl ;
	os << "</TD>" << endl ;       	
      }
      os << "</TR>" << endl ; 
    }
    
    os << "</TBODY></TABLE>" << endl ;

    return os ;
  }


  ///output operator
  ostream& StatSample::print_tex (ostream& os, const string title) const {
    
    bool weightMode = _weight->nevents() > 0 ?  true : false ;

    os << "" << endl;
    os << "% Efficiency table %" << endl;
    os << "" << endl;
    os << "\\begin{table}[p]" << endl;
    os << "\\begin{center}" << endl;
    os << "\\begin{tabular}{lrrr" ; 
    if (weightMode) os << "r" ;
    os << "}" << endl;
    os << "  \\hline  \\hline" << endl;
    os << "  Selection & Events & Relative  & Total  " ;
    if (weightMode) os << "& Total Corrected by Event Weights " ;
    os << "\\\\ \\hline" << endl;
    
    os << tex(eventSelection(0)->name()) << " & " ;
    os <<  nevents(0) << " & & " ;
    if (weightMode) os << " & " ;
    os << "\\\\ " << endl ; 

    for (unsigned int n = 1; n < size() ; n++) {
      
      os << tex(eventSelection(n)->name()) << " & " ;
      os <<  nevents(n) << " & ";

      if (eventSelection(n)->isWeight()) {	
	os << " $\\mathit{ " << eff(n) << " \\pm " 
	   << effErr(n) << " }$ & & " ;
	if (weightMode) os << " & " ;
      } else {	
	os << " $ " << 100.0*eff(n) << " \\pm " 
	   << 100.0*effErr(n) << " ~\\% $ & " ;
	os << " $ " << 100.0*effGlob(n) << " \\pm " 
	   << 100.0*effErrGlob(n) << "~\\% $ " ;
	if (weightMode) 
	  os << " $ " << 100.0*correctedEfficiency(n) << " \\pm " 
	     << 100.0*correctedEffErr(n) << "~\\% $ " ;
      }

      os << " \\\\ " << endl ; 
    }

    os << "  \\hline " << endl;
    os << " \\hline" << endl;
    os << " \\end{tabular}" << endl;
    os << " \\caption{" << title << " Sample " << name() << " }" << endl;
    os << " \\label{Table:" <<  title.c_str() << ":" << name() << "}" << endl;
    os << "\\end{center}" << endl;
    os << "\\end{table}" << endl; 
    os << endl;

    return os ;    
  }

  
  std::string StatSample::tex(const std::string& init) {
    string name ;
    for (unsigned int i=0; i<init.size(); i++) {
      string ch ;
      if (init.substr(i,1) == "_") ch = "\\_" ;
      else if (init.substr(i,2) == ">=") {
	ch = "$\\geq$" ;
	i++ ;
      }
      else if (init.substr(i,2) == "<=") {
	ch = "$\\leq$" ;
	i++ ;
      }
      else if (init.substr(i,1) == "<") ch = "$<$" ;
      else if (init.substr(i,1) == ">") ch = "$>$" ;
      else ch = init.substr(i,1) ;
      name = name + ch ;
    }
    return name ;
  }

}

ClassImp(cafe::StatSample);
