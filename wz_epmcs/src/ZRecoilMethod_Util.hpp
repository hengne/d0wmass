#ifndef INC_ZRECOILMETHOD_UTIL
#define INC_ZRECOILMETHOD_UTIL
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TRandom3.h>
#include <TROOT.h>
#include <TString.h>
#include <vector>
#include <TMath.h>

using namespace std;

class ZRecoilMethod_Util {

 public:
  ZRecoilMethod_Util(TString data_recoilname, std::vector<double> recoil_pT_bin_edges, std::vector<double> course_pT_bin_edges,
		     std::vector<double> lumi_edges, bool CConly=true);
  ~ZRecoilMethod_Util();
  
  void PickRecoil(double gen_ZpX, double gen_ZpY, double& data_RecoilPx, double& data_RecoilPy, TRandom3 * dummy );
  double PickSET(double gen_ZpT, double theRecoil);
  int findbin( double value , vector<double> & vec );
  int FindPtBin(double thePt);
  int FindPhiBin(double thePhi);
  int FindCoursePtBin(double thePt);
  int FindLumiBin(double theLumi);

  TH1F *InstLumi_WZ , *RunNo_WZ;

 private:
  
  double *_recoil_pT_bin_means;
  std::vector<double> _recoil_pT_bin_edges;
  std::vector<double> _recoil_Phi_bin_edges;
  std::vector<double> _course_pT_bin_edges;
  std::vector<double> _Lumi_bin_edges;
  bool _isCConly;

  TFile *therecoilFile;

  vector<vector<TH2F*> > _recoilhist;
  vector<vector<TH2F*> > _int_recoilhist;
  vector<TH1F*> _SEThist;
  TH1F * SETdist;
  TGraph *ut_means , *uparaz_means;
  
  const static bool use_old_ascii_files = false;
  const static int ux_uy_flag = 0;
  const static bool use_inverse_probs = true;
};

#endif
