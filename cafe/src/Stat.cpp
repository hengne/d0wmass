#include "cafe/Stat.hpp"
#include "cafe/Config.hpp"
#include "cafe/StatSample.hpp"
#include <stdexcept>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

cafe::Stat* STAT = 0 ; 

namespace cafe {

  StatPointer::StatPointer(Stat* stat) : _stat(stat) { }
  StatPointer::~StatPointer() {}

  void StatPointer::EventSelected(const string& selection_name) {
    if (_stat) _stat->EventSelected(selection_name)  ;
    return ;
  }

  void StatPointer::applyWeight(const std::string& weight_name, double weight, 
				double weight_pos, double weight_neg) {
    if (_stat) _stat->applyWeight(weight_name, weight, weight_pos, weight_neg) ;
    return ;
  }

  //================================================================================

  Stat::Stat(const char *name) : Processor(name), _event(0), _parent_stat(0)  { 

	///
	/// If we are the first one, we establish ourselves as the primere dude. Otherwise, we don't do anything. Errors will
	/// occur further down if the user tries to do two Stat at once without some careful shuffling.
	///

	if (!STAT) {
	  STAT = this ;
	} else {
	  throw std::runtime_error ("You may have only a single STAT object around at a time! First Stat object was named " + STAT->name() + " and this second one is named " + name + ".");
	}
  }

  Stat::Stat (const char *name, bool ignore_duplicate)
	: Processor (name), _event(0), _parent_stat(0)
  {
	if (!STAT) {
	  STAT = this ;
	} else {
	  if (!ignore_duplicate) {
  		throw std::runtime_error ("You may have only a single STAT object around at a time! First Stat object was named " + STAT->name() + " and this second one is named " + name + ".");
	  }
	}
  }

  Stat::~Stat() {} ;

  void Stat::chain(void)
  {
	/// We can't chain if we are already in the chain!
	assert (_parent_stat == 0);
	assert (this != STAT);

	_parent_stat = STAT;
	STAT = this;
  }

  void Stat::unchain(void)
  {
	/// Can't unchain if we aren't in a chain!
	assert (_parent_stat != 0);
	assert (this == STAT);

	STAT = _parent_stat;
	_parent_stat = 0;
  }

  ///
  /// Get a list of all applied weights from the parent and apply them down here.
  ///
  void Stat::inheritWeights (void)
  {
	assert (_parent_stat != 0);
	assert (this == STAT);

	///
	/// Use only the first stat sample to do the weight mapping.
	///

	const StatSample *stat_sample = _parent_stat->get_samples().front();

	int num_selections = stat_sample->size();
	for (int i = 0; i < num_selections; i++) {
	  const StatSelection *stat = stat_sample->eventSelection(i);
	  if (stat->isWeight()) {
		const StatWeight *stat_wt = dynamic_cast<const StatWeight*> (stat);
		double wt = stat_wt->weight();
		double wt_neg = stat_wt->weight_neg();
		double wt_pos = stat_wt->weight_pos();

		applyWeight (stat_wt->name(), wt, wt_neg, wt_pos);
	  } else {
		EventSelected (stat->name());
	  }
	}
  }

