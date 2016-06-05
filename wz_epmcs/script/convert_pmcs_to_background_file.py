#!/usr/bin/python
# -*- coding: utf-8 -*-

#from Numeric import *
#from LinearAlgebra import *
#from math import *
from ROOT import *
import os
import time

gStyle.SetOptStat(0)
gStyle.SetCanvasColor(0)
gStyle.SetOptFit(1)

print os.sys.argv[1]

outfilename = 'bkgd_shape_wtaunu_new_shifted_resbos.root'
if len(os.sys.argv) > 2 :
  outfilename = os.sys.argv[2]

wtnu_file = TFile.Open( os.sys.argv[1] , 'read' )
wtnu_bkgd = TFile.Open( outfilename , 'recreate' )

hist_maps = [ ['mass_spatial' , 'hWcandMt_CC_49' , 'WCandMt_Spatial_Match_0'],
  ['Wpt_spatial' , 'hWcandWPt_CC' , 'WCandPt_Spatial_Match_0'],
  ['Wvertex_spatial' , 'hWcandVtx_CC' , 'WCandVtx_Spatial_Match_0'],
  ['Wphi_spatial' , 'hWcandWPhi_CC' , 'WCandPhi_Spatial_Match_0'],
  ['elecpt_spatial' , 'hWcandElecPt_CC_49' , 'WCandElecPt_Spatial_Match_0'],
  ['eleceta_spatial' , 'hWcandElecEta_CC' , 'WCandElecEta_Spatial_Match_0'],
  ['elecdeteta_spatial' , 'hWcandElecDetEta_CC' , 'WCandElecDetEta_Spatial_Match_0'],
  ['elecphi_spatial' , 'hWcandElecPhi_CC' , 'WCandElecPhi_Spatial_Match_0'],
  ['elecdetphi_spatial' , 'hWcandElecDetPhi_CC' , 'WCandElecDetPhi_Spatial_Match_0'],
  ['elecphitrkatdca_spatial' , 'hWcandElecPhiTrkAtDCA_CC' , 'WCandElecPhiTrkAtDCA_Spatial_Match_0'],
  ['elecphitrkatem3_spatial' , 'hWcandElecPhiTrkAtEM3_CC' , 'WCandElecPhiTrkAtEM3_Spatial_Match_0'],
  ['elecdetphicalo_spatial' , 'hWcandElecDetPhiCALO_CC' , 'WCandElecDetPhiCALO_Spatial_Match_0'],
  ['met_spatial' , 'hWcandMet_CC_49' , 'WCandMet_Spatial_Match_0'],
  ['metphi_spatial' , 'hWcandMetPhi_CC' , 'WCandMetPhi_Spatial_Match_0'],
  ['metx_spatial' , 'hWcandMetx_CC' , 'WCandMetx_Spatial_Match_0'],
  ['mety_spatial' , 'hWcandMety_CC' , 'WCandMety_Spatial_Match_0'],
  ['instlumi_spatial' , 'hWcandLumi_CC' , 'WCandInstLumi_Spatial_Match_0'],
  ['scalarEt_spatial' , 'hWcandScalarEt_CC' , 'WCandScalarEt_Spatial_Match_0'],
  ['upara_spatial' , 'hWcandUpara_CC' , 'WCandUPara_Spatial_Match_0'],
  ['uperp_spatial' , 'hWcandUperp_CC' , 'WCandUPerp_Spatial_Match_0'],
  ['WRecoilpt_spatial' , 'hWcandRecoilPt_CC' , 'WCandRecoilPt_Spatial_Match_0'],
  ['WRecoilpx_spatial' , 'hWcandRecoilPx_CC' , 'WCandRecoilPx_Spatial_Match_0'],
  ['WRecoilpy_spatial' , 'hWcandRecoilPy_CC' , 'WCandRecoilPy_Spatial_Match_0'],
  ['WRecoilphi_spatial' , 'hWcandRecoilPhi_CC' , 'WCandRecoilPhi_Spatial_Match_0'],
  ['deltaphi_emrecoil_spatial' , 'hWcandElecRecoilDeltaPhi_CC' , 'WCandElecRecoilDeltaPhi_Spatial_Match_0'],
  ['deltaphi_emmet_spatial' , 'hWcandElecMETDeltaPhi_CC' , 'WCandElecMetDeltaPhi_Spatial_Match_0'],
  ['deltaphi_metrecoil_spatial' , 'hWcandMETRecoilDeltaPhi_CC' , 'WCandMetRecoilDeltaPhi_Spatial_Match_0'],
  ['utbin_spatial' , 'hWcandMt_UtBin0_CC_49' , 'WCandMt_UtBin_Spatial_Match_0'],
  ['electrkpt_spatial' , 'hWcandElecTrkPt_CC' , 'WCandElecTrkPt_Spatial_Match_0'],
  ['electrkptove_spatial' , 'hWcandElecTrkPtOvE_CC' , 'WCandElecTrkPtOvE_Spatial_Match_0'],
  ['electrkphiem3mod_spatial' , 'hWcandElecTrkPhiModEM3_CC' , 'WCandElec_TrkPhiEM3Mod_Spatial_Match_0'],
  ['mtoverlay_spatial' , 'hWcandMtUpara_CC_49' , 'WCandMtUpara_Spatial_Match_0' ] ,
  ['mtoverlay_spatial' , 'hWcandMtUpara1_CC_49' , 'WCandMtUpara1_Spatial_Match_0' ] ,
  ['mtoverlay_spatial' , 'hWcandMtUpara2_CC_49' , 'WCandMtUpara2_Spatial_Match_0' ] ,
  ['eptoverlay_spatial', 'hWcandElecPtUpara_CC_49' , 'WCandElecPtUpara_Spatial_Match_0' ] ,
  ['eptoverlay_spatial', 'hWcandElecPtUpara1_CC_49' , 'WCandElecPtUpara1_Spatial_Match_0' ] ,
  ['eptoverlay_spatial', 'hWcandElecPtUpara2_CC_49' , 'WCandElecPtUpara2_Spatial_Match_0' ] ,
  ['metoverlay_spatial', 'hWcandMetUpara_CC_49' , 'WCandMetUpara_Spatial_Match_0' ] ,
  ['metoverlay_spatial', 'hWcandMetUpara1_CC_49' , 'WCandMetUpara1_Spatial_Match_0' ] ,
  ['metoverlay_spatial', 'hWcandMetUpara2_CC_49' , 'WCandMetUpara2_Spatial_Match_0' ] ,
  ['wptoverlay_spatial', 'hWcandWPtUpara_CC' , 'WCandWPtUpara_Spatial_Match_0' ] ,
  ['wptoverlay_spatial', 'hWcandWPtUpara1_CC' , 'WCandWPtUpara1_Spatial_Match_0' ] ,
  ['wptoverlay_spatial', 'hWcandWPtUpara2_CC' , 'WCandWPtUpara2_Spatial_Match_0' ] ,
  ]

wtnu_bkgd.cd()
new_dir = TDirectoryFile( 'WCand_Hist' , 'WCand_Hist' )

for hist0,hist1,hist2 in hist_maps :
  default_dir = wtnu_file.Get('default')
  hist = default_dir.Get(hist1)
  if hist1 == 'hWcandMt_UtBin0_CC_49' :
    for i in [ 1 , 2 ] :
      temp_hist = default_dir.Get( 'hWcandMt_UtBin%i_CC_49' % i )
      hist.Add( temp_hist )
  if hist :
    new_dir.cd()
    new_hist = hist.Clone( hist2 )
    new_hist.SetDirectory( new_dir )
    new_hist.Write()

new_dir.Write()
