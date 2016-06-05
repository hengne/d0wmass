#ifndef TriggerCounter_HPP_
#define TriggerCounter_HPP_

#include <map>

#include "cafe/Event.hpp"
#include "cafe/Processor.hpp"

using namespace cafe;

class TriggerCounter : public cafe::Processor {
  
 public:

 // Constructor, destructor: 
  TriggerCounter(const char *name);
  ~TriggerCounter();
  
  void begin();
  bool processEvent(cafe::Event& event);
  void finish();
  void inputFileOpened(TFile *file);
  void inputFileClosing(TFile *file);

  ClassDef(TriggerCounter, 0);
  
 private:
  
  typedef std::map<std::string, UInt_t> counter_map;
  counter_map counter;
  counter_map exclusive;
  UInt_t events;
	std::string _basicname;
	int tgvtrigger_count;
	int ntgvtrigger_count;
	int e1trigger_count;
	int e2trigger_count;
	int te1trigger_count;
	int te2trigger_count;
	int te3trigger_count;
	int te4trigger_count;
	int te5trigger_count;
	int de1trigger_count;
	int de2trigger_count;
	int de3trigger_count;
	int de4trigger_count;
	int de5trigger_count;
	int de6trigger_count;
	int de7trigger_count;
	int de8trigger_count;
	int dmu1trigger_count;
	int dmu2trigger_count;
	int dmu3trigger_count;
	int dmu4trigger_count;
	int dmu5trigger_count;
	int me1trigger_count;
	int me2trigger_count;
	int me3trigger_count;
	int me4trigger_count;
	int me5trigger_count;
	int jt1trigger_count;
	int jt2trigger_count;
	int jt3trigger_count;
	int mjtrigger_count;
	int mtktrigger_count;
	int muhtrigger_count;
	int mujtrigger_count;
	int isht22_count;
	int sht25_count;
	int ish30_count;
	int sh35_count;
	int l70_count;
	int t15sh20_count;
	int t13sht15_count;
	int t13_isht15_count;
	int lh2ish24_count;
	int lh2sh27_count;
	int lh2l70_count;
	int t14lh2sh17_count;
	int _2l15sh15_l20_count;
	int _2sh10_sh15_count;
	int _2_t10l10_l15_count;
	int _2l6_l8_t5sh6_count;
	int _2l20_l25_count;
	int _2t5sh5_count;
	int _1l1mm2_count;
	int _2lm0mm0tlm3_count;
	int tk10_2lm3_count;
	int itk10_ilm6_count;
	int tk8_tlm8_count;
	int _2lm6_count;
	int lm6_tk12_count;
	int _2tk3tk5tlm3_count;
	int ish7_trk5_count;
	int ish7_mm5_count;
	int lel15_trk5_count;
	int lel15_mm5_count;	
	int sh12_trk5_count;
	int sh12_mm5_count;
	int rd5_count;
	int aco_mht_lm0_count;
	int aco_mht_er2_count;
	int aco_mht_bdv_count;
	int mhtaco_count;	
	int met_count;
	int mht40_ht_count;

	int e1trigger_count_exc;
	int e2trigger_count_exc;
	int te1trigger_count_exc;
	int te2trigger_count_exc;
	int te3trigger_count_exc;
	int te4trigger_count_exc;
	int te5trigger_count_exc;
	int de1trigger_count_exc;
	int de2trigger_count_exc;
	int de3trigger_count_exc;
	int de4trigger_count_exc;
	int de5trigger_count_exc;
	int de6trigger_count_exc;
	int de7trigger_count_exc;
	int de8trigger_count_exc;
	int dmu1trigger_count_exc;
	int dmu2trigger_count_exc;
	int dmu3trigger_count_exc;
	int dmu4trigger_count_exc;
	int dmu5trigger_count_exc;
	int me1trigger_count_exc;
	int me2trigger_count_exc;
	int me3trigger_count_exc;
	int me4trigger_count_exc;
	int me5trigger_count_exc;
	int jt1trigger_count_exc;
	int jt2trigger_count_exc;
	int jt3trigger_count_exc;
	int mjtrigger_count_exc;
	int mtktrigger_count_exc;
	int muhtrigger_count_exc;
	int mujtrigger_count_exc;
	int isht22_count_exc;
	int sht25_count_exc;
	int ish30_count_exc;
	int sh35_count_exc;
	int l70_count_exc;
	int t15sh20_count_exc;
	int t13sht15_count_exc;
	int t13_isht15_count_exc;
	int lh2ish24_count_exc;
	int lh2sh27_count_exc;
	int lh2l70_count_exc;
	int t14lh2sh17_count_exc;
	int _2l15sh15_l20_count_exc;
	int _2sh10_sh15_count_exc;
	int _2_t10l10_l15_count_exc;
	int _2l6_l8_t5sh6_count_exc;
	int _2l20_l25_count_exc;
	int _2t5sh5_count_exc;
	int _1l1mm2_count_exc;
	int _2lm0mm0tlm3_count_exc;
	int tk10_2lm3_count_exc;
	int itk10_ilm6_count_exc;
	int tk8_tlm8_count_exc;
	int _2lm6_count_exc;
	int lm6_tk12_count_exc;
	int _2tk3tk5tlm3_count_exc;
	int ish7_trk5_count_exc;
	int ish7_mm5_count_exc;
	int lel15_trk5_count_exc;
	int lel15_mm5_count_exc;	
	int sh12_trk5_count_exc;
	int sh12_mm5_count_exc;
	int rd5_count_exc;
	int aco_mht_lm0_count_exc;
	int aco_mht_er2_count_exc;
	int aco_mht_bdv_count_exc;
	int mhtaco_count_exc;	
	int met_count_exc;
	int mht40_ht_count_exc;
};

#endif