  void Stat::begin() 
  {
      Config config(name());
	
      // Get .AddSample entry
      vector<string> sample = config.getVString("Sample"," ,");
      for (vector<string>::const_iterator it = sample.begin() ;
	   it != sample.end() ; it++) {

	  string s = *it ;
	  while (s.size() > 0 && s.substr(0,1) == " ") s.erase(0,1) ;
	  while (s.size() > 0 && s.substr(s.size()-1,1) == " ") s.erase(s.size()-1,1) ;      
	  if (s.size() ==0 ) continue ;

	  _samples.push_back(s) ;

	  Config sample_config(s);

	  vector<string> tags = sample_config.getVString("UseTag"," ,");
	  if (tags.size()>0) _samples.back().AddTags(tags) ;

	  vector<string> tags_and = sample_config.getVString("AndTag"," ,");
	  if (tags_and.size()>0) _samples.back().AddAndTags(tags_and) ;
      }
    
      /// add systematics
      vector<string> syst = config.getVString("Systematics"," ,");      
      for( vector<string>::const_iterator it = syst.begin() ;
	   it != syst.end(); it++) add_syst(*it) ;    

      if (_samples.size() == 0)
	  _samples.push_back(StatSample(name())) ;

      tag(config.getVString("InitialTag",",")) ;
    
      _ignoreauto = config.get("IgnoreAutoRecords",false) ;
      _precision = config.get("Precision",3) ;
      _update = config.get("Update",0) ;

      _output_name = config.get("Output", "efficiencies");
      _title = config.get("TexTitle","");

      // read this variable first here just to avoid the error message "not used" in cafe
      config.get("PrintSystematics", false) ;
  }

  void Stat::finish(){

    ofstream html( (_output_name + ".html").c_str() );
    html.setf(ios::fixed);
    html.precision(_precision) ;
    print_html(html) ;

    if (_title != "") {
      ofstream tex( (_output_name + ".tex").c_str() );
      tex.setf(ios::fixed);
      tex.precision(_precision) ;
      print_tex(tex, _title) ;
      tex.close() ;
    }
  }

  void Stat::eventEnd() {
    _event = 0 ;

    for (vector<StatSample>::iterator it = _samples.begin() ;
	 it != _samples.end() ; it++) it->Clear() ;

    for (vector<Syst>::iterator it = _syst.begin() ;
	 it != _syst.end() ; it++) {
      it->pos.Clear() ;
      it->neg.Clear() ;
    }    
  }

  bool Stat::processEvent(cafe::Event& event) {

    StatPointer stat ;
    if (event.get("StatPointer", stat)) {
      err() << "ERROR! Stat: [" << name() << "] An another instance of the Stat proccesor is running! "
	    << "Only one instance of the Stat processor must be used!" << endl;
      throw runtime_error("Stat:: Only one instance allow for the cafe::Stat processor!") ;
    }
    stat = this ;
    event.put("StatPointer", stat) ;


    //--------------------------------------------------

    _event = &event ;

    // tag event
    for (vector<string>::const_iterator it = _tags.begin() ;
	 it!= _tags.end(); it++) _event->tag(*it)  ;

    for (vector<StatSample>::iterator it = _samples.begin() ;
	 it != _samples.end() ; it++)  
      it->add(_event) ;

    for (vector<Syst>::iterator it = _syst.begin() ;
	 it != _syst.end() ; it++) {
      it->pos.add(_event) ;
      it->neg.add(_event) ;
    }

    if (_update > 0 && eventCount()%_update == 0) finish() ;

    return true ;
  }

  void Stat::EventSelected(const string& selection_name) {
    if (!_event)  return ;
    for (vector<StatSample>::iterator it = _samples.begin() ;
	 it != _samples.end() ; it++) {
      if (!_ignoreauto || selection_name.substr(0,9) != "PROCESSOR")
	it->add(_event, selection_name) ;
    }
    for (vector<Syst>::iterator it = _syst.begin() ;
	 it != _syst.end() ; it++) {
      if (!_ignoreauto || selection_name.substr(0,9) != "PROCESSOR") {
	it->pos.add(_event, selection_name) ;
	it->neg.add(_event, selection_name) ;
      }
    }
    return ; 
  }


  void Stat::applyWeight(const std::string& weight_name, 
			 double weight, double weight_pos, double weight_neg) {
    for (vector<StatSample>::iterator it = _samples.begin() ;
	 it != _samples.end() ; it++) 
      it->applyWeight(_event, weight_name, weight, weight_pos, weight_neg) ;

    for (vector<Syst>::iterator it = _syst.begin() ;
	 it != _syst.end() ; it++) {
      it->pos.applyWeight(_event, weight_name, weight, weight_pos, weight_neg) ;
      it->neg.applyWeight(_event, weight_name, weight, weight_pos, weight_neg) ;
    }

    return ; 
  }

