#ifndef CAFE_STAT_HPP__
#define CAFE_STAT_HPP__

#include "cafe/StatSample.hpp"
#include "cafe/Processor.hpp"

#include <string>
#include <vector>
#include <map>

namespace cafe {

  /// Structure with samples for the systematics study
  struct Syst {
    std::string name ;
    const StatSample* reference;
    StatSample pos, neg ;
    Syst(const std::string& syst_name, const StatSample* reference_sample) :
      name(syst_name), reference(reference_sample), 
      pos(reference_sample->name()+"_"+name+"_pos"), 
      neg(reference_sample->name()+"_"+name+"_neg") {

      pos.AddTags(reference->tags()) ;
      //      pos.AddAndTags(reference->tagsAnd()) ;
      pos.AddAndTags(syst_name+"_pos") ;

      neg.AddTags(reference->tags()) ;
      //      neg.AddAndTags(reference->tagsAnd()) ;
      neg.AddAndTags(syst_name+"_neg") ;

    }
  };
    
 /*! \brief Class to collect selections statistics and print efficiencies.

 The Stat processor is designed to handle the event selection efficiencies 
 and events weights applied during the cut flow. To calculate the efficiency 
 one must add  "Stat(stname)" call in the beginning of the instruction
 "cafe.Run: ...". Than add following lines
 to the selection code (see, e.g. caf_util/src/ TopologicalSelector.cpp):

 \code
 #include "cafe/Stat.hpp" 
 StatPointer stat ; 
 event.get("StatPointer", stat) ; 
 
 ... Selection 1 ...
 
 stat->EventSelected("Selection 1 name") ;
 
 ... Selection 2 ....
 
 stat->EventSelected("Selection 2 name") ;
 \endcode

 For each cut the efficiency is calculated as 
 "number of events after cut" divided by "number of events before cut".
 The total selection efficiency is calculated as
 "number of events after cut" divided by "initial number of events", 
 where "initial number of events" corresponds to the position of the 
 "Stat(stname)" call in the "cafe.Run: ..." event flow.
 The best place for adding this processor is after "FindDuplicateEvents"
 processor, but before a first selector.
 The output efficiencies and corresponding statistical errors 
 will be printed in the html and tex file.
 These efficiencies as well as the number of events after each cut  
 available via Stat class accessors. \n

 One can also apply the event weights at the any place in the cut flow.
 For this add the following instruction to the code 
 (see e.g. caf_eff_utils/src/ MuonCorr.cpp): 

 \code
 stat.applyWeight(weight_name, weight) ; 
 \endcode

 Individual weights are saved in the Stat class and the global event weight
 calculated as the product of  all individual event weights applied up
 to the current selection. The average weights are printed
 in the output html file as well as the efficiency corrected by the global 
 event weight. One should note the the product of the average individual 
 event weights are not equal to the average global weight, because
 the averaging is done at the different selection stage and depends 
 on the event sample selected at this stage. All individual weights and
 the global event weight available via Stat accessors. For example, to
 correct the histogram with the global event weight, one could add 
 following lines to the code:

 \code
 #include "cafe/Stat.hpp" 
 StatPointer stat ; 
 event.get("StatPointer", stat) ; 

 Stat* statptr = stat.pointer() ;
 double weight = 0.0 ; // or any error value you want
 if (statptr) {
    try {
    weight = statptr->eventWeight("global"); 
    } catch (cafe::StatWeightNotFoundException& ex) {
    // you can do something different here, or just ignore the exception
      err() << "Processor [" << name()
	    <<"]: weight not found " << ex._weight_name ;
	    << endl ;
      exit(1) ;
    }
}

 hist->Fill(x,weight);
 \endcode

 To make the histogram of the individual event weight one could use 
 following example: 
 \code

 float weight = statptr->eventWeight("individual_weight_name"); 
 hist->Fill(weight) ;
 \endcode

 If you process several different samples in one job, Stat processor 
 can handle with situation and keep efficiencies and weights for 
 each sample separately.
 First, one need to specify sample names using the Sample configuration option, e.g. 
 \code
 stname.Sample: sample_name1, sample_name2.
 \endcode 

 If no sample specified, the default sample with name equal to the  
 Stat class name will be created.
 Than the event tags to tag different samples should be specified:

 \code
 sample_name1.UseTag: tag1 
 sample_name2.UseTag: tag2
 \endcode

 If tag is not specified all selected events will be added to a sample. 
 One event can be counted in the several samples.

 Finally one should tag the events in the 
 very beginning acording to the sample flavor 
 (before Stat processor in the "cafe.Run: ..." instruction).
 For this you need a special processor. Such processor could compare
 the file name with the given mask and assign a tag according to the file name. 
 An example of a processor could be found in the tt_emu_caf package 
 (see TagFileName processor).

 All accessors in the Stat class have an option to specify the sample name 
 when you acess efficiencies and weights.

 The Stat processor also can handle the systematics errors. 
 If systematics errors 
 come from the uncertainties in the event weight than it is sufficient 
 to specify weights with systematics shift
 together with the nominal event weight:

 \code
 stat.applyWeight(weight_name, weight, weight_positly_shifted, weight_negatively_shifted) ; 
 \endcode


 The errors for the average event weight in the output html table will contains 
 corresponding positive and negative systematics.

 If the systematics change the selection parameter (e.g. JES will affect the 
 jet pT cut efficiency), one need to create different selection chains (samples) 
 for nominal value, positively and negatively shifted values. 
 See caf_util/configs/ testJES.config \n
 First you should declared your systematics sample in the Stat processor. For 
 example for the systematics named "JES":

 \code
 stname.Systematics: JES
 \endcode

 Than you define your 3 processing chain for nominal, positively and 
 negatively shifted values:

\code
 cafe.Run: Stat(stname)
 ...
 +cafe.Run: Fork(jes)
 jes.Run: Group(jespos) Group(jesneg) Group(jesmain) 
 \endcode

 Here "jesmain" chain will use the nominal value, "jespos" and "jesneg"
 will shift all jet energies before applying standard selection (see
 caf_util/configs/ testJES.config for details). 
 Each processing chain must be tagged with appropriated tags. The appropriate 
 tag for the systematics called "JES" will be "JES" for the nominal value,
 "JES_pos" for the positively shifted value and "JES_neg" for the negatively shifted one. Than you should tag your events accordingly:

 \code
 cafe.Tag: JES JES_pos JES_neg
 jes.Untag: JES JES_pos  JES_neg
 jespos.Tag: JES_pos
 jesneg.Tag: JES_neg
 jesmain.Tag: JES
 \endcode
 Please, note that in the beginning of the event processing  you must tag the event with all 3 tags,
 than after Fork processor (in fact using the  Fork processor interfaces) 
 you must remove all these tags and tag each branch 
 with the corresponding tag.
 The systematics table will be printed in the end of the html or tex 
 output file.


 Configuration options:

 - .Output:  output file name without extension  [default: efficiencies] 

 - .Sample:  data or MC sample name   [default: processor name] 
 - SampleName.UseTag:  tag1, tag2     [default: no tag, all events will be used]

 - .InitialTag: tag1,tag2  tag all events with following tags [default: events are not tagged]

 - .TexTitle: if this option is specified the output tex file will be created with name
   OutputFilename.tex and title in the file will be set to TexTitle [default: ""]

 - .Precision: the presecion parameter for html and text output streams 
 (number of numbers after the floating point) [default: 3]

 - .IgnoreAutoRecords: ignore records made automatically (with "PROCESSOR" keyword) [default: 0 (false)] 

 - .Update: n specify number of event to make and updated statistic files. 0 means no update, 
 sttaistcs will be printed after end of the job [default: 0]

 - .Systematics: specify the list of the systematics names. The samples to study this systematics 
   (posistive and negative) will be added to the stat object. User must additionally tag events for these samples
   with tags name, name_pos and name_neg, where name if the systematics name.

 - .PrintSystematics: print the output html selection table for the systematics samples [default:false]

    \author Viatcheslav Shary (shary@fnal.gov)
  */
  
