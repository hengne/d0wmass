#include "PMCSVtx.hpp"

// default constructor
PMCSVtx::PMCSVtx() {
  _xvtx = _yvtx = _zvtx = 0.;  
}

// simple constructor
PMCSVtx::PMCSVtx(double xvtx, double yvtx, double zvtx) {
  _xvtx = xvtx;
  _yvtx = yvtx;
  _zvtx = zvtx;
}

// set vertex
void PMCSVtx::SetVtx(double xvtx, double yvtx, double zvtx) {
  _xvtx = xvtx;
  _yvtx = yvtx;
  _zvtx = zvtx;
}

// smear vertex
void PMCSVtx::SmearVtx(double vtx_res, TRandom3 *dummy) {
  _zvtx = _zvtx + dummy->Gaus(0., 1.)*vtx_res;
}