  //================================================================================

  ///output operator
  ostream& Stat::print_html (ostream& os) const {

    // head of the page ===========================================================
    os << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">" << endl ;
    os << "<HTML><HEAD><TITLE>ANALYSIS EFFICIENCIES</TITLE>" << endl ;
    os << "<META content=\"text/html; charset=windows-1252\" http-equiv=Content-Type>" << endl ;
    os << "</HEAD>" << endl ;
    os << "<BODY aLink=#006600 bgColor=#fffaf0" << endl ;
    os << "link=\"blue\" text=\"black\" vLink=\"blue\">" << endl ;
    os << " <H2 ALIGN=CENTER> " << endl ;
    os << "ANALYSIS EFFICIENCIES" << endl ;
    os << "</H2>" << endl ;
    os << "" << endl ;
    
    os << "<TABLE align=right border=0 cellPadding=10 width=\"95%\">" << endl ;
    os << "  <TBODY>" << endl ;
    os << "  <TR>" << endl ;
    os << "    <TD WIDTH=\"60%\">" << endl ;
    os << "  </TD>" << endl ;
    os << "  <TD>last updated:" << endl ;
    os << "      <SCRIPT language=JavaScript>" << endl ;
    os << " <!-- " << endl ;
    os << "document.writeln(document.lastModified);" << endl ;
    os << "// -->" << endl ;
    os << "</SCRIPT>" << endl ;
    os << "       </TD></TR></TBODY></TABLE> <BR>" << endl ;
    os << " " << endl ;
    
    os << "<HR noShade>" << endl ;
    
    //--------------- Results table ------------------------------

    bool only_one = true ;
    
    if (_samples.size() > 1) {
      for (vector<StatSample>::const_iterator it = _samples.begin()+1 ;
	   it != _samples.end() ; it++) 
	if (!_samples.begin()->compareNames(*it)) {
	  only_one = false ;
	  break ;
	}
    }
  
    // number of tabels per page
    size_t ntables = 3 ;
    if(!only_one) ntables = 2 ;       

    for (size_t ns = 0 ; ns < _samples.size(); ns += ntables) {
      
      vector<StatSample>::const_iterator itbegin = _samples.begin() + ns;
      vector<StatSample>::const_iterator itend  ;
      if (ns+ntables < _samples.size()) itend = _samples.begin() + ns + ntables ;
      else itend = _samples.end() ;
      
      // table width in pixels
      int column_width = 450 ;
      int width = column_width ;
      if (_samples.size() - ns == 1) width = 2*width  ;
      else if (only_one) width = (1+min(_samples.size() - ns, ntables))*width ;
      else width = min(_samples.size() - ns, ntables)*2*width ;
      
      os << "<TABLE BORDERCOLORDARK=\"996633\"  BORDERCOLOR=\"CC9966\" BORDERCOLORLIGHT=\"FFCC99\"   border=3 cellPadding=5 width=" << width << ">" << endl ;
      os << "<TBODY align=right>" << endl ;
      
      os << "<TR>" << endl ;
      for (vector<StatSample>::const_iterator jt = itbegin ;
	   jt != itend ; jt++) {
	
	bool weightMode = jt->eventWeight()->nevents() > 0 ?  true : false ;

	if (!only_one || jt == itbegin) {
	  os << "<TH align=left>" << endl ;
	  os << "SELECTION"   ;
	  os << " </TH>" << endl ;
	}
	
	if (weightMode) 
	  os << "<TH align=center colspan=4>" << endl ; 
	else 
	  os << "<TH align=center colspan=3>" << endl ; 

	os <<  jt->name() << endl ;
	if (jt->tags().size()>0) {
	  os << " (tags:"  ;
	  for (vector<string>::const_iterator it = jt->tags().begin() ;
	       it != jt->tags().end(); it++) 
	    os << " " << *it ;
	  os << ")" << endl ;
	}
	os << "</TH>" << endl ; 
      }

      os << "</TR>" << endl ;
      
      bool color = false ;
      
      unsigned int selsize = 1 ;
      for (vector<StatSample>::const_iterator jt = itbegin ;
	     jt != itend ; jt++) 
	selsize = max(jt->size(),selsize) ;

      for (unsigned int n = 0; n < selsize ; n++) {
	
	if (color) {
	  os << "<TR BGCOLOR=#bfefff>" << endl ; 
	  color = !color ;
	} else { 
	  os << "<TR>" << endl ; 
	  color = !color ;
	}      
     
      for (vector<StatSample>::const_iterator jt = itbegin ;
	     jt != itend ; jt++) {

	bool weightMode = jt->eventWeight()->nevents() > 0 ?  true : false ;
	
	if (n >= jt->size()) {
	  if (!only_one || jt == itbegin) os << "<TD>&#160;</TD> " ; 	    
	  os << "<TD>&#160;</TD> <TD>&#160;</TD> <TD>&#160;</TD>" ;
	  if (weightMode) os << "<TD>&#160;</TD> " ;
	  os << endl ; 
	  continue ;
	}

	if (!only_one || jt == itbegin) {
	  os << "<TD align=left>" << endl ; 
	  os <<  jt->eventSelection(n)->name() << endl ;
	  os << "</TD>" << endl ; 
	}

	  
	os << "<TD TITLE=\"Number of events\">" << endl ; 
	os <<  jt->nevents(n) << endl ;
	if (n==0) {
	  os << "<TD>&#160;</TD> <TD>&#160;</TD>" ; 
	  if (weightMode) os << "<TD>&#160;</TD> " ;
	  os << endl ; 
	  continue ;
	}
	
	if (jt->eventSelection(n)->isWeight()) {
	  if (jt->eventSelection(n)->name() == jt->eventWeight()->name()) 
	    os << "</TD> <TD TITLE=\"Global event weight\">" << endl ; 
	  else 
	    os << "</TD> <TD TITLE=\"Average weight\">" << endl ; 
	  os << jt->eff(n) << "&#177;" << jt->effErr(n)<< endl ;
	  const StatWeight* w = jt->eventWeight(n) ;
	  if (w->weight_average_pos()>=0 || 
	      w->weight_average_neg()>=0 )
	    os << " +" << w->weight_average_pos() - w->weight_average()
	       << " -" << w->weight_average() - w->weight_average_neg() ;
	  os << "</TD> <TD> &#160;</TD>" ;
	  if (weightMode) os << "<TD>&#160;</TD> " ;
	  os << endl ; 
	  continue ;
	} 
	
	os << "</TD><TD TITLE=\"Selection efficiency\">"<< endl ;
	os << 100.0*jt->eff(n) << "&#177;" << 100.0*jt->effErr(n) << "%"
	   << endl ;
	os << "</TD><TD TITLE=\"Global efficiency\">"<< endl ;
	os << 100.0*jt->effGlob(n) << "&#177;" << 100.0*jt->effErrGlob(n) << "%" 
	   << endl ;
	os << "</TD>" << endl ; 
	if (weightMode) {
	  os << "</TD><TD TITLE=\"Global efficiency corrected by the event weight\">"<< endl ;
	  os << 100.0*jt->correctedEfficiency(n) << "&#177;" << 100.0*jt->correctedEffErr(n) << "%" 
	     << endl ;
	  os << "</TD>" << endl ;       	
	}
      }
      os << "</TR>" << endl ; 
      }

      os << "</TBODY></TABLE>" << endl ;
    }

    os << "<BR><BR>" << endl ;


    // systematics samples   

    if (_syst.size()>0) {
    os << "<TABLE BORDERCOLORDARK=\"996633\"  BORDERCOLOR=\"CC9966\" BORDERCOLORLIGHT=\"FFCC99\"   border=3 cellPadding=5 width=1200>" << endl ;
    os << "<TBODY align=right>" << endl ;
    
    os << "<TR>" << endl ;
    os << "<TH align=left>SYSTEMATICS</TH>" << endl ;
    os << "<TH align=left>SAMPLE</TH>" << endl ;
    os << "<TH>POSITIVE</TH>" << endl ;
    os << "<TH>NEGATIVE</TH>" << endl ;
    os << "</TR>" << endl ;
    
    for (vector<Syst>::const_iterator jt = _syst.begin() ;
	 jt != _syst.end() ; jt++) {
      os << "<TR>" << endl ;
      os << "<TD align=left>" ;
      os << jt->name ;
      os << "</TD>" << endl ;      
      os << "<TD align=left>" ;
      os << jt->reference->name() ;
      os << "</TD>" << endl ;      

      os << "<TD align>" ;
      os << 100*syst_pos(jt) << "&#177;" << 100*systerr_pos(jt) << " %";
      os << "</TD>" << endl ;      

      os << "<TD align>" ;
      os << 100*syst_neg(jt) << "&#177;" << 100*systerr_neg(jt) << " %";
      os << "</TD>" << endl ;      
      os << "</TR>" << endl ;
    }	      

    os << "</TBODY></TABLE>" << endl ;
    }
    
    // print systematics sample selections 
      Config config(name());
      if (config.get("PrintSystematics", false) ) {
	for (vector<Syst>::const_iterator jt = _syst.begin() ;
	     jt != _syst.end() ; jt++) {
	  jt->pos.HtmlTable(os) ;
	  jt->neg.HtmlTable(os) ;
	}
      }

    os << "</BODY>" << endl ;

    return os ;
    
  }

