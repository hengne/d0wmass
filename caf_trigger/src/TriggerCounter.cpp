#include <iostream>
#include <iomanip>

#include "cafe/Processor.hpp"
#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "tmb_tree/TMBTrigger.hpp"

#include "caf_trigger/TriggerCounter.hpp"

using namespace std;

// Constructor, destructor: 
TriggerCounter::TriggerCounter(const char *name) : cafe::Processor(name)
{
	cafe::Config config(name);
	_basicname = std::string(name);
}

TriggerCounter::~TriggerCounter()
{

}

void TriggerCounter::begin()
{
  
        events = 0;
        tgvtrigger_count = 0;
        ntgvtrigger_count = 0;
	e1trigger_count = 0;
	e2trigger_count = 0;
	te1trigger_count = 0;
	te2trigger_count = 0;
	te3trigger_count = 0;
	te4trigger_count = 0;
	te5trigger_count = 0;
	de1trigger_count = 0;
	de2trigger_count = 0;
	de3trigger_count = 0;
	de4trigger_count = 0;
	de5trigger_count = 0;
	de6trigger_count = 0;
	de7trigger_count = 0;
	de8trigger_count = 0;
	dmu1trigger_count = 0;
	dmu2trigger_count = 0;
	dmu3trigger_count = 0;
	dmu4trigger_count = 0;
	dmu5trigger_count = 0;
	me1trigger_count = 0;
	me2trigger_count = 0;
	me3trigger_count = 0;
	me4trigger_count = 0;
	me5trigger_count = 0;
	jt1trigger_count = 0;
	jt2trigger_count = 0;
	jt3trigger_count = 0;
	mjtrigger_count = 0;
	muhtrigger_count = 0;
	mujtrigger_count = 0;
	mtktrigger_count = 0;
	isht22_count = 0;
	sht25_count = 0;
	ish30_count = 0;
	sh35_count = 0;
	l70_count = 0;
	t15sh20_count = 0;
	t13sht15_count = 0;
	t13_isht15_count = 0;
	lh2ish24_count = 0;
	lh2sh27_count = 0;
	lh2l70_count = 0;
	t14lh2sh17_count = 0;
	_2l15sh15_l20_count = 0;
	_2sh10_sh15_count = 0;
	_2_t10l10_l15_count = 0;
	_2l6_l8_t5sh6_count = 0;
	_2l20_l25_count = 0;
	_2t5sh5_count = 0;
	_1l1mm2_count = 0;
	_2lm0mm0tlm3_count = 0;
	tk10_2lm3_count = 0;
	itk10_ilm6_count = 0;
	tk8_tlm8_count = 0;
	_2lm6_count = 0;
	lm6_tk12_count = 0;
	_2tk3tk5tlm3_count = 0;
	ish7_trk5_count = 0;
	ish7_mm5_count = 0;
	lel15_trk5_count = 0;
	lel15_mm5_count = 0;	
	sh12_trk5_count = 0;
	sh12_mm5_count = 0;
	rd5_count = 0;
	aco_mht_lm0_count = 0;
	aco_mht_er2_count = 0;
	aco_mht_bdv_count = 0;
	mhtaco_count = 0;	
	met_count = 0;
	mht40_ht_count = 0;
	
	e1trigger_count_exc = 0;
	e2trigger_count_exc = 0;
	te1trigger_count_exc = 0;
	te2trigger_count_exc = 0;
	te3trigger_count_exc = 0;
	te4trigger_count_exc = 0;
	te5trigger_count_exc = 0;
	de1trigger_count_exc = 0;
	de2trigger_count_exc = 0;
	de3trigger_count_exc = 0;
	de4trigger_count_exc = 0;
	de5trigger_count_exc = 0;
	de6trigger_count_exc = 0;
	de7trigger_count_exc = 0;
	de8trigger_count_exc = 0;
	dmu1trigger_count_exc = 0;
	dmu2trigger_count_exc = 0;
	dmu3trigger_count_exc = 0;
	dmu4trigger_count_exc = 0;
	dmu5trigger_count_exc = 0;
	me1trigger_count_exc = 0;
	me2trigger_count_exc = 0;
	me3trigger_count_exc = 0;
	me4trigger_count_exc = 0;
	me5trigger_count_exc = 0;
	jt1trigger_count_exc = 0;
	jt2trigger_count_exc = 0;
	jt3trigger_count_exc = 0;
	mjtrigger_count_exc = 0;
	mujtrigger_count_exc = 0;
	muhtrigger_count_exc = 0;
	mtktrigger_count_exc = 0;
	isht22_count_exc = 0;
	sht25_count_exc = 0;
	ish30_count_exc = 0;
	sh35_count_exc = 0;
	l70_count_exc = 0;
	t15sh20_count_exc = 0;
	t13sht15_count_exc = 0;
	t13_isht15_count_exc = 0;
	lh2ish24_count_exc = 0;
	lh2sh27_count_exc = 0;
	lh2l70_count_exc = 0;
	t14lh2sh17_count_exc = 0;
	_2l15sh15_l20_count_exc = 0;
	_2sh10_sh15_count_exc = 0;
	_2_t10l10_l15_count_exc = 0;
	_2l6_l8_t5sh6_count_exc = 0;
	_2l20_l25_count_exc = 0;
	_2t5sh5_count_exc = 0;
	_1l1mm2_count_exc = 0;
	_2lm0mm0tlm3_count_exc = 0;
	tk10_2lm3_count_exc = 0;
	itk10_ilm6_count_exc = 0;
	tk8_tlm8_count_exc = 0;
	_2lm6_count_exc = 0;
	lm6_tk12_count_exc = 0;
	_2tk3tk5tlm3_count_exc = 0;
	ish7_trk5_count_exc = 0;
	ish7_mm5_count_exc = 0;
	lel15_trk5_count_exc = 0;
	lel15_mm5_count_exc = 0;	
	sh12_trk5_count_exc = 0;
	sh12_mm5_count_exc = 0;
	rd5_count_exc = 0;
	aco_mht_lm0_count_exc = 0;
	aco_mht_er2_count_exc = 0;
	aco_mht_bdv_count_exc = 0;
	mhtaco_count_exc = 0;	
	met_count_exc = 0;
	mht40_ht_count_exc = 0;
}