  class Stat : public cafe::Processor{

    std::vector<StatSample> _samples ; //< number of selected events for the different samples
    std::vector<Syst> _syst ; //< vector with systematics samples
    cafe::Event* _event ; //< pointer to the event object
    std::vector<std::string> _tags ; //< initial tags used to tag events
    bool _ignoreauto ;  //< ignore records made automatically
    int _precision ; //< presicion parameter for output streams
    unsigned long int _update ; // number of events between output statistics updates
    std::string _output_name;   // name of efficiencies file
    std::string _title;

    /// return positive systematics  only from Syst samples
    double syst_pos(std::vector<Syst>::const_iterator jt) const ;

    /// return negative systematics only from Syst samples
    double syst_neg(std::vector<Syst>::const_iterator jt) const ;

    /// return error for the positive systematics only from Syst samples
    double systerr_pos(std::vector<Syst>::const_iterator jt) const ;

    /// return error for the positive systematics only from Syst samples
    double systerr_neg(std::vector<Syst>::const_iterator jt) const ;

	/// Pointer to the paretn Stat object if we are chained.
	Stat *_parent_stat;

  public:

	/// What everyone else should use
    Stat(const char *name);
	/// Use if you are trying to keep more than one around at once.
	Stat(const char *name, bool duplicate_ok);
    ~Stat();