  //================================================================================

  ///output operator
  ostream& Stat::print_tex (ostream& os, const string title) const {

    for (vector<StatSample>::const_iterator jt = _samples.begin() ;
	 jt != _samples.end() ; jt++) jt->print_tex(os, title) ;


    //------ Systematics tables ----------------------------------------

    for (vector<Syst>::const_iterator jt = _syst.begin() ;
	 jt != _syst.end() ; jt++) {
      
      os << "" << endl;
      os << "% Systematics table %" << endl;
      os << "" << endl;
      os << "\\begin{table}[p]" << endl;
      os << "\\begin{center}" << endl;
      os << "\\begin{tabular}{llrr}" << endl;
      os << "  \\hline  \\hline" << endl;
      os << "  Systematics & Sample & Positive [\\%] & Negative  [\\%] \\\\ \\hline" << endl;      
      os << StatSample::tex(jt->name) << " &  " ;
      os << StatSample::tex(jt->reference->name()) << " &  " ;
      os << " $ " << 100.0*syst_pos(jt)<< "\\pm " << 100.0*systerr_pos(jt) << " $ & $ " 
	 << 100.0*syst_neg(jt)<< "\\pm " << 100.0*systerr_neg(jt) << " $ \\\\ " << endl ;
      os << "  \\hline " << endl;
      
      os << " \\hline" << endl;
      os << " \\end{tabular}" << endl;
      os << " \\caption{ Systematics }" << endl;
      os << " \\label{Table:syst:}" << endl;
      os << "\\end{center}" << endl;
      os << "\\end{table}" << endl; 
      os << endl;      
    }

    return os ;
      
  }