bool TriggerCounter::processEvent(cafe::Event& event)
{
  bool passed = true;

  Collection<TMBTrigger> triggers = event.getTriggers();
        bool tgvtrigger = false;
        bool ntgvtrigger = false;
	bool e1trigger = false;
	bool e2trigger = false;
	bool te1trigger = false;
	bool te2trigger = false;
	bool te3trigger = false;
	bool te4trigger = false;
	bool te5trigger = false;
	bool de1trigger = false;
	bool de2trigger = false;
	bool de3trigger = false;
	bool de4trigger = false;
	bool de5trigger = false;
	bool de6trigger = false;
	bool de7trigger = false;
	bool de8trigger = false;
	bool dmu1trigger = false;
	bool dmu2trigger = false;
	bool dmu3trigger = false;
	bool dmu4trigger = false;
	bool dmu5trigger = false;
	bool me1trigger = false;
	bool me2trigger = false;
	bool me3trigger = false;
	bool me4trigger = false;
	bool me5trigger = false;
	bool jt1trigger = false;
	bool jt2trigger = false;
	bool jt3trigger = false;
	bool mjtrigger = false;
	bool mujtrigger = false;
	bool muhtrigger = false;
	bool mtktrigger = false;
	bool isht22 = false;
	bool sht25 = false;
	bool ish30 = false;
	bool sh35 = false;
	bool l70 = false;
	bool t15sh20 = false;
	bool t13sht15 = false;
	bool t13_isht15 = false;
	bool lh2ish24 = false;
	bool lh2sh27 = false;
	bool lh2l70 = false;
	bool t14lh2sh17 = false;
	bool _2l15sh15_l20 = false;
	bool _2sh10_sh15 = false;
	bool _2_t10l10_l15 = false;
	bool _2l6_l8_t5sh6 = false;
	bool _2l20_l25 = false;
	bool _2t5sh5 = false;
	bool _1l1mm2 = false;
	bool _2lm0mm0tlm3 = false;
	bool tk10_2lm3 = false;
	bool itk10_ilm6 = false;
	bool tk8_tlm8 = false;
	bool _2lm6 = false;
	bool lm6_tk12 = false;
	bool _2tk3tk5tlm3 = false;
	bool ish7_trk5 = false;
	bool ish7_mm5 = false;
	bool lel15_trk5 = false;
	bool lel15_mm5 = false;	
	bool sh12_trk5 = false;
	bool sh12_mm5 = false;
	bool rd5 = false;
	bool aco_mht_lm0 = false;
	bool aco_mht_er2 = false;
	bool aco_mht_bdv = false;
	bool mhtaco = false;	
	bool met = false;
	bool mht40_ht = false;
	int singleele1 = 0, singleele2 = 0, singleele3 = 0, singleele4 = 0, singleele5 = 0, singleele6 = 0, singleele7 = 0;
	int diele1 = 0, diele2 = 0, diele3 = 0, diele4 = 0, diele5 = 0, diele6 = 0, diele7 = 0, diele8 = 0;
	int dimu1 = 0, dimu2 = 0, dimu3 = 0, dimu4 = 0, dimu5 = 0;
	int muj = 0, muh = 0, mtk = 0;
	int emu1 = 0, emu2 = 0, emu3 = 0, emu4 = 0, emu5 = 0;
	int aco1 = 0, aco2 = 0, aco3 = 0, aco4 = 0;
	int singleele1_filt = 0, singleele2_filt = 0, singleele3_filt = 0, singleele4_filt = 0, singleele5_filt = 0, singleele6_filt = 0;
	int singleele7_filt = 0, singleele8_filt = 0, singleele9_filt = 0, singleele10_filt = 0, singleele11_filt = 0, singleele12_filt = 0;
	int diele1_filt = 0, diele2_filt = 0, diele3_filt = 0, diele4_filt = 0, diele5_filt = 0, diele6_filt = 0;
	int dimu1_filt = 0, dimu2_filt = 0, dimu3_filt = 0, dimu4_filt = 0, dimu5_filt = 0, dimu6_filt = 0, dimu7_filt = 0, dimu8_filt = 0;
	int emu1_filt = 0, emu2_filt = 0, emu3_filt = 0, emu4_filt = 0, emu5_filt = 0, emu6_filt = 0, emu7_filt = 0;
	int aco1_filt = 0, aco2_filt = 0, aco3_filt = 0, aco4_filt = 0, aco5_filt = 0, aco6_filt = 0;
        int tgv = 0, ntgv = 0;
       
  for(Collection<TMBTrigger>::const_iterator it = triggers.begin();
      it != triggers.end();
      ++it) {
    counter[(*it).getTrgName()]++;


		TString triggername((*it).getTrgName());
		if(triggername.Contains("E1_") && !triggername.Contains("TE1_") && 
			 !triggername.Contains("DE1_") && !triggername.Contains("ME1_")) { e1trigger = true; singleele1++;}
		if(triggername.Contains("E2_") && !triggername.Contains("TE2_") && 
			 !triggername.Contains("DE2_") && !triggername.Contains("ME2_")) { e2trigger = true; singleele2++;}
		if(triggername.Contains("NOLUM")) { tgvtrigger = true; tgv++;}
		if(!triggername.Contains("NOLUM")) { ntgvtrigger = true; ntgv++;}
		if(triggername.Contains("TE1_")) { te1trigger = true; singleele3++;}
		if(triggername.Contains("TE2_")) { te2trigger = true; singleele4++;}
		if(triggername.Contains("TE3_")) { te3trigger = true; singleele5++;}
		if(triggername.Contains("TE4_")) { te4trigger = true; singleele6++;}
		if(triggername.Contains("TE5_")) { te5trigger = true; singleele7++;}
		if(triggername.Contains("DE1_")) { de1trigger = true; diele1++;}
		if(triggername.Contains("DE2_")) { de2trigger = true; diele2++;}
		if(triggername.Contains("DE3_")) { de3trigger = true; diele3++;}
		if(triggername.Contains("DE4_")) { de4trigger = true; diele4++;}
		if(triggername.Contains("DE5_")) { de5trigger = true; diele5++;}
		if(triggername.Contains("DE6_")) { de6trigger = true; diele6++;}
		if(triggername.Contains("DE7_")) { de7trigger = true; diele7++;}
		if(triggername.Contains("DE8_")) { de8trigger = true; diele8++;}
		if(triggername.Contains("DMU1_")) { dmu1trigger = true; dimu1++;}
		if(triggername.Contains("DMU2_")) { dmu2trigger = true; dimu2++;}
		if(triggername.Contains("DMU3_")) { dmu3trigger = true; dimu3++;}
		if(triggername.Contains("DMU4_")) { dmu4trigger = true; dimu4++;}
		if(triggername.Contains("DMU5_")) { dmu5trigger = true; dimu5++;}
		if(triggername.Contains("ME1_")) { me1trigger = true; emu1++;}
		if(triggername.Contains("ME2_")) { me2trigger = true; emu2++;}
		if(triggername.Contains("ME3_")) { me3trigger = true; emu3++;}
		if(triggername.Contains("ME4_")) { me4trigger = true; emu4++;}
		if(triggername.Contains("ME5_")) { me5trigger = true; emu5++;}
		if(triggername.Contains("JT1_")) { jt1trigger = true; aco1++;}
		if(triggername.Contains("JT2_")) { jt2trigger = true; aco2++;}
		if(triggername.Contains("JT3_")) { jt3trigger = true; aco3++;}
		if(triggername.Contains("MJ_")) { mjtrigger = true; aco4++;}
		if(triggername.Contains("MTK")) { mtktrigger = true; mtk++;}
		if(triggername.Contains("MUHI")) { muhtrigger = true; muh++;}
		if(triggername.Contains("MUJ")) { mujtrigger = true; muj++;}
		if(triggername.Contains("_ISHT22")) { isht22 = true; singleele1_filt++;}
		if(triggername.Contains("_SHT25")) { sht25 = true; singleele2_filt++;}
		if(triggername.Contains("_ISH30")) { ish30 = true; singleele3_filt++;}
		if(triggername.Contains("_SH35")) { sh35 = true; singleele4_filt++;}
		if(triggername.Contains("_L70")) { l70 = true; singleele5_filt++;}
		if(triggername.Contains("_T15SH20")) { t15sh20 = true; singleele6_filt++;}
		if(triggername.Contains("_T13SHT15")) { t13sht15 = true; singleele7_filt++;}
		if(triggername.Contains("_T13_ISHT15")) { t13_isht15 = true; singleele8_filt++;}
		if(triggername.Contains("_LH2ISH24")) { lh2ish24 = true; singleele9_filt++;}
		if(triggername.Contains("_LH2SH27")) { lh2sh27 = true; singleele10_filt++;}
		if(triggername.Contains("_LH2L70")) { lh2l70 = true; singleele11_filt++;}
		if(triggername.Contains("_T14LH2SH17")) { t14lh2sh17 = true; singleele12_filt++;}
		if(triggername.Contains("_2L15SH15_L20")) { _2l15sh15_l20 = true; diele1_filt++;}
		if(triggername.Contains("_2SH10_SH15")) { _2sh10_sh15 = true; diele2_filt++;}
		if(triggername.Contains("_2_T10L10_L15")) { _2_t10l10_l15 = true; diele3_filt++;}
		if(triggername.Contains("_2L6_L8_T5SH6")) { _2l6_l8_t5sh6 = true; diele4_filt++;}
		if(triggername.Contains("_2L20_L25")) { _2l20_l25 = true; diele5_filt++;}
		if(triggername.Contains("_2T5SH5")) { _2t5sh5 = true; diele6_filt++;}
		if(triggername.Contains("_1L1MM2")) { _1l1mm2 = true; dimu1_filt++;}
		if(triggername.Contains("_2LM0MM0TLM3")) { _2lm0mm0tlm3 = true; dimu2_filt++;}
		if(triggername.Contains("_TK10_2LM3")) { tk10_2lm3 = true; dimu3_filt++;}
		if(triggername.Contains("_ITK10_ILM6")) { itk10_ilm6 = true; dimu4_filt++;}
		if(triggername.Contains("_TK8_TLM8")) { tk8_tlm8 = true; dimu5_filt++;}
		if(triggername.Contains("_2LM6")) { _2lm6 = true; dimu6_filt++;}
		if(triggername.Contains("_LM6_TK12")) { lm6_tk12 = true; dimu7_filt++;}
		if(triggername.Contains("_2TK3TK5TLM3")) { _2tk3tk5tlm3 = true; dimu8_filt++;}
		if(triggername.Contains("_ISH7_TRK5")) { ish7_trk5 = true; emu1_filt++;}
		if(triggername.Contains("_ISH7_MM5")) { ish7_mm5 = true; emu2_filt++;}
		if(triggername.Contains("_LEL15_TRK5")) { lel15_trk5 = true; emu3_filt++;}
		if(triggername.Contains("_LEL15_MM5")) { lel15_mm5 = true; emu4_filt++;}	
		if(triggername.Contains("_SH12_TRK5")) { sh12_trk5 = true; emu5_filt++;}
		if(triggername.Contains("_SH12_MM5")) { sh12_mm5 = true; emu6_filt++;}
		if(triggername.Contains("_RD5")) { rd5 = true; emu7_filt++;}
		if(triggername.Contains("_ACO_MHT_LM0")) { aco_mht_lm0 = true; aco1_filt++;}
		if(triggername.Contains("_ACO_MHT_ER2")) { aco_mht_er2 = true; aco2_filt++;}
		if(triggername.Contains("_ACO_MHT_BDV")) { aco_mht_bdv = true; aco3_filt++;}
		if(triggername.Contains("_MHTACO")) { mhtaco = true; aco4_filt++;}	
		if(triggername.Contains("_MET")) { met = true; aco5_filt++;}
		if(triggername.Contains("_MHT40_HT")) { mht40_ht = true; aco6_filt++;}
  }
  if (triggers.size() == 1) {
    //out() << triggers[0].getTrgName() << std::endl;
    exclusive[triggers[0].getTrgName()]++;
  }
	int singleele = 1, diele = 1, dimu = 1, emu = 1, aco = 1;
	if(!singleele1 && !singleele2 && !singleele3 && !singleele4 && !singleele5 && !singleele6 && !singleele7) singleele = 0;
	if(!diele1 && !diele2 && !diele3 && !diele4 && !diele5 && !diele6 && !diele7 && !diele8) diele = 0;
	if(!dimu1 && !dimu2 && !dimu3 && !dimu4 && !dimu5) dimu = 0;
	if(!emu1 && !emu2 && !emu3 && !emu4 && !emu5) emu = 0;
	if(!aco1 && !aco2 && !aco3 && !aco4) aco = 0;
	
	int singleele_filt = 1, diele_filt = 1, dimu_filt = 1, emu_filt = 1, aco_filt = 1;
	if(!singleele1_filt && !singleele2_filt && !singleele3_filt && !singleele4_filt && !singleele5_filt && !singleele6_filt &&
		 !singleele7_filt && !singleele8_filt && !singleele9_filt && !singleele10_filt && !singleele11_filt && !singleele12_filt) singleele_filt = 0;
	if(!diele1_filt && !diele2_filt && !diele3_filt && !diele4_filt && !diele5_filt && !diele6_filt) diele_filt = 0;
	if(!dimu1_filt && !dimu2_filt && !dimu3_filt && !dimu4_filt && !dimu5_filt && !dimu6_filt && !dimu7_filt && !dimu8_filt) dimu_filt = 0;
	if(!emu1_filt && !emu2_filt && !emu3_filt && !emu4_filt && !emu5_filt && !emu6_filt && !emu7_filt) emu_filt = 0;
	if(!aco1_filt && !aco2_filt && !aco3_filt && !aco4_filt && !aco5_filt && !aco6_filt) aco_filt = 0;

        if (tgvtrigger) {tgvtrigger_count++;}
        if (ntgvtrigger) {ntgvtrigger_count++;}
        
	if(e1trigger) {e1trigger_count++;if(singleele1 >= 1 && singleele7 == 0 && 
																			singleele2 == 0 && singleele3 == 0 && singleele4 == 0 && singleele5 == 0 && singleele6 == 0 &&  
																			diele == 0 && emu == 0) e1trigger_count_exc++;}
	if(e2trigger) {e2trigger_count++;if(singleele2 >= 1 && singleele7 == 0 && 
																			singleele1 == 0 && singleele3 == 0 && singleele4 == 0 && singleele5 == 0 && singleele6 == 0 &&
																			diele == 0 && emu == 0) e2trigger_count_exc++;}
	if(te1trigger) {te1trigger_count++;if(singleele3 >= 1 && singleele7 == 0 && 
																				singleele2 == 0 && singleele1 == 0 && singleele4 == 0 && singleele5 == 0 && singleele6 == 0 &&
																				diele == 0 && emu == 0) te1trigger_count_exc++;}
	if(te2trigger) {te2trigger_count++;if(singleele4 >= 1 && singleele7 == 0 && 
																				singleele2 == 0 && singleele3 == 0 && singleele1 == 0 && singleele5 == 0 && singleele6 == 0 &&
																				diele == 0 && emu == 0) te2trigger_count_exc++;}
	if(te3trigger) {te3trigger_count++;if(singleele5 >= 1 && singleele7 == 0 && 
																				singleele2 == 0 && singleele3 == 0 && singleele4 == 0 && singleele1 == 0 && singleele6 == 0 &&
																				diele == 0 && emu == 0) te3trigger_count_exc++;}
	if(te4trigger) {te4trigger_count++;if(singleele6 >= 1 && singleele7 == 0 && 
																				singleele2 == 0 && singleele3 == 0 && singleele4 == 0 && singleele5 == 0 && singleele1 == 0 &&
																				diele == 0 && emu == 0) te4trigger_count_exc++;}
	if(te5trigger) {te5trigger_count++;if(singleele7 >= 1 && singleele1 == 0 && 
																				singleele2 == 0 && singleele3 == 0 && singleele4 == 0 && singleele5 == 0 && singleele6 == 0 &&
																				diele == 0 && emu == 0) te5trigger_count_exc++;}
	if(de1trigger) {de1trigger_count++;if(singleele == 0 && diele1 >= 1 && emu == 0 &&
																				diele2 == 0 && diele3 ==0 && diele4 == 0 && diele5 ==0 && 
																				diele6 == 0 && diele7 == 0 && diele8 ==0) de1trigger_count_exc++;}
	if(de2trigger) {de2trigger_count++;if(singleele == 0 && diele2 >= 1 && emu == 0 &&
																				diele1 == 0 && diele3 ==0 && diele4 == 0 && diele5 ==0 && 
																				diele6 == 0 && diele7 == 0 && diele8 ==0) de2trigger_count_exc++;}
	if(de3trigger) {de3trigger_count++;if(singleele == 0 && diele3 >= 1 && emu == 0 &&
																				diele2 == 0 && diele1 ==0 && diele4 == 0 && diele5 ==0 && 
																				diele6 == 0 && diele7 == 0 && diele8 ==0) de3trigger_count_exc++;}
	if(de4trigger) {de4trigger_count++;if(singleele == 0 && diele4 >= 1 && emu == 0 &&
																				diele2 == 0 && diele3 ==0 && diele1 == 0 && diele5 ==0 && 
																				diele6 == 0 && diele7 == 0 && diele8 ==0) de4trigger_count_exc++;}
	if(de5trigger) {de5trigger_count++;if(singleele == 0 && diele5 >= 1 && emu == 0 && 
																				diele2 == 0 && diele3 ==0 && diele4 == 0 && diele1 ==0 && 
																				diele6 == 0 && diele7 == 0 && diele8 ==0) de5trigger_count_exc++;}
	if(de6trigger) {de6trigger_count++;if(singleele == 0 && diele6 >= 1 && emu == 0 &&
																				diele2 == 0 && diele3 ==0 && diele4 == 0 && diele5 ==0 && 
																				diele1 == 0 && diele7 == 0 && diele8 ==0) de6trigger_count_exc++;}
	if(de7trigger) {de7trigger_count++;if(singleele == 0 && diele7 >= 1 && emu == 0 &&
																				diele2 == 0 && diele3 ==0 && diele4 == 0 && diele5 ==0 && 
																				diele6 == 0 && diele1 == 0 && diele8 ==0) de7trigger_count_exc++;}
	if(de8trigger) {de8trigger_count++;if(singleele == 0 && diele8 >= 1 && emu == 0 &&
																				diele2 == 0 && diele3 ==0 && diele4 == 0 && diele5 ==0 && 
																				diele6 == 0 && diele7 == 0 && diele1 ==0) de8trigger_count_exc++;}
	if(dmu1trigger) {dmu1trigger_count++;if(dimu1 >= 1 && emu == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																					dimu2 == 0 && dimu3 == 0 && dimu4 == 0 && dimu5 == 0) dmu1trigger_count_exc++;}
	if(dmu2trigger) {dmu2trigger_count++;if(dimu2 >= 1 && emu == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																					dimu1 == 0 && dimu3 == 0 && dimu4 == 0 && dimu5 == 0) dmu2trigger_count_exc++;}
	if(dmu3trigger) {dmu3trigger_count++;if(dimu3 >= 1 && emu == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																					dimu2 == 0 && dimu1 == 0 && dimu4 == 0 && dimu5 == 0) dmu3trigger_count_exc++;}
	if(dmu4trigger) {dmu4trigger_count++;if(dimu4 >= 1 && emu == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																					dimu2 == 0 && dimu3 == 0 && dimu1 == 0 && dimu5 == 0) dmu4trigger_count_exc++;}
	if(dmu5trigger) {dmu5trigger_count++;if(dimu5 >= 1 && emu == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																					dimu2 == 0 && dimu3 == 0 && dimu4 == 0 && dimu1 == 0) dmu5trigger_count_exc++;}
	if(me1trigger) {me1trigger_count++;if(emu1 >= 1 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																				emu2 == 0 && emu3 == 0 && emu4 == 0 && emu5 == 0) me1trigger_count_exc++;}
	if(me2trigger) {me2trigger_count++;if(emu2 >= 1 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																				emu1 == 0 && emu3 == 0 && emu4 == 0 && emu5 == 0) me2trigger_count_exc++;}
	if(me3trigger) {me3trigger_count++;if(emu3 >= 1 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																				emu2 == 0 && emu1 == 0 && emu4 == 0 && emu5 == 0) me3trigger_count_exc++;}
	if(me4trigger) {me4trigger_count++;if(emu4 >= 1 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																				emu2 == 0 && emu3 == 0 && emu1 == 0 && emu5 == 0) me4trigger_count_exc++;}
	if(me5trigger) {me5trigger_count++;if(emu5 >= 1 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 &&
																				emu2 == 0 && emu3 == 0 && emu4 == 0 && emu1 == 0) me5trigger_count_exc++;}
	if(jt1trigger) {jt1trigger_count++;if(aco1 >= 1 && aco2 == 0 && aco3 == 0 && aco4 == 0 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 && emu == 0) jt1trigger_count_exc++;}
	if(jt2trigger) {jt2trigger_count++;if(aco2 >= 1 && aco1 == 0 && aco3 == 0 && aco4 == 0 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 && emu == 0 ) jt2trigger_count_exc++;}
	if(jt3trigger) {jt3trigger_count++;if(aco3 >= 1 && aco2 == 0 && aco1 == 0 && aco4 == 0 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 && emu == 0) jt3trigger_count_exc++;}
	if(mjtrigger)  {mjtrigger_count++ ;if(aco4 >= 1 && aco2 == 0 && aco3 == 0 && aco1 == 0 && singleele == 0 && mtk == 0 && muh == 0 && muj == 0 && emu == 0) mjtrigger_count_exc++;}

        if(mtktrigger) {mtktrigger_count++;if(mtk >= 1 && aco == 0 && singleele == 0 && muh == 0 && muj == 0 && dimu == 0 && emu == 0) mtktrigger_count_exc++;}
        if(muhtrigger) {muhtrigger_count++;if(muh >= 1 && aco == 0 && singleele == 0 && mtk == 0 && muj == 0 && dimu == 0 && emu == 0) muhtrigger_count_exc++;}
        if(mujtrigger) {mujtrigger_count++;if(muj >= 1 && aco == 0 && singleele == 0 && mtk == 0 && muh == 0 && dimu == 0 && emu == 0) mujtrigger_count_exc++;}
        
	if(isht22) {isht22_count++;if(singleele1_filt >= 1 && 
																singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
																singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
																diele_filt == 0 && emu_filt == 0) isht22_count_exc++;}
	if(sht25) {sht25_count++;if(singleele2_filt >= 1 && 
															singleele1_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
															singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
															singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
															diele_filt == 0 && emu_filt == 0) sht25_count_exc++;}
	if(ish30) {ish30_count++;if(singleele3_filt >= 1 && 
															singleele2_filt == 0 && singleele1_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
															singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
															singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
															diele_filt == 0 && emu_filt == 0) ish30_count_exc++;}
	if(sh35) {sh35_count++;if(singleele4_filt >= 1 && 
														singleele2_filt == 0 && singleele3_filt == 0 && singleele1_filt == 0 && singleele5_filt == 0 && 
														singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
														singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
														diele_filt == 0 && emu_filt == 0) sh35_count_exc++;}
	if(l70) {l70_count++;if(singleele5_filt >= 1 && 
													singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele1_filt == 0 && 
													singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
													singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
													diele_filt == 0 && emu_filt == 0) l70_count_exc++;}
	if(t15sh20) {t15sh20_count++;if(singleele6_filt >= 1 && 
																	singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																	singleele1_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
																	singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
																	diele_filt == 0 && emu_filt == 0) t15sh20_count_exc++;}
	if(t13sht15) {t13sht15_count++;if(singleele7_filt >= 1 && 
																		singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																		singleele6_filt == 0 && singleele1_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
																		singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
																		diele_filt == 0 && emu_filt == 0) t13sht15_count_exc++;}
	if(t13_isht15) {t13_isht15_count++;if(singleele8_filt >= 1 && 
																				singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																				singleele6_filt == 0 && singleele7_filt == 0 && singleele1_filt == 0 && singleele9_filt == 0 && 
																				singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
																				diele_filt == 0 && emu_filt == 0) t13_isht15_count_exc++;}
	if(lh2ish24) {lh2ish24_count++;if(singleele9_filt >= 1 && 
																		singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																		singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele1_filt == 0 && 
																		singleele10_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
																		diele_filt == 0 && emu_filt == 0) lh2ish24_count_exc++;}
	if(lh2sh27) {lh2sh27_count++;if(singleele10_filt >= 1 && 
																	singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																	singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
																	singleele1_filt == 0 && singleele11_filt == 0 && singleele12_filt == 0 && 
																	diele_filt == 0 && emu_filt == 0) lh2sh27_count_exc++;}
	if(lh2l70) {lh2l70_count++;if(singleele11_filt >= 1 && 
																singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
																singleele10_filt == 0 && singleele1_filt == 0 && singleele12_filt == 0 && 
																diele_filt == 0 && emu_filt == 0) lh2l70_count_exc++;}
	if(t14lh2sh17) {t14lh2sh17_count++;if(singleele12_filt >= 1 && 
																				singleele2_filt == 0 && singleele3_filt == 0 && singleele4_filt == 0 && singleele5_filt == 0 && 
																				singleele6_filt == 0 && singleele7_filt == 0 && singleele8_filt == 0 && singleele9_filt == 0 && 
																				singleele10_filt == 0 && singleele11_filt == 0 && singleele1_filt == 0 && 
																				diele_filt == 0 && emu_filt == 0) t14lh2sh17_count_exc++;}
	if(_2l15sh15_l20) {_2l15sh15_l20_count++;if(singleele_filt == 0 && diele1_filt == 1 && emu_filt == 0 &&
																							diele2_filt == 0 && diele3_filt == 0 && diele4_filt == 0 &&
																							diele5_filt == 0 && diele6_filt == 0) _2l15sh15_l20_count_exc++;}
	if(_2sh10_sh15) {_2sh10_sh15_count++;if(singleele_filt == 0 && diele2_filt >= 1 && emu_filt == 0 &&
																					diele1_filt == 0 && diele3_filt == 0 && diele4_filt == 0 &&
																					diele5_filt == 0 && diele6_filt == 0) _2sh10_sh15_count_exc++;}
	if(_2_t10l10_l15) {_2_t10l10_l15_count++;if(singleele_filt == 0 && diele3_filt >= 1 && emu_filt == 0 &&
																							diele2_filt == 0 && diele1_filt == 0 && diele4_filt == 0 &&
																							diele5_filt == 0 && diele6_filt == 0) _2_t10l10_l15_count_exc++;}
	if(_2l6_l8_t5sh6) {_2l6_l8_t5sh6_count++;if(singleele_filt == 0 && diele4_filt >= 1 && emu_filt == 0 &&
																							diele2_filt == 0 && diele3_filt == 0 && diele1_filt == 0 &&
																							diele5_filt == 0 && diele6_filt == 0) _2l6_l8_t5sh6_count_exc++;}
	if(_2l20_l25) {_2l20_l25_count++;if(singleele_filt == 0 && diele5_filt >= 1 && emu_filt == 0 &&
																			diele2_filt == 0 && diele3_filt == 0 && diele4_filt == 0 &&
																			diele1_filt == 0 && diele6_filt == 0) _2l20_l25_count_exc++;}
	if(_2t5sh5) {_2t5sh5_count++;if(singleele_filt == 0 && diele6_filt >= 1 && emu_filt == 0 &&
																	diele2_filt == 0 && diele3_filt == 0 && diele4_filt == 0 &&
																	diele5_filt == 0 && diele1_filt == 0) _2t5sh5_count_exc++;}
	if(_1l1mm2) {_1l1mm2_count++;if(dimu1_filt >= 1 && emu_filt == 0 &&
																	dimu2_filt == 0 && dimu3_filt == 0 && dimu4_filt == 0 && 
																	dimu5_filt == 0 && dimu6_filt == 0 && dimu7_filt == 0 && dimu8_filt == 0) _1l1mm2_count_exc++;}
	if(_2lm0mm0tlm3) {_2lm0mm0tlm3_count++;if(dimu2_filt >= 1 && emu_filt == 0 && 
																						dimu1_filt == 0 && dimu3_filt == 0 && dimu4_filt == 0 && 
																						dimu5_filt == 0 && dimu6_filt == 0 && dimu7_filt == 0 && dimu8_filt == 0) _2lm0mm0tlm3_count_exc++;}
	if(tk10_2lm3) {tk10_2lm3_count++;if(dimu3_filt >= 1 && emu_filt == 0 &&
																			dimu1_filt == 0 && dimu2_filt == 0 && dimu4_filt == 0 && 
																			dimu5_filt == 0 && dimu6_filt == 0 && dimu7_filt == 0 && dimu8_filt == 0) tk10_2lm3_count_exc++;}
	if(itk10_ilm6) {itk10_ilm6_count++;if(dimu4_filt >= 1 && emu_filt == 0 &&
																				dimu1_filt == 0 && dimu2_filt == 0 && dimu3_filt == 0 && 
																				dimu5_filt == 0 && dimu6_filt == 0 && dimu7_filt == 0 && dimu8_filt == 0) itk10_ilm6_count_exc++;}
	if(tk8_tlm8) {tk8_tlm8_count++;if(dimu5_filt >= 1 && emu_filt == 0 &&
																		dimu1_filt == 0 && dimu2_filt == 0 && dimu3_filt == 0 && 
																		dimu4_filt == 0 && dimu6_filt == 0 && dimu7_filt == 0 && dimu8_filt == 0) tk8_tlm8_count_exc++;}
	if(_2lm6) {_2lm6_count++;if(dimu6_filt >= 1 && emu_filt == 0 &&
															dimu1_filt == 0 && dimu2_filt == 0 && dimu3_filt == 0 && 
															dimu4_filt == 0 && dimu5_filt == 0 && dimu7_filt == 0 && dimu8_filt == 0) _2lm6_count_exc++;}
	if(lm6_tk12) {lm6_tk12_count++;if(dimu7_filt >= 1 && emu_filt == 0 &&
																		dimu1_filt == 0 && dimu2_filt == 0 && dimu3_filt == 0 && 
																		dimu4_filt == 0 && dimu5_filt == 0 && dimu6_filt == 0 && dimu8_filt == 0) lm6_tk12_count_exc++;}
	if(_2tk3tk5tlm3) {_2tk3tk5tlm3_count++;if(dimu8_filt >= 1 && emu_filt == 0 &&
															dimu1_filt == 0 && dimu2_filt == 0 && dimu3_filt == 0 && 
															dimu4_filt == 0 && dimu5_filt == 0 && dimu6_filt == 0 && dimu7_filt == 0) _2tk3tk5tlm3_count_exc++;}

	if(ish7_trk5) {ish7_trk5_count++;if(dimu_filt == 1 && emu1_filt >= 1 && 
																			emu2_filt == 0 && emu3_filt == 0 && emu4_filt == 0 && 
																			emu5_filt == 0 && emu6_filt == 0 && emu7_filt == 0 && 
																			singleele_filt == 0) ish7_trk5_count_exc++;}
	if(ish7_mm5) {ish7_mm5_count++;if(dimu_filt == 1 && emu2_filt >= 1 && 
																		emu1_filt == 0 && emu3_filt == 0 && emu4_filt == 0 && 
																		emu5_filt == 0 && emu6_filt == 0 && emu7_filt == 0 && 
																		singleele_filt == 0) ish7_mm5_count_exc++;}
	if(lel15_trk5) {lel15_trk5_count++;if(dimu_filt == 1 && emu3_filt >= 1 && 
																				emu2_filt == 0 && emu1_filt == 0 && emu4_filt == 0 && 
																				emu5_filt == 0 && emu6_filt == 0 && emu7_filt == 0 && 
																				singleele_filt == 0) lel15_trk5_count_exc++;}
	if(lel15_mm5) {lel15_mm5_count++;if(dimu_filt == 1 && emu4_filt >= 1 && 
																			emu2_filt == 0 && emu3_filt == 0 && emu1_filt == 0 && 
																			emu5_filt == 0 && emu6_filt == 0 && emu7_filt == 0 && 
																			singleele_filt == 0) lel15_mm5_count_exc++;}	
	if(sh12_trk5) {sh12_trk5_count++;if(dimu_filt == 1 && emu5_filt >= 1 && 
																			emu2_filt == 0 && emu3_filt == 0 && emu4_filt == 0 && 
																			emu1_filt == 0 && emu6_filt == 0 && emu7_filt == 0 && 
																			singleele_filt == 0) sh12_trk5_count_exc++;}
	if(sh12_mm5) {sh12_mm5_count++;if(dimu_filt == 1 && emu6_filt >= 1 && 
																		emu2_filt == 0 && emu3_filt == 0 && emu4_filt == 0 && 
																		emu5_filt == 0 && emu1_filt == 0 && emu7_filt == 0 && 
																		singleele_filt == 0) sh12_mm5_count_exc++;}
	if(rd5) {rd5_count++;if(dimu_filt == 1 && emu7_filt >= 1 && 
													emu2_filt == 0 && emu3_filt == 0 && emu4_filt == 0 && 
													emu5_filt == 0 && emu6_filt == 0 && emu1_filt == 0 && 
													singleele_filt == 0) rd5_count_exc++;}
	if(aco_mht_lm0) {aco_mht_lm0_count++;if(aco1_filt >= 1 && aco2_filt == 0 && aco3_filt == 0 &&
																				aco4_filt == 0 && aco5_filt == 0 && aco6_filt == 0) aco_mht_lm0_count_exc++;}
	if(aco_mht_er2) {aco_mht_er2_count++;if(aco2_filt >= 1 && aco1_filt == 0 && aco3_filt == 0 &&
																					aco4_filt == 0 && aco5_filt == 0 && aco6_filt == 0) aco_mht_er2_count_exc++;}
	if(aco_mht_bdv) {aco_mht_bdv_count++;if(aco3_filt >= 1 && aco2_filt == 0 && aco1_filt == 0 &&
																					aco4_filt == 0 && aco5_filt == 0 && aco6_filt == 0) aco_mht_bdv_count_exc++;}
	if(mhtaco) {mhtaco_count++;if(aco4_filt >= 1 && aco2_filt == 0 && aco3_filt == 0 &&
																aco1_filt == 0 && aco5_filt == 0 && aco6_filt == 0) mhtaco_count_exc++;}	
	if(met) {met_count++;if(aco5_filt >= 1 && aco2_filt == 0 && aco3_filt == 0 &&
													aco4_filt == 0 && aco1_filt == 0 && aco6_filt == 0) met_count_exc++;}
	if(mht40_ht) {mht40_ht_count++;if(aco6_filt >= 1 && aco2_filt == 0 && aco3_filt == 0 &&
																		aco4_filt == 0 && aco5_filt == 0 && aco1_filt == 0) mht40_ht_count_exc++;}

	
  events++;

  return passed;
}	


