Updated central mass:

/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_78419_20120626_115602/resbos_wenu_v2_run2b34_newvar_centralmass_78419.root
/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_79419_20120626_115602/resbos_wenu_v2_run2b34_newvar_centralmass_79419.root
/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_80400_20120626_115645/resbos_wenu_v2_run2b34_newvar_centralmass_80400.root
/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_80419_20120626_115701/resbos_wenu_v2_run2b34_newvar_centralmass_80419.root
/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_80440_20120626_115724/resbos_wenu_v2_run2b34_newvar_centralmass_80440.root
/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_81419_20120626_115739/resbos_wenu_v2_run2b34_newvar_centralmass_81419.root
/prj_root/5007/wz2_write/jenny/resbos_wenu_v2_run2b34_newvar_centralmass_82419_20120626_115758/resbos_wenu_v2_run2b34_newvar_centralmass_82419.root

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_centralmass_80419.root mt_cm.root resbos_wenu_v2_run2b34_newvar_centralmass_80419.root  mt 2 >& mt_cm.log

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_78419.root sv78419.root resbos_wenu_v2_run2b34_newvar_centralmass_78419.root 2 sv 78.419 >& sv78419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_79419.root sv79419.root resbos_wenu_v2_run2b34_newvar_centralmass_79419.root 2 sv 79.419 >& sv79419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_80400.root sv80400.root resbos_wenu_v2_run2b34_newvar_centralmass_80400.root 2 sv 80.400 >& sv80400.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_80419.root sv80419.root resbos_wenu_v2_run2b34_newvar_centralmass_80419.root 2 sv 80.419 >& sv80419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_80440.root sv80440.root resbos_wenu_v2_run2b34_newvar_centralmass_80440.root 2 sv 80.440 >& sv80440.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_81419.root sv81419.root resbos_wenu_v2_run2b34_newvar_centralmass_81419.root 2 sv 81.419 >& sv81419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_82419.root sv82419.root resbos_wenu_v2_run2b34_newvar_centralmass_82419.root 2 sv 82.419 >& sv82419.log


nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x trkmatch_15_32_fid.root mt.root trkmatch_15_32_fid.root  mt 2 >& mt.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x trkmatch_15_32_fid.root pt.root trkmatch_15_32_fid.root  pt 2 >& pt.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x trkmatch_15_32_fid.root met.root trkmatch_15_32_fid.root  met 2 >& met.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x trkmatch_15_32_fid.root sv.root trkmatch_15_32_fid.root  2 sv 80.419 >& sv.log

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x trkmatch_15_32_fid.root mtgen.root trkmatch_15_32_fid.root  mtgen 2 >& mtgen.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x trkmatch_15_32_fid.root ptgen.root trkmatch_15_32_fid.root  ptgen 2 >& ptgen.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x trkmatch_15_32_fid.root metgen.root trkmatch_15_32_fid.root  metgen 2 >& metgen.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x trkmatch_15_32_fid.root svgen.root trkmatch_15_32_fid.root  2 svgen 80.419 >& svgen.log






=================================================

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_78419.root sv78419.root resbos_wenu_v2_run2b34_newvar_centralmass_78419.root 2 sv 78.419 >& sv78419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_79419.root sv79419.root resbos_wenu_v2_run2b34_newvar_centralmass_79419.root 2 sv 79.419 >& sv79419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_80400.root sv82400.root resbos_wenu_v2_run2b34_newvar_centralmass_80400.root 2 sv 82.400 >& sv82400.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_80419.root sv80419.root resbos_wenu_v2_run2b34_newvar_centralmass_80419.root 2 sv 80.419 >& sv80419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_80440.root sv82440.root resbos_wenu_v2_run2b34_newvar_centralmass_80440.root 2 sv 82.440 >& sv82440.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_81419.root sv81419.root resbos_wenu_v2_run2b34_newvar_centralmass_81419.root 2 sv 81.419 >& sv81419.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_centralmass_82419.root sv82419.root resbos_wenu_v2_run2b34_newvar_centralmass_82419.root 2 sv 82.419 >& sv82419.log

#Note: the 80400 and 80440 files were misnamed, were actually 82.400 and 82.440 mass points
#nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x tmp.root svtmp.root tmp.root 2 sv 80.419 >& svtmp.log
#nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x tmp.root mttmp.root tmp.root mt 2 >& mttmp.log
# ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x tmp.root pttmp.root tmp.root pt 2 >& pttmp.log
#./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x tmp.root mettmp.root tmp.root met 2 >& mettmp.log

#resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root
#resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root
#pythia_wen_run2b34_newvar_default.root

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root mt.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  mt 2 >& mt.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root pt.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  pt 2 >& pt.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root met.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  met 2 >& met.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root sv.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  2 sv 80.419 >& sv.log

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root mtgen.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  mtgen 2 >& mtgen.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root ptgen.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  ptgen 2 >& ptgen.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root metgen.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  metgen 2 >& metgen.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root svgen.root resbos_wenu_v2_run2b34_newvar_default_20120618_165024_v2.root  2 svgen 80.419 >& svgen.log


nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root mtsmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  mt 2 >& mtsmallrange.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root ptsmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  pt 2 >& ptsmallrange.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root metsmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  met 2 >& metsmallrange.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root svsmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  2 sv 80.419 >& svsmallrange.log

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root mtgensmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  mtgen 2 >& mtgensmallrange.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root ptgensmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  ptgen 2 >& ptgensmallrange.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root metgensmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  metgen 2 >& metgensmallrange.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root svgensmallrange.root resbos_wenu_v2_run2b34_newvar_default_20120618_172928_smallrange.root  2 svgen 80.419 >& svgensmallrange.log


nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x pythia_wen_run2b34_newvar_default.root mtpythia.root pythia_wen_run2b34_newvar_default.root  mt 2 >& mtpythia.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x pythia_wen_run2b34_newvar_default.root ptpythia.root pythia_wen_run2b34_newvar_default.root  pt 2 >& ptpythia.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x pythia_wen_run2b34_newvar_default.root metpythia.root pythia_wen_run2b34_newvar_default.root  met 2 >& metpythia.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x pythia_wen_run2b34_newvar_default.root svpythia.root pythia_wen_run2b34_newvar_default.root  2 sv 80.419 >& svpythia.log

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x pythia_wen_run2b34_newvar_default.root mtgenpythia.root pythia_wen_run2b34_newvar_default.root  mtgen 2 >& mtgenpythia.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x pythia_wen_run2b34_newvar_default.root ptgenpythia.root pythia_wen_run2b34_newvar_default.root  ptgen 2 >& ptgenpythia.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_raf_x pythia_wen_run2b34_newvar_default.root metgenpythia.root pythia_wen_run2b34_newvar_default.root  metgen 2 >& metgenpythia.log
nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x pythia_wen_run2b34_newvar_default.root svgenpythia.root pythia_wen_run2b34_newvar_default.root  2 svgen 80.419 >& svgenpythia.log

./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromhist_PDF_x hor_3_15_32_fid.root out.root hor_3_15_32_fid.root mt 2

./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x hor_3_15_32_fid.root out2.root hor_3_15_32_fid.root 2 sv 80.419


nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_rafcheck_20120621_122007_pdfsmallrange.root test.root resbos_wenu_v2_run2b34_newvar_default_rafcheck_20120621_122007_pdfsmallrange.root  2 sv 80.419
the value of the parameters are... 80.419
the errors of the parameters are... 0.0016306

old range:
the value of the parameters are... 80.419
the errors of the parameters are... 0.00263315


nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_rafcheck_rafzb_rafescaletrig_20120621_122012_pdfsmallrange.root test.root resbos_wenu_v2_run2b34_newvar_default_rafcheck_rafzb_rafescaletrig_20120621_122012_pdfsmallrange.root  2 sv 80.419
the value of the parameters are... 80.419
the errors of the parameters are... 0.0015765

nohup ./shbin/Linux2.4-GCC_3_4-maxopt/findWMass_fromSingVariableHist_notrial_x resbos_wenu_v2_run2b34_newvar_default_rafcheck_rafzb_20120621_122007_pdfsmallrange.root test.root resbos_wenu_v2_run2b34_newvar_default_rafcheck_rafzb_20120621_122007_pdfsmallrange.root  2 sv 80.419
the value of the parameters are... 80.419
the errors of the parameters are... 0.00157235

--> rafaels pdf files have 
root [2] hWcandSingVariable_CC->Integral()
(const Double_t)2.44174548918677717e+07
--> mine have
root [4] hWcandSingVariable_CC->Integral()
(const Double_t)6.84849673090480864e+07


--> so differences between me and rafael are stats related and maybe also fit range related (HAVE CHANGED THIS CONFIG FILE FOR NEW RANGE IN ABOVE)  Not related to template mass binning or parameter file differences


hor_3_15_32_fid.root, sv:
W mass: 80.419 0.00571494
PDF error: 0.0370526-->fitting error?
PDF error (CC): 0.0202299

hor_3_15_32_fid.root, mt:
W mass: 80.419 0.00225872
PDF error: 0.00835028
PDF error (CC): 0.0154558

hor_3_15_32_fid.root, pt:
W mass: 80.419 0.00237478
PDF error: 0.0146592
PDF error (CC): 0.0220744

hor_3_15_32_fid.root, met:
W mass: 80.419 0.00263388
PDF error: 0.00855875
PDF error (CC): 0.0171152

hor_2_15_32_fid.root, sv:
W mass: 80.419 0.00568006
PDF error: 0.0376076-->no fitting error, some pdfs just have big jumps
PDF error (CC): 0.0200501

hor_2_15_32_fid.root, mt:
W mass: 80.419 0.00224463
PDF error: 0.00841785
PDF error (CC): 0.0154635


hor_2_15_32_fid.root, sv:
W mass: 80.419 0.00568006
PDF error: 0.0376076
PDF error (CC): 0.0200501

hor_2_15_32_fid.root, mt:
W mass: 80.419 0.00224463
PDF error: 0.00841785
PDF error (CC): 0.0154635
=========================================
NEW:
hor_2_15_32_fid.root, mt, normal 65 to 90 range:
W mass: 80.419 0.00224626
PDF error: 0.00827223
PDF error (CC): 0.0155154

hor_2_15_32_fid.root, sv:
W mass: 80.419 0.00573095
PDF error: 0.0363663
PDF error (CC): 0.0204301

hor_2_15_32_fid.root, sv, no longitudinal smearing:
W mass: 80.419 0.00572643
PDF error: 0.0364204
PDF error (CC): 0.0204524

hor_2_15_32_fid.root, sv, using full -30 to 30 range:
W mass: 80.419 0.00285542
PDF error: 0.0388125
PDF error (CC): 0.0231393

hor_2_15_32_fid.root, mt, using 75 to 85 range:
W mass: 80.419 0.00481277
PDF error: 0.00600686
PDF error (CC): 0.00931924