  double Stat::efficiencyCorrected(const std::string& sample_name) const {
    if (sample_name == "not_specified") return _samples.front().correctedEfficiency() ;
    for (vector<StatSample>::const_iterator it = _samples.begin() ;
         it != _samples.end() ; it++)
      if (it->name() == sample_name) return it->correctedEfficiency() ;
    cerr << "Stat::efficiencyCorrected ERROR: no sample with name \"" << sample_name
          << "\" has been found. " << endl ;
    return 0 ;
  }
                                                        
  double Stat::efficiency(const std::string& sample_name) const {
    if (sample_name == "not_specified") return _samples.front().effGlob() ;
    for (vector<StatSample>::const_iterator it = _samples.begin() ;
         it != _samples.end() ; it++)
      if (it->name() == sample_name) return it->effGlob() ;
    cerr << "Stat::efficiency ERROR: no sample with name \"" << sample_name
          << "\" has been found. " << endl ;
    return 0 ;
  } 

  double Stat::eventWeight(const std::string& name, const std::string sample_name) const {
    if (sample_name == "not_specified") 
      return _samples.front().eventWeight(name)->weight() ;

    for (vector<StatSample>::const_iterator it = _samples.begin() ;
	 it != _samples.end() ; it++) 
      if (it->name() == sample_name )
	return it -> eventWeight(name)->weight() ;

    return -1.0 ;
  }
  