void TriggerCounter::finish() 
{

	out() << "+-------------------------------------------------------------+" << endl;
	out() << " Event summary for instance " << _basicname << endl;
	out() << std::endl << "Trigger counts using " << events << " events:" << std::endl;
        out() << left << setw(20) << "Name" << setw(15) << "Inclusive (%)" << setw(15) << "Exclusive (%)" << std::endl; 
        
        for (counter_map::const_iterator it = counter.begin(); it != counter.end(); it++) {
             out() << left << setw(25) << it->first << setw(15) << fixed << setprecision(3) << (it->second)/(Float_t)events*100;
             out() << setw(15) << fixed << setprecision(3) << exclusive[it->first]/(Float_t)events*100 << std::endl;    
	}
	out() << "+-------------------------------------------------------------+" << endl;
	out() << left << setw(25) << "TGV TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)tgvtrigger_count/(Float_t)events*100;
  out() << std::endl;    		
	out() << left << setw(25) << "NON-TGV TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)ntgvtrigger_count/(Float_t)events*100;
  out() << std::endl;    		
	out() << left << setw(25) << "E1 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)e1trigger_count/(Float_t)events*100;	
	out() << setw(15) << fixed << setprecision(3) << (Float_t)e1trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "E2 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)e2trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)e2trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "TE1 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)te1trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)te1trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "TE2 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)te2trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)te2trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "TE3 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)te3trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)te3trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "TE4 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)te4trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)te4trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "TE5 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)te5trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)te5trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DE1 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de1trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de1trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "DE2 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de2trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de2trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DE3 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de3trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de3trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "DE4 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de4trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de4trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DE5 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de5trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de5trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DE6 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de6trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de6trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "DE7 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de7trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de7trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DE8 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)de8trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)de8trigger_count_exc/(Float_t)events*100;
  out() << std::endl;
	out() << left << setw(25) << "DMU1 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)dmu1trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)dmu1trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "DMU2 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)dmu2trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)dmu2trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DMU3 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)dmu3trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)dmu3trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "DMU4 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)dmu4trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)dmu4trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "DMU5 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)dmu5trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)dmu5trigger_count_exc/(Float_t)events*100;
  out() << std::endl; 
	out() << left << setw(25) << "ME1 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)me1trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)me1trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "ME2 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)me2trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)me2trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ME3 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)me3trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)me3trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "ME4 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)me4trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)me4trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ME5 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)me5trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)me5trigger_count_exc/(Float_t)events*100;
  out() << std::endl; 
	out() << left << setw(25) << "JT1 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)jt1trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)jt1trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "JT2 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)jt2trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)jt2trigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "JT3 TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)jt3trigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)jt3trigger_count_exc/(Float_t)events*100;
  out() << std::endl;    
	out() << left << setw(25) << "MJ TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)mjtrigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)mjtrigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "MTK TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)mtktrigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)mtktrigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "MUHI TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)muhtrigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)muhtrigger_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "MUJ TRIGGER" << setw(15) << fixed << setprecision(3) << (Float_t)mujtrigger_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)mujtrigger_count_exc/(Float_t)events*100;
  out() << std::endl;  


	out() << "+============================ FILTER =========================+" << endl;
	out() << "---> Single electron filter" << endl;
	out() << left << setw(25) << "ISHT22 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)isht22_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)isht22_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "SHT25 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)sht25_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)sht25_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ISH30 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)ish30_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)ish30_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "SH35 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)sh35_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)sh35_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "L70 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)l70_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)l70_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "T13SHT15 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)t13sht15_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)t13sht15_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "T15SH20 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)t15sh20_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)t15sh20_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "T13_ISHT15 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)t13_isht15_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)t13_isht15_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "LH2ISH24 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)lh2ish24_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)lh2ish24_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "LH2SH27 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)lh2sh27_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)lh2sh27_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "LH2L70 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)lh2l70_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)lh2l70_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "T14LH2SH17 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)t14lh2sh17_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)t14lh2sh17_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << "---> Dielectron filter" << endl;
	out() << left << setw(25) << "2L15SH15_L20 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2l15sh15_l20_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2l15sh15_l20_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2SH10_SH15 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2sh10_sh15_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2sh10_sh15_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2_T10L10_L15 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2_t10l10_l15_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2_t10l10_l15_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2L6_L8_T5SH6 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2l6_l8_t5sh6_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2l6_l8_t5sh6_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2L20_L25 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2l20_l25_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2l20_l25_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2T5SH5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2t5sh5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2t5sh5_count_exc/(Float_t)events*100;
  out() << std::endl;
	out() << "---> Dimuon filter" << endl;
	out() << left << setw(25) << "1L1MM2 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_1l1mm2_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_1l1mm2_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2LM0MM0TLM3 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2lm0mm0tlm3_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2lm0mm0tlm3_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "TK10_2LM3 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)tk10_2lm3_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)tk10_2lm3_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ITK10_ILM6 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)itk10_ilm6_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)itk10_ilm6_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "TK8_TLM8 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)tk8_tlm8_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)tk8_tlm8_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "2LM6 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2lm6_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2lm6_count_exc/(Float_t)events*100;
  out() << std::endl;
	out() << left << setw(25) << "LM6_TK12 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)lm6_tk12_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)lm6_tk12_count_exc/(Float_t)events*100;
  out() << std::endl;
	out() << left << setw(25) << "2TK3TK5TLM3 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)_2tk3tk5tlm3_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)_2tk3tk5tlm3_count_exc/(Float_t)events*100;
  out() << std::endl;
	out() << "---> Electron muon filter" << endl;
	out() << left << setw(25) << "ISH7_TRK5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)ish7_trk5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)ish7_trk5_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ISH7_MM5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)ish7_mm5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)ish7_mm5_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "LEL15_TRK5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)lel15_trk5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)lel15_trk5_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "LEL15_MM5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)lel15_mm5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)lel15_mm5_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "SH12_TRK5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)sh12_trk5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)sh12_trk5_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "SH12_MM5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)sh12_mm5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)sh12_mm5_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "RD5 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)rd5_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)rd5_count_exc/(Float_t)events*100;
  out() << std::endl;
	out() << "---> Jets+MET filter" << endl;
	out() << left << setw(25) << "ACO_MHT_LM0 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)aco_mht_lm0_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)aco_mht_lm0_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ACO_MHT_ER2 FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)aco_mht_er2_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)aco_mht_er2_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "ACO_MHT_BDV FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)aco_mht_bdv_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)aco_mht_bdv_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "MHTACO FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)mhtaco_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)mhtaco_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "MET FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)met_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)met_count_exc/(Float_t)events*100;
  out() << std::endl;  
	out() << left << setw(25) << "MHT40_HT FILTER" << setw(15) << fixed << setprecision(3) << (Float_t)mht40_ht_count/(Float_t)events*100;
	out() << setw(15) << fixed << setprecision(3) << (Float_t)mht40_ht_count_exc/(Float_t)events*100;
  out() << std::endl;  





}


void TriggerCounter::inputFileOpened(TFile *file)
{

}

void TriggerCounter::inputFileClosing(TFile *file)
{

}

ClassImp(TriggerCounter);