    /*! \brief Return event weight by name. Return global event weight for the first sample by default.
      If weight with specified name  was not found or sample with name sample_name does not exist
      return -1.0 
    */ 
    double eventWeight(const std::string& name="global", 
		       const std::string sample_name="not_specified") const ;


    /// Return a Collection of event weights available. The global event weight comes first
    Collection<EventWeight> ListEventWeights(const std::string sample_name="not_specified") const ;

    /// Return number of events by selection name
    double nevents(const std::string& name="Initial", const std::string& sample_name="not_specified") const ;

    /// return efficiency corrected by the global event weight
    double efficiencyCorrected(const std::string& sample_name="not_specified") const;

    /// return global efficiency 
    double efficiency(const std::string& sample_name="not_specified") const;

    /// return positive systematics with name "name" for the sample sample_name 
    /// if systematics is a weight, the statistical errors on the weight will be added to systematics 
    double syst_pos(const std::string& name, const std::string& sample_name="not_specified") const ; 

    /// return negative systematics with name "name" for the sample sample_name 
    /// if systematics is a weight, the statistical errors on the weight will be added to systematics 
    double syst_neg(const std::string& name, const std::string& sample_name="not_specified") const ; 

    /// return error for the positive systematics with name name for the sample sample_name 
    double systerr_pos(const std::string& name, const std::string& sample_name="not_specified") const ; 

    /// return error for the positive systematics with name name for the sample sample_name 
    double systerr_neg(const std::string& name, const std::string& sample_name="not_specified") const ; 

    /// retun list of samples
    std::vector<const cafe::StatSample*> get_samples() const ;

    /// retun list of systematics samples
    std::vector<const cafe::Syst*> get_syst() const ;

    /// initialization
    void begin();

    /// Print efficiencies
    void finish() ;

    /// increase number of events  before any selection
    bool processEvent(cafe::Event& event);

    /// Increase number of event selected. If such selection does not exist it will be added
    void EventSelected(const std::string& selection_name) ;

    /// apply weight to efficiency calculation. 
    void applyWeight(const std::string& weight_name, 
		     double weight, double weight_pos=-1.0, double weight_neg=-1.0) ;

    /// make clean in the end of the event
    void eventEnd() ;

    /// Add sample and return reference to it
    StatSample&  add_sample(const std::string& name) {_samples.push_back(name); return _samples.back();} 

    /*! \brief Add samples for the systematics (with name "name") study. If sample == 0, 
              systematics samples will be added to all existing samples .
    */
    void add_syst(const std::string& name, StatSample* sample=0) ;

    /// these tags will be added to the list to event tag in the begining ProcessEvent
    void tag(const std::vector<std::string>& tags) ;

   ///output operator
    ostream& print_html(ostream& os) const ; 
    ostream& print_tex(ostream& os, const std::string title="Efficiency") const ; 

	// Use when you need to use a sub-stat processor.
	void chain (void);
	void unchain (void);
	
	// Use to inherrit current weights from parent
	void inheritWeights();
    
  public:
    ClassDef(Stat, 0) ;
  };

   /// Pointer to the Stat object. Created and deleted at each event processing.
  class StatPointer {
    Stat* _stat ;
    
  public :
    StatPointer(Stat* stat=0) ;
    virtual ~StatPointer() ;
    Stat* pointer() {return _stat;}
 
    /// Increase number of event counted by Stat object. If such selection does not exist it will be added
    void EventSelected(const std::string& selection_name) ;

    /// apply weight to efficiency calculation. 
    void applyWeight(const std::string& weight_name, 
		     double weight, double weight_pos=-1.0, double weight_neg=-1.0) ;

    ClassDef(StatPointer, 0) ;

  } ;
}

#endif // CAFE_STAT_HPP__