  Collection<EventWeight> Stat::ListEventWeights(const std::string sample_name) const {
    if (sample_name == "not_specified") 
      return _samples.front().ListEventWeights() ;

    for (vector<StatSample>::const_iterator it = _samples.begin() ;
	 it != _samples.end() ; it++) 
      if (it->name() == sample_name ) 
	return it -> ListEventWeights();

    Collection<EventWeight> useless_collection;
    return useless_collection;
  }
  
  double Stat::nevents(const string& name, const string& sample_name) const {
    if (sample_name == "not_specified") return _samples.front().nevents(name) ;
    for (vector<StatSample>::const_iterator it = _samples.begin() ;
	 it != _samples.end() ; it++) 
      if (it->name() == sample_name) return it->nevents(name) ;
    cerr << "Stat::nevents ERROR: no sample with name \"" << sample_name
	  << "\" has been found. " << endl ;
    return 0 ;
  }

  void Stat::tag(const vector<string>& tags) {
    for(vector<string>::const_iterator it = tags.begin();
	it != tags.end(); it++) _tags.push_back(*it) ;
  }
  

  void Stat::add_syst(const string& name, StatSample* sample) {
    if(sample) {
      _syst.push_back(Syst(name, sample)) ;
      sample->AddAndTags(name) ;
      return ;
    }
    
    for (vector<StatSample>::iterator it = _samples.begin();
	 it != _samples.end(); it++) {
      _syst.push_back(Syst(name,&(*it))) ;
      it->AddAndTags(name) ;
    }
  }


  double Stat::syst_pos(std::vector<Syst>::const_iterator jt) const {
    if (jt->pos.nevents() <= 0  || jt->reference->nevents() <= 0 || jt->reference->effGlob() <= 0 ) return 0 ;
    return jt->pos.effGlob() / jt->reference->effGlob() - 1.0  ;
  }

  double Stat::systerr_pos(std::vector<Syst>::const_iterator jt) const {
    double s1 = jt->pos.nevents(jt->pos.size()-1) ;
    double s2 = jt->reference->nevents(jt->reference->size()-1) ;
    if (s1 == s2)  return 0 ;
    if (s1 > s2) return sqrt(s2/s1*(s1-s2))/s1 ;
    return sqrt(s1/s2*(s2-s1))/s2 ;
  }

  double Stat::syst_pos(const std::string& name, const std::string& sample_name) const {
    vector<Syst>::const_iterator jt = _syst.begin() ;
    for (; jt != _syst.end(); jt++) 
      if (jt->name == name && (sample_name == "not_specified" || jt->reference->name() == sample_name))
	break ;
    if (jt != _syst.end()) return syst_pos(jt) ;

    // if systematics sample with name "name"  was not found, 
    // try find weight with name "name"

    vector<StatSample> ::const_iterator it = _samples.begin();    
    if (sample_name != "not_specified") {
      for ( ; it != _samples.end() ; it++) 
	if (it->name() == sample_name) break ;
      if (it == _samples.end()) return 0 ;
    }
    
    const StatWeight* w = it->eventWeight(name) ;
    if (!w->isWeight()) return 0 ;
    
    if (w->weight_average_pos() < 0 ) return 0 ;
    float err = w->weight_average_pos() - w->weight_average() ;

    // add also  statistical fluctuation  on weight
    float sign = err < 0 ? -1.0 : 1.0 ;
    return sign*sqrt(err*err +pow(w->err(),2)) ;
  }

