#ifndef RUNIIB4RELCALIB_HPP
#define RUNIIB4RELCALIB_HPP
#include <map>


class RunIIb4RelCalib {

public:
  RunIIb4RelCalib();
  ~RunIIb4RelCalib();
  float EnergyCorrection(int ieta, int iphi, int layer, int run_number);

private:

  struct CellAddressJ {
    int ieta;
    int iphi;
    int layer;
    
    bool operator<( const CellAddressJ & n ) const {
      bool decision=false;
      if (this->ieta == n.ieta) {
	if (this->iphi == n.iphi) {
	  decision = (this->layer < n.layer);
	} else {
	  decision = (this->iphi < n.iphi);
	}
      } else {
	decision = (this->ieta < n.ieta);
      }
      return decision;
    }

  };


  void FillOne(std::map<struct CellAddressJ,float>* Target,
	       char* filename,
	       std::map<struct CellAddressJ,float>* RunIIb4a,
	       std::map<int,struct CellAddressJ>* channel2phys);


  std::map<struct CellAddressJ,float> _Fact_RunIIb4ab;
  std::map<struct CellAddressJ,float> _Fact_RunIIb4b;
  std::map<struct CellAddressJ,float> _Fact_RunIIb4c;
  std::map<struct CellAddressJ,float> _Fact_RunIIb4d;


};
#endif