  double Stat::systerr_pos(const std::string& name, const std::string& sample_name) const {
    vector<Syst>::const_iterator jt = _syst.begin() ;
    for (; jt != _syst.end(); jt++) 
      if (jt->name == name && (sample_name == "not_specified" || jt->reference->name() == sample_name))
	break ;
    if (jt != _syst.end()) return systerr_pos(jt) ;
    return -1.0 ;
  }


  double Stat::syst_neg(std::vector<Syst>::const_iterator jt) const {
    if (jt->neg.nevents() <= 0  || jt->reference->nevents() <= 0 || jt->reference->effGlob() <= 0 ) return 0 ;
    return jt->neg.effGlob() / jt->reference->effGlob() - 1.0  ;
  }

  double Stat::systerr_neg(std::vector<Syst>::const_iterator jt) const {
    double s1 = jt->neg.nevents(jt->neg.size()-1) ;
    double s2 = jt->reference->nevents(jt->reference->size()-1) ;
    if (s1 == s2)  return 0 ;
    if (s1 > s2) return sqrt(s2/s1*(s1-s2))/s1 ;
    return sqrt(s1/s2*(s2-s1))/s2 ;
  }

  double Stat::syst_neg(const std::string& name, const std::string& sample_name) const {
    vector<Syst>::const_iterator jt = _syst.begin() ;
    for (; jt != _syst.end(); jt++) 
      if (jt->name == name && (sample_name == "not_specified" || jt->reference->name() == sample_name))
	break ;
    if (jt != _syst.end()) return syst_neg(jt) ;

    // if systematics sample with name "name"  was not found, 
    // try find weight with name "name"

    vector<StatSample> ::const_iterator it = _samples.begin();    
    if (sample_name != "not_specified") {
      for ( ; it != _samples.end() ; it++) 
	if (it->name() == sample_name) break ;
      if (it == _samples.end()) return 0 ;
    }
    
    const StatWeight* w = it->eventWeight(name) ;
    if (!w->isWeight()) return 0 ;
    
    if (w->weight_average_neg() < 0 ) return 0 ;
    float err = w->weight_average_neg() - w->weight_average() ;

    // add also  statistical fluctuation  on weight
    float sign = err < 0 ? -1.0 : 1.0 ;
    return sign*sqrt(err*err +pow(w->err(),2)) ;

  }

  double Stat::systerr_neg(const std::string& name, const std::string& sample_name) const {
    vector<Syst>::const_iterator jt = _syst.begin() ;
    for (; jt != _syst.end(); jt++) 
      if (jt->name == name && (sample_name == "not_specified" || jt->reference->name() == sample_name))
	break ;
    if (jt != _syst.end()) return systerr_neg(jt) ;
    return -1.0 ;
  }

  vector<const StatSample*> Stat::get_samples() const {
    vector<const StatSample*> s ;
    for (vector<StatSample>::const_iterator it = _samples.begin();
	 it != _samples.end(); it++) s.push_back(&(*it)) ;
    return s ;
  }

  vector<const Syst*> Stat::get_syst() const {
    vector<const Syst*> s ;
    for (vector<Syst>::const_iterator it = _syst.begin();
	 it != _syst.end(); it++) s.push_back(&(*it)) ;
    return s ;
  }

}

ClassImp(cafe::Stat);
ClassImp(cafe::StatPointer);
