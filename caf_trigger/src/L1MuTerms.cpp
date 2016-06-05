#include "caf_trigger/L1MuTerms.hpp"
#include <iostream>
L1MuTermsClass::L1MuTermsClass(){
  //default useless constructor
}

L1MuTermsClass::~L1MuTermsClass(){
   //destructor
}

L1MuTermsClass::L1MuTermsClass(const TMBL1Muon *l1muon, const bool& isRun2B){

   // Constructor using TMBL1Muon objects
   reset();

   // Generate handy maps
   if ( isRun2B ) {
     map_mtmRun2B();
     map_mtcxxRun2B();
   } else {
     map_mtmRun2A();
     map_mtcxxRun2A();
   }

   // Fill trigger terms
   // These three must be called in this order!
   fill_mtcxx(l1muon);
   if ( isRun2B ) {
     fill_mtcmRun2B();
     fill_mtmRun2B();
   } else {
     fill_mtcmRun2A();
     fill_mtmRun2A();
   }
}

void L1MuTermsClass::reset(){
   for(int i=0; i<8; ++i){
      for (int j=0; j<18; ++j){
	 _MTCxxCentral[i][j] = 0;
	 _MTCxxNorth[i][j] = 0;
	 _MTCxxSouth[i][j] = 0;
      }
   }

   for(int i = 0;i<256;++i){
      if (i<36){
	 _MTCCCounters[i] = 0;
	 _MTCNCounters[i] = 0;
	 _MTCSCounters[i] = 0;
      }
      _muoManagTerms.reset(i);
   }
}

void L1MuTermsClass::update_terms(const TMBL1Muon *l1muon, const bool& isRun2B){
   reset(); 
   if ( isRun2B ) {
     if (_TMTermMap.size()==0) map_mtmRun2B();
     if (_mtc05ForwardMap.size()==0) map_mtcxxRun2B();
   } else {
     if (_TMTermMap.size()==0) map_mtmRun2A();
     if (_mtc05ForwardMap.size()==0) map_mtcxxRun2A();
   }
   fill_mtcxx(l1muon);
   if ( isRun2B ) {
     fill_mtcmRun2B();
     fill_mtmRun2B();
   } else {
     fill_mtcmRun2A();
     fill_mtmRun2A();
   }
}

void L1MuTermsClass::map_mtmRun2A(){
   // Crude, but effective
   _TMTermMap.insert(std::make_pair("mu1ptxaxxy", 0));
   _TMTermMap.insert(std::make_pair("mu1pt1cllx", 1));
   _TMTermMap.insert(std::make_pair("mu1pt2cllx", 2));
   _TMTermMap.insert(std::make_pair("mu1pt3cllx", 3));
   _TMTermMap.insert(std::make_pair("mu1pt4cllx", 4));
   _TMTermMap.insert(std::make_pair("mu1ptxottx", 5));
   _TMTermMap.insert(std::make_pair("mu1pt2cttx", 6));
   _TMTermMap.insert(std::make_pair("mu1pt3cttx", 7));
   _TMTermMap.insert(std::make_pair("mu1pt4cttx", 8));
   _TMTermMap.insert(std::make_pair("mu1ptxctlx", 9));
   _TMTermMap.insert(std::make_pair("mu1pt2ctlx", 10));
   _TMTermMap.insert(std::make_pair("mu1pt3ctlx", 11));
   _TMTermMap.insert(std::make_pair("mu1pt4ctlx", 12));
   _TMTermMap.insert(std::make_pair("mu1pt1wllx", 13));
   _TMTermMap.insert(std::make_pair("mu1pt2wllx", 14));
   _TMTermMap.insert(std::make_pair("mu1pt3wllx", 15));
   _TMTermMap.insert(std::make_pair("mu1pt4wllx", 16));
   _TMTermMap.insert(std::make_pair("mu1ptxtttx", 17));
   _TMTermMap.insert(std::make_pair("mu1pt2wttx", 18));
   _TMTermMap.insert(std::make_pair("mu1pt3wttx", 19));
   _TMTermMap.insert(std::make_pair("mu1pt4wttx", 20));
   _TMTermMap.insert(std::make_pair("mu1ptxwtlx", 21));
   _TMTermMap.insert(std::make_pair("mu1pt2wtlx", 22));
   _TMTermMap.insert(std::make_pair("mu1pt3wtlx", 23));
   _TMTermMap.insert(std::make_pair("mu1pt4wtlx", 24));
   _TMTermMap.insert(std::make_pair("mu1pt1allx", 25));
   _TMTermMap.insert(std::make_pair("mu1pt2allx", 26));
   _TMTermMap.insert(std::make_pair("mu1pt3allx", 27));
   _TMTermMap.insert(std::make_pair("mu1pt4allx", 28));
   _TMTermMap.insert(std::make_pair("mu1ptxotlx", 29));
   _TMTermMap.insert(std::make_pair("mu1pt2attx", 30));
   _TMTermMap.insert(std::make_pair("mu1pt3attx", 31));
   _TMTermMap.insert(std::make_pair("mu1pt4attx", 32));
   _TMTermMap.insert(std::make_pair("mu1ptxatlx", 33));
   _TMTermMap.insert(std::make_pair("mu1pt2atlx", 34));
   _TMTermMap.insert(std::make_pair("mu1pt3atlx", 35));
   _TMTermMap.insert(std::make_pair("mu1pt4atlx", 36));
   _TMTermMap.insert(std::make_pair("mu1pt4wxxx", 37));
   _TMTermMap.insert(std::make_pair("mu1ptxcllx", 38));
   _TMTermMap.insert(std::make_pair("mu1ptxcttx", 39));
   _TMTermMap.insert(std::make_pair("mu1ptxctxx", 40));
   _TMTermMap.insert(std::make_pair("mu1ptxwllx", 41));
   _TMTermMap.insert(std::make_pair("mu1ptxwttx", 42));
   _TMTermMap.insert(std::make_pair("mu1ptxwtxx", 43));
   _TMTermMap.insert(std::make_pair("mu1ptxallx", 44));
   _TMTermMap.insert(std::make_pair("mu1ptxattx", 45));
   _TMTermMap.insert(std::make_pair("mu1ptxatxx", 46));
   _TMTermMap.insert(std::make_pair("mu1ptxbllx", 47));
   _TMTermMap.insert(std::make_pair("mu1ptxbttx", 48));
   _TMTermMap.insert(std::make_pair("mu1ptxbtxx", 49));
   _TMTermMap.insert(std::make_pair("mu1ptxttlx", 50));
   _TMTermMap.insert(std::make_pair("mu2pt1cllx", 51));
   _TMTermMap.insert(std::make_pair("mu2pt2cllx", 52));
   _TMTermMap.insert(std::make_pair("mu2pt3cllx", 53));
   _TMTermMap.insert(std::make_pair("mu2pt4cllx", 54));
   _TMTermMap.insert(std::make_pair("mu2pt1alxx", 55));
   _TMTermMap.insert(std::make_pair("mu2pt2alxx", 56));
   _TMTermMap.insert(std::make_pair("mu2pt3alxx", 57));
   _TMTermMap.insert(std::make_pair("mu2pt4alxx", 58));
   _TMTermMap.insert(std::make_pair("mu2pt1ctlz", 59));
   _TMTermMap.insert(std::make_pair("mu2pt2ctlx", 60));
   _TMTermMap.insert(std::make_pair("mu2pt3ctlx", 61));
   _TMTermMap.insert(std::make_pair("mu2pt4ctlx", 62));
   _TMTermMap.insert(std::make_pair("mu2pt1wllx", 63));
   _TMTermMap.insert(std::make_pair("mu2pt2wllx", 64));
   _TMTermMap.insert(std::make_pair("mu2pt3wllx", 65));
   _TMTermMap.insert(std::make_pair("mu2pt4wllx", 66));
   _TMTermMap.insert(std::make_pair("mu2ptxntxx", 67));
   _TMTermMap.insert(std::make_pair("mu2pt2wtxx", 68));
   _TMTermMap.insert(std::make_pair("mu2pt3wtxx", 69));
   _TMTermMap.insert(std::make_pair("mu2pt4wtxx", 70));
   _TMTermMap.insert(std::make_pair("mu2ptxstxx", 71));
   _TMTermMap.insert(std::make_pair("mu2pt2wtlx", 72));
   _TMTermMap.insert(std::make_pair("mu2pt3wtlx", 73));
   _TMTermMap.insert(std::make_pair("mu2pt4wtlx", 74));
   _TMTermMap.insert(std::make_pair("mu2pt1wlxx", 75));
   _TMTermMap.insert(std::make_pair("mu2pt2wlxx", 76));
   _TMTermMap.insert(std::make_pair("mu2pt3wlxx", 77));
   _TMTermMap.insert(std::make_pair("mu2pt4wlxx", 78));
   _TMTermMap.insert(std::make_pair("mu2pt2atxx", 79));
   _TMTermMap.insert(std::make_pair("mu2pt3atxx", 80));
   _TMTermMap.insert(std::make_pair("mu2pt4atxx", 81));
   _TMTermMap.insert(std::make_pair("mu2pt2atlx", 82));
   _TMTermMap.insert(std::make_pair("mu2pt3atlx", 83));
   _TMTermMap.insert(std::make_pair("mu2pt4atlx", 84));
   _TMTermMap.insert(std::make_pair("mu2pt4wxxx", 85));
   _TMTermMap.insert(std::make_pair("mu2ptxcllx", 86));
   _TMTermMap.insert(std::make_pair("mu2ptxcllz", 87));
   _TMTermMap.insert(std::make_pair("mu2ptxcttx", 88));
   _TMTermMap.insert(std::make_pair("mu2ptxcttl", 89));
   _TMTermMap.insert(std::make_pair("mu2ptxctxx", 90));
   _TMTermMap.insert(std::make_pair("mu2ptxctxl", 91));
   _TMTermMap.insert(std::make_pair("mu2ptxctlx", 92));
   _TMTermMap.insert(std::make_pair("mu2ptxwllx", 93));
   _TMTermMap.insert(std::make_pair("mu2ptxwlxx", 94));
   _TMTermMap.insert(std::make_pair("mu2ptxwttx", 95));
   _TMTermMap.insert(std::make_pair("mu2ptxwttl", 96));
   _TMTermMap.insert(std::make_pair("mu2ptxwtxx", 97));
   _TMTermMap.insert(std::make_pair("mu2ptxwtxl", 98));
   _TMTermMap.insert(std::make_pair("mu2ptxwtlx", 99));
   _TMTermMap.insert(std::make_pair("mu2ptxallx", 100));
   _TMTermMap.insert(std::make_pair("mu2ptxalxx", 101));
   _TMTermMap.insert(std::make_pair("mu2ptxattx", 102));
   _TMTermMap.insert(std::make_pair("mu2ptxattl", 103));
   _TMTermMap.insert(std::make_pair("mu2ptxatxx", 104));
   _TMTermMap.insert(std::make_pair("mu2ptxatxl", 105));
   _TMTermMap.insert(std::make_pair("mu2ptxatlx", 106));
   _TMTermMap.insert(std::make_pair("mu2pt1allx", 107));
   _TMTermMap.insert(std::make_pair("mu2pt2allx", 108));
   _TMTermMap.insert(std::make_pair("mu2pt4allx", 109));
   _TMTermMap.insert(std::make_pair("mu1pt1clxx", 110));
   _TMTermMap.insert(std::make_pair("mu1pt2clxx", 111));
   _TMTermMap.insert(std::make_pair("mu1pt3clxx", 112));
   _TMTermMap.insert(std::make_pair("mu1pt4clxx", 113));
   _TMTermMap.insert(std::make_pair("mu1ptxclxx", 114));
   _TMTermMap.insert(std::make_pair("mu1ptxclxz", 115));
   _TMTermMap.insert(std::make_pair("mu1ptxclxc", 116));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlx", 117));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlz", 118));
   _TMTermMap.insert(std::make_pair("mu1pt2ctxx", 119));
   _TMTermMap.insert(std::make_pair("mu1pt3ctxx", 120));
   _TMTermMap.insert(std::make_pair("mu1pt4ctxx", 121));
   _TMTermMap.insert(std::make_pair("mu1ptxcxtx", 122));
   _TMTermMap.insert(std::make_pair("mu1pt1wlxx", 123));
   _TMTermMap.insert(std::make_pair("mu1pt2wlxx", 124));
   _TMTermMap.insert(std::make_pair("mu1pt3wlxx", 125));
   _TMTermMap.insert(std::make_pair("mu1pt4wlxx", 126));
   _TMTermMap.insert(std::make_pair("mu1ptxwlxx", 127));
   _TMTermMap.insert(std::make_pair("mu1ptxwxlx", 128));
   _TMTermMap.insert(std::make_pair("mu1pt2wtxx", 129));
   _TMTermMap.insert(std::make_pair("mu1pt3wtxx", 130));
   _TMTermMap.insert(std::make_pair("mu1pt4wtxx", 131));
   _TMTermMap.insert(std::make_pair("mu1ptxwxtx", 132));
   _TMTermMap.insert(std::make_pair("mu1pt1alxx", 133));
   _TMTermMap.insert(std::make_pair("mu1pt2alxx", 134));
   _TMTermMap.insert(std::make_pair("mu1pt3alxx", 135));
   _TMTermMap.insert(std::make_pair("mu1pt4alxx", 136));
   _TMTermMap.insert(std::make_pair("mu1ptxalxx", 137));
   _TMTermMap.insert(std::make_pair("mu1ptxaxlx", 138));
   _TMTermMap.insert(std::make_pair("mu1pt2atxx", 139));
   _TMTermMap.insert(std::make_pair("mu1pt3atxx", 140));
   _TMTermMap.insert(std::make_pair("mu1pt4atxx", 141));
   _TMTermMap.insert(std::make_pair("mu1ptxaxtx", 142));
   _TMTermMap.insert(std::make_pair("mu1ptxblxx", 143));
   _TMTermMap.insert(std::make_pair("mu1ptxbxlx", 144));
   _TMTermMap.insert(std::make_pair("mu1ptxbxtx", 145));
   _TMTermMap.insert(std::make_pair("mu1pt1nlxx", 146));
   _TMTermMap.insert(std::make_pair("mu1pt2nlxx", 147));
   _TMTermMap.insert(std::make_pair("mu1pt3nlxx", 148));
   _TMTermMap.insert(std::make_pair("mu1pt4nlxx", 149));
   _TMTermMap.insert(std::make_pair("mu1ptxnlxx", 150));
   _TMTermMap.insert(std::make_pair("mu1ptxnxlx", 151));
   _TMTermMap.insert(std::make_pair("mu1pt2ntxx", 152));
   _TMTermMap.insert(std::make_pair("mu1pt3ntxx", 153));
   _TMTermMap.insert(std::make_pair("mu1pt4ntxx", 154));
   _TMTermMap.insert(std::make_pair("mu1ptxntxx", 155));
   _TMTermMap.insert(std::make_pair("mu1ptxnxtx", 156));
   _TMTermMap.insert(std::make_pair("mu1ptxolxx", 157));
   _TMTermMap.insert(std::make_pair("mu1ptxoxlx", 158));
   _TMTermMap.insert(std::make_pair("mu1ptxotxx", 159));
   _TMTermMap.insert(std::make_pair("mu1ptxoxtx", 160));
   _TMTermMap.insert(std::make_pair("mu1ptxplxx", 161));
   _TMTermMap.insert(std::make_pair("mu1ptxplxb", 162));
   _TMTermMap.insert(std::make_pair("mu1ptxpxlx", 163));
   _TMTermMap.insert(std::make_pair("mu1ptxpxlb", 164));
   _TMTermMap.insert(std::make_pair("mu1ptxpxlc", 165));
   _TMTermMap.insert(std::make_pair("mu1ptxptxx", 166));
   _TMTermMap.insert(std::make_pair("mu1ptxpxtx", 167));
   _TMTermMap.insert(std::make_pair("mu1pt1slxx", 168));
   _TMTermMap.insert(std::make_pair("mu1pt2slxx", 169));
   _TMTermMap.insert(std::make_pair("mu1pt3slxx", 170));
   _TMTermMap.insert(std::make_pair("mu1pt4slxx", 171));
   _TMTermMap.insert(std::make_pair("mu1ptxslxx", 172));
   _TMTermMap.insert(std::make_pair("mu1ptxsxlx", 173));
   _TMTermMap.insert(std::make_pair("mu1pt2stxx", 174));
   _TMTermMap.insert(std::make_pair("mu1pt3stxx", 175));
   _TMTermMap.insert(std::make_pair("mu1pt4stxx", 176));
   _TMTermMap.insert(std::make_pair("mu1ptxstxx", 177));
   _TMTermMap.insert(std::make_pair("mu1ptxsxtx", 178));
   _TMTermMap.insert(std::make_pair("mu1ptxtlxx", 179));
   _TMTermMap.insert(std::make_pair("mu1ptxtxlx", 180));
   _TMTermMap.insert(std::make_pair("mu1ptxttxx", 181));
   _TMTermMap.insert(std::make_pair("mu1ptxtxtx", 182));
   _TMTermMap.insert(std::make_pair("mu1ptxulxx", 183));
   _TMTermMap.insert(std::make_pair("mu1ptxulxb", 184));
   _TMTermMap.insert(std::make_pair("mu1ptxuxlx", 185));
   _TMTermMap.insert(std::make_pair("mu1ptxuxlb", 186));
   _TMTermMap.insert(std::make_pair("mu1ptxuxlc", 187));
   _TMTermMap.insert(std::make_pair("mu1ptxutxx", 188));
   _TMTermMap.insert(std::make_pair("mu1ptxuxtx", 189));
   _TMTermMap.insert(std::make_pair("mu2pt1clxx", 190));
   _TMTermMap.insert(std::make_pair("mu2pt2clxx", 191));
   _TMTermMap.insert(std::make_pair("mu2pt3clxx", 192));
   _TMTermMap.insert(std::make_pair("mu2pt4clxx", 193));
   _TMTermMap.insert(std::make_pair("mu2ptxclxx", 194));
   _TMTermMap.insert(std::make_pair("mu2ptxbtxx", 195));
   _TMTermMap.insert(std::make_pair("mu2ptxclxc", 196));
   _TMTermMap.insert(std::make_pair("mu2ptxcxlx", 197));
   _TMTermMap.insert(std::make_pair("mu2ptxcxlz", 198));
   _TMTermMap.insert(std::make_pair("mu2pt2ctxx", 199));
   _TMTermMap.insert(std::make_pair("mu2pt3ctxx", 200));
   _TMTermMap.insert(std::make_pair("mu2pt4ctxx", 201));
   _TMTermMap.insert(std::make_pair("mu2ptxcxtx", 202));
   _TMTermMap.insert(std::make_pair("mu2pt1nlxx", 203));
   _TMTermMap.insert(std::make_pair("mu2pt2nlxx", 204));
   _TMTermMap.insert(std::make_pair("mu2pt3nlxx", 205));
   _TMTermMap.insert(std::make_pair("mu2pt4nlxx", 206));
   _TMTermMap.insert(std::make_pair("mu2ptxnlxx", 207));
   _TMTermMap.insert(std::make_pair("mu2ptxnxlx", 208));
   _TMTermMap.insert(std::make_pair("mu2pt2ntxx", 209));
   _TMTermMap.insert(std::make_pair("mu2pt3ntxx", 210));
   _TMTermMap.insert(std::make_pair("mu2pt4ntxx", 211));
   _TMTermMap.insert(std::make_pair("mu2ptxnxtx", 212));
   _TMTermMap.insert(std::make_pair("mu2ptxolxx", 213));
   _TMTermMap.insert(std::make_pair("mu2ptxoxlx", 214));
   _TMTermMap.insert(std::make_pair("mu2ptxotxx", 215));
   _TMTermMap.insert(std::make_pair("mu2ptxoxtx", 216));
   _TMTermMap.insert(std::make_pair("mu2ptxplxx", 217));
   _TMTermMap.insert(std::make_pair("mu2ptxpxlx", 218));
   _TMTermMap.insert(std::make_pair("mu2ptxptxx", 219));
   _TMTermMap.insert(std::make_pair("mu2ptxpxtx", 220));
   _TMTermMap.insert(std::make_pair("mu2pt1slxx", 221));
   _TMTermMap.insert(std::make_pair("mu2pt2slxx", 222));
   _TMTermMap.insert(std::make_pair("mu2pt3slxx", 223));
   _TMTermMap.insert(std::make_pair("mu2pt4slxx", 224));
   _TMTermMap.insert(std::make_pair("mu2ptxslxx", 225));
   _TMTermMap.insert(std::make_pair("mu2ptxsxlx", 226));
   _TMTermMap.insert(std::make_pair("mu2pt2stxx", 227));
   _TMTermMap.insert(std::make_pair("mu2pt3stxx", 228));
   _TMTermMap.insert(std::make_pair("mu2pt4stxx", 229));
   _TMTermMap.insert(std::make_pair("mu2ptxsxtx", 230));
   _TMTermMap.insert(std::make_pair("mu2ptxtlxx", 231));
   _TMTermMap.insert(std::make_pair("mu2ptxtxlx", 232));
   _TMTermMap.insert(std::make_pair("mu2ptxttxx", 233));
   _TMTermMap.insert(std::make_pair("mu2ptxtxtx", 234));
   _TMTermMap.insert(std::make_pair("mu2ptxulxx", 235));
   _TMTermMap.insert(std::make_pair("mu2ptxuxlx", 236));
   _TMTermMap.insert(std::make_pair("mu2ptxutxx", 237));
   _TMTermMap.insert(std::make_pair("mu2ptxuxtx", 238));
   _TMTermMap.insert(std::make_pair("mu2pt1clxo", 239));
   _TMTermMap.insert(std::make_pair("mu2pt1cllo", 240));
   _TMTermMap.insert(std::make_pair("mu2pt2clxo", 241));
   _TMTermMap.insert(std::make_pair("mu2pt2cllo", 242));
   _TMTermMap.insert(std::make_pair("mu1ptxoxxe", 243));
   _TMTermMap.insert(std::make_pair("mu1ptxpxxe", 244));
   _TMTermMap.insert(std::make_pair("mu1ptxsxxe", 245));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlb", 246));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlc", 247));
   _TMTermMap.insert(std::make_pair("mu1ptxattt", 248));
   _TMTermMap.insert(std::make_pair("mu1ptxclxt", 249));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlt", 250));
   _TMTermMap.insert(std::make_pair("mu1ptxplxt", 251));
   _TMTermMap.insert(std::make_pair("mu1ptxpxlt", 252));
   _TMTermMap.insert(std::make_pair("mu1ptxulxt", 253));
   _TMTermMap.insert(std::make_pair("mu1ptxuxlt", 254));
   _TMTermMap.insert(std::make_pair("mu1ptxallt", 255));
}

void L1MuTermsClass::map_mtmRun2B(){
   // Crude, but effective
   _TMTermMap.insert(std::make_pair("mu1ptxaxxy",   0));
   _TMTermMap.insert(std::make_pair("mu1pt3ctxx",   1));
   _TMTermMap.insert(std::make_pair("mu1pt4ctxx",   2));
   _TMTermMap.insert(std::make_pair("mu1pt5ctxx",   3));
   _TMTermMap.insert(std::make_pair("mu1pt6ctxx",   4));
   _TMTermMap.insert(std::make_pair("mu1pt8ctxx",   5));
   _TMTermMap.insert(std::make_pair("mu1p13ctxx",   6));
   _TMTermMap.insert(std::make_pair("mu1ptxctxx",   7));
   _TMTermMap.insert(std::make_pair("mu1pt3ctlx",   8));
   _TMTermMap.insert(std::make_pair("mu1pt4ctlx",   9));
   _TMTermMap.insert(std::make_pair("mu1pt5ctlx",  10));
   _TMTermMap.insert(std::make_pair("mu1pt6ctlx",  11));
   _TMTermMap.insert(std::make_pair("mu1pt8ctlx",  12));
   _TMTermMap.insert(std::make_pair("mu1p13ctlx",  13));
   _TMTermMap.insert(std::make_pair("mu1ptxctlx",  14));
   _TMTermMap.insert(std::make_pair("mu1pt3cttx",  15));
   _TMTermMap.insert(std::make_pair("mu1pt4cttx",  16));
   _TMTermMap.insert(std::make_pair("mu1pt5cttx",  17));
   _TMTermMap.insert(std::make_pair("mu1pt6cttx",  18));
   _TMTermMap.insert(std::make_pair("mu1pt8cttx",  19));
   _TMTermMap.insert(std::make_pair("mu1p13cttx",  20));
   _TMTermMap.insert(std::make_pair("mu1ptxcttx",  21));
   _TMTermMap.insert(std::make_pair("mu1pt3wtxx",  22));
   _TMTermMap.insert(std::make_pair("mu1pt4wtxx",  23));
   _TMTermMap.insert(std::make_pair("mu1pt5wtxx",  24));
   _TMTermMap.insert(std::make_pair("mu1pt6wtxx",  25));
   _TMTermMap.insert(std::make_pair("mu1pt8wtxx",  26));
   _TMTermMap.insert(std::make_pair("mu1p13wtxx",  27));
   _TMTermMap.insert(std::make_pair("mu1ptxwtxx",  28));
   _TMTermMap.insert(std::make_pair("mu1pt3wtlx",  29));
   _TMTermMap.insert(std::make_pair("mu1pt4wtlx",  30));
   _TMTermMap.insert(std::make_pair("mu1pt5wtlx",  31));
   _TMTermMap.insert(std::make_pair("mu1pt6wtlx",  32));
   _TMTermMap.insert(std::make_pair("mu1pt8wtlx",  33));
   _TMTermMap.insert(std::make_pair("mu1p13wtlx",  34));
   _TMTermMap.insert(std::make_pair("mu1ptxwtlx",  35));
   _TMTermMap.insert(std::make_pair("mu1pt3wttx",  36));
   _TMTermMap.insert(std::make_pair("mu1pt4wttx",  37));
   _TMTermMap.insert(std::make_pair("mu1pt5wttx",  38));
   _TMTermMap.insert(std::make_pair("mu1pt6wttx",  39));
   _TMTermMap.insert(std::make_pair("mu1pt8wttx",  40));
   _TMTermMap.insert(std::make_pair("mu1p13wttx",  41));
   _TMTermMap.insert(std::make_pair("mu1ptxwttx",  42));
   _TMTermMap.insert(std::make_pair("mu1pt3atxx",  43));
   _TMTermMap.insert(std::make_pair("mu1pt4atxx",  44));
   _TMTermMap.insert(std::make_pair("mu1pt5atxx",  45));
   _TMTermMap.insert(std::make_pair("mu1pt6atxx",  46));
   _TMTermMap.insert(std::make_pair("mu1pt8atxx",  47));
   _TMTermMap.insert(std::make_pair("mu1p13atxx",  48));
   _TMTermMap.insert(std::make_pair("mu1ptxatxx",  49));
   _TMTermMap.insert(std::make_pair("mu1pt3atlx",  50));
   _TMTermMap.insert(std::make_pair("mu1pt4atlx",  51));
   _TMTermMap.insert(std::make_pair("mu1pt5atlx",  52));
   _TMTermMap.insert(std::make_pair("mu1pt6atlx",  53));
   _TMTermMap.insert(std::make_pair("mu1pt8atlx",  54));
   _TMTermMap.insert(std::make_pair("mu1p13atlx",  55));
   _TMTermMap.insert(std::make_pair("mu1ptxatlx",  56));
   _TMTermMap.insert(std::make_pair("mu1pt3attx",  57));
   _TMTermMap.insert(std::make_pair("mu1pt4attx",  58));
   _TMTermMap.insert(std::make_pair("mu1pt5attx",  59));
   _TMTermMap.insert(std::make_pair("mu1pt6attx",  60));
   _TMTermMap.insert(std::make_pair("mu1pt8attx",  61));
   _TMTermMap.insert(std::make_pair("mu1p13attx",  62));
   _TMTermMap.insert(std::make_pair("mu1ptxattx",  63));
   _TMTermMap.insert(std::make_pair("mu1pt3clxx",  64));
   _TMTermMap.insert(std::make_pair("mu1ptxclxx",  65));
   _TMTermMap.insert(std::make_pair("mu1pt3cllx",  66));
   _TMTermMap.insert(std::make_pair("mu1ptxcllx",  67));
   _TMTermMap.insert(std::make_pair("mu1pt3wlxx",  68));
   _TMTermMap.insert(std::make_pair("mu1ptxwlxx",  69));
   _TMTermMap.insert(std::make_pair("mu1ptxwllx",  70));
   _TMTermMap.insert(std::make_pair("mu1pt3alxx",  71));
   _TMTermMap.insert(std::make_pair("mu1ptxalxx",  72));
   _TMTermMap.insert(std::make_pair("mu1ptxallx",  73));
   _TMTermMap.insert(std::make_pair("mu1pt3ptxx",  74));
   _TMTermMap.insert(std::make_pair("mu1pt4ptxx",  75));
   _TMTermMap.insert(std::make_pair("mu1pt5ptxx",  76));
   _TMTermMap.insert(std::make_pair("mu1pt6ptxx",  77));
   _TMTermMap.insert(std::make_pair("mu1pt8ptxx",  78));
   _TMTermMap.insert(std::make_pair("mu1p13ptxx",  79));
   _TMTermMap.insert(std::make_pair("mu1ptxptxx",  80));
   _TMTermMap.insert(std::make_pair("mu1pt3utxx",  81));
   _TMTermMap.insert(std::make_pair("mu1pt4utxx",  82));
   _TMTermMap.insert(std::make_pair("mu1pt5utxx",  83));
   _TMTermMap.insert(std::make_pair("mu1pt6utxx",  84));
   _TMTermMap.insert(std::make_pair("mu1pt8utxx",  85));
   _TMTermMap.insert(std::make_pair("mu1p13utxx",  86));
   _TMTermMap.insert(std::make_pair("mu1ptxutxx",  87));
   _TMTermMap.insert(std::make_pair("mu1pt3btxx",  88));
   _TMTermMap.insert(std::make_pair("mu1pt4btxx",  89));
   _TMTermMap.insert(std::make_pair("mu1pt5btxx",  90));
   _TMTermMap.insert(std::make_pair("mu1pt6btxx",  91));
   _TMTermMap.insert(std::make_pair("mu1pt8btxx",  92));
   _TMTermMap.insert(std::make_pair("mu1p13btxx",  93));
   _TMTermMap.insert(std::make_pair("mu1ptxbtxx",  94));
   _TMTermMap.insert(std::make_pair("mu1pt3ptlx",  95));
   _TMTermMap.insert(std::make_pair("mu1pt4ptlx",  96));
   _TMTermMap.insert(std::make_pair("mu1pt5ptlx",  97));
   _TMTermMap.insert(std::make_pair("mu1pt6ptlx",  98));
   _TMTermMap.insert(std::make_pair("mu1pt8ptlx",  99));
   _TMTermMap.insert(std::make_pair("mu1p13ptlx", 100));
   _TMTermMap.insert(std::make_pair("mu1ptxptlx", 101));
   _TMTermMap.insert(std::make_pair("mu1pt3utlx", 102));
   _TMTermMap.insert(std::make_pair("mu1pt4utlx", 103));
   _TMTermMap.insert(std::make_pair("mu1pt5utlx", 104));
   _TMTermMap.insert(std::make_pair("mu1pt6utlx", 105));
   _TMTermMap.insert(std::make_pair("mu1pt8utlx", 106));
   _TMTermMap.insert(std::make_pair("mu1p13utlx", 107));
   _TMTermMap.insert(std::make_pair("mu1ptxutlx", 108));
   _TMTermMap.insert(std::make_pair("mu1pt3btlx", 109));
   _TMTermMap.insert(std::make_pair("mu1pt4btlx", 110));
   _TMTermMap.insert(std::make_pair("mu1pt5btlx", 111));
   _TMTermMap.insert(std::make_pair("mu1pt6btlx", 112));
   _TMTermMap.insert(std::make_pair("mu1pt8btlx", 113));
   _TMTermMap.insert(std::make_pair("mu1p13btlx", 114));
   _TMTermMap.insert(std::make_pair("mu1ptxbtlx", 115));
   _TMTermMap.insert(std::make_pair("mu1pt3pttx", 116));
   _TMTermMap.insert(std::make_pair("mu1pt4pttx", 117));
   _TMTermMap.insert(std::make_pair("mu1pt5pttx", 118));
   _TMTermMap.insert(std::make_pair("mu1pt6pttx", 119));
   _TMTermMap.insert(std::make_pair("mu1pt8pttx", 120));
   _TMTermMap.insert(std::make_pair("mu1p13pttx", 121));
   _TMTermMap.insert(std::make_pair("mu1ptxpttx", 122));
   _TMTermMap.insert(std::make_pair("mu1pt3uttx", 123));
   _TMTermMap.insert(std::make_pair("mu1pt4uttx", 124));
   _TMTermMap.insert(std::make_pair("mu1pt5uttx", 125));
   _TMTermMap.insert(std::make_pair("mu1pt6uttx", 126));
   _TMTermMap.insert(std::make_pair("mu1pt8uttx", 127));
   _TMTermMap.insert(std::make_pair("mu1p13uttx", 128));
   _TMTermMap.insert(std::make_pair("mu1ptxuttx", 129));
   _TMTermMap.insert(std::make_pair("mu1pt3bttx", 130));
   _TMTermMap.insert(std::make_pair("mu1pt4bttx", 131));
   _TMTermMap.insert(std::make_pair("mu1pt5bttx", 132));
   _TMTermMap.insert(std::make_pair("mu1pt6bttx", 133));
   _TMTermMap.insert(std::make_pair("mu1pt8bttx", 134));
   _TMTermMap.insert(std::make_pair("mu1p13bttx", 135));
   _TMTermMap.insert(std::make_pair("mu1ptxbttx", 136));
   _TMTermMap.insert(std::make_pair("mu1p10wxxx", 137));
   _TMTermMap.insert(std::make_pair("mu2pt3ctxx", 138));
   _TMTermMap.insert(std::make_pair("mu2pt4ctxx", 139));
   _TMTermMap.insert(std::make_pair("mu2pt5ctxx", 140));
   _TMTermMap.insert(std::make_pair("mu2pt6ctxx", 141));
   _TMTermMap.insert(std::make_pair("mu2pt8ctxx", 142));
   _TMTermMap.insert(std::make_pair("mu2p13ctxx", 143));
   _TMTermMap.insert(std::make_pair("mu2ptxctxx", 144));
   _TMTermMap.insert(std::make_pair("mu2pt3ctlx", 145));
   _TMTermMap.insert(std::make_pair("mu2pt4ctlx", 146));
   _TMTermMap.insert(std::make_pair("mu2pt5ctlx", 147));
   _TMTermMap.insert(std::make_pair("mu2pt6ctlx", 148));
   _TMTermMap.insert(std::make_pair("mu2pt8ctlx", 149));
   _TMTermMap.insert(std::make_pair("mu2p13ctlx", 150));
   _TMTermMap.insert(std::make_pair("mu2ptxctlx", 151));
   _TMTermMap.insert(std::make_pair("mu2pt3cttx", 152));
   _TMTermMap.insert(std::make_pair("mu2pt4cttx", 153));
   _TMTermMap.insert(std::make_pair("mu2pt5cttx", 154));
   _TMTermMap.insert(std::make_pair("mu2pt6cttx", 155));
   _TMTermMap.insert(std::make_pair("mu2pt8cttx", 156));
   _TMTermMap.insert(std::make_pair("mu2p13cttx", 157));
   _TMTermMap.insert(std::make_pair("mu2ptxcttx", 158));
   _TMTermMap.insert(std::make_pair("mu2pt3clxx", 159));
   _TMTermMap.insert(std::make_pair("mu2pt4clxx", 160));
   _TMTermMap.insert(std::make_pair("mu2ptxclxx", 161));
   _TMTermMap.insert(std::make_pair("mu2pt3cllx", 162));
   _TMTermMap.insert(std::make_pair("mu2ptxcllx", 163));
   _TMTermMap.insert(std::make_pair("mu2pt3wtxx", 164));
   _TMTermMap.insert(std::make_pair("mu2pt4wtxx", 165));
   _TMTermMap.insert(std::make_pair("mu2pt5wtxx", 166));
   _TMTermMap.insert(std::make_pair("mu2pt6wtxx", 167));
   _TMTermMap.insert(std::make_pair("mu2pt8wtxx", 168));
   _TMTermMap.insert(std::make_pair("mu2p13wtxx", 169));
   _TMTermMap.insert(std::make_pair("mu2ptxwtxx", 170));
   _TMTermMap.insert(std::make_pair("mu2pt3wtlx", 171));
   _TMTermMap.insert(std::make_pair("mu2pt4wtlx", 172));
   _TMTermMap.insert(std::make_pair("mu2pt5wtlx", 173));
   _TMTermMap.insert(std::make_pair("mu2pt6wtlx", 174));
   _TMTermMap.insert(std::make_pair("mu2pt8wtlx", 175));
   _TMTermMap.insert(std::make_pair("mu2p13wtlx", 176));
   _TMTermMap.insert(std::make_pair("mu2ptxwtlx", 177));
   _TMTermMap.insert(std::make_pair("mu2pt3wttx", 178));
   _TMTermMap.insert(std::make_pair("mu2pt4wttx", 179));
   _TMTermMap.insert(std::make_pair("mu2pt5wttx", 180));
   _TMTermMap.insert(std::make_pair("mu2pt6wttx", 181));
   _TMTermMap.insert(std::make_pair("mu2pt8wttx", 182));
   _TMTermMap.insert(std::make_pair("mu2p13wttx", 183));
   _TMTermMap.insert(std::make_pair("mu2ptxwttx", 184));
   _TMTermMap.insert(std::make_pair("mu2pt3atxx", 185));
   _TMTermMap.insert(std::make_pair("mu2pt4atxx", 186));
   _TMTermMap.insert(std::make_pair("mu2pt5atxx", 187));
   _TMTermMap.insert(std::make_pair("mu2pt6atxx", 188));
   _TMTermMap.insert(std::make_pair("mu2pt8atxx", 189));
   _TMTermMap.insert(std::make_pair("mu2p13atxx", 190));
   _TMTermMap.insert(std::make_pair("mu2ptxatxx", 191));
   _TMTermMap.insert(std::make_pair("mu2pt3atlx", 192));
   _TMTermMap.insert(std::make_pair("mu2pt4atlx", 193));
   _TMTermMap.insert(std::make_pair("mu2pt5atlx", 194));
   _TMTermMap.insert(std::make_pair("mu2pt6atlx", 195));
   _TMTermMap.insert(std::make_pair("mu2pt8atlx", 196));
   _TMTermMap.insert(std::make_pair("mu2p13atlx", 197));
   _TMTermMap.insert(std::make_pair("mu2ptxatlx", 198));
   _TMTermMap.insert(std::make_pair("mu2pt3attx", 199));
   _TMTermMap.insert(std::make_pair("mu2pt4attx", 200));
   _TMTermMap.insert(std::make_pair("mu2pt5attx", 201));
   _TMTermMap.insert(std::make_pair("mu2pt6attx", 202));
   _TMTermMap.insert(std::make_pair("mu2pt8attx", 203));
   _TMTermMap.insert(std::make_pair("mu2p13attx", 204));
   _TMTermMap.insert(std::make_pair("mu2ptxattx", 205));
   _TMTermMap.insert(std::make_pair("mu2pt3wlxx", 206));
   _TMTermMap.insert(std::make_pair("mu2ptxwlxx", 207));
   _TMTermMap.insert(std::make_pair("mu1ptxbtxw", 208));
   _TMTermMap.insert(std::make_pair("mu2ptxwllx", 209));
   _TMTermMap.insert(std::make_pair("mu2pt3alxx", 210));
   _TMTermMap.insert(std::make_pair("mu2ptxallx", 211));
   _TMTermMap.insert(std::make_pair("mu2pt3btxx", 212));
   _TMTermMap.insert(std::make_pair("mu2pt4btxx", 213));
   _TMTermMap.insert(std::make_pair("mu2pt5btxx", 214));
   _TMTermMap.insert(std::make_pair("mu2pt6btxx", 215));
   _TMTermMap.insert(std::make_pair("mu2pt8btxx", 216));
   _TMTermMap.insert(std::make_pair("mu2p13btxx", 217));
   _TMTermMap.insert(std::make_pair("mu2ptxbtxx", 218));
   _TMTermMap.insert(std::make_pair("mu2pt3btlx", 219));
   _TMTermMap.insert(std::make_pair("mu2pt4btlx", 220));
   _TMTermMap.insert(std::make_pair("mu2pt5btlx", 221));
   _TMTermMap.insert(std::make_pair("mu2pt6btlx", 222));
   _TMTermMap.insert(std::make_pair("mu2pt8btlx", 223));
   _TMTermMap.insert(std::make_pair("mu2p13btlx", 224));
   _TMTermMap.insert(std::make_pair("mu2ptxbtlx", 225));
   _TMTermMap.insert(std::make_pair("mu2pt3bttx", 226));
   _TMTermMap.insert(std::make_pair("mu2pt4bttx", 227));
   _TMTermMap.insert(std::make_pair("mu2pt5bttx", 228));
   _TMTermMap.insert(std::make_pair("mu2pt6bttx", 229));
   _TMTermMap.insert(std::make_pair("mu2pt8bttx", 230));
   _TMTermMap.insert(std::make_pair("mu2p13bttx", 231));
   _TMTermMap.insert(std::make_pair("mu2ptxbttx", 232));
   _TMTermMap.insert(std::make_pair("mu1ptxblxx", 233));
   _TMTermMap.insert(std::make_pair("mu1ptxbllx", 234));
   _TMTermMap.insert(std::make_pair("mu2ptxblxx", 235));
   _TMTermMap.insert(std::make_pair("mu2ptxbllx", 236));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlx", 237));
   _TMTermMap.insert(std::make_pair("mu2ptxcxlx", 238));
   _TMTermMap.insert(std::make_pair("mu1ptxcxtx", 239));
   _TMTermMap.insert(std::make_pair("mu2ptxcxtx", 240));
   _TMTermMap.insert(std::make_pair("mu1ptxbtlw", 241));
   _TMTermMap.insert(std::make_pair("mu2ptxbtlw", 242));
   _TMTermMap.insert(std::make_pair("mu1ptxbttw", 243));
   _TMTermMap.insert(std::make_pair("mu2ptxbttw", 244));
   _TMTermMap.insert(std::make_pair("mu2pt3clxo", 245));
   _TMTermMap.insert(std::make_pair("mu2pt4clxo", 246));
   _TMTermMap.insert(std::make_pair("mu2pt3cllo", 247));
   _TMTermMap.insert(std::make_pair("mu1ptxattt", 248));
   _TMTermMap.insert(std::make_pair("mu1ptxclxt", 249));
   _TMTermMap.insert(std::make_pair("mu1ptxcxlt", 250));
   _TMTermMap.insert(std::make_pair("mu1ptxplxt", 251));
   _TMTermMap.insert(std::make_pair("mu1ptxpxlt", 252));
   _TMTermMap.insert(std::make_pair("mu1ptxulxt", 253));
   _TMTermMap.insert(std::make_pair("mu1ptxuxlt", 254));
   _TMTermMap.insert(std::make_pair("mu1ptxallt", 255));
}
void L1MuTermsClass::map_mtcxxRun2A(){
   
   // Maps to enumerated constants
   _cttReqMap.clear();
   _cttReqMap.insert(std::make_pair("ptx", _ctt_x));
   _cttReqMap.insert(std::make_pair("pt1", _ctt_1));
   _cttReqMap.insert(std::make_pair("pt2", _ctt_2));
   _cttReqMap.insert(std::make_pair("pt3", _ctt_3));
   _cttReqMap.insert(std::make_pair("pt4", _ctt_4));

   _etaReqMap.clear();
   _etaReqMap.insert(std::make_pair("c", _eta_c));
   _etaReqMap.insert(std::make_pair("w", _eta_w));
   _etaReqMap.insert(std::make_pair("a", _eta_a));
   _etaReqMap.insert(std::make_pair("b", _eta_b));

   _scintReqMap.clear();
   _scintReqMap.insert(std::make_pair("x", _scint_x));
   _scintReqMap.insert(std::make_pair("l", _scint_l));
   _scintReqMap.insert(std::make_pair("t", _scint_t));
   _scintReqMap.insert(std::make_pair("c", _scint_c));

   _wireReqMap.clear();
   _wireReqMap.insert(std::make_pair("x", _wire_x));
   _wireReqMap.insert(std::make_pair("l", _wire_l));
   _wireReqMap.insert(std::make_pair("t", _wire_t));

   // Maps to MTCxx counters (these use enumerated constants as keys)

   // Central 05 (implements Table 2 in Octant Trigger Decision document)
   _mtc05CentralMap.clear();
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 0));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 1));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 2));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 3));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_l ), 4));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_l ), 5));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_t ), 6));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_t ), 7));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_t ), 8));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_l ), 9));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_c ), 10));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_t ), 11));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_x ), 12));

   // Central 10 (implemets Table 4 in Octant Trigger Decision document)
   _mtc10CentralMap.clear();
   _mtc10CentralMap.insert(std::make_pair(_wire_l, 15));
   _mtc10CentralMap.insert(std::make_pair(_wire_t, 16));

   // Forward 05 (part of Table 5 in Octant Trigger Decision document)
   _mtc05ForwardMap.clear();
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 0));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 1));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_l ), 2));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_l ), 3));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_t ), 4));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_t ), 5));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_t ), 6));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_l ), 7));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_t ), 9));

   // Forward 10 (part of Table 6 in the Octant Trigger Decision document)
   _mtc10ForwardMap.clear();
   _mtc10ForwardMap.insert(std::make_pair(_wire_l, 12));
   _mtc10ForwardMap.insert(std::make_pair(_wire_t, 14));

   // Far 05 (part of Table 5 in Octant Trigger Decision document)
   // Note that, for a given scintillator requirement, ALL ctt pT
   // cuts map to the SAME COUNTER (there is no track matching for
   // |eta|s beyond 1.5).
   _mtc05FarMap.clear();
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_t ), 10));

   // Far 10 (part of Table 6 in the Octant Trigger Decision document)
   _mtc10FarMap.clear();
   _mtc10FarMap.insert(std::make_pair(_wire_l, 13));
   _mtc10FarMap.insert(std::make_pair(_wire_t, 15));

}

void L1MuTermsClass::map_mtcxxRun2B(){

   // Maps to enumerated constants
   _cttReqMap.clear();
   _cttReqMap.insert(std::make_pair("ptx", _ctt_x));
   _cttReqMap.insert(std::make_pair("pt3", _ctt_1));
   _cttReqMap.insert(std::make_pair("pt4", _ctt_2));
   _cttReqMap.insert(std::make_pair("pt5", _ctt_3));
   _cttReqMap.insert(std::make_pair("pt6", _ctt_4));
   _cttReqMap.insert(std::make_pair("pt8", _ctt_5));
   _cttReqMap.insert(std::make_pair("p13", _ctt_6));
 
   _etaReqMap.clear();
   _etaReqMap.insert(std::make_pair("c", _eta_c));
   _etaReqMap.insert(std::make_pair("w", _eta_w));
   _etaReqMap.insert(std::make_pair("a", _eta_a));
   _etaReqMap.insert(std::make_pair("b", _eta_b)); 

   _scintReqMap.clear();
   _scintReqMap.insert(std::make_pair("x", _scint_x));
   _scintReqMap.insert(std::make_pair("l", _scint_l));
   _scintReqMap.insert(std::make_pair("t", _scint_t));
   _scintReqMap.insert(std::make_pair("c", _scint_c));
 
   _wireReqMap.clear();
   _wireReqMap.insert(std::make_pair("x", _wire_x));
   _wireReqMap.insert(std::make_pair("l", _wire_l));
   _wireReqMap.insert(std::make_pair("t", _wire_t));

   // Maps to MTCxx counters (these use enumerated constants as keys)
 
   // Central 05 (implements Table 2 in Octant Trigger Decision document)
   _mtc05CentralMap.clear();
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 0));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 1));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 2));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 3));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_5, _scint_t ), 4));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_6, _scint_t ), 5));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_t ), 6));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_t ), 7));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_t ), 8));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_l ), 9));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_t ), 10));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_t ), 11));
   _mtc05CentralMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_x ), 12));

   // Central 10 (implemets Table 4 in Octant Trigger Decision document)
   _mtc10CentralMap.clear();
   _mtc10CentralMap.insert(std::make_pair(_wire_l, 15));
   _mtc10CentralMap.insert(std::make_pair(_wire_t, 16));
                                                                                                                                                             
   // Forward 05 (part of Table 5 in Octant Trigger Decision document)
   _mtc05ForwardMap.clear();
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 0));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_t ), 1));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_5, _scint_t ), 2));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_6, _scint_t ), 3));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_t ), 4));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_t ), 5));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_t ), 6));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_l ), 7));
   _mtc05ForwardMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_t ), 9));
                                                                                                                                                             
   // Forward 10 (part of Table 6 in the Octant Trigger Decision document)
   _mtc10ForwardMap.clear();
   _mtc10ForwardMap.insert(std::make_pair(_wire_l, 12));
   _mtc10ForwardMap.insert(std::make_pair(_wire_t, 14));

   // Far 05 (part of Table 5 in Octant Trigger Decision document)
   // Note that, for a given scintillator requirement, ALL ctt pT
   // cuts map to the SAME COUNTER (there is no track matching for
   // |eta|s beyond 1.5).
   _mtc05FarMap.clear();
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_5, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_6, _scint_l ), 8));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_x, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_1, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_2, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_3, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_4, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_5, _scint_t ), 10));
   _mtc05FarMap.insert(
      std::make_pair(std::make_pair( _ctt_6, _scint_t ), 10));

   // Far 10 (part of Table 6 in the Octant Trigger Decision document)
   _mtc10FarMap.clear();
   _mtc10FarMap.insert(std::make_pair(_wire_l, 13));
   _mtc10FarMap.insert(std::make_pair(_wire_t, 15));

}

void L1MuTermsClass::fetch_Counters( 
   std::vector<int> &counters,
   const std::multimap< std::pair<int, int>, int > &mtcxxMap,
   const std::pair<int, int> &key) {

   std::multimap< std::pair<int, int>, int >::const_iterator iter;
   std::multimap< std::pair<int, int>, int >::const_iterator lower;
   std::multimap< std::pair<int, int>, int >::const_iterator upper;

   lower = mtcxxMap.lower_bound(key);
   upper = mtcxxMap.upper_bound(key);
   for (iter = lower; iter != upper; ++iter) {
      counters.push_back(iter->second);
   }

}

void L1MuTermsClass::fetch_Counters( std::vector<int> &counters, 
				     const std::map< int, int > &mtcxxMap,
				     int key) {
   std::map< int, int >::const_iterator iter;
   iter=mtcxxMap.find(key);
   if (iter!=mtcxxMap.end()) {
      counters.push_back(iter->second);
   }
}

void L1MuTermsClass::fill_mtcxx(const TMBL1Muon *l1muon)
{

   // Stuff raw octant counters into arrays
   for(int octant=0;octant<8;++octant)
   {
      for (int i=0; i<18; ++i)
      {
	 _MTCxxCentral[octant][i] = l1muon->Central(octant,i);
	 _MTCxxNorth[octant][i] = l1muon->North(octant,i);
	 _MTCxxSouth[octant][i] = l1muon->South(octant,i);
      }
   }
} 

void L1MuTermsClass::fill_mtcmRun2A(){

   // Generate the regional MTCM terms from the MTCxx counters
   for(int oct=0;oct<8;++oct)
   {
      for (int i=0; i<18; ++i)
      {
	 if(i == 13 || i == 14 || i == 17){ // BOTs and debug terms
	    _MTCCCounters[i] |= _MTCxxCentral[oct][i];
	 } else{    
	    _MTCCCounters[i] += _MTCxxCentral[oct][i];
	 }

	 if(i == 11 || i == 16 || i == 17){// BOTs and debug terms
	    _MTCNCounters[i] |= _MTCxxNorth[oct][i];
	    _MTCSCounters[i] |= _MTCxxSouth[oct][i];
	 } else{    
	    _MTCNCounters[i] += _MTCxxNorth[oct][i];
	    _MTCSCounters[i] += _MTCxxSouth[oct][i];	    
	 }
      }
   }

   // Now do the combination counters 
   // (Note: they're different for north & south vs central....)
   for(int oct=0;oct<8;++oct) {

      // Central
      _MTCCCounters[18] += 
	 OctantCounterCombine(_MTCxxCentral[oct][0], _MTCxxCentral[oct][15]);
      _MTCCCounters[19] += 
	 OctantCounterCombine(_MTCxxCentral[oct][1], _MTCxxCentral[oct][15]);
      _MTCCCounters[20] += 
	 OctantCounterCombine(_MTCxxCentral[oct][2], _MTCxxCentral[oct][15]);
      _MTCCCounters[21] += 
	 OctantCounterCombine(_MTCxxCentral[oct][3], _MTCxxCentral[oct][15]);
      _MTCCCounters[22] += 
	 OctantCounterCombine(_MTCxxCentral[oct][4], _MTCxxCentral[oct][15]);
      _MTCCCounters[23] += 
	 OctantCounterCombine(_MTCxxCentral[oct][5], _MTCxxCentral[oct][15]);
      _MTCCCounters[24] += 
	 OctantCounterCombine(_MTCxxCentral[oct][9], _MTCxxCentral[oct][15]);
      _MTCCCounters[25] += 
	 OctantCounterCombine(_MTCxxCentral[oct][6], _MTCxxCentral[oct][16]);
      _MTCCCounters[26] += 
	 OctantCounterCombine(_MTCxxCentral[oct][7], _MTCxxCentral[oct][16]);
      _MTCCCounters[27] += 
	 OctantCounterCombine(_MTCxxCentral[oct][8], _MTCxxCentral[oct][16]);
      _MTCCCounters[28] += 
	 OctantCounterCombine(_MTCxxCentral[oct][11], _MTCxxCentral[oct][16]);
      _MTCCCounters[29] += 
	 OctantCounterCombine(_MTCxxCentral[oct][6], _MTCxxCentral[oct][15]);
      _MTCCCounters[30] += 
	 OctantCounterCombine(_MTCxxCentral[oct][7], _MTCxxCentral[oct][15]);
      _MTCCCounters[31] += 
	 OctantCounterCombine(_MTCxxCentral[oct][8], _MTCxxCentral[oct][15]);
      _MTCCCounters[32] += 
	 OctantCounterCombine(_MTCxxCentral[oct][11], _MTCxxCentral[oct][15]);

      // North
      _MTCNCounters[18] += 
	 OctantCounterCombine(_MTCxxNorth[oct][0], _MTCxxNorth[oct][12]);
      _MTCNCounters[19] += 
	 OctantCounterCombine(_MTCxxNorth[oct][1], _MTCxxNorth[oct][12]);
      _MTCNCounters[20] += 
	 OctantCounterCombine(_MTCxxNorth[oct][2], _MTCxxNorth[oct][12]);
      _MTCNCounters[21] += 
	 OctantCounterCombine(_MTCxxNorth[oct][3], _MTCxxNorth[oct][12]);
      _MTCNCounters[22] += 
	 OctantCounterCombine(_MTCxxNorth[oct][7], _MTCxxNorth[oct][12]);
      _MTCNCounters[23] += 
	 OctantCounterCombine(_MTCxxNorth[oct][4], _MTCxxNorth[oct][14]);
      _MTCNCounters[24] += 
	 OctantCounterCombine(_MTCxxNorth[oct][5], _MTCxxNorth[oct][14]);
      _MTCNCounters[25] += 
	 OctantCounterCombine(_MTCxxNorth[oct][6], _MTCxxNorth[oct][14]);
      _MTCNCounters[26] += 
	 OctantCounterCombine(_MTCxxNorth[oct][9], _MTCxxNorth[oct][14]);
      _MTCNCounters[27] += 
	 OctantCounterCombine(_MTCxxNorth[oct][4], _MTCxxNorth[oct][12]);
      _MTCNCounters[28] += 
	 OctantCounterCombine(_MTCxxNorth[oct][5], _MTCxxNorth[oct][12]);
      _MTCNCounters[29] += 
	 OctantCounterCombine(_MTCxxNorth[oct][6], _MTCxxNorth[oct][12]);
      _MTCNCounters[30] += 
	 OctantCounterCombine(_MTCxxNorth[oct][9], _MTCxxNorth[oct][12]);
      _MTCNCounters[31] += 
	 OctantCounterCombine(_MTCxxNorth[oct][8], _MTCxxNorth[oct][13]);
      _MTCNCounters[32] += 
	 OctantCounterCombine(_MTCxxNorth[oct][10], _MTCxxNorth[oct][15]);
      _MTCNCounters[33] += 
	 OctantCounterCombine(_MTCxxNorth[oct][10], _MTCxxNorth[oct][13]);
   
      // South
      _MTCSCounters[18] += 
	 OctantCounterCombine(_MTCxxSouth[oct][0], _MTCxxSouth[oct][12]);
      _MTCSCounters[19] += 
	 OctantCounterCombine(_MTCxxSouth[oct][1], _MTCxxSouth[oct][12]);
      _MTCSCounters[20] += 
	 OctantCounterCombine(_MTCxxSouth[oct][2], _MTCxxSouth[oct][12]);
      _MTCSCounters[21] += 
	 OctantCounterCombine(_MTCxxSouth[oct][3], _MTCxxSouth[oct][12]);
      _MTCSCounters[22] += 
	 OctantCounterCombine(_MTCxxSouth[oct][7], _MTCxxSouth[oct][12]);
      _MTCSCounters[23] += 
	 OctantCounterCombine(_MTCxxSouth[oct][4], _MTCxxSouth[oct][14]);
      _MTCSCounters[24] += 
	 OctantCounterCombine(_MTCxxSouth[oct][5], _MTCxxSouth[oct][14]);
      _MTCSCounters[25] += 
	 OctantCounterCombine(_MTCxxSouth[oct][6], _MTCxxSouth[oct][14]);
      _MTCSCounters[26] += 
	 OctantCounterCombine(_MTCxxSouth[oct][9], _MTCxxSouth[oct][14]);
      _MTCSCounters[27] += 
	 OctantCounterCombine(_MTCxxSouth[oct][4], _MTCxxSouth[oct][12]);
      _MTCSCounters[28] += 
	 OctantCounterCombine(_MTCxxSouth[oct][5], _MTCxxSouth[oct][12]);
      _MTCSCounters[29] += 
	 OctantCounterCombine(_MTCxxSouth[oct][6], _MTCxxSouth[oct][12]);
      _MTCSCounters[30] += 
	 OctantCounterCombine(_MTCxxSouth[oct][9], _MTCxxSouth[oct][12]);
      _MTCSCounters[31] += 
	 OctantCounterCombine(_MTCxxSouth[oct][8], _MTCxxSouth[oct][13]);
      _MTCSCounters[32] += 
	 OctantCounterCombine(_MTCxxSouth[oct][10], _MTCxxSouth[oct][15]);
      _MTCSCounters[33] += 
	 OctantCounterCombine(_MTCxxSouth[oct][10], _MTCxxSouth[oct][13]);
   }

   // Counters not used
   _MTCCCounters[33] = 0;
   _MTCCCounters[34] = 0;
   _MTCCCounters[35] = 0;
   _MTCNCounters[34] = 0;
   _MTCNCounters[35] = 0;
   _MTCSCounters[34] = 0;
   _MTCSCounters[35] = 0;

   // Make sure we don't go over the two bits
   for (int i=0; i<36; ++i)
   {
      if(i != 13 && i != 14 && i != 17){
	 if (_MTCCCounters[i]>2) _MTCCCounters[i]=2;
      }
      if(i != 11 && i != 16 && i != 17){
	 if (_MTCNCounters[i]>2) _MTCNCounters[i]=2;
	 if (_MTCSCounters[i]>2) _MTCSCounters[i]=2;
      }
   }

   return;

}  // End of L1MuTerma::fill_mtcm

void L1MuTermsClass::fill_mtcmRun2B(){

   // Generate the regional MTCM terms from the MTCxx counters
   for(int oct=0;oct<8;++oct)
   {
      for (int i=0; i<18; ++i)
      {
	 if(i == 13 || i == 14 || i == 17){ // BOTs and debug terms
	    _MTCCCounters[i] |= _MTCxxCentral[oct][i];
	 } else{    
	    _MTCCCounters[i] += _MTCxxCentral[oct][i];
	 }

	 if(i == 11 || i == 16 || i == 17){// BOTs and debug terms
	    _MTCNCounters[i] |= _MTCxxNorth[oct][i];
	    _MTCSCounters[i] |= _MTCxxSouth[oct][i];
	 } else{    
	    _MTCNCounters[i] += _MTCxxNorth[oct][i];
	    _MTCSCounters[i] += _MTCxxSouth[oct][i];	    
	 }
      }
   }

   // Now do the combination counters 
   // (Note: they're different for north & south vs central....)
   for(int oct=0;oct<8;++oct) {

      // Central
      _MTCCCounters[18] += 
	 OctantCounterCombine(_MTCxxCentral[oct][0], _MTCxxCentral[oct][15]);
      _MTCCCounters[19] += 
	 OctantCounterCombine(_MTCxxCentral[oct][1], _MTCxxCentral[oct][15]);
      _MTCCCounters[20] += 
	 OctantCounterCombine(_MTCxxCentral[oct][9], _MTCxxCentral[oct][15]);
      _MTCCCounters[21] += 
	 OctantCounterCombine(_MTCxxCentral[oct][10],_MTCxxCentral[oct][15]);
      _MTCCCounters[22] += 
	 OctantCounterCombine(_MTCxxCentral[oct][6], _MTCxxCentral[oct][15]);
      _MTCCCounters[23] += 
	 OctantCounterCombine(_MTCxxCentral[oct][7], _MTCxxCentral[oct][15]);
      _MTCCCounters[24] += 
	 OctantCounterCombine(_MTCxxCentral[oct][8], _MTCxxCentral[oct][15]);
      _MTCCCounters[25] += 
	 OctantCounterCombine(_MTCxxCentral[oct][4], _MTCxxCentral[oct][15]);
      _MTCCCounters[26] += 
	 OctantCounterCombine(_MTCxxCentral[oct][5], _MTCxxCentral[oct][15]);
      _MTCCCounters[27] += 
	 OctantCounterCombine(_MTCxxCentral[oct][11],_MTCxxCentral[oct][15]);
      _MTCCCounters[28] += 
	 OctantCounterCombine(_MTCxxCentral[oct][10],_MTCxxCentral[oct][16]);
      _MTCCCounters[29] += 
	 OctantCounterCombine(_MTCxxCentral[oct][6], _MTCxxCentral[oct][16]);
      _MTCCCounters[30] += 
	 OctantCounterCombine(_MTCxxCentral[oct][7], _MTCxxCentral[oct][16]);
      _MTCCCounters[31] += 
	 OctantCounterCombine(_MTCxxCentral[oct][8], _MTCxxCentral[oct][16]);
      _MTCCCounters[32] += 
	 OctantCounterCombine(_MTCxxCentral[oct][4], _MTCxxCentral[oct][16]);
      _MTCCCounters[33] += 
	 OctantCounterCombine(_MTCxxCentral[oct][5], _MTCxxCentral[oct][16]);
      _MTCCCounters[34] += 
	 OctantCounterCombine(_MTCxxCentral[oct][11],_MTCxxCentral[oct][16]);

      // North
      _MTCNCounters[18] += 
	 OctantCounterCombine(_MTCxxNorth[oct][7], _MTCxxNorth[oct][12]);
      _MTCNCounters[19] += 
	 OctantCounterCombine(_MTCxxNorth[oct][1], _MTCxxNorth[oct][12]);
      _MTCNCounters[20] += 
	 OctantCounterCombine(_MTCxxNorth[oct][4], _MTCxxNorth[oct][12]);
      _MTCNCounters[21] += 
	 OctantCounterCombine(_MTCxxNorth[oct][5], _MTCxxNorth[oct][12]);
      _MTCNCounters[22] += 
	 OctantCounterCombine(_MTCxxNorth[oct][6], _MTCxxNorth[oct][12]);
      _MTCNCounters[23] += 
	 OctantCounterCombine(_MTCxxNorth[oct][2], _MTCxxNorth[oct][12]);
      _MTCNCounters[24] += 
	 OctantCounterCombine(_MTCxxNorth[oct][3], _MTCxxNorth[oct][12]);
      _MTCNCounters[25] += 
	 OctantCounterCombine(_MTCxxNorth[oct][9], _MTCxxNorth[oct][12]);
      _MTCNCounters[26] += 
	 OctantCounterCombine(_MTCxxNorth[oct][1], _MTCxxNorth[oct][14]);
      _MTCNCounters[27] += 
	 OctantCounterCombine(_MTCxxNorth[oct][4], _MTCxxNorth[oct][14]);
      _MTCNCounters[28] += 
	 OctantCounterCombine(_MTCxxNorth[oct][5], _MTCxxNorth[oct][14]);
      _MTCNCounters[29] += 
	 OctantCounterCombine(_MTCxxNorth[oct][6], _MTCxxNorth[oct][14]);
      _MTCNCounters[30] += 
	 OctantCounterCombine(_MTCxxNorth[oct][2], _MTCxxNorth[oct][14]);
      _MTCNCounters[31] += 
	 OctantCounterCombine(_MTCxxNorth[oct][3], _MTCxxNorth[oct][14]);
      _MTCNCounters[32] += 
	 OctantCounterCombine(_MTCxxNorth[oct][9] ,_MTCxxNorth[oct][14]);
      _MTCNCounters[33] += 
	 OctantCounterCombine(_MTCxxNorth[oct][8] ,_MTCxxNorth[oct][13]);
      _MTCNCounters[34] += 
	 OctantCounterCombine(_MTCxxNorth[oct][10],_MTCxxNorth[oct][13]);
      _MTCNCounters[35] += 
	 OctantCounterCombine(_MTCxxNorth[oct][10],_MTCxxNorth[oct][15]);
   
      // South
      _MTCSCounters[18] += 
	 OctantCounterCombine(_MTCxxSouth[oct][7], _MTCxxSouth[oct][12]);
      _MTCSCounters[19] += 
	 OctantCounterCombine(_MTCxxSouth[oct][1], _MTCxxSouth[oct][12]);
      _MTCSCounters[20] += 
	 OctantCounterCombine(_MTCxxSouth[oct][4], _MTCxxSouth[oct][12]);
      _MTCSCounters[21] += 
	 OctantCounterCombine(_MTCxxSouth[oct][5], _MTCxxSouth[oct][12]);
      _MTCSCounters[22] += 
	 OctantCounterCombine(_MTCxxSouth[oct][6], _MTCxxSouth[oct][12]);
      _MTCSCounters[23] += 
	 OctantCounterCombine(_MTCxxSouth[oct][2], _MTCxxSouth[oct][12]);
      _MTCSCounters[24] += 
	 OctantCounterCombine(_MTCxxSouth[oct][3], _MTCxxSouth[oct][12]);
      _MTCSCounters[25] += 
	 OctantCounterCombine(_MTCxxSouth[oct][9], _MTCxxSouth[oct][12]);
      _MTCSCounters[26] += 
	 OctantCounterCombine(_MTCxxSouth[oct][1], _MTCxxSouth[oct][14]);
      _MTCSCounters[27] += 
	 OctantCounterCombine(_MTCxxSouth[oct][4], _MTCxxSouth[oct][14]);
      _MTCSCounters[28] += 
	 OctantCounterCombine(_MTCxxSouth[oct][5], _MTCxxSouth[oct][14]);
      _MTCSCounters[29] += 
	 OctantCounterCombine(_MTCxxSouth[oct][6], _MTCxxSouth[oct][14]);
      _MTCSCounters[30] += 
	 OctantCounterCombine(_MTCxxSouth[oct][2], _MTCxxSouth[oct][14]);
      _MTCSCounters[31] += 
	 OctantCounterCombine(_MTCxxSouth[oct][3], _MTCxxSouth[oct][14]);
      _MTCSCounters[32] += 
	 OctantCounterCombine(_MTCxxSouth[oct][9], _MTCxxSouth[oct][14]);
      _MTCSCounters[33] += 
	 OctantCounterCombine(_MTCxxSouth[oct][8], _MTCxxSouth[oct][13]);
      _MTCSCounters[34] += 
	 OctantCounterCombine(_MTCxxSouth[oct][10],_MTCxxSouth[oct][13]);
      _MTCSCounters[35] += 
	 OctantCounterCombine(_MTCxxSouth[oct][10],_MTCxxSouth[oct][15]);
   }

   // Counters not used
   _MTCCCounters[35] = 0;

   // Make sure we don't go over the two bits
   for (int i=0; i<36; ++i)
   {
      if(i != 13 && i != 14 && i != 17){
	 if (_MTCCCounters[i]>2) _MTCCCounters[i]=2;
      }
      if(i != 11 && i != 16 && i != 17){
	 if (_MTCNCounters[i]>2) _MTCNCounters[i]=2;
	 if (_MTCSCounters[i]>2) _MTCSCounters[i]=2;
      }
   }

   return;

}  // End of L1MuTerma::fill_mtcm

void L1MuTermsClass::fill_mtmRun2B() {
  // Build the 256 MTM triggers for Run2B.

  // Give names to the counters for easy identification.
  // We call these counters single system counters.
  int C1SLP      = _MTCCCounters[0];
  int C1SLN      = _MTCCCounters[1];
  int C2SLP      = _MTCCCounters[2];
  int C2SLN      = _MTCCCounters[3];
  int C5ST       = _MTCCCounters[4];
  int C6ST       = _MTCCCounters[5];
  int C2ST       = _MTCCCounters[6];
  int C3ST       = _MTCCCounters[7];
  int C4ST       = _MTCCCounters[8];
  int CXSL       = _MTCCCounters[9];
  int C1ST       = _MTCCCounters[10];
  int CXST       = _MTCCCounters[11];
  int CHXX       = _MTCCCounters[12]; // this is the TTK(1,10) trigger
  int CXSX       = _MTCCCounters[13];
  int CXWC       = _MTCCCounters[14];
  int CXWL       = _MTCCCounters[15];
  int CXWT       = _MTCCCounters[16];
  int CXWX       = _MTCCCounters[17];
 
  int N1SL       = _MTCNCounters[0];
  int N1ST       = _MTCNCounters[1];
  int N5ST       = _MTCNCounters[2];
  int N6ST       = _MTCNCounters[3];
  int N2ST       = _MTCNCounters[4];
  int N3ST       = _MTCNCounters[5];
  int N4ST       = _MTCNCounters[6];
  int NXSL       = _MTCNCounters[7];
  int OXSL       = _MTCNCounters[8];
  int NXST       = _MTCNCounters[9];
  int OXST       = _MTCNCounters[10];
  int NXSX       = _MTCNCounters[11];
  int NXWL       = _MTCNCounters[12];
  int OXWL       = _MTCNCounters[13];
  int NXWT       = _MTCNCounters[14];
  int OXWT       = _MTCNCounters[15];
  int NXWC       = _MTCNCounters[16];
  int NXWX       = _MTCNCounters[17];

  int S1SL       = _MTCSCounters[0];
  int S1ST       = _MTCSCounters[1];
  int S5ST       = _MTCSCounters[2];
  int S6ST       = _MTCSCounters[3];
  int S2ST       = _MTCSCounters[4];
  int S3ST       = _MTCSCounters[5];
  int S4ST       = _MTCSCounters[6];
  int SXSL       = _MTCSCounters[7];
  int TXSL       = _MTCSCounters[8];
  int SXST       = _MTCSCounters[9];
  int TXST       = _MTCSCounters[10];
  int SXSX       = _MTCSCounters[11];
  int SXWL       = _MTCSCounters[12];
  int TXWL       = _MTCSCounters[13];
  int SXWT       = _MTCSCounters[14];
  int TXWT       = _MTCSCounters[15];
  int SXWC       = _MTCSCounters[16];
  int SXWX       = _MTCSCounters[17];
 
 
  // New combined system counters.
  int C1LLP = _MTCCCounters[18];
  int C1LLN = _MTCCCounters[19];
  int CXLL = _MTCCCounters[20];
  int C1TL = _MTCCCounters[21];
  int C2TL = _MTCCCounters[22];
  int C3TL = _MTCCCounters[23];
  int C4TL = _MTCCCounters[24];
  int C5TL = _MTCCCounters[25];
  int C6TL = _MTCCCounters[26];
  int CXTL = _MTCCCounters[27];
  int C1TT = _MTCCCounters[28];
  int C2TT = _MTCCCounters[29];
  int C3TT = _MTCCCounters[30];
  int C4TT = _MTCCCounters[31];
  int C5TT = _MTCCCounters[32];
  int C6TT = _MTCCCounters[33];
  int CXTT = _MTCCCounters[34];
  int CSPARE = _MTCCCounters[35];

  int NXLL = _MTCNCounters[18];
  int N1TL = _MTCNCounters[19];
  int N2TL = _MTCNCounters[20];
  int N3TL = _MTCNCounters[21];
  int N4TL = _MTCNCounters[22];
  int N5TL = _MTCNCounters[23];
  int N6TL = _MTCNCounters[24];
  int NXTL = _MTCNCounters[25];
  int N1TT = _MTCNCounters[26];
  int N2TT = _MTCNCounters[27];
  int N3TT = _MTCNCounters[28];
  int N4TT = _MTCNCounters[29];
  int N5TT = _MTCNCounters[30];
  int N6TT = _MTCNCounters[31];
  int NXTT = _MTCNCounters[32];
  int OXLL = _MTCNCounters[33];
  int OXTL = _MTCNCounters[34];
  int OXTT = _MTCNCounters[35];
                                                                                                               
  int SXLL  = _MTCSCounters[18];
  int S1TL  = _MTCSCounters[19];
  int S2TL  = _MTCSCounters[20];
  int S3TL  = _MTCSCounters[21];
  int S4TL  = _MTCSCounters[22];
  int S5TL  = _MTCSCounters[23];
  int S6TL  = _MTCSCounters[24];
  int SXTL  = _MTCSCounters[25];
  int S1TT  = _MTCSCounters[26];
  int S2TT  = _MTCSCounters[27];
  int S3TT  = _MTCSCounters[28];
  int S4TT  = _MTCSCounters[29];
  int S5TT  = _MTCSCounters[30];
  int S6TT  = _MTCSCounters[31];
  int SXTT  = _MTCSCounters[32];
  int TXLL  = _MTCSCounters[33];
  int TXTL  = _MTCSCounters[34];
  int TXTT  = _MTCSCounters[35];

  // Version 5 of the MTM trigger list. For each
  // trigger it provides the MTM trigger number, the
  // nickname of the trigger and the trigger logic.
  // First the test triggers are given, then the single
  // muon triggers and finall the dimuon triggers.
  // Triggers which are built out of counters come
  // before triggers which use combinations of triggers.
  // (We used to do the test triggers first, then 1mu triggers, 
  // then 2mu triggers using counters first as the other build off these.)
  // Now we form these triggers in order.  There is a python script
  // (/home/jtemple/Documents/octCount/convert_logic.py on clued0)
  // that converts directly from .tdf logic to .cpp
  // It's not elegant, and, as of 5/28/06, it still needs to be checked
  // for bugs, but it should provide an efficient way of moving from .tdf
  // logic to simulator logic.
  
  //  mtm 0
  // mu1ptxaxxy -- always on
  _muoManagTerms.set(0);

  // mtm 1
  //mu1pt3ctxx 
  if  (C1ST>0)  _muoManagTerms.set(1);

  // mtm 2
  //mu1pt4ctxx 
  if  (C2ST>0)  _muoManagTerms.set(2);

  // mtm 3
  //mu1pt5ctxx 
  if  (C3ST>0)  _muoManagTerms.set(3);

  // mtm 4
  //mu1pt6ctxx 
  if  (C4ST>0)  _muoManagTerms.set(4);

  // mtm 5
  //mu1pt8ctxx 
  if  (C5ST>0)  _muoManagTerms.set(5);

  // mtm 6
  //mu1p13ctxx 
  if  (C6ST>0)  _muoManagTerms.set(6);

  // mtm 7
  //mu1ptxctxx 
  if  (CXST>0)  _muoManagTerms.set(7);

  // mtm 8
  //mu1pt3ctlx 
  if  (C1TL>0)  _muoManagTerms.set(8);

  // mtm 9
  //mu1pt4ctlx 
  if  (C2TL>0)  _muoManagTerms.set(9);

  // mtm 10
  //mu1pt5ctlx 
  if  (C3TL>0)  _muoManagTerms.set(10);

  // mtm 11
  //mu1pt6ctlx 
  if  (C4TL>0)  _muoManagTerms.set(11);

  // mtm 12
  //mu1pt8ctlx 
  if  (C5TL>0)  _muoManagTerms.set(12);

  // mtm 13
  //mu1p13ctlx 
  if  (C6TL>0)  _muoManagTerms.set(13);

  // mtm 14
  //mu1ptxctlx 
  if  (CXTL>0)  _muoManagTerms.set(14);

  // mtm 15
  //mu1pt3cttx 
  if  (C1TT>0)  _muoManagTerms.set(15);

  // mtm 16
  //mu1pt4cttx 
  if  (C2TT>0)  _muoManagTerms.set(16);

  // mtm 17
  //mu1pt5cttx 
  if  (C3TT>0)  _muoManagTerms.set(17);

  // mtm 18
  //mu1pt6cttx 
  if  (C4TT>0)  _muoManagTerms.set(18);

  // mtm 19
  //mu1pt8cttx 
  if  (C5TT>0)  _muoManagTerms.set(19);

  // mtm 20
  //mu1p13cttx 
  if  (C6TT>0)  _muoManagTerms.set(20);

  // mtm 21
  //mu1ptxcttx 
  if  (CXTT>0)  _muoManagTerms.set(21);

  // mtm 22
  //mu1pt3wtxx 
  if  (C1ST>0 || N1ST>0 || S1ST>0)  _muoManagTerms.set(22);

  // mtm 23
  //mu1pt4wtxx 
  if  (C2ST>0 || N2ST>0 || S2ST>0)  _muoManagTerms.set(23);

  // mtm 24
  //mu1pt5wtxx 
  if  (C3ST>0 || N3ST>0 || S3ST>0)  _muoManagTerms.set(24);

  // mtm 25
  //mu1pt6wtxx 
  if  (C4ST>0 || N4ST>0 || S4ST>0)  _muoManagTerms.set(25);

  // mtm 26
  //mu1pt8wtxx 
  if  (C5ST>0 || N5ST>0 || S5ST>0)  _muoManagTerms.set(26);

  // mtm 27
  //mu1p13wtxx 
  if  (C6ST>0 || N6ST>0 || S6ST>0)  _muoManagTerms.set(27);

  // mtm 28
  //mu1ptxwtxx 
  if  (CXST>0 || NXST>0 || SXST>0)  _muoManagTerms.set(28);

  // mtm 29
  //mu1pt3wtlx 
  if  (C1TL>0 || N1TL>0 || S1TL>0)  _muoManagTerms.set(29);

  // mtm 30
  //mu1pt4wtlx 
  if  (C2TL>0 || N2TL>0 || S2TL>0)  _muoManagTerms.set(30);

  // mtm 31
  //mu1pt5wtlx 
  if  (C3TL>0 || N3TL>0 || S3TL>0)  _muoManagTerms.set(31);

  // mtm 32
  //mu1pt6wtlx 
  if  (C4TL>0 || N4TL>0 || S4TL>0)  _muoManagTerms.set(32);

  // mtm 33
  //mu1pt8wtlx 
  if  (C5TL>0 || N5TL>0 || S5TL>0)  _muoManagTerms.set(33);

  // mtm 34
  //mu1p13wtlx 
  if  (C6TL>0 || N6TL>0 || S6TL>0)  _muoManagTerms.set(34);

  // mtm 35
  //mu1ptxwtlx 
  if  (CXTL>0 || NXTL>0 || SXTL>0)  _muoManagTerms.set(35);

  // mtm 36
  //mu1pt3wttx 
  if  (C1TT>0 || N1TT>0 || S1TT>0)  _muoManagTerms.set(36);

  // mtm 37
  //mu1pt4wttx 
  if  (C2TT>0 || N2TT>0 || S2TT>0)  _muoManagTerms.set(37);

  // mtm 38
  //mu1pt5wttx 
  if  (C3TT>0 || N3TT>0 || S3TT>0)  _muoManagTerms.set(38);

  // mtm 39
  //mu1pt6wttx 
  if  (C4TT>0 || N4TT>0 || S4TT>0)  _muoManagTerms.set(39);

  // mtm 40
  //mu1pt8wttx 
  if  (C5TT>0 || N5TT>0 || S5TT>0)  _muoManagTerms.set(40);

  // mtm 41
  //mu1p13wttx 
  if  (C6TT>0 || N6TT>0 || S6TT>0)  _muoManagTerms.set(41);

  // mtm 42
  //mu1ptxwttx 
  if  (CXTT>0 || NXTT>0 || SXTT>0)  _muoManagTerms.set(42);

  // mtm 43
  //mu1pt3atxx 
  if  (C1ST>0 || N1ST>0 || OXST>0 || S1ST>0 || TXST>0)  _muoManagTerms.set(43);

  // mtm 44
  //mu1pt4atxx 
  if  (C2ST>0 || N2ST>0 || OXST>0 || S2ST>0 || TXST>0)  _muoManagTerms.set(44);

  // mtm 45
  //mu1pt5atxx 
  if  (C3ST>0 || N3ST>0 || OXST>0 || S3ST>0 || TXST>0)  _muoManagTerms.set(45);

  // mtm 46
  //mu1pt6atxx 
  if  (C4ST>0 || N4ST>0 || OXST>0 || S4ST>0 || TXST>0)  _muoManagTerms.set(46);

  // mtm 47
  //mu1pt8atxx 
  if  (C5ST>0 || N5ST>0 || OXST>0 || S5ST>0 || TXST>0)  _muoManagTerms.set(47);

  // mtm 48
  //mu1p13atxx 
  if  (C6ST>0 || N6ST>0 || OXST>0 || S6ST>0 || TXST>0)  _muoManagTerms.set(48);

  // mtm 49
  //mu1ptxatxx 
  if  (CXST>0 || NXST>0 || OXST>0 || SXST>0 || TXST>0)  _muoManagTerms.set(49);

  // mtm 50
  //mu1pt3atlx 
  if  (C1TL>0 || N1TL>0 || OXTL>0 || S1TL>0 || TXTL>0)  _muoManagTerms.set(50);

  // mtm 51
  //mu1pt4atlx 
  if  (C2TL>0 || N2TL>0 || OXTL>0 || S2TL>0 || TXTL>0)  _muoManagTerms.set(51);

  // mtm 52
  //mu1pt5atlx 
  if  (C3TL>0 || N3TL>0 || OXTL>0 || S3TL>0 || TXTL>0)  _muoManagTerms.set(52);

  // mtm 53
  //mu1pt6atlx 
  if  (C4TL>0 || N4TL>0 || OXTL>0 || S4TL>0 || TXTL>0)  _muoManagTerms.set(53);

  // mtm 54
  //mu1pt8atlx 
  if  (C5TL>0 || N5TL>0 || OXTL>0 || S5TL>0 || TXTL>0)  _muoManagTerms.set(54);

  // mtm 55
  //mu1p13atlx 
  if  (C6TL>0 || N6TL>0 || OXTL>0 || S6TL>0 || TXTL>0)  _muoManagTerms.set(55);

  // mtm 56
  //mu1ptxatlx 
  if  (CXTL>0 || NXTL>0 || OXTL>0 || SXTL>0 || TXTL>0)  _muoManagTerms.set(56);

  // mtm 57
  //mu1pt3attx 
  if  (C1TT>0 || N1TT>0 || OXTT>0 || S1TT>0 || TXTT>0)  _muoManagTerms.set(57);

  // mtm 58
  //mu1pt4attx 
  if  (C2TT>0 || N2TT>0 || OXTT>0 || S2TT>0 || TXTT>0)  _muoManagTerms.set(58);

  // mtm 59
  //mu1pt5attx 
  if  (C3TT>0 || N3TT>0 || OXTT>0 || S3TT>0 || TXTT>0)  _muoManagTerms.set(59);

  // mtm 60
  //mu1pt6attx 
  if  (C4TT>0 || N4TT>0 || OXTT>0 || S4TT>0 || TXTT>0)  _muoManagTerms.set(60);

  // mtm 61
  //mu1pt8attx 
  if  (C5TT>0 || N5TT>0 || OXTT>0 || S5TT>0 || TXTT>0)  _muoManagTerms.set(61);

  // mtm 62
  //mu1p13attx 
  if  (C6TT>0 || N6TT>0 || OXTT>0 || S6TT>0 || TXTT>0)  _muoManagTerms.set(62);

  // mtm 63
  //mu1ptxattx 
  if  (CXTT>0 || NXTT>0 || OXTT>0 || SXTT>0 || TXTT>0)  _muoManagTerms.set(63);

  // mtm 64
  //mu1pt3clxx 
  if  (C1SLP>0 || C1SLN>0)  _muoManagTerms.set(64);

  // mtm 65
  //mu1ptxclxx 
  if  (CXSL>0)  _muoManagTerms.set(65);

  // mtm 66
  //mu1pt3cllx 
  if  (C1LLP>0 || C1LLN>0)  _muoManagTerms.set(66);

  // mtm 67
  //mu1ptxcllx 
  if  (CXLL>0)  _muoManagTerms.set(67);

  // mtm 68
  //mu1pt3wlxx 
  if  (C1SLP>0 || C1SLN>0 || N1SL>0 || S1SL>0)  _muoManagTerms.set(68);

  // mtm 69
  //mu1ptxwlxx 
  if  (CXSL>0 || NXSL>0 || SXSL>0)  _muoManagTerms.set(69);

  // mtm 70
  //mu1ptxwllx 
  if  (CXLL>0 || NXLL>0 || SXLL>0)  _muoManagTerms.set(70);

  // mtm 71
  //mu1pt3alxx 
  if  (C1SLP>0 || C1SLN>0 || N1SL>0 || S1SL>0 || OXSL>0 || TXSL>0)  _muoManagTerms.set(71);

  // mtm 72
  //mu1ptxalxx 
  if  (CXSL>0 || NXSL>0 || SXSL>0 || OXSL>0 || TXSL>0)  _muoManagTerms.set(72);

  // mtm 73
  //mu1ptxallx 
  if  (CXLL>0 || NXLL>0 || SXLL>0 || OXLL>0 || TXLL>0)  _muoManagTerms.set(73);

  // mtm 74
  //mu1pt3ptxx 
  if  (N1ST>0 || OXST>0)  _muoManagTerms.set(74);

  // mtm 75
  //mu1pt4ptxx 
  if  (N2ST>0 || OXST>0)  _muoManagTerms.set(75);

  // mtm 76
  //mu1pt5ptxx 
  if  (N3ST>0 || OXST>0)  _muoManagTerms.set(76);

  // mtm 77
  //mu1pt6ptxx 
  if  (N4ST>0 || OXST>0)  _muoManagTerms.set(77);

  // mtm 78
  //mu1pt8ptxx 
  if  (N5ST>0 || OXST>0)  _muoManagTerms.set(78);

  // mtm 79
  //mu1p13ptxx 
  if  (N6ST>0 || OXST>0)  _muoManagTerms.set(79);

  // mtm 80
  //mu1ptxptxx 
  if  (NXST>0 || OXST>0)  _muoManagTerms.set(80);

  // mtm 81
  //mu1pt3utxx 
  if  (S1ST>0 || TXST>0)  _muoManagTerms.set(81);

  // mtm 82
  //mu1pt4utxx 
  if  (S2ST>0 || TXST>0)  _muoManagTerms.set(82);

  // mtm 83
  //mu1pt5utxx 
  if  (S3ST>0 || TXST>0)  _muoManagTerms.set(83);

  // mtm 84
  //mu1pt6utxx 
  if  (S4ST>0 || TXST>0)  _muoManagTerms.set(84);

  // mtm 85
  //mu1pt8utxx 
  if  (S5ST>0 || TXST>0)  _muoManagTerms.set(85);

  // mtm 86
  //mu1p13utxx 
  if  (S6ST>0 || TXST>0)  _muoManagTerms.set(86);

  // mtm 87
  //mu1ptxutxx 
  if  (SXST>0 || TXST>0)  _muoManagTerms.set(87);

  // mtm 88
  //mu1pt3btxx 
  if  (N1ST>0 || OXST>0 || S1ST>0 || TXST>0)  _muoManagTerms.set(88);

  // mtm 89
  //mu1pt4btxx 
  if  (N2ST>0 || OXST>0 || S2ST>0 || TXST>0)  _muoManagTerms.set(89);

  // mtm 90
  //mu1pt5btxx 
  if  (N3ST>0 || OXST>0 || S3ST>0 || TXST>0)  _muoManagTerms.set(90);

  // mtm 91
  //mu1pt6btxx 
  if  (N4ST>0 || OXST>0 || S4ST>0 || TXST>0)  _muoManagTerms.set(91);

  // mtm 92
  //mu1pt8btxx 
  if  (N5ST>0 || OXST>0 || S5ST>0 || TXST>0)  _muoManagTerms.set(92);

  // mtm 93
  //mu1p13btxx 
  if  (N6ST>0 || OXST>0 || S6ST>0 || TXST>0)  _muoManagTerms.set(93);

  // mtm 94
  //mu1ptxbtxx 
  if  (NXST>0 || OXST>0 || SXST>0 || TXST>0)  _muoManagTerms.set(94);

  // mtm 95
  //mu1pt3ptlx 
  if  (N1TL>0 || OXTL>0)  _muoManagTerms.set(95);

  // mtm 96
  //mu1pt4ptlx 
  if  (N2TL>0 || OXTL>0)  _muoManagTerms.set(96);

  // mtm 97
  //mu1pt5ptlx 
  if  (N3TL>0 || OXTL>0)  _muoManagTerms.set(97);

  // mtm 98
  //mu1pt6ptlx 
  if  (N4TL>0 || OXTL>0)  _muoManagTerms.set(98);

  // mtm 99
  //mu1pt8ptlx 
  if  (N5TL>0 || OXTL>0)  _muoManagTerms.set(99);

  // mtm 100
  //mu1p13ptlx 
  if  (N6TL>0 || OXTL>0)  _muoManagTerms.set(100);

  // mtm 101
  //mu1ptxptlx 
  if  (NXTL>0 || OXTL>0)  _muoManagTerms.set(101);

  // mtm 102
  //mu1pt3utlx 
  if  (S1TL>0 || TXTL>0)  _muoManagTerms.set(102);

  // mtm 103
  //mu1pt4utlx 
  if  (S2TL>0 || TXTL>0)  _muoManagTerms.set(103);

  // mtm 104
  //mu1pt5utlx 
  if  (S3TL>0 || TXTL>0)  _muoManagTerms.set(104);

  // mtm 105
  //mu1pt6utlx 
  if  (S4TL>0 || TXTL>0)  _muoManagTerms.set(105);

  // mtm 106
  //mu1pt8utlx 
  if  (S5TL>0 || TXTL>0)  _muoManagTerms.set(106);

  // mtm 107
  //mu1p13utlx 
  if  (S6TL>0 || TXTL>0)  _muoManagTerms.set(107);

  // mtm 108
  //mu1ptxutlx 
  if  (SXTL>0 || TXTL>0)  _muoManagTerms.set(108);

  // mtm 109
  //mu1pt3btlx 
  if  (N1TL>0 || OXTL>0 || S1TL>0 || TXTL>0)  _muoManagTerms.set(109);

  // mtm 110
  //mu1pt4btlx 
  if  (N2TL>0 || OXTL>0 || S2TL>0 || TXTL>0)  _muoManagTerms.set(110);

  // mtm 111
  //mu1pt5btlx 
  if  (N3TL>0 || OXTL>0 || S3TL>0 || TXTL>0)  _muoManagTerms.set(111);

  // mtm 112
  //mu1pt6btlx 
  if  (N4TL>0 || OXTL>0 || S4TL>0 || TXTL>0)  _muoManagTerms.set(112);

  // mtm 113
  //mu1pt8btlx 
  if  (N5TL>0 || OXTL>0 || S5TL>0 || TXTL>0)  _muoManagTerms.set(113);

  // mtm 114
  //mu1p13btlx 
  if  (N6TL>0 || OXTL>0 || S6TL>0 || TXTL>0)  _muoManagTerms.set(114);

  // mtm 115
  //mu1ptxbtlx 
  if  (NXTL>0 || OXTL>0 || SXTL>0 || TXTL>0)  _muoManagTerms.set(115);

  // mtm 116
  //mu1pt3pttx 
  if  (N1TT>0 || OXTT>0)  _muoManagTerms.set(116);

  // mtm 117
  //mu1pt4pttx 
  if  (N2TT>0 || OXTT>0)  _muoManagTerms.set(117);

  // mtm 118
  //mu1pt5pttx 
  if  (N3TT>0 || OXTT>0)  _muoManagTerms.set(118);

  // mtm 119
  //mu1pt6pttx 
  if  (N4TT>0 || OXTT>0)  _muoManagTerms.set(119);

  // mtm 120
  //mu1pt8pttx 
  if  (N5TT>0 || OXTT>0)  _muoManagTerms.set(120);

  // mtm 121
  //mu1p13pttx 
  if  (N6TT>0 || OXTT>0)  _muoManagTerms.set(121);

  // mtm 122
  //mu1ptxpttx 
  if  (NXTT>0 || OXTT>0)  _muoManagTerms.set(122);

  // mtm 123
  //mu1pt3uttx 
  if  (S1TT>0 || TXTT>0)  _muoManagTerms.set(123);

  // mtm 124
  //mu1pt4uttx 
  if  (S2TT>0 || TXTT>0)  _muoManagTerms.set(124);

  // mtm 125
  //mu1pt5uttx 
  if  (S3TT>0 || TXTT>0)  _muoManagTerms.set(125);

  // mtm 126
  //mu1pt6uttx 
  if  (S4TT>0 || TXTT>0)  _muoManagTerms.set(126);

  // mtm 127
  //mu1pt8uttx 
  if  (S5TT>0 || TXTT>0)  _muoManagTerms.set(127);

  // mtm 128
  //mu1p13uttx 
  if  (S6TT>0 || TXTT>0)  _muoManagTerms.set(128);

  // mtm 129
  //mu1ptxuttx 
  if  (SXTT>0 || TXTT>0)  _muoManagTerms.set(129);

  // mtm 130
  //mu1pt3bttx 
  if  (N1TT>0 || OXTT>0 || S1TT>0 || TXTT>0)  _muoManagTerms.set(130);

  // mtm 131
  //mu1pt4bttx 
  if  (N2TT>0 || OXTT>0 || S2TT>0 || TXTT>0)  _muoManagTerms.set(131);

  // mtm 132
  //mu1pt5bttx 
  if  (N3TT>0 || OXTT>0 || S3TT>0 || TXTT>0)  _muoManagTerms.set(132);

  // mtm 133
  //mu1pt6bttx 
  if  (N4TT>0 || OXTT>0 || S4TT>0 || TXTT>0)  _muoManagTerms.set(133);

  // mtm 134
  //mu1pt8bttx 
  if  (N5TT>0 || OXTT>0 || S5TT>0 || TXTT>0)  _muoManagTerms.set(134);

  // mtm 135
  //mu1p13bttx 
  if  (N6TT>0 || OXTT>0 || S6TT>0 || TXTT>0)  _muoManagTerms.set(135);

  // mtm 136
  //mu1ptxbttx 
  if  (NXTT>0 || OXTT>0 || SXTT>0 || TXTT>0)  _muoManagTerms.set(136);

  // mtm 137
  //mu1p10wxxx 
  if  (CHXX>0)  _muoManagTerms.set(137);

  // mtm 138
  //mu2pt3ctxx 
  if  (C1ST>1)  _muoManagTerms.set(138);

  // mtm 139
  //mu2pt4ctxx 
  if  (C2ST>1)  _muoManagTerms.set(139);

  // mtm 140
  //mu2pt5ctxx 
  if  (C3ST>1)  _muoManagTerms.set(140);

  // mtm 141
  //mu2pt6ctxx 
  if  (C4ST>1)  _muoManagTerms.set(141);

  // mtm 142
  //mu2pt8ctxx 
  if  (C5ST>1)  _muoManagTerms.set(142);

  // mtm 143
  //mu2p13ctxx 
  if  (C6ST>1)  _muoManagTerms.set(143);

  // mtm 144
  //mu2ptxctxx 
  if  (CXST>1)  _muoManagTerms.set(144);

  // mtm 145
  //mu2pt3ctlx 
  if  (C1TL>1)  _muoManagTerms.set(145);

  // mtm 146
  //mu2pt4ctlx 
  if  (C2TL>1)  _muoManagTerms.set(146);

  // mtm 147
  //mu2pt5ctlx 
  if  (C3TL>1)  _muoManagTerms.set(147);

  // mtm 148
  //mu2pt6ctlx 
  if  (C4TL>1)  _muoManagTerms.set(148);

  // mtm 149
  //mu2pt8ctlx 
  if  (C5TL>1)  _muoManagTerms.set(149);

  // mtm 150
  //mu2p13ctlx 
  if  (C6TL>1)  _muoManagTerms.set(150);

  // mtm 151
  //mu2ptxctlx 
  if  (CXTL>1)  _muoManagTerms.set(151);

  // mtm 152
  //mu2pt3cttx 
  if  (C1TT>1)  _muoManagTerms.set(152);

  // mtm 153
  //mu2pt4cttx 
  if  (C2TT>1)  _muoManagTerms.set(153);

  // mtm 154
  //mu2pt5cttx 
  if  (C3TT>1)  _muoManagTerms.set(154);

  // mtm 155
  //mu2pt6cttx 
  if  (C4TT>1)  _muoManagTerms.set(155);

  // mtm 156
  //mu2pt8cttx 
  if  (C5TT>1)  _muoManagTerms.set(156);

  // mtm 157
  //mu2p13cttx 
  if  (C6TT>1)  _muoManagTerms.set(157);

  // mtm 158
  //mu2ptxcttx 
  if  (CXTT>1)  _muoManagTerms.set(158);

  // mtm 159
  //mu2pt3clxx 
  if (C1SLP == 1 && C1SLN == 1) _muoManagTerms.set(159);
  if (C1SLP == 2) _muoManagTerms.set(159);
  if (C1SLP == 3) _muoManagTerms.set(159);
  if (C1SLN == 2) _muoManagTerms.set(159);
  if (C1SLN == 3) _muoManagTerms.set(159);

  // mtm 160
  //mu2pt4clxx 
  if (C2SLP == 1 && C2SLN == 1) _muoManagTerms.set(160);
  if (C2SLP == 2) _muoManagTerms.set(160);
  if (C2SLP == 3) _muoManagTerms.set(160);
  if (C2SLN == 2) _muoManagTerms.set(160);
  if (C2SLN == 3) _muoManagTerms.set(160);

  // mtm 161
  //mu2ptxclxx 
  if  (CXSL>1)  _muoManagTerms.set(161);

  // mtm 162
  //mu2pt3cllx 
  if (C1LLP == 1 && C1LLN == 1) _muoManagTerms.set(162);
  if (C1LLP == 2) _muoManagTerms.set(162);
  if (C1LLP == 3) _muoManagTerms.set(162);
  if (C1LLN == 2) _muoManagTerms.set(162);
  if (C1LLN == 3) _muoManagTerms.set(162);

  // mtm 163
  //mu2ptxcllx 
  if  (CXLL>1)  _muoManagTerms.set(163);

  // mtm 164
  //mu2pt3wtxx 
  if (C1ST == 1 && N1ST == 1) _muoManagTerms.set(164);
  if (C1ST == 1 && S1ST == 1) _muoManagTerms.set(164);
  if (N1ST == 1 && S1ST == 1) _muoManagTerms.set(164);
  if (C1ST == 2) _muoManagTerms.set(164);
  if (C1ST == 3) _muoManagTerms.set(164);
  if (N1ST == 2) _muoManagTerms.set(164);
  if (N1ST == 3) _muoManagTerms.set(164);
  if (S1ST == 2) _muoManagTerms.set(164);
  if (S1ST == 3) _muoManagTerms.set(164);

  // mtm 165
  //mu2pt4wtxx 
  if (C2ST == 1 && N2ST == 1) _muoManagTerms.set(165);
  if (C2ST == 1 && S2ST == 1) _muoManagTerms.set(165);
  if (N2ST == 1 && S2ST == 1) _muoManagTerms.set(165);
  if (C2ST == 2) _muoManagTerms.set(165);
  if (C2ST == 3) _muoManagTerms.set(165);
  if (N2ST == 2) _muoManagTerms.set(165);
  if (N2ST == 3) _muoManagTerms.set(165);
  if (S2ST == 2) _muoManagTerms.set(165);
  if (S2ST == 3) _muoManagTerms.set(165);

  // mtm 166
  //mu2pt5wtxx 
  if (C3ST == 1 && N3ST == 1) _muoManagTerms.set(166);
  if (C3ST == 1 && S3ST == 1) _muoManagTerms.set(166);
  if (N3ST == 1 && S3ST == 1) _muoManagTerms.set(166);
  if (C3ST == 2) _muoManagTerms.set(166);
  if (C3ST == 3) _muoManagTerms.set(166);
  if (N3ST == 2) _muoManagTerms.set(166);
  if (N3ST == 3) _muoManagTerms.set(166);
  if (S3ST == 2) _muoManagTerms.set(166);
  if (S3ST == 3) _muoManagTerms.set(166);

  // mtm 167
  //mu2pt6wtxx 
  if (C4ST == 1 && N4ST == 1) _muoManagTerms.set(167);
  if (C4ST == 1 && S4ST == 1) _muoManagTerms.set(167);
  if (N4ST == 1 && S4ST == 1) _muoManagTerms.set(167);
  if (C4ST == 2) _muoManagTerms.set(167);
  if (C4ST == 3) _muoManagTerms.set(167);
  if (N4ST == 2) _muoManagTerms.set(167);
  if (N4ST == 3) _muoManagTerms.set(167);
  if (S4ST == 2) _muoManagTerms.set(167);
  if (S4ST == 3) _muoManagTerms.set(167);

  // mtm 168
  //mu2pt8wtxx 
  if (C5ST == 1 && N5ST == 1) _muoManagTerms.set(168);
  if (C5ST == 1 && S5ST == 1) _muoManagTerms.set(168);
  if (N5ST == 1 && S5ST == 1) _muoManagTerms.set(168);
  if (C5ST == 2) _muoManagTerms.set(168);
  if (C5ST == 3) _muoManagTerms.set(168);
  if (N5ST == 2) _muoManagTerms.set(168);
  if (N5ST == 3) _muoManagTerms.set(168);
  if (S5ST == 2) _muoManagTerms.set(168);
  if (S5ST == 3) _muoManagTerms.set(168);

  // mtm 169
  //mu2p13wtxx 
  if (C6ST == 1 && N6ST == 1) _muoManagTerms.set(169);
  if (C6ST == 1 && S6ST == 1) _muoManagTerms.set(169);
  if (N6ST == 1 && S6ST == 1) _muoManagTerms.set(169);
  if (C6ST == 2) _muoManagTerms.set(169);
  if (C6ST == 3) _muoManagTerms.set(169);
  if (N6ST == 2) _muoManagTerms.set(169);
  if (N6ST == 3) _muoManagTerms.set(169);
  if (S6ST == 2) _muoManagTerms.set(169);
  if (S6ST == 3) _muoManagTerms.set(169);

  // mtm 170
  //mu2ptxwtxx 
  if (CXST == 1 && NXST == 1) _muoManagTerms.set(170);
  if (CXST == 1 && SXST == 1) _muoManagTerms.set(170);
  if (NXST == 1 && SXST == 1) _muoManagTerms.set(170);
  if (CXST == 2) _muoManagTerms.set(170);
  if (CXST == 3) _muoManagTerms.set(170);
  if (NXST == 2) _muoManagTerms.set(170);
  if (NXST == 3) _muoManagTerms.set(170);
  if (SXST == 2) _muoManagTerms.set(170);
  if (SXST == 3) _muoManagTerms.set(170);

  // mtm 171
  //mu2pt3wtlx 
  if (C1TL == 1 && N1TL == 1) _muoManagTerms.set(171);
  if (C1TL == 1 && S1TL == 1) _muoManagTerms.set(171);
  if (N1TL == 1 && S1TL == 1) _muoManagTerms.set(171);
  if (C1TL == 2) _muoManagTerms.set(171);
  if (C1TL == 3) _muoManagTerms.set(171);
  if (N1TL == 2) _muoManagTerms.set(171);
  if (N1TL == 3) _muoManagTerms.set(171);
  if (S1TL == 2) _muoManagTerms.set(171);
  if (S1TL == 3) _muoManagTerms.set(171);

  // mtm 172
  //mu2pt4wtlx 
  if (C2TL == 1 && N2TL == 1) _muoManagTerms.set(172);
  if (C2TL == 1 && S2TL == 1) _muoManagTerms.set(172);
  if (N2TL == 1 && S2TL == 1) _muoManagTerms.set(172);
  if (C2TL == 2) _muoManagTerms.set(172);
  if (C2TL == 3) _muoManagTerms.set(172);
  if (N2TL == 2) _muoManagTerms.set(172);
  if (N2TL == 3) _muoManagTerms.set(172);
  if (S2TL == 2) _muoManagTerms.set(172);
  if (S2TL == 3) _muoManagTerms.set(172);

  // mtm 173
  //mu2pt5wtlx 
  if (C3TL == 1 && N3TL == 1) _muoManagTerms.set(173);
  if (C3TL == 1 && S3TL == 1) _muoManagTerms.set(173);
  if (N3TL == 1 && S3TL == 1) _muoManagTerms.set(173);
  if (C3TL == 2) _muoManagTerms.set(173);
  if (C3TL == 3) _muoManagTerms.set(173);
  if (N3TL == 2) _muoManagTerms.set(173);
  if (N3TL == 3) _muoManagTerms.set(173);
  if (S3TL == 2) _muoManagTerms.set(173);
  if (S3TL == 3) _muoManagTerms.set(173);

  // mtm 174
  //mu2pt6wtlx 
  if (C4TL == 1 && N4TL == 1) _muoManagTerms.set(174);
  if (C4TL == 1 && S4TL == 1) _muoManagTerms.set(174);
  if (N4TL == 1 && S4TL == 1) _muoManagTerms.set(174);
  if (C4TL == 2) _muoManagTerms.set(174);
  if (C4TL == 3) _muoManagTerms.set(174);
  if (N4TL == 2) _muoManagTerms.set(174);
  if (N4TL == 3) _muoManagTerms.set(174);
  if (S4TL == 2) _muoManagTerms.set(174);
  if (S4TL == 3) _muoManagTerms.set(174);

  // mtm 175
  //mu2pt8wtlx 
  if (C5TL == 1 && N5TL == 1) _muoManagTerms.set(175);
  if (C5TL == 1 && S5TL == 1) _muoManagTerms.set(175);
  if (N5TL == 1 && S5TL == 1) _muoManagTerms.set(175);
  if (C5TL == 2) _muoManagTerms.set(175);
  if (C5TL == 3) _muoManagTerms.set(175);
  if (N5TL == 2) _muoManagTerms.set(175);
  if (N5TL == 3) _muoManagTerms.set(175);
  if (S5TL == 2) _muoManagTerms.set(175);
  if (S5TL == 3) _muoManagTerms.set(175);

  // mtm 176
  //mu2p13wtlx 
  if (C6TL == 1 && N6TL == 1) _muoManagTerms.set(176);
  if (C6TL == 1 && S6TL == 1) _muoManagTerms.set(176);
  if (N6TL == 1 && S6TL == 1) _muoManagTerms.set(176);
  if (C6TL == 2) _muoManagTerms.set(176);
  if (C6TL == 3) _muoManagTerms.set(176);
  if (N6TL == 2) _muoManagTerms.set(176);
  if (N6TL == 3) _muoManagTerms.set(176);
  if (S6TL == 2) _muoManagTerms.set(176);
  if (S6TL == 3) _muoManagTerms.set(176);

  // mtm 177
  //mu2ptxwtlx 
  if (CXTL == 1 && NXTL == 1) _muoManagTerms.set(177);
  if (CXTL == 1 && SXTL == 1) _muoManagTerms.set(177);
  if (NXTL == 1 && SXTL == 1) _muoManagTerms.set(177);
  if (CXTL == 2) _muoManagTerms.set(177);
  if (CXTL == 3) _muoManagTerms.set(177);
  if (NXTL == 2) _muoManagTerms.set(177);
  if (NXTL == 3) _muoManagTerms.set(177);
  if (SXTL == 2) _muoManagTerms.set(177);
  if (SXTL == 3) _muoManagTerms.set(177);

  // mtm 178
  //mu2pt3wttx 
  if (C1TT == 1 && N1TT == 1) _muoManagTerms.set(178);
  if (C1TT == 1 && S1TT == 1) _muoManagTerms.set(178);
  if (N1TT == 1 && S1TT == 1) _muoManagTerms.set(178);
  if (C1TT == 2) _muoManagTerms.set(178);
  if (C1TT == 3) _muoManagTerms.set(178);
  if (N1TT == 2) _muoManagTerms.set(178);
  if (N1TT == 3) _muoManagTerms.set(178);
  if (S1TT == 2) _muoManagTerms.set(178);
  if (S1TT == 3) _muoManagTerms.set(178);

  // mtm 179
  //mu2pt4wttx 
  if (C2TT == 1 && N2TT == 1) _muoManagTerms.set(179);
  if (C2TT == 1 && S2TT == 1) _muoManagTerms.set(179);
  if (N2TT == 1 && S2TT == 1) _muoManagTerms.set(179);
  if (C2TT == 2) _muoManagTerms.set(179);
  if (C2TT == 3) _muoManagTerms.set(179);
  if (N2TT == 2) _muoManagTerms.set(179);
  if (N2TT == 3) _muoManagTerms.set(179);
  if (S2TT == 2) _muoManagTerms.set(179);
  if (S2TT == 3) _muoManagTerms.set(179);

  // mtm 180
  //mu2pt5wttx 
  if (C3TT == 1 && N3TT == 1) _muoManagTerms.set(180);
  if (C3TT == 1 && S3TT == 1) _muoManagTerms.set(180);
  if (N3TT == 1 && S3TT == 1) _muoManagTerms.set(180);
  if (C3TT == 2) _muoManagTerms.set(180);
  if (C3TT == 3) _muoManagTerms.set(180);
  if (N3TT == 2) _muoManagTerms.set(180);
  if (N3TT == 3) _muoManagTerms.set(180);
  if (S3TT == 2) _muoManagTerms.set(180);
  if (S3TT == 3) _muoManagTerms.set(180);

  // mtm 181
  //mu2pt6wttx 
  if (C4TT == 1 && N4TT == 1) _muoManagTerms.set(181);
  if (C4TT == 1 && S4TT == 1) _muoManagTerms.set(181);
  if (N4TT == 1 && S4TT == 1) _muoManagTerms.set(181);
  if (C4TT == 2) _muoManagTerms.set(181);
  if (C4TT == 3) _muoManagTerms.set(181);
  if (N4TT == 2) _muoManagTerms.set(181);
  if (N4TT == 3) _muoManagTerms.set(181);
  if (S4TT == 2) _muoManagTerms.set(181);
  if (S4TT == 3) _muoManagTerms.set(181);

  // mtm 182
  //mu2pt8wttx 
  if (C5TT == 1 && N5TT == 1) _muoManagTerms.set(182);
  if (C5TT == 1 && S5TT == 1) _muoManagTerms.set(182);
  if (N5TT == 1 && S5TT == 1) _muoManagTerms.set(182);
  if (C5TT == 2) _muoManagTerms.set(182);
  if (C5TT == 3) _muoManagTerms.set(182);
  if (N5TT == 2) _muoManagTerms.set(182);
  if (N5TT == 3) _muoManagTerms.set(182);
  if (S5TT == 2) _muoManagTerms.set(182);
  if (S5TT == 3) _muoManagTerms.set(182);

  // mtm 183
  //mu2p13wttx 
  if (C6TT == 1 && N6TT == 1) _muoManagTerms.set(183);
  if (C6TT == 1 && S6TT == 1) _muoManagTerms.set(183);
  if (N6TT == 1 && S6TT == 1) _muoManagTerms.set(183);
  if (C6TT == 2) _muoManagTerms.set(183);
  if (C6TT == 3) _muoManagTerms.set(183);
  if (N6TT == 2) _muoManagTerms.set(183);
  if (N6TT == 3) _muoManagTerms.set(183);
  if (S6TT == 2) _muoManagTerms.set(183);
  if (S6TT == 3) _muoManagTerms.set(183);

  // mtm 184
  //mu2ptxwttx 
  if (CXTT == 1 && NXTT == 1) _muoManagTerms.set(184);
  if (CXTT == 1 && SXTT == 1) _muoManagTerms.set(184);
  if (NXTT == 1 && SXTT == 1) _muoManagTerms.set(184);
  if (CXTT == 2) _muoManagTerms.set(184);
  if (CXTT == 3) _muoManagTerms.set(184);
  if (NXTT == 2) _muoManagTerms.set(184);
  if (NXTT == 3) _muoManagTerms.set(184);
  if (SXTT == 2) _muoManagTerms.set(184);
  if (SXTT == 3) _muoManagTerms.set(184);

  // mtm 185
  //mu2pt3atxx 
  if (C1ST == 1 && N1ST == 1) _muoManagTerms.set(185);
  if (C1ST == 1 && S1ST == 1) _muoManagTerms.set(185);
  if (C1ST == 1 && OXST == 1) _muoManagTerms.set(185);
  if (C1ST == 1 && TXST == 1) _muoManagTerms.set(185);
  if (C1ST == 2) _muoManagTerms.set(185);
  if (C1ST == 3) _muoManagTerms.set(185);
  if (N1ST == 1 && S1ST == 1) _muoManagTerms.set(185);
  if (N1ST == 1 && OXST == 1) _muoManagTerms.set(185);
  if (N1ST == 1 && TXST == 1) _muoManagTerms.set(185);
  if (N1ST == 2) _muoManagTerms.set(185);
  if (N1ST == 3) _muoManagTerms.set(185);
  if (S1ST == 1 && OXST == 1) _muoManagTerms.set(185);
  if (S1ST == 1 && TXST == 1) _muoManagTerms.set(185);
  if (S1ST == 2) _muoManagTerms.set(185);
  if (S1ST == 3) _muoManagTerms.set(185);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(185);
  if (OXST == 2) _muoManagTerms.set(185);
  if (OXST == 3) _muoManagTerms.set(185);
  if (TXST == 2) _muoManagTerms.set(185);
  if (TXST == 3) _muoManagTerms.set(185);

  // mtm 186
  //mu2pt4atxx 
  if (C2ST == 1 && N2ST == 1) _muoManagTerms.set(186);
  if (C2ST == 1 && S2ST == 1) _muoManagTerms.set(186);
  if (C2ST == 1 && OXST == 1) _muoManagTerms.set(186);
  if (C2ST == 1 && TXST == 1) _muoManagTerms.set(186);
  if (C2ST == 2) _muoManagTerms.set(186);
  if (C2ST == 3) _muoManagTerms.set(186);
  if (N2ST == 1 && S2ST == 1) _muoManagTerms.set(186);
  if (N2ST == 1 && OXST == 1) _muoManagTerms.set(186);
  if (N2ST == 1 && TXST == 1) _muoManagTerms.set(186);
  if (N2ST == 2) _muoManagTerms.set(186);
  if (N2ST == 3) _muoManagTerms.set(186);
  if (S2ST == 1 && OXST == 1) _muoManagTerms.set(186);
  if (S2ST == 1 && TXST == 1) _muoManagTerms.set(186);
  if (S2ST == 2) _muoManagTerms.set(186);
  if (S2ST == 3) _muoManagTerms.set(186);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(186);
  if (OXST == 2) _muoManagTerms.set(186);
  if (OXST == 3) _muoManagTerms.set(186);
  if (TXST == 2) _muoManagTerms.set(186);
  if (TXST == 3) _muoManagTerms.set(186);

  // mtm 187
  //mu2pt5atxx 
  if (C3ST == 1 && N3ST == 1) _muoManagTerms.set(187);
  if (C3ST == 1 && S3ST == 1) _muoManagTerms.set(187);
  if (C3ST == 1 && OXST == 1) _muoManagTerms.set(187);
  if (C3ST == 1 && TXST == 1) _muoManagTerms.set(187);
  if (C3ST == 2) _muoManagTerms.set(187);
  if (C3ST == 3) _muoManagTerms.set(187);
  if (N3ST == 1 && S3ST == 1) _muoManagTerms.set(187);
  if (N3ST == 1 && OXST == 1) _muoManagTerms.set(187);
  if (N3ST == 1 && TXST == 1) _muoManagTerms.set(187);
  if (N3ST == 2) _muoManagTerms.set(187);
  if (N3ST == 3) _muoManagTerms.set(187);
  if (S3ST == 1 && OXST == 1) _muoManagTerms.set(187);
  if (S3ST == 1 && TXST == 1) _muoManagTerms.set(187);
  if (S3ST == 2) _muoManagTerms.set(187);
  if (S3ST == 3) _muoManagTerms.set(187);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(187);
  if (OXST == 2) _muoManagTerms.set(187);
  if (OXST == 3) _muoManagTerms.set(187);
  if (TXST == 2) _muoManagTerms.set(187);
  if (TXST == 3) _muoManagTerms.set(187);

  // mtm 188
  //mu2pt6atxx 
  if (C4ST == 1 && N4ST == 1) _muoManagTerms.set(188);
  if (C4ST == 1 && S4ST == 1) _muoManagTerms.set(188);
  if (C4ST == 1 && OXST == 1) _muoManagTerms.set(188);
  if (C4ST == 1 && TXST == 1) _muoManagTerms.set(188);
  if (C4ST == 2) _muoManagTerms.set(188);
  if (C4ST == 3) _muoManagTerms.set(188);
  if (N4ST == 1 && S4ST == 1) _muoManagTerms.set(188);
  if (N4ST == 1 && OXST == 1) _muoManagTerms.set(188);
  if (N4ST == 1 && TXST == 1) _muoManagTerms.set(188);
  if (N4ST == 2) _muoManagTerms.set(188);
  if (N4ST == 3) _muoManagTerms.set(188);
  if (S4ST == 1 && OXST == 1) _muoManagTerms.set(188);
  if (S4ST == 1 && TXST == 1) _muoManagTerms.set(188);
  if (S4ST == 2) _muoManagTerms.set(188);
  if (S4ST == 3) _muoManagTerms.set(188);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(188);
  if (OXST == 2) _muoManagTerms.set(188);
  if (OXST == 3) _muoManagTerms.set(188);
  if (TXST == 2) _muoManagTerms.set(188);
  if (TXST == 3) _muoManagTerms.set(188);

  // mtm 189
  //mu2pt8atxx 
  if (C5ST == 1 && N5ST == 1) _muoManagTerms.set(189);
  if (C5ST == 1 && S5ST == 1) _muoManagTerms.set(189);
  if (C5ST == 1 && OXST == 1) _muoManagTerms.set(189);
  if (C5ST == 1 && TXST == 1) _muoManagTerms.set(189);
  if (C5ST == 2) _muoManagTerms.set(189);
  if (C5ST == 3) _muoManagTerms.set(189);
  if (N5ST == 1 && S5ST == 1) _muoManagTerms.set(189);
  if (N5ST == 1 && OXST == 1) _muoManagTerms.set(189);
  if (N5ST == 1 && TXST == 1) _muoManagTerms.set(189);
  if (N5ST == 2) _muoManagTerms.set(189);
  if (N5ST == 3) _muoManagTerms.set(189);
  if (S5ST == 1 && OXST == 1) _muoManagTerms.set(189);
  if (S5ST == 1 && TXST == 1) _muoManagTerms.set(189);
  if (S5ST == 2) _muoManagTerms.set(189);
  if (S5ST == 3) _muoManagTerms.set(189);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(189);
  if (OXST == 2) _muoManagTerms.set(189);
  if (OXST == 3) _muoManagTerms.set(189);
  if (TXST == 2) _muoManagTerms.set(189);
  if (TXST == 3) _muoManagTerms.set(189);

  // mtm 190
  //mu2p13atxx 
  if (C6ST == 1 && N6ST == 1) _muoManagTerms.set(190);
  if (C6ST == 1 && S6ST == 1) _muoManagTerms.set(190);
  if (C6ST == 1 && OXST == 1) _muoManagTerms.set(190);
  if (C6ST == 1 && TXST == 1) _muoManagTerms.set(190);
  if (C6ST == 2) _muoManagTerms.set(190);
  if (C6ST == 3) _muoManagTerms.set(190);
  if (N6ST == 1 && S6ST == 1) _muoManagTerms.set(190);
  if (N6ST == 1 && OXST == 1) _muoManagTerms.set(190);
  if (N6ST == 1 && TXST == 1) _muoManagTerms.set(190);
  if (N6ST == 2) _muoManagTerms.set(190);
  if (N6ST == 3) _muoManagTerms.set(190);
  if (S6ST == 1 && OXST == 1) _muoManagTerms.set(190);
  if (S6ST == 1 && TXST == 1) _muoManagTerms.set(190);
  if (S6ST == 2) _muoManagTerms.set(190);
  if (S6ST == 3) _muoManagTerms.set(190);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(190);
  if (OXST == 2) _muoManagTerms.set(190);
  if (OXST == 3) _muoManagTerms.set(190);
  if (TXST == 2) _muoManagTerms.set(190);
  if (TXST == 3) _muoManagTerms.set(190);

  // mtm 191
  //mu2ptxatxx 
  if (CXST == 1 && NXST == 1) _muoManagTerms.set(191);
  if (CXST == 1 && SXST == 1) _muoManagTerms.set(191);
  if (CXST == 1 && OXST == 1) _muoManagTerms.set(191);
  if (CXST == 1 && TXST == 1) _muoManagTerms.set(191);
  if (CXST == 2) _muoManagTerms.set(191);
  if (CXST == 3) _muoManagTerms.set(191);
  if (NXST == 1 && SXST == 1) _muoManagTerms.set(191);
  if (NXST == 1 && OXST == 1) _muoManagTerms.set(191);
  if (NXST == 1 && TXST == 1) _muoManagTerms.set(191);
  if (NXST == 2) _muoManagTerms.set(191);
  if (NXST == 3) _muoManagTerms.set(191);
  if (SXST == 1 && OXST == 1) _muoManagTerms.set(191);
  if (SXST == 1 && TXST == 1) _muoManagTerms.set(191);
  if (SXST == 2) _muoManagTerms.set(191);
  if (SXST == 3) _muoManagTerms.set(191);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(191);
  if (OXST == 2) _muoManagTerms.set(191);
  if (OXST == 3) _muoManagTerms.set(191);
  if (TXST == 2) _muoManagTerms.set(191);
  if (TXST == 3) _muoManagTerms.set(191);

  // mtm 192
  //mu2pt3atlx 
  if (C1TL == 1 && N1TL == 1) _muoManagTerms.set(192);
  if (C1TL == 1 && S1TL == 1) _muoManagTerms.set(192);
  if (C1TL == 1 && OXTL == 1) _muoManagTerms.set(192);
  if (C1TL == 1 && TXTL == 1) _muoManagTerms.set(192);
  if (C1TL == 2) _muoManagTerms.set(192);
  if (C1TL == 3) _muoManagTerms.set(192);
  if (N1TL == 1 && S1TL == 1) _muoManagTerms.set(192);
  if (N1TL == 1 && OXTL == 1) _muoManagTerms.set(192);
  if (N1TL == 1 && TXTL == 1) _muoManagTerms.set(192);
  if (N1TL == 2) _muoManagTerms.set(192);
  if (N1TL == 3) _muoManagTerms.set(192);
  if (S1TL == 1 && OXTL == 1) _muoManagTerms.set(192);
  if (S1TL == 1 && TXTL == 1) _muoManagTerms.set(192);
  if (S1TL == 2) _muoManagTerms.set(192);
  if (S1TL == 3) _muoManagTerms.set(192);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(192);
  if (OXTL == 2) _muoManagTerms.set(192);
  if (OXTL == 3) _muoManagTerms.set(192);
  if (TXTL == 2) _muoManagTerms.set(192);
  if (TXTL == 3) _muoManagTerms.set(192);

  // mtm 193
  //mu2pt4atlx 
  if (C2TL == 1 && N2TL == 1) _muoManagTerms.set(193);
  if (C2TL == 1 && S2TL == 1) _muoManagTerms.set(193);
  if (C2TL == 1 && OXTL == 1) _muoManagTerms.set(193);
  if (C2TL == 1 && TXTL == 1) _muoManagTerms.set(193);
  if (C2TL == 2) _muoManagTerms.set(193);
  if (C2TL == 3) _muoManagTerms.set(193);
  if (N2TL == 1 && S2TL == 1) _muoManagTerms.set(193);
  if (N2TL == 1 && OXTL == 1) _muoManagTerms.set(193);
  if (N2TL == 1 && TXTL == 1) _muoManagTerms.set(193);
  if (N2TL == 2) _muoManagTerms.set(193);
  if (N2TL == 3) _muoManagTerms.set(193);
  if (S2TL == 1 && OXTL == 1) _muoManagTerms.set(193);
  if (S2TL == 1 && TXTL == 1) _muoManagTerms.set(193);
  if (S2TL == 2) _muoManagTerms.set(193);
  if (S2TL == 3) _muoManagTerms.set(193);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(193);
  if (OXTL == 2) _muoManagTerms.set(193);
  if (OXTL == 3) _muoManagTerms.set(193);
  if (TXTL == 2) _muoManagTerms.set(193);
  if (TXTL == 3) _muoManagTerms.set(193);

  // mtm 194
  //mu2pt5atlx 
  if (C3TL == 1 && N3TL == 1) _muoManagTerms.set(194);
  if (C3TL == 1 && S3TL == 1) _muoManagTerms.set(194);
  if (C3TL == 1 && OXTL == 1) _muoManagTerms.set(194);
  if (C3TL == 1 && TXTL == 1) _muoManagTerms.set(194);
  if (C3TL == 2) _muoManagTerms.set(194);
  if (C3TL == 3) _muoManagTerms.set(194);
  if (N3TL == 1 && S3TL == 1) _muoManagTerms.set(194);
  if (N3TL == 1 && OXTL == 1) _muoManagTerms.set(194);
  if (N3TL == 1 && TXTL == 1) _muoManagTerms.set(194);
  if (N3TL == 2) _muoManagTerms.set(194);
  if (N3TL == 3) _muoManagTerms.set(194);
  if (S3TL == 1 && OXTL == 1) _muoManagTerms.set(194);
  if (S3TL == 1 && TXTL == 1) _muoManagTerms.set(194);
  if (S3TL == 2) _muoManagTerms.set(194);
  if (S3TL == 3) _muoManagTerms.set(194);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(194);
  if (OXTL == 2) _muoManagTerms.set(194);
  if (OXTL == 3) _muoManagTerms.set(194);
  if (TXTL == 2) _muoManagTerms.set(194);
  if (TXTL == 3) _muoManagTerms.set(194);

  // mtm 195
  //mu2pt6atlx 
  if (C4TL == 1 && N4TL == 1) _muoManagTerms.set(195);
  if (C4TL == 1 && S4TL == 1) _muoManagTerms.set(195);
  if (C4TL == 1 && OXTL == 1) _muoManagTerms.set(195);
  if (C4TL == 1 && TXTL == 1) _muoManagTerms.set(195);
  if (C4TL == 2) _muoManagTerms.set(195);
  if (C4TL == 3) _muoManagTerms.set(195);
  if (N4TL == 1 && S4TL == 1) _muoManagTerms.set(195);
  if (N4TL == 1 && OXTL == 1) _muoManagTerms.set(195);
  if (N4TL == 1 && TXTL == 1) _muoManagTerms.set(195);
  if (N4TL == 2) _muoManagTerms.set(195);
  if (N4TL == 3) _muoManagTerms.set(195);
  if (S4TL == 1 && OXTL == 1) _muoManagTerms.set(195);
  if (S4TL == 1 && TXTL == 1) _muoManagTerms.set(195);
  if (S4TL == 2) _muoManagTerms.set(195);
  if (S4TL == 3) _muoManagTerms.set(195);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(195);
  if (OXTL == 2) _muoManagTerms.set(195);
  if (OXTL == 3) _muoManagTerms.set(195);
  if (TXTL == 2) _muoManagTerms.set(195);
  if (TXTL == 3) _muoManagTerms.set(195);

  // mtm 196
  //mu2pt8atlx 
  if (C5TL == 1 && N5TL == 1) _muoManagTerms.set(196);
  if (C5TL == 1 && S5TL == 1) _muoManagTerms.set(196);
  if (C5TL == 1 && OXTL == 1) _muoManagTerms.set(196);
  if (C5TL == 1 && TXTL == 1) _muoManagTerms.set(196);
  if (C5TL == 2) _muoManagTerms.set(196);
  if (C5TL == 3) _muoManagTerms.set(196);
  if (N5TL == 1 && S5TL == 1) _muoManagTerms.set(196);
  if (N5TL == 1 && OXTL == 1) _muoManagTerms.set(196);
  if (N5TL == 1 && TXTL == 1) _muoManagTerms.set(196);
  if (N5TL == 2) _muoManagTerms.set(196);
  if (N5TL == 3) _muoManagTerms.set(196);
  if (S5TL == 1 && OXTL == 1) _muoManagTerms.set(196);
  if (S5TL == 1 && TXTL == 1) _muoManagTerms.set(196);
  if (S5TL == 2) _muoManagTerms.set(196);
  if (S5TL == 3) _muoManagTerms.set(196);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(196);
  if (OXTL == 2) _muoManagTerms.set(196);
  if (OXTL == 3) _muoManagTerms.set(196);
  if (TXTL == 2) _muoManagTerms.set(196);
  if (TXTL == 3) _muoManagTerms.set(196);

  // mtm 197
  //mu2p13atlx 
  if (C6TL == 1 && N6TL == 1) _muoManagTerms.set(197);
  if (C6TL == 1 && S6TL == 1) _muoManagTerms.set(197);
  if (C6TL == 1 && OXTL == 1) _muoManagTerms.set(197);
  if (C6TL == 1 && TXTL == 1) _muoManagTerms.set(197);
  if (C6TL == 2) _muoManagTerms.set(197);
  if (C6TL == 3) _muoManagTerms.set(197);
  if (N6TL == 1 && S6TL == 1) _muoManagTerms.set(197);
  if (N6TL == 1 && OXTL == 1) _muoManagTerms.set(197);
  if (N6TL == 1 && TXTL == 1) _muoManagTerms.set(197);
  if (N6TL == 2) _muoManagTerms.set(197);
  if (N6TL == 3) _muoManagTerms.set(197);
  if (S6TL == 1 && OXTL == 1) _muoManagTerms.set(197);
  if (S6TL == 1 && TXTL == 1) _muoManagTerms.set(197);
  if (S6TL == 2) _muoManagTerms.set(197);
  if (S6TL == 3) _muoManagTerms.set(197);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(197);
  if (OXTL == 2) _muoManagTerms.set(197);
  if (OXTL == 3) _muoManagTerms.set(197);
  if (TXTL == 2) _muoManagTerms.set(197);
  if (TXTL == 3) _muoManagTerms.set(197);

  // mtm 198
  //mu2ptxatlx 
  if (CXTL == 1 && NXTL == 1) _muoManagTerms.set(198);
  if (CXTL == 1 && SXTL == 1) _muoManagTerms.set(198);
  if (CXTL == 1 && OXTL == 1) _muoManagTerms.set(198);
  if (CXTL == 1 && TXTL == 1) _muoManagTerms.set(198);
  if (CXTL == 2) _muoManagTerms.set(198);
  if (CXTL == 3) _muoManagTerms.set(198);
  if (NXTL == 1 && SXTL == 1) _muoManagTerms.set(198);
  if (NXTL == 1 && OXTL == 1) _muoManagTerms.set(198);
  if (NXTL == 1 && TXTL == 1) _muoManagTerms.set(198);
  if (NXTL == 2) _muoManagTerms.set(198);
  if (NXTL == 3) _muoManagTerms.set(198);
  if (SXTL == 1 && OXTL == 1) _muoManagTerms.set(198);
  if (SXTL == 1 && TXTL == 1) _muoManagTerms.set(198);
  if (SXTL == 2) _muoManagTerms.set(198);
  if (SXTL == 3) _muoManagTerms.set(198);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(198);
  if (OXTL == 2) _muoManagTerms.set(198);
  if (OXTL == 3) _muoManagTerms.set(198);
  if (TXTL == 2) _muoManagTerms.set(198);
  if (TXTL == 3) _muoManagTerms.set(198);

  // mtm 199
  //mu2pt3attx 
  if (C1TT == 1 && N1TT == 1) _muoManagTerms.set(199);
  if (C1TT == 1 && S1TT == 1) _muoManagTerms.set(199);
  if (C1TT == 1 && OXTT == 1) _muoManagTerms.set(199);
  if (C1TT == 1 && TXTT == 1) _muoManagTerms.set(199);
  if (C1TT == 2) _muoManagTerms.set(199);
  if (C1TT == 3) _muoManagTerms.set(199);
  if (N1TT == 1 && S1TT == 1) _muoManagTerms.set(199);
  if (N1TT == 1 && OXTT == 1) _muoManagTerms.set(199);
  if (N1TT == 1 && TXTT == 1) _muoManagTerms.set(199);
  if (N1TT == 2) _muoManagTerms.set(199);
  if (N1TT == 3) _muoManagTerms.set(199);
  if (S1TT == 1 && OXTT == 1) _muoManagTerms.set(199);
  if (S1TT == 1 && TXTT == 1) _muoManagTerms.set(199);
  if (S1TT == 2) _muoManagTerms.set(199);
  if (S1TT == 3) _muoManagTerms.set(199);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(199);
  if (OXTT == 2) _muoManagTerms.set(199);
  if (OXTT == 3) _muoManagTerms.set(199);
  if (TXTT == 2) _muoManagTerms.set(199);
  if (TXTT == 3) _muoManagTerms.set(199);

  // mtm 200
  //mu2pt4attx 
  if (C2TT == 1 && N2TT == 1) _muoManagTerms.set(200);
  if (C2TT == 1 && S2TT == 1) _muoManagTerms.set(200);
  if (C2TT == 1 && OXTT == 1) _muoManagTerms.set(200);
  if (C2TT == 1 && TXTT == 1) _muoManagTerms.set(200);
  if (C2TT == 2) _muoManagTerms.set(200);
  if (C2TT == 3) _muoManagTerms.set(200);
  if (N2TT == 1 && S2TT == 1) _muoManagTerms.set(200);
  if (N2TT == 1 && OXTT == 1) _muoManagTerms.set(200);
  if (N2TT == 1 && TXTT == 1) _muoManagTerms.set(200);
  if (N2TT == 2) _muoManagTerms.set(200);
  if (N2TT == 3) _muoManagTerms.set(200);
  if (S2TT == 1 && OXTT == 1) _muoManagTerms.set(200);
  if (S2TT == 1 && TXTT == 1) _muoManagTerms.set(200);
  if (S2TT == 2) _muoManagTerms.set(200);
  if (S2TT == 3) _muoManagTerms.set(200);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(200);
  if (OXTT == 2) _muoManagTerms.set(200);
  if (OXTT == 3) _muoManagTerms.set(200);
  if (TXTT == 2) _muoManagTerms.set(200);
  if (TXTT == 3) _muoManagTerms.set(200);

  // mtm 201
  //mu2pt5attx 
  if (C3TT == 1 && N3TT == 1) _muoManagTerms.set(201);
  if (C3TT == 1 && S3TT == 1) _muoManagTerms.set(201);
  if (C3TT == 1 && OXTT == 1) _muoManagTerms.set(201);
  if (C3TT == 1 && TXTT == 1) _muoManagTerms.set(201);
  if (C3TT == 2) _muoManagTerms.set(201);
  if (C3TT == 3) _muoManagTerms.set(201);
  if (N3TT == 1 && S3TT == 1) _muoManagTerms.set(201);
  if (N3TT == 1 && OXTT == 1) _muoManagTerms.set(201);
  if (N3TT == 1 && TXTT == 1) _muoManagTerms.set(201);
  if (N3TT == 2) _muoManagTerms.set(201);
  if (N3TT == 3) _muoManagTerms.set(201);
  if (S3TT == 1 && OXTT == 1) _muoManagTerms.set(201);
  if (S3TT == 1 && TXTT == 1) _muoManagTerms.set(201);
  if (S3TT == 2) _muoManagTerms.set(201);
  if (S3TT == 3) _muoManagTerms.set(201);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(201);
  if (OXTT == 2) _muoManagTerms.set(201);
  if (OXTT == 3) _muoManagTerms.set(201);
  if (TXTT == 2) _muoManagTerms.set(201);
  if (TXTT == 3) _muoManagTerms.set(201);

  // mtm 202
  //mu2pt6attx 
  if (C4TT == 1 && N4TT == 1) _muoManagTerms.set(202);
  if (C4TT == 1 && S4TT == 1) _muoManagTerms.set(202);
  if (C4TT == 1 && OXTT == 1) _muoManagTerms.set(202);
  if (C4TT == 1 && TXTT == 1) _muoManagTerms.set(202);
  if (C4TT == 2) _muoManagTerms.set(202);
  if (C4TT == 3) _muoManagTerms.set(202);
  if (N4TT == 1 && S4TT == 1) _muoManagTerms.set(202);
  if (N4TT == 1 && OXTT == 1) _muoManagTerms.set(202);
  if (N4TT == 1 && TXTT == 1) _muoManagTerms.set(202);
  if (N4TT == 2) _muoManagTerms.set(202);
  if (N4TT == 3) _muoManagTerms.set(202);
  if (S4TT == 1 && OXTT == 1) _muoManagTerms.set(202);
  if (S4TT == 1 && TXTT == 1) _muoManagTerms.set(202);
  if (S4TT == 2) _muoManagTerms.set(202);
  if (S4TT == 3) _muoManagTerms.set(202);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(202);
  if (OXTT == 2) _muoManagTerms.set(202);
  if (OXTT == 3) _muoManagTerms.set(202);
  if (TXTT == 2) _muoManagTerms.set(202);
  if (TXTT == 3) _muoManagTerms.set(202);

  // mtm 203
  //mu2pt8attx 
  if (C5TT == 1 && N5TT == 1) _muoManagTerms.set(203);
  if (C5TT == 1 && S5TT == 1) _muoManagTerms.set(203);
  if (C5TT == 1 && OXTT == 1) _muoManagTerms.set(203);
  if (C5TT == 1 && TXTT == 1) _muoManagTerms.set(203);
  if (C5TT == 2) _muoManagTerms.set(203);
  if (C5TT == 3) _muoManagTerms.set(203);
  if (N5TT == 1 && S5TT == 1) _muoManagTerms.set(203);
  if (N5TT == 1 && OXTT == 1) _muoManagTerms.set(203);
  if (N5TT == 1 && TXTT == 1) _muoManagTerms.set(203);
  if (N5TT == 2) _muoManagTerms.set(203);
  if (N5TT == 3) _muoManagTerms.set(203);
  if (S5TT == 1 && OXTT == 1) _muoManagTerms.set(203);
  if (S5TT == 1 && TXTT == 1) _muoManagTerms.set(203);
  if (S5TT == 2) _muoManagTerms.set(203);
  if (S5TT == 3) _muoManagTerms.set(203);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(203);
  if (OXTT == 2) _muoManagTerms.set(203);
  if (OXTT == 3) _muoManagTerms.set(203);
  if (TXTT == 2) _muoManagTerms.set(203);
  if (TXTT == 3) _muoManagTerms.set(203);

  // mtm 204
  //mu2p13attx 
  if (C6TT == 1 && N6TT == 1) _muoManagTerms.set(204);
  if (C6TT == 1 && S6TT == 1) _muoManagTerms.set(204);
  if (C6TT == 1 && OXTT == 1) _muoManagTerms.set(204);
  if (C6TT == 1 && TXTT == 1) _muoManagTerms.set(204);
  if (C6TT == 2) _muoManagTerms.set(204);
  if (C6TT == 3) _muoManagTerms.set(204);
  if (N6TT == 1 && S6TT == 1) _muoManagTerms.set(204);
  if (N6TT == 1 && OXTT == 1) _muoManagTerms.set(204);
  if (N6TT == 1 && TXTT == 1) _muoManagTerms.set(204);
  if (N6TT == 2) _muoManagTerms.set(204);
  if (N6TT == 3) _muoManagTerms.set(204);
  if (S6TT == 1 && OXTT == 1) _muoManagTerms.set(204);
  if (S6TT == 1 && TXTT == 1) _muoManagTerms.set(204);
  if (S6TT == 2) _muoManagTerms.set(204);
  if (S6TT == 3) _muoManagTerms.set(204);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(204);
  if (OXTT == 2) _muoManagTerms.set(204);
  if (OXTT == 3) _muoManagTerms.set(204);
  if (TXTT == 2) _muoManagTerms.set(204);
  if (TXTT == 3) _muoManagTerms.set(204);

  // mtm 205
  //mu2ptxattx 
  if (CXTT == 1 && NXTT == 1) _muoManagTerms.set(205);
  if (CXTT == 1 && SXTT == 1) _muoManagTerms.set(205);
  if (CXTT == 1 && OXTT == 1) _muoManagTerms.set(205);
  if (CXTT == 1 && TXTT == 1) _muoManagTerms.set(205);
  if (CXTT == 2) _muoManagTerms.set(205);
  if (CXTT == 3) _muoManagTerms.set(205);
  if (NXTT == 1 && SXTT == 1) _muoManagTerms.set(205);
  if (NXTT == 1 && OXTT == 1) _muoManagTerms.set(205);
  if (NXTT == 1 && TXTT == 1) _muoManagTerms.set(205);
  if (NXTT == 2) _muoManagTerms.set(205);
  if (NXTT == 3) _muoManagTerms.set(205);
  if (SXTT == 1 && OXTT == 1) _muoManagTerms.set(205);
  if (SXTT == 1 && TXTT == 1) _muoManagTerms.set(205);
  if (SXTT == 2) _muoManagTerms.set(205);
  if (SXTT == 3) _muoManagTerms.set(205);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(205);
  if (OXTT == 2) _muoManagTerms.set(205);
  if (OXTT == 3) _muoManagTerms.set(205);
  if (TXTT == 2) _muoManagTerms.set(205);
  if (TXTT == 3) _muoManagTerms.set(205);

  // mtm 206
  //mu2pt3wlxx 
  if (C1SLP == 1 && C1SLN == 1) _muoManagTerms.set(206);
  if (C1SLP == 1 && N1SL == 1) _muoManagTerms.set(206);
  if (C1SLP == 1 && S1SL == 1) _muoManagTerms.set(206);
  if (C1SLP == 2) _muoManagTerms.set(206);
  if (C1SLP == 3) _muoManagTerms.set(206);
  if (C1SLN == 1 && N1SL == 1) _muoManagTerms.set(206);
  if (C1SLN == 1 && S1SL == 1) _muoManagTerms.set(206);
  if (C1SLN == 2) _muoManagTerms.set(206);
  if (C1SLN == 3) _muoManagTerms.set(206);
  if (N1SL == 1 && S1SL == 1) _muoManagTerms.set(206);
  if (N1SL == 2) _muoManagTerms.set(206);
  if (N1SL == 3) _muoManagTerms.set(206);
  if (S1SL == 2) _muoManagTerms.set(206);
  if (S1SL == 3) _muoManagTerms.set(206);

  // mtm 207
  //mu2ptxwlxx 
  if (CXSL == 1 && NXSL == 1) _muoManagTerms.set(207);
  if (CXSL == 1 && SXSL == 1) _muoManagTerms.set(207);
  if (CXSL == 2) _muoManagTerms.set(207);
  if (CXSL == 3) _muoManagTerms.set(207);
  if (NXSL == 1 && SXSL == 1) _muoManagTerms.set(207);
  if (NXSL == 2) _muoManagTerms.set(207);
  if (NXSL == 3) _muoManagTerms.set(207);
  if (SXSL == 2) _muoManagTerms.set(207);
  if (SXSL == 3) _muoManagTerms.set(207);

  // mtm 208
  //mu1ptxbtxw
  if (NXST>0 || SXST>0) _muoManagTerms.set(208);


  // mtm 209
  //mu2ptxwllx 
  if (CXLL == 1 && NXLL == 1) _muoManagTerms.set(209);
  if (CXLL == 1 && SXLL == 1) _muoManagTerms.set(209);
  if (CXLL == 2) _muoManagTerms.set(209);
  if (CXLL == 3) _muoManagTerms.set(209);
  if (NXLL == 1 && SXLL == 1) _muoManagTerms.set(209);
  if (NXLL == 2) _muoManagTerms.set(209);
  if (NXLL == 3) _muoManagTerms.set(209);
  if (SXLL == 2) _muoManagTerms.set(209);
  if (SXLL == 3) _muoManagTerms.set(209);

  // mtm 210
  //mu2pt3alxx 
  if (C1SLP == 1 && C1SLN == 1) _muoManagTerms.set(210);
  if (C1SLP == 1 && N1SL == 1) _muoManagTerms.set(210);
  if (C1SLP == 1 && S1SL == 1) _muoManagTerms.set(210);
  if (C1SLP == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (C1SLP == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (C1SLP == 2) _muoManagTerms.set(210);
  if (C1SLP == 3) _muoManagTerms.set(210);
  if (C1SLN == 1 && N1SL == 1) _muoManagTerms.set(210);
  if (C1SLN == 1 && S1SL == 1) _muoManagTerms.set(210);
  if (C1SLN == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (C1SLN == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (C1SLN == 2) _muoManagTerms.set(210);
  if (C1SLN == 3) _muoManagTerms.set(210);
  if (N1SL == 1 && S1SL == 1) _muoManagTerms.set(210);
  if (N1SL == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (N1SL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (N1SL == 2) _muoManagTerms.set(210);
  if (N1SL == 3) _muoManagTerms.set(210);
  if (S1SL == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (S1SL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (S1SL == 2) _muoManagTerms.set(210);
  if (S1SL == 3) _muoManagTerms.set(210);
  if (OXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (OXSL == 2) _muoManagTerms.set(210);
  if (OXSL == 3) _muoManagTerms.set(210);
  if (SXSL == 2) _muoManagTerms.set(210);
  if (SXSL == 3) _muoManagTerms.set(210);

  // mtm 211
  //mu2ptxalxx 
  if (CXSL == 1 && NXSL == 1) _muoManagTerms.set(210);
  if (CXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (CXSL == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (CXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (CXSL == 2) _muoManagTerms.set(210);
  if (CXSL == 3) _muoManagTerms.set(210);
  if (NXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (NXSL == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (NXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (NXSL == 2) _muoManagTerms.set(210);
  if (NXSL == 3) _muoManagTerms.set(210);
  if (SXSL == 1 && OXSL == 1) _muoManagTerms.set(210);
  if (SXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (SXSL == 2) _muoManagTerms.set(210);
  if (SXSL == 3) _muoManagTerms.set(210);
  if (OXSL == 1 && SXSL == 1) _muoManagTerms.set(210);
  if (OXSL == 2) _muoManagTerms.set(210);
  if (OXSL == 3) _muoManagTerms.set(210);
  if (SXSL == 2) _muoManagTerms.set(210);
  if (SXSL == 3) _muoManagTerms.set(210);

  // mtm 211
  //mu2ptxallx 
  if (CXLL == 1 && NXLL == 1) _muoManagTerms.set(211);
  if (CXLL == 1 && SXLL == 1) _muoManagTerms.set(211);
  if (CXLL == 1 && OXLL == 1) _muoManagTerms.set(211);
  if (CXLL == 1 && TXLL == 1) _muoManagTerms.set(211);
  if (CXLL == 2) _muoManagTerms.set(211);
  if (CXLL == 3) _muoManagTerms.set(211);
  if (NXLL == 1 && SXLL == 1) _muoManagTerms.set(211);
  if (NXLL == 1 && OXLL == 1) _muoManagTerms.set(211);
  if (NXLL == 1 && TXLL == 1) _muoManagTerms.set(211);
  if (NXLL == 2) _muoManagTerms.set(211);
  if (NXLL == 3) _muoManagTerms.set(211);
  if (SXLL == 1 && OXLL == 1) _muoManagTerms.set(211);
  if (SXLL == 1 && TXLL == 1) _muoManagTerms.set(211);
  if (SXLL == 2) _muoManagTerms.set(211);
  if (SXLL == 3) _muoManagTerms.set(211);
  if (OXLL == 1 && TXLL == 1) _muoManagTerms.set(211);
  if (OXLL == 2) _muoManagTerms.set(211);
  if (OXLL == 3) _muoManagTerms.set(211);
  if (TXLL == 2) _muoManagTerms.set(211);
  if (TXLL == 3) _muoManagTerms.set(211);

  // mtm 212
  //mu2pt3btxx 
  if (N1ST == 1 && S1ST == 1) _muoManagTerms.set(212);
  if (N1ST == 1 && OXST == 1) _muoManagTerms.set(212);
  if (N1ST == 1 && TXST == 1) _muoManagTerms.set(212);
  if (N1ST == 2) _muoManagTerms.set(212);
  if (N1ST == 3) _muoManagTerms.set(212);
  if (S1ST == 1 && OXST == 1) _muoManagTerms.set(212);
  if (S1ST == 1 && TXST == 1) _muoManagTerms.set(212);
  if (S1ST == 2) _muoManagTerms.set(212);
  if (S1ST == 3) _muoManagTerms.set(212);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(212);
  if (OXST == 2) _muoManagTerms.set(212);
  if (OXST == 3) _muoManagTerms.set(212);
  if (TXST == 2) _muoManagTerms.set(212);
  if (TXST == 3) _muoManagTerms.set(212);

  // mtm 213
  //mu2pt4btxx 
  if (N2ST == 1 && S2ST == 1) _muoManagTerms.set(213);
  if (N2ST == 1 && OXST == 1) _muoManagTerms.set(213);
  if (N2ST == 1 && TXST == 1) _muoManagTerms.set(213);
  if (N2ST == 2) _muoManagTerms.set(213);
  if (N2ST == 3) _muoManagTerms.set(213);
  if (S2ST == 1 && OXST == 1) _muoManagTerms.set(213);
  if (S2ST == 1 && TXST == 1) _muoManagTerms.set(213);
  if (S2ST == 2) _muoManagTerms.set(213);
  if (S2ST == 3) _muoManagTerms.set(213);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(213);
  if (OXST == 2) _muoManagTerms.set(213);
  if (OXST == 3) _muoManagTerms.set(213);
  if (TXST == 2) _muoManagTerms.set(213);
  if (TXST == 3) _muoManagTerms.set(213);

  // mtm 214
  //mu2pt5btxx 
  if (N3ST == 1 && S3ST == 1) _muoManagTerms.set(214);
  if (N3ST == 1 && OXST == 1) _muoManagTerms.set(214);
  if (N3ST == 1 && TXST == 1) _muoManagTerms.set(214);
  if (N3ST == 2) _muoManagTerms.set(214);
  if (N3ST == 3) _muoManagTerms.set(214);
  if (S3ST == 1 && OXST == 1) _muoManagTerms.set(214);
  if (S3ST == 1 && TXST == 1) _muoManagTerms.set(214);
  if (S3ST == 2) _muoManagTerms.set(214);
  if (S3ST == 3) _muoManagTerms.set(214);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(214);
  if (OXST == 2) _muoManagTerms.set(214);
  if (OXST == 3) _muoManagTerms.set(214);
  if (TXST == 2) _muoManagTerms.set(214);
  if (TXST == 3) _muoManagTerms.set(214);

  // mtm 215
  //mu2pt6btxx 
  if (N4ST == 1 && S4ST == 1) _muoManagTerms.set(215);
  if (N4ST == 1 && OXST == 1) _muoManagTerms.set(215);
  if (N4ST == 1 && TXST == 1) _muoManagTerms.set(215);
  if (N4ST == 2) _muoManagTerms.set(215);
  if (N4ST == 3) _muoManagTerms.set(215);
  if (S4ST == 1 && OXST == 1) _muoManagTerms.set(215);
  if (S4ST == 1 && TXST == 1) _muoManagTerms.set(215);
  if (S4ST == 2) _muoManagTerms.set(215);
  if (S4ST == 3) _muoManagTerms.set(215);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(215);
  if (OXST == 2) _muoManagTerms.set(215);
  if (OXST == 3) _muoManagTerms.set(215);
  if (TXST == 2) _muoManagTerms.set(215);
  if (TXST == 3) _muoManagTerms.set(215);

  // mtm 216
  //mu2pt8btxx 
  if (N5ST == 1 && S5ST == 1) _muoManagTerms.set(216);
  if (N5ST == 1 && OXST == 1) _muoManagTerms.set(216);
  if (N5ST == 1 && TXST == 1) _muoManagTerms.set(216);
  if (N5ST == 2) _muoManagTerms.set(216);
  if (N5ST == 3) _muoManagTerms.set(216);
  if (S5ST == 1 && OXST == 1) _muoManagTerms.set(216);
  if (S5ST == 1 && TXST == 1) _muoManagTerms.set(216);
  if (S5ST == 2) _muoManagTerms.set(216);
  if (S5ST == 3) _muoManagTerms.set(216);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(216);
  if (OXST == 2) _muoManagTerms.set(216);
  if (OXST == 3) _muoManagTerms.set(216);
  if (TXST == 2) _muoManagTerms.set(216);
  if (TXST == 3) _muoManagTerms.set(216);

  // mtm 217
  //mu2p13btxx 
  if (N6ST == 1 && S6ST == 1) _muoManagTerms.set(217);
  if (N6ST == 1 && OXST == 1) _muoManagTerms.set(217);
  if (N6ST == 1 && TXST == 1) _muoManagTerms.set(217);
  if (N6ST == 2) _muoManagTerms.set(217);
  if (N6ST == 3) _muoManagTerms.set(217);
  if (S6ST == 1 && OXST == 1) _muoManagTerms.set(217);
  if (S6ST == 1 && TXST == 1) _muoManagTerms.set(217);
  if (S6ST == 2) _muoManagTerms.set(217);
  if (S6ST == 3) _muoManagTerms.set(217);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(217);
  if (OXST == 2) _muoManagTerms.set(217);
  if (OXST == 3) _muoManagTerms.set(217);
  if (TXST == 2) _muoManagTerms.set(217);
  if (TXST == 3) _muoManagTerms.set(217);

  // mtm 218
  //mu2ptxbtxx 
  if (NXST == 1 && SXST == 1) _muoManagTerms.set(218);
  if (NXST == 1 && OXST == 1) _muoManagTerms.set(218);
  if (NXST == 1 && TXST == 1) _muoManagTerms.set(218);
  if (NXST == 2) _muoManagTerms.set(218);
  if (NXST == 3) _muoManagTerms.set(218);
  if (SXST == 1 && OXST == 1) _muoManagTerms.set(218);
  if (SXST == 1 && TXST == 1) _muoManagTerms.set(218);
  if (SXST == 2) _muoManagTerms.set(218);
  if (SXST == 3) _muoManagTerms.set(218);
  if (OXST == 1 && TXST == 1) _muoManagTerms.set(218);
  if (OXST == 2) _muoManagTerms.set(218);
  if (OXST == 3) _muoManagTerms.set(218);
  if (TXST == 2) _muoManagTerms.set(218);
  if (TXST == 3) _muoManagTerms.set(218);

  // mtm 219
  //mu2pt3btlx 
  if (N1TL == 1 && S1TL == 1) _muoManagTerms.set(219);
  if (N1TL == 1 && OXTL == 1) _muoManagTerms.set(219);
  if (N1TL == 1 && TXTL == 1) _muoManagTerms.set(219);
  if (N1TL == 2) _muoManagTerms.set(219);
  if (N1TL == 3) _muoManagTerms.set(219);
  if (S1TL == 1 && OXTL == 1) _muoManagTerms.set(219);
  if (S1TL == 1 && TXTL == 1) _muoManagTerms.set(219);
  if (S1TL == 2) _muoManagTerms.set(219);
  if (S1TL == 3) _muoManagTerms.set(219);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(219);
  if (OXTL == 2) _muoManagTerms.set(219);
  if (OXTL == 3) _muoManagTerms.set(219);
  if (TXTL == 2) _muoManagTerms.set(219);
  if (TXTL == 3) _muoManagTerms.set(219);

  // mtm 220
  //mu2pt4btlx 
  if (N2TL == 1 && S2TL == 1) _muoManagTerms.set(220);
  if (N2TL == 1 && OXTL == 1) _muoManagTerms.set(220);
  if (N2TL == 1 && TXTL == 1) _muoManagTerms.set(220);
  if (N2TL == 2) _muoManagTerms.set(220);
  if (N2TL == 3) _muoManagTerms.set(220);
  if (S2TL == 1 && OXTL == 1) _muoManagTerms.set(220);
  if (S2TL == 1 && TXTL == 1) _muoManagTerms.set(220);
  if (S2TL == 2) _muoManagTerms.set(220);
  if (S2TL == 3) _muoManagTerms.set(220);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(220);
  if (OXTL == 2) _muoManagTerms.set(220);
  if (OXTL == 3) _muoManagTerms.set(220);
  if (TXTL == 2) _muoManagTerms.set(220);
  if (TXTL == 3) _muoManagTerms.set(220);

  // mtm 221
  //mu2pt5btlx 
  if (N3TL == 1 && S3TL == 1) _muoManagTerms.set(221);
  if (N3TL == 1 && OXTL == 1) _muoManagTerms.set(221);
  if (N3TL == 1 && TXTL == 1) _muoManagTerms.set(221);
  if (N3TL == 2) _muoManagTerms.set(221);
  if (N3TL == 3) _muoManagTerms.set(221);
  if (S3TL == 1 && OXTL == 1) _muoManagTerms.set(221);
  if (S3TL == 1 && TXTL == 1) _muoManagTerms.set(221);
  if (S3TL == 2) _muoManagTerms.set(221);
  if (S3TL == 3) _muoManagTerms.set(221);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(221);
  if (OXTL == 2) _muoManagTerms.set(221);
  if (OXTL == 3) _muoManagTerms.set(221);
  if (TXTL == 2) _muoManagTerms.set(221);
  if (TXTL == 3) _muoManagTerms.set(221);

  // mtm 222
  //mu2pt6btlx 
  if (N4TL == 1 && S4TL == 1) _muoManagTerms.set(222);
  if (N4TL == 1 && OXTL == 1) _muoManagTerms.set(222);
  if (N4TL == 1 && TXTL == 1) _muoManagTerms.set(222);
  if (N4TL == 2) _muoManagTerms.set(222);
  if (N4TL == 3) _muoManagTerms.set(222);
  if (S4TL == 1 && OXTL == 1) _muoManagTerms.set(222);
  if (S4TL == 1 && TXTL == 1) _muoManagTerms.set(222);
  if (S4TL == 2) _muoManagTerms.set(222);
  if (S4TL == 3) _muoManagTerms.set(222);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(222);
  if (OXTL == 2) _muoManagTerms.set(222);
  if (OXTL == 3) _muoManagTerms.set(222);
  if (TXTL == 2) _muoManagTerms.set(222);
  if (TXTL == 3) _muoManagTerms.set(222);

  // mtm 223
  //mu2pt8btlx 
  if (N5TL == 1 && S5TL == 1) _muoManagTerms.set(223);
  if (N5TL == 1 && OXTL == 1) _muoManagTerms.set(223);
  if (N5TL == 1 && TXTL == 1) _muoManagTerms.set(223);
  if (N5TL == 2) _muoManagTerms.set(223);
  if (N5TL == 3) _muoManagTerms.set(223);
  if (S5TL == 1 && OXTL == 1) _muoManagTerms.set(223);
  if (S5TL == 1 && TXTL == 1) _muoManagTerms.set(223);
  if (S5TL == 2) _muoManagTerms.set(223);
  if (S5TL == 3) _muoManagTerms.set(223);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(223);
  if (OXTL == 2) _muoManagTerms.set(223);
  if (OXTL == 3) _muoManagTerms.set(223);
  if (TXTL == 2) _muoManagTerms.set(223);
  if (TXTL == 3) _muoManagTerms.set(223);

  // mtm 224
  //mu2p13btlx 
  if (N6TL == 1 && S6TL == 1) _muoManagTerms.set(224);
  if (N6TL == 1 && OXTL == 1) _muoManagTerms.set(224);
  if (N6TL == 1 && TXTL == 1) _muoManagTerms.set(224);
  if (N6TL == 2) _muoManagTerms.set(224);
  if (N6TL == 3) _muoManagTerms.set(224);
  if (S6TL == 1 && OXTL == 1) _muoManagTerms.set(224);
  if (S6TL == 1 && TXTL == 1) _muoManagTerms.set(224);
  if (S6TL == 2) _muoManagTerms.set(224);
  if (S6TL == 3) _muoManagTerms.set(224);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(224);
  if (OXTL == 2) _muoManagTerms.set(224);
  if (OXTL == 3) _muoManagTerms.set(224);
  if (TXTL == 2) _muoManagTerms.set(224);
  if (TXTL == 3) _muoManagTerms.set(224);

  // mtm 225
  //mu2ptxbtlx 
  if (NXTL == 1 && SXTL == 1) _muoManagTerms.set(225);
  if (NXTL == 1 && OXTL == 1) _muoManagTerms.set(225);
  if (NXTL == 1 && TXTL == 1) _muoManagTerms.set(225);
  if (NXTL == 2) _muoManagTerms.set(225);
  if (NXTL == 3) _muoManagTerms.set(225);
  if (SXTL == 1 && OXTL == 1) _muoManagTerms.set(225);
  if (SXTL == 1 && TXTL == 1) _muoManagTerms.set(225);
  if (SXTL == 2) _muoManagTerms.set(225);
  if (SXTL == 3) _muoManagTerms.set(225);
  if (OXTL == 1 && TXTL == 1) _muoManagTerms.set(225);
  if (OXTL == 2) _muoManagTerms.set(225);
  if (OXTL == 3) _muoManagTerms.set(225);
  if (TXTL == 2) _muoManagTerms.set(225);
  if (TXTL == 3) _muoManagTerms.set(225);

  // mtm 226
  //mu2pt3bttx 
  if (N1TT == 1 && S1TT == 1) _muoManagTerms.set(226);
  if (N1TT == 1 && OXTT == 1) _muoManagTerms.set(226);
  if (N1TT == 1 && TXTT == 1) _muoManagTerms.set(226);
  if (N1TT == 2) _muoManagTerms.set(226);
  if (N1TT == 3) _muoManagTerms.set(226);
  if (S1TT == 1 && OXTT == 1) _muoManagTerms.set(226);
  if (S1TT == 1 && TXTT == 1) _muoManagTerms.set(226);
  if (S1TT == 2) _muoManagTerms.set(226);
  if (S1TT == 3) _muoManagTerms.set(226);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(226);
  if (OXTT == 2) _muoManagTerms.set(226);
  if (OXTT == 3) _muoManagTerms.set(226);
  if (TXTT == 2) _muoManagTerms.set(226);
  if (TXTT == 3) _muoManagTerms.set(226);

  // mtm 227
  //mu2pt4bttx 
  if (N2TT == 1 && S2TT == 1) _muoManagTerms.set(227);
  if (N2TT == 1 && OXTT == 1) _muoManagTerms.set(227);
  if (N2TT == 1 && TXTT == 1) _muoManagTerms.set(227);
  if (N2TT == 2) _muoManagTerms.set(227);
  if (N2TT == 3) _muoManagTerms.set(227);
  if (S2TT == 1 && OXTT == 1) _muoManagTerms.set(227);
  if (S2TT == 1 && TXTT == 1) _muoManagTerms.set(227);
  if (S2TT == 2) _muoManagTerms.set(227);
  if (S2TT == 3) _muoManagTerms.set(227);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(227);
  if (OXTT == 2) _muoManagTerms.set(227);
  if (OXTT == 3) _muoManagTerms.set(227);
  if (TXTT == 2) _muoManagTerms.set(227);
  if (TXTT == 3) _muoManagTerms.set(227);

  // mtm 228
  //mu2pt5bttx 
  if (N3TT == 1 && S3TT == 1) _muoManagTerms.set(228);
  if (N3TT == 1 && OXTT == 1) _muoManagTerms.set(228);
  if (N3TT == 1 && TXTT == 1) _muoManagTerms.set(228);
  if (N3TT == 2) _muoManagTerms.set(228);
  if (N3TT == 3) _muoManagTerms.set(228);
  if (S3TT == 1 && OXTT == 1) _muoManagTerms.set(228);
  if (S3TT == 1 && TXTT == 1) _muoManagTerms.set(228);
  if (S3TT == 2) _muoManagTerms.set(228);
  if (S3TT == 3) _muoManagTerms.set(228);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(228);
  if (OXTT == 2) _muoManagTerms.set(228);
  if (OXTT == 3) _muoManagTerms.set(228);
  if (TXTT == 2) _muoManagTerms.set(228);
  if (TXTT == 3) _muoManagTerms.set(228);

  // mtm 229
  //mu2pt6bttx 
  if (N4TT == 1 && S4TT == 1) _muoManagTerms.set(229);
  if (N4TT == 1 && OXTT == 1) _muoManagTerms.set(229);
  if (N4TT == 1 && TXTT == 1) _muoManagTerms.set(229);
  if (N4TT == 2) _muoManagTerms.set(229);
  if (N4TT == 3) _muoManagTerms.set(229);
  if (S4TT == 1 && OXTT == 1) _muoManagTerms.set(229);
  if (S4TT == 1 && TXTT == 1) _muoManagTerms.set(229);
  if (S4TT == 2) _muoManagTerms.set(229);
  if (S4TT == 3) _muoManagTerms.set(229);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(229);
  if (OXTT == 2) _muoManagTerms.set(229);
  if (OXTT == 3) _muoManagTerms.set(229);
  if (TXTT == 2) _muoManagTerms.set(229);
  if (TXTT == 3) _muoManagTerms.set(229);

  // mtm 230
  //mu2pt8bttx 
  if (N5TT == 1 && S5TT == 1) _muoManagTerms.set(230);
  if (N5TT == 1 && OXTT == 1) _muoManagTerms.set(230);
  if (N5TT == 1 && TXTT == 1) _muoManagTerms.set(230);
  if (N5TT == 2) _muoManagTerms.set(230);
  if (N5TT == 3) _muoManagTerms.set(230);
  if (S5TT == 1 && OXTT == 1) _muoManagTerms.set(230);
  if (S5TT == 1 && TXTT == 1) _muoManagTerms.set(230);
  if (S5TT == 2) _muoManagTerms.set(230);
  if (S5TT == 3) _muoManagTerms.set(230);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(230);
  if (OXTT == 2) _muoManagTerms.set(230);
  if (OXTT == 3) _muoManagTerms.set(230);
  if (TXTT == 2) _muoManagTerms.set(230);
  if (TXTT == 3) _muoManagTerms.set(230);

  // mtm 231
  //mu2p13bttx 
  if (N6TT == 1 && S6TT == 1) _muoManagTerms.set(231);
  if (N6TT == 1 && OXTT == 1) _muoManagTerms.set(231);
  if (N6TT == 1 && TXTT == 1) _muoManagTerms.set(231);
  if (N6TT == 2) _muoManagTerms.set(231);
  if (N6TT == 3) _muoManagTerms.set(231);
  if (S6TT == 1 && OXTT == 1) _muoManagTerms.set(231);
  if (S6TT == 1 && TXTT == 1) _muoManagTerms.set(231);
  if (S6TT == 2) _muoManagTerms.set(231);
  if (S6TT == 3) _muoManagTerms.set(231);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(231);
  if (OXTT == 2) _muoManagTerms.set(231);
  if (OXTT == 3) _muoManagTerms.set(231);
  if (TXTT == 2) _muoManagTerms.set(231);
  if (TXTT == 3) _muoManagTerms.set(231);

  // mtm 232
  //mu2ptxbttx 
  if (NXTT == 1 && SXTT == 1) _muoManagTerms.set(232);
  if (NXTT == 1 && OXTT == 1) _muoManagTerms.set(232);
  if (NXTT == 1 && TXTT == 1) _muoManagTerms.set(232);
  if (NXTT == 2) _muoManagTerms.set(232);
  if (NXTT == 3) _muoManagTerms.set(232);
  if (SXTT == 1 && OXTT == 1) _muoManagTerms.set(232);
  if (SXTT == 1 && TXTT == 1) _muoManagTerms.set(232);
  if (SXTT == 2) _muoManagTerms.set(232);
  if (SXTT == 3) _muoManagTerms.set(232);
  if (OXTT == 1 && TXTT == 1) _muoManagTerms.set(232);
  if (OXTT == 2) _muoManagTerms.set(232);
  if (OXTT == 3) _muoManagTerms.set(232);
  if (TXTT == 2) _muoManagTerms.set(232);
  if (TXTT == 3) _muoManagTerms.set(232);

  // mtm 233
  //mu1ptxblxx 
  if  (NXSL>0 || OXSL>0 || SXSL>0 || TXSL>0)  _muoManagTerms.set(233);

  // mtm 234
  //mu1ptxbllx 
  if  (NXLL>0 || OXLL>0 || SXLL>0 || TXLL>0)  _muoManagTerms.set(234);

  // mtm 235
  //mu2ptxblxx 
  if (NXSL == 1 && SXSL == 1) _muoManagTerms.set(235);
  if (NXSL == 1 && OXSL == 1) _muoManagTerms.set(235);
  if (NXSL == 1 && TXSL == 1) _muoManagTerms.set(235);
  if (NXSL == 2) _muoManagTerms.set(235);
  if (NXSL == 3) _muoManagTerms.set(235);
  if (SXSL == 1 && OXSL == 1) _muoManagTerms.set(235);
  if (SXSL == 1 && TXSL == 1) _muoManagTerms.set(235);
  if (SXSL == 2) _muoManagTerms.set(235);
  if (SXSL == 3) _muoManagTerms.set(235);
  if (OXSL == 1 && TXSL == 1) _muoManagTerms.set(235);
  if (OXSL == 2) _muoManagTerms.set(235);
  if (OXSL == 3) _muoManagTerms.set(235);
  if (TXSL == 2) _muoManagTerms.set(235);
  if (TXSL == 3) _muoManagTerms.set(235);

  // mtm 236
  //mu2ptxbllx 
  if (NXLL == 1 && SXLL == 1) _muoManagTerms.set(236);
  if (NXLL == 1 && OXLL == 1) _muoManagTerms.set(236);
  if (NXLL == 1 && TXLL == 1) _muoManagTerms.set(236);
  if (NXLL == 2) _muoManagTerms.set(236);
  if (NXLL == 3) _muoManagTerms.set(236);
  if (SXLL == 1 && OXLL == 1) _muoManagTerms.set(236);
  if (SXLL == 1 && TXLL == 1) _muoManagTerms.set(236);
  if (SXLL == 2) _muoManagTerms.set(236);
  if (SXLL == 3) _muoManagTerms.set(236);
  if (OXLL == 1 && TXLL == 1) _muoManagTerms.set(236);
  if (OXLL == 2) _muoManagTerms.set(236);
  if (OXLL == 3) _muoManagTerms.set(236);
  if (TXLL == 2) _muoManagTerms.set(236);
  if (TXLL == 3) _muoManagTerms.set(236);

  // mtm 237
  //mu1ptxcxlx 
  if  (CXWL>0)  _muoManagTerms.set(237);

  // mtm 238
  //mu2ptxcxlx 
  if  (CXWL>1)  _muoManagTerms.set(238);

  // mtm 239
  //mu1ptxcxtx 
  if  (CXWT>0)  _muoManagTerms.set(239);

  // mtm 240
  //mu2ptxcxtx 
  if  (CXWT>1)  _muoManagTerms.set(240);

  // mtm 241
  //mu1ptxbtlw
  if ((SXTL>0) || (NXTL>0)) _muoManagTerms.set(241);

  // mtm 242
  //mu2ptxbtlw
  if ((SXTL+NXTL)>1) _muoManagTerms.set(242);

  // mtm 243
  //mu1ptxbttw
  if ((SXTT>0) || (NXTT>0)) _muoManagTerms.set(243);


  // mtm 244
  //mu1ptxbttw
  if ((SXTT+NXTT)>1) _muoManagTerms.set(244);

  // mtm 245
  //mu2pt3clxo 
  if  (C1SLP>0 && C1SLN>0)  _muoManagTerms.set(245);

  // mtm 246
  //mu2pt4clxo 
  if  (C2SLP>0 && C2SLN>0)  _muoManagTerms.set(246);

  // mtm 247
  //mu2pt3cllo 
  if  (C1LLP>0 && C1LLN>0)  _muoManagTerms.set(247);

  // mtm 248
  //mu1ptxattt 
  if (CXSX == 1) _muoManagTerms.set(248);
  if (CXWX == 1) _muoManagTerms.set(248);
  if (NXSX == 1) _muoManagTerms.set(248);
  if (NXWX == 1) _muoManagTerms.set(248);
  if (SXSX == 1) _muoManagTerms.set(248);
  if (SXWX == 1) _muoManagTerms.set(248);

  // mtm 249
  //mu1ptxclxt 
  if  (CXSX == 1 || CXSX == 3)  _muoManagTerms.set(249);

  // mtm 250
  //mu1ptxcxlt 
  if  (CXWX == 1 || CXWX == 3)  _muoManagTerms.set(250);

  // mtm 251
  //mu1ptxplxt 
  if  (NXSX == 1 || NXSX == 3)  _muoManagTerms.set(251);

  // mtm 252
  //mu1ptxpxlt 
  if  (NXWX == 1 || NXWX ==3)  _muoManagTerms.set(252);

  // mtm 253
  //mu1ptxulxt 
  if  (SXSX == 1 || SXSX == 3)  _muoManagTerms.set(253);

  // mtm 254
  //mu1ptxuxlt 
  if  (SXWX == 1 || SXWX ==3)  _muoManagTerms.set(254);

  // mtm 255
  //mu1ptxallt 
  if (CXSX == 1 && CXWX == 1 && NXSX == 1 && NXWX == 1 && SXSX == 1 && SXWX == 1) _muoManagTerms.set(255);

  // Version 5 of the MTM simulator ends here. 
  return;
}

void L1MuTermsClass::fill_mtmRun2A() {
  // Build the 256 MTM triggers for Run2A.

  // Give names to the counters for easy identification.
  // We call these counters single system counters.
  int C1SLP      = _MTCCCounters[0];
  int C1SLN      = _MTCCCounters[1];
  int C2SLP      = _MTCCCounters[2];
  int C2SLN      = _MTCCCounters[3];
  int C3SL       = _MTCCCounters[4];
  int C4SL       = _MTCCCounters[5];
  int C2ST       = _MTCCCounters[6];
  int C3ST       = _MTCCCounters[7];
  int C4ST       = _MTCCCounters[8];
  int CXSL       = _MTCCCounters[9];
  int CXSC       = _MTCCCounters[10];
  int CXST       = _MTCCCounters[11];
  int C4XX       = _MTCCCounters[12];
  int CXSX       = _MTCCCounters[13];
  int CXWC       = _MTCCCounters[14];
  int CXWL       = _MTCCCounters[15];
  int CXWT       = _MTCCCounters[16];
  int CXWX       = _MTCCCounters[17];

  int N1SL       = _MTCNCounters[0];
  int N2SL       = _MTCNCounters[1];
  int N3SL       = _MTCNCounters[2];
  int N4SL       = _MTCNCounters[3];
  int N2ST       = _MTCNCounters[4];
  int N3ST       = _MTCNCounters[5];
  int N4ST       = _MTCNCounters[6];
  int NXSL       = _MTCNCounters[7];
  int OXSL       = _MTCNCounters[8];
  int NXST       = _MTCNCounters[9];
  int OXST       = _MTCNCounters[10];
  int NXSX       = _MTCNCounters[11];
  int NXWL       = _MTCNCounters[12];
  int OXWL       = _MTCNCounters[13];
  int NXWT       = _MTCNCounters[14];
  int OXWT       = _MTCNCounters[15];
  int NXWC       = _MTCNCounters[16];
  int NXWX       = _MTCNCounters[17];

  int S1SL       = _MTCSCounters[0];
  int S2SL       = _MTCSCounters[1];
  int S3SL       = _MTCSCounters[2];
  int S4SL       = _MTCSCounters[3];
  int S2ST       = _MTCSCounters[4];
  int S3ST       = _MTCSCounters[5];
  int S4ST       = _MTCSCounters[6];
  int SXSL       = _MTCSCounters[7];
  int TXSL       = _MTCSCounters[8];
  int SXST       = _MTCSCounters[9];
  int TXST       = _MTCSCounters[10];
  int SXSX       = _MTCSCounters[11];
  int SXWL       = _MTCSCounters[12];
  int TXWL       = _MTCSCounters[13];
  int SXWT       = _MTCSCounters[14];
  int TXWT       = _MTCSCounters[15];
  int SXWC       = _MTCSCounters[16];
  int SXWX       = _MTCSCounters[17];

  // New combined system counters.
  int C1LLP = _MTCCCounters[18];
  int C1LLN = _MTCCCounters[19];
  int C2LLP = _MTCCCounters[20]; 
  int C2LLN = _MTCCCounters[21];
  int C3LL = _MTCCCounters[22];
  int C4LL = _MTCCCounters[23];
  int CXLL = _MTCCCounters[24];
  int C2TT = _MTCCCounters[25];
  int C3TT = _MTCCCounters[26]; 
  int C4TT = _MTCCCounters[27];
  int CXTT = _MTCCCounters[28];
  int C2TL = _MTCCCounters[29];
  int C3TL = _MTCCCounters[30];
  int C4TL = _MTCCCounters[31];
  int CXTL = _MTCCCounters[32];
  int CSPARE0 = _MTCCCounters[33];
  int CSPARE1 = _MTCCCounters[34];
  int CSPARE2 = _MTCCCounters[35];

  int N1LL = _MTCNCounters[18];
  int N2LL = _MTCNCounters[19];
  int N3LL = _MTCNCounters[20];
  int N4LL = _MTCNCounters[21];
  int NXLL = _MTCNCounters[22];
  int N2TT = _MTCNCounters[23];
  int N3TT = _MTCNCounters[24];
  int N4TT = _MTCNCounters[25];
  int NXTT = _MTCNCounters[26];
  int N2TL = _MTCNCounters[27];
  int N3TL = _MTCNCounters[28];
  int N4TL = _MTCNCounters[29];
  int NXTL = _MTCNCounters[30];
  int OXLL = _MTCNCounters[31];
  int OXTT = _MTCNCounters[32];
  int OXTL = _MTCNCounters[33];
  int NSPARE0 = _MTCNCounters[34];
  int NSPARE1 = _MTCNCounters[35];

  int S1LL  = _MTCSCounters[18];
  int S2LL  = _MTCSCounters[19];
  int S3LL  = _MTCSCounters[20];
  int S4LL  = _MTCSCounters[21];
  int SXLL  = _MTCSCounters[22];
  int S2TT  = _MTCSCounters[23];
  int S3TT  = _MTCSCounters[24];
  int S4TT  = _MTCSCounters[25];
  int SXTT  = _MTCSCounters[26];
  int S2TL  = _MTCSCounters[27];
  int S3TL  = _MTCSCounters[28];
  int S4TL  = _MTCSCounters[29];
  int SXTL  = _MTCSCounters[30];
  int TXLL  = _MTCSCounters[31];
  int TXTT  = _MTCSCounters[32];
  int TXTL  = _MTCSCounters[33];
  int SSPARE0  = _MTCSCounters[34];
  int SSPARE1  = _MTCSCounters[35];

  // Version 2.32 of the MTM trigger list. For each
  // trigger it provides the MTM trigger number, the
  // nickname of the trigger and the trigger logic.
  // First the test triggers are given, then the single
  // muon triggers and finall the dimuon triggers.
  // Triggers which are built out of counters come
  // before triggers which use combinations of triggers.
  
  // Test triggers.
  //  mtm 110
  //  mu1pt1clxx
  if (C1SLP > 0 || C1SLN > 0) _muoManagTerms.set(110);

  //  mtm 111
  //  mu1pt2clxx
  if (C2SLP > 0 || C2SLN > 0) _muoManagTerms.set(111);

  //  mtm 112
  //  mu1pt3clxx
  if (C3SL > 0) _muoManagTerms.set(112);

  //  mtm 113
  //  mu1pt4clxx
  if (C4SL > 0) _muoManagTerms.set(113);
  
  // mtm 114
  // mu1ptxclxx
  if (CXSL > 0) _muoManagTerms.set(114);

  //  historical duplicate
  //  mtm 115
  //  mu1ptxclxz -- was mu1ptxclxa;
  //  now reserved for future use
  //if (CXSL > 0) _muoManagTerms.set(115);

  //  mtm 116
  //  mu1ptxclxc
  if (CXSC > 0) _muoManagTerms.set(116);

  //  mtm 117
  //  mu1ptxcxlx
  if (CXWL > 0) _muoManagTerms.set(117);
  
  //  mtm 118
  //  mu1ptxcxlz
  //;

  //  mtm 119
  //  mu1pt2ctxx
  if (C2ST > 0) _muoManagTerms.set(119);

  //  mtm 120
  //  mu1pt3ctxx
  if (C3ST > 0) _muoManagTerms.set(120);

  //  mtm 121
  //  mu1pt4ctxx
  if (C4ST > 0) _muoManagTerms.set(121);
  
  //  mtm 122
  //  mu1ptxcxtx
  if (CXWT > 0) _muoManagTerms.set(122);

  //  for mtm 123-145 see after mtm 189

  //  mtm 146
  //  mu1pt1nlxx
  if (N1SL > 0) _muoManagTerms.set(146);

  //  mtm 147
  //  mu1pt2nlxx
  if (N2SL > 0) _muoManagTerms.set(147);

  //  mtm 148
  //  mu1pt3nlxx
  if (N3SL > 0) _muoManagTerms.set(148);

  //  mtm 149
  //  mu1pt4nlxx
  if (N4SL > 0) _muoManagTerms.set(149);

  //  mtm 150
  //  mu1ptxnlxx
  if (NXSL > 0) _muoManagTerms.set(150);

  //  mtm 151
  //  mu1ptxnxlx
  if (NXWL > 0) _muoManagTerms.set(151);

  //  mtm 152
  //  mu1pt2ntxx
  if (N2ST > 0) _muoManagTerms.set(152);

  //  mtm 153
  //  mu1pt3ntxx
  if (N3ST > 0) _muoManagTerms.set(153);

  //  mtm 154
  //  mu1pt4ntxx
  if (N4ST > 0) _muoManagTerms.set(154);

  //  mtm 155
  //  mu1ptxntxx
  if (NXST > 0) _muoManagTerms.set(155);

  //  mtm 156
  //  mu1ptxnxtx
  if (NXWT > 0) _muoManagTerms.set(156);

  //  mtm 157
  //  mu1ptxolxx
  if (OXSL > 0) _muoManagTerms.set(157);

  //  mtm 158
  //  mu1ptxoxlx
  if (OXWL > 0) _muoManagTerms.set(158);

  //  mtm 159
  //  mu1ptxotxx
  if (OXST > 0) _muoManagTerms.set(159);

  //  mtm 160
  //  mu1ptxoxtx
  if (OXWT > 0) _muoManagTerms.set(160);

  //  mtm 161
  //  mu1ptxplxx
  if ( _muoManagTerms.test(150) || _muoManagTerms.test(157) )
    _muoManagTerms.set(161);

  //  mtm 162
  //  mu1ptxplxb
  if (NXSX > 1) _muoManagTerms.set(162);

  //  mtm 163
  //  mu1ptxpxlx
  if ( _muoManagTerms.test(151) || _muoManagTerms.test(158) )
    _muoManagTerms.set(163);

  //  mtm 164
  //  mu1ptxpxlb
  if (NXWC == 1 || NXWC == 3) _muoManagTerms.set(164);

  //  mtm 165
  //  mu1ptxpxlc
  if (NXWC > 1)  _muoManagTerms.set(165);

  //  mtm 166
  //  mu1ptxptxx
  if ( _muoManagTerms.test(155) || _muoManagTerms.test(159) )
    _muoManagTerms.set(166);

  //  mtm 167
  //  mu1ptxpxtx
  if ( _muoManagTerms.test(156) || _muoManagTerms.test(160) )
    _muoManagTerms.set(167);

  //  mtm 168
  //  mu1pt1slxx
  if (S1SL > 0) _muoManagTerms.set(168);

  //  mtm 169
  //  mu1pt2slxx
  if (S2SL > 0) _muoManagTerms.set(169);

  //  mtm 170
  //  mu1pt3slxx
  if (S3SL > 0) _muoManagTerms.set(170);

  //  mtm 171
  //  mu1pt4slxx
  if (S4SL > 0) _muoManagTerms.set(171);

  //  mtm 172
  //  mu1ptxslxx
  if (SXSL > 0) _muoManagTerms.set(172);

  //  mtm 173
  //  mu1ptxsxlx
  if (SXWL > 0) _muoManagTerms.set(173);

  //  mtm 174
  //  mu1pt2stxx
  if (S2ST > 0) _muoManagTerms.set(174);

  //  mtm 175
  //  mu1pt3stxx
  if (S3ST > 0) _muoManagTerms.set(175);

  //  mtm 176
  //  mu1pt4stxx
  if (S4ST > 0) _muoManagTerms.set(176);

  //  mtm 177
  //  mu1ptxstxx
  if (SXST > 0) _muoManagTerms.set(177);

  //  mtm 178
  //  mu1ptxsxtx
  if (SXWT > 0) _muoManagTerms.set(178);

  //  mtm 179
  //  mu1ptxtlxx
  if (TXSL > 0) _muoManagTerms.set(179);

  //  mtm 180
  //  mu1ptxtxlx
  if (TXWL > 0) _muoManagTerms.set(180);

  //  mtm 181
  //  mu1ptxttxx
  if (TXST > 0) _muoManagTerms.set(181);

  //  mtm 182
  //  mu1ptxtxtx
  if (TXWT > 0) _muoManagTerms.set(182);

  //  mtm 183
  //  mu1ptxulxx
  if ( _muoManagTerms.test(172) || _muoManagTerms.test(179) )
    _muoManagTerms.set(183);

  //  mtm 184
  //  mu1ptxulxb
  if (SXSX > 1) _muoManagTerms.set(184);

  //  mtm 185
  //  mu1ptxuxlx
  if ( _muoManagTerms.test(173) || _muoManagTerms.test(180) )
    _muoManagTerms.set(185);

  //  mtm 186
  //  mu1ptxuxlb
  if (SXWC == 1 || SXWC == 3) _muoManagTerms.set(186);

  //  mtm 187
  //  mu1ptxuxlc
  if (SXWC > 1)  _muoManagTerms.set(187);

  //  mtm 188
  //  mu1ptxutxx
  if ( _muoManagTerms.test(177) || _muoManagTerms.test(181) )
    _muoManagTerms.set(188);

  //  mtm 189
  //  mu1ptxuxtx
  if ( _muoManagTerms.test(178) || _muoManagTerms.test(182) )
    _muoManagTerms.set(189);

  // resume mtm 123 and following here
  // removed _muoManagTerms.test numbers and replaced them with conditions
  // that fired those triggers
  // (e.g., replaced " || _muoManagTerms.test(149)" 
  //  with "|| N4SL > 0".
  // This is a bit redundant, but it makes for easier comparisons
  // with MaxPlus logic files.

  // mtm 123
  // mu1pt1wlxx
   if ( _muoManagTerms.test(110) || N1SL > 0 || S1SL > 0 )
    _muoManagTerms.set(123); 

  // mtm 124
  // mu1pt2wlxx
   if ( _muoManagTerms.test(111) || N2SL > 0 || S2SL > 0 )
    _muoManagTerms.set(124); 

  // mtm 125
  // mu1pt3wlxx
   if ( _muoManagTerms.test(112) || N3SL > 0 || S3SL > 0 )
    _muoManagTerms.set(125); 

  // mtm 126
  // mu1pt4wlxx
   if ( _muoManagTerms.test(113) || N4SL > 0 || S4SL > 0 )
    _muoManagTerms.set(126); 

  // mtm 127
  // mu1ptxwlxx
   if ( _muoManagTerms.test(114) || NXSL > 0 || SXSL > 0 )
    _muoManagTerms.set(127); 

  // mtm 128
  // mu1ptxwxlx
   if ( _muoManagTerms.test(117) || NXWL > 0 || SXWL > 0 )
    _muoManagTerms.set(128); 

  // mtm 129
  // mu1pt2wtxx
   if ( _muoManagTerms.test(119) || N2ST > 0 || S2ST > 0 )
    _muoManagTerms.set(129); 

  // mtm 130
  // mu1pt3wtxx
   if ( _muoManagTerms.test(120) || N3ST > 0 || S3ST > 0 )
    _muoManagTerms.set(130); 

  // mtm 131
  // mu1pt4wtxx
   if ( _muoManagTerms.test(121) || N4ST > 0 || S4ST > 0 )
    _muoManagTerms.set(131); 

  // mtm 132
  // mu1ptxwxtx
   if ( _muoManagTerms.test(122) || NXST > 0 || SXST > 0 )
    _muoManagTerms.set(132); 

  // mtm 133
  // mu1pt1alxx
   if ( _muoManagTerms.test(123) || OXSL > 0 || TXSL > 0 )
    _muoManagTerms.set(133); 

  // mtm 134
  // mu1pt2alxx
   if ( _muoManagTerms.test(124) || OXSL > 0 || TXSL > 0 )
    _muoManagTerms.set(134); 

  // mtm 135
  // mu1pt3alxx
   if ( _muoManagTerms.test(125) || OXSL > 0 || TXSL > 0 )
    _muoManagTerms.set(135); 

  // mtm 136
  // mu1pt4alxx
   if ( _muoManagTerms.test(126) || OXSL > 0 || TXSL > 0 )
    _muoManagTerms.set(136); 

  // mtm 137
  // mu1ptxalxx
   if ( _muoManagTerms.test(127) || OXSL > 0 || TXSL > 0 ) 
    _muoManagTerms.set(137); 

  // mtm 138
  // mu1ptxaxlx
   if ( _muoManagTerms.test(128) || OXWL > 0 || TXWL > 0 )
    _muoManagTerms.set(138); 

  // mtm 139
  // mu1pt2atxx
   if ( _muoManagTerms.test(129) || OXST > 0 || TXST > 0 )
    _muoManagTerms.set(139); 

  // mtm 140
  // mu1pt3atxx
   if ( _muoManagTerms.test(130) || OXST > 0 || TXST > 0 ) 
    _muoManagTerms.set(140); 

  // mtm 141
  // mu1pt4atxx
   if ( _muoManagTerms.test(131) || OXST > 0 || TXST > 0 )
    _muoManagTerms.set(141); 

  // mtm 142
  // mu1ptxaxtx
   if ( _muoManagTerms.test(132) || OXWT > 0 || TXWT > 0 )
    _muoManagTerms.set(142); 

  // mtm 143
  // mu1ptxblxx
   if ( _muoManagTerms.test(161) || _muoManagTerms.test(183) )
    _muoManagTerms.set(143); 

  // mtm 144
  // mu1ptxbxlx
   if ( _muoManagTerms.test(163) || _muoManagTerms.test(185) )
    _muoManagTerms.set(144); 

  // mtm 145
  // mu1ptxbxtx
   if ( _muoManagTerms.test(167) || _muoManagTerms.test(189) )
    _muoManagTerms.set(145); 

   //  start test dimuon terms here 
   //  check 190 and 191 when i can think 
   //  mtm 190
   //  mu2pt1clxx
   // trigger fires if C1SLP >=2, C1SLN >=2, or
   // if C1SLP = C1SLN = 1 AND C3SL = C4SL = 0
  if ( (C1SLP == 0 && C1SLN == 2) ||
       (C1SLP == 0 && C1SLN == 3) ||
       (C1SLP == 1 && C1SLN == 1 && C3SL == 0 && C4SL == 0) ||
       (C1SLP == 1 && C1SLN == 2) ||
       (C1SLP == 1 && C1SLN == 3) ||
       (C1SLP == 2 && C1SLN == 0) ||
       (C1SLP == 2 && C1SLN == 1) ||
       (C1SLP == 2 && C1SLN == 2) ||
       (C1SLP == 2 && C1SLN == 3) ||
       (C1SLP == 3 && C1SLN == 0) ||
       (C1SLP == 3 && C1SLN == 1) ||
       (C1SLP == 3 && C1SLN == 2) ||
       (C1SLP == 3 && C1SLN == 3) )
       _muoManagTerms.set(190);

  //  mtm 191
  //  mu2pt2clxx
  if ( (C2SLP == 0 && C2SLN == 2) ||
       (C2SLP == 0 && C2SLN == 3) ||
       (C2SLP == 1 && C2SLN == 1 && C3SL == 0 && C4SL == 0) ||
       (C2SLP == 1 && C2SLN == 2) ||
       (C2SLP == 1 && C2SLN == 3) ||
       (C2SLP == 2 && C2SLN == 0) ||
       (C2SLP == 2 && C2SLN == 1) ||
       (C2SLP == 2 && C2SLN == 2) ||
       (C2SLP == 2 && C2SLN == 3) ||
       (C2SLP == 3 && C2SLN == 0) ||
       (C2SLP == 3 && C2SLN == 1) ||
       (C2SLP == 3 && C2SLN == 2) ||
       (C2SLP == 3 && C2SLN == 3) )
       _muoManagTerms.set(191);

  //  mtm 192
  //  mu2pt3clxx
  if (C3SL > 1) _muoManagTerms.set(192);

  //  mtm 193
  //  mu2pt4clxx
  if (C4SL > 1) _muoManagTerms.set(193);

  //  mtm 194
  //  mu2ptxclxx
  if (CXSL > 1) _muoManagTerms.set(194);

  //  mtm 195 -- moved to end of trigger list

  //  mtm 196
  //  mu2ptxclxc
  if (CXSC > 1) _muoManagTerms.set(196);

  //  mtm 197
  //  mu2ptxcxlx
  if (CXWL > 1) _muoManagTerms.set(197);

  //  mtm 198
  //  mu2ptxcxlz -- reserved for future use
  // ;

  //  mtm 199
  //  mu2pt2ctxx
  if (C2ST > 1) _muoManagTerms.set(199);

  //  mtm 200
  //  mu2pt3ctxx
  if (C3ST > 1) _muoManagTerms.set(200);

  //  mtm 201
  //  mu2pt4ctxx
  if (C4ST > 1) _muoManagTerms.set(201);

  //  mtm 202
  //  mu2ptxcxtx -- was labeled as mu2ptxctxx (which is term 90)
  if (CXWT > 1) _muoManagTerms.set(202);

  //  mtm 203
  //  mu2pt1nlxx
  if (N1SL > 1) _muoManagTerms.set(203);

  //  mtm 204
  //  mu2pt2nlxx
  if (N2SL > 1) _muoManagTerms.set(204);

  //  mtm 205
  //  mu2pt3nlxx
  if (N3SL > 1) _muoManagTerms.set(205);

  //  mtm 206
  //  mu2pt4nlxx
  if (N4SL > 1) _muoManagTerms.set(206);

  //  mtm 207
  //  mu2ptxnlxx
  if (NXSL > 1) _muoManagTerms.set(207);

  //  mtm 208
  //  mu2ptxnxlx
  if (NXWL > 1) _muoManagTerms.set(208);

  //  mtm 209
  //  mu2pt2ntxx
  if (N2ST > 1) _muoManagTerms.set(209);

  //  mtm 210
  //  mu2pt3ntxx
  if (N3ST > 1) _muoManagTerms.set(210);

  //  mtm 211
  //  mu2pt4ntxx
  if (N4ST > 1) _muoManagTerms.set(211);

  //  mtm 67
  //  mu2ptxntxx
  if (NXST > 1) _muoManagTerms.set(67);

  //  mtm 212
  //  mu2ptxnxtx
  if (NXWT > 1) _muoManagTerms.set(212);

  //  mtm 213
  //  mu2ptxolxx
  if (OXSL > 1) _muoManagTerms.set(213);

  //  mtm 214
  //  mu2ptxoxlx
  if (OXWL > 1) _muoManagTerms.set(214);

  //  mtm 215
  //  mu2ptxotxx
  if (OXST > 1) _muoManagTerms.set(215);

  //  mtm 216
  //  mu2ptxoxtx
  if (OXWT > 1) _muoManagTerms.set(216);

  //  mtm 217
  //  mu2ptxplxx
  // truth table is [1,1] -> 1
  // [2,X] -> 1, [3,X] -> 1
  // [X,2] -> 1, [X,3] -> 1
  if ( (NXSL == 1 && OXSL == 1) ||
       (NXSL > 1) ||
       (OXSL > 1) )
       _muoManagTerms.set(217);

  //  mtm 218
  //  mu2ptxpxlx
  if ( (NXWL == 1 && OXWL == 1) ||
       (NXWL > 1) ||
       (OXWL > 1) )
       _muoManagTerms.set(218);

  //  mtm 219
  //  mu2ptxptxx
  if ( (NXST == 1 && OXST == 1) ||
       (NXST > 1) ||
       (OXST > 1) )
       _muoManagTerms.set(219);

  //  mtm 220
  //  mu2ptxpxtx
  if ( (NXWT == 1 && OXWT == 1) ||
       (NXWT > 1) ||
       (OXWT > 1) )
       _muoManagTerms.set(220);

  //  mtm 221
  //  mu2pt1slxx
  if (S1SL > 1) _muoManagTerms.set(221);

  //  mtm 222
  //  mu2pt2slxx -- was mislabeled as mu2pt1slxx (term 221)
  if (S2SL > 1) _muoManagTerms.set(222);

  //  mtm 223
  //  mu2pt3slxx
  if (S3SL > 1) _muoManagTerms.set(223);

  //  mtm 224
  //  mu2pt4slxx
  if (S4SL > 1) _muoManagTerms.set(224);

  //  mtm 225
  //  mu2ptxslxx
  if (SXSL > 1) _muoManagTerms.set(225);

  //  mtm 226
  //  mu2ptxsxlx
  if (SXWL > 1) _muoManagTerms.set(226);

  //  mtm 227
  //  mu2pt2stxx
  if (S2ST > 1) _muoManagTerms.set(227);

  //  mtm 228
  //  mu2pt3stxx
  if (S3ST > 1) _muoManagTerms.set(228);

  //  mtm 229
  //  mu2pt4stxx
  if (S4ST > 1) _muoManagTerms.set(229);

  //  mtm 71
  //  mu2ptxstxx
  if (SXST > 1) _muoManagTerms.set(71);

  //  mtm 230
  //  mu2ptxsxtx
  if (SXWT > 1) _muoManagTerms.set(230);

  //  mtm 231
  //  mu2ptxtlxx
  if (TXSL > 1) _muoManagTerms.set(231);

  //  mtm 232
  //  mu2ptxtxlx
  if (TXWL > 1) _muoManagTerms.set(232);

  //  mtm 233
  //  mu2ptxttxx
  if (TXST > 1) _muoManagTerms.set(233);

  //  mtm 234
  //  mu2ptxtxtx
  if (TXWT > 1) _muoManagTerms.set(234);

  //  mtm 235
  //  mu2ptxulxx
  if ( (SXSL == 1 && TXSL == 1) ||
       (SXSL > 1) ||
       (TXSL > 1) )
       _muoManagTerms.set(235);

  //  mtm 236
  //  mu2ptxuxlx
  if ( (SXWL == 1 && TXWL == 1) ||
       (SXWL > 1) ||
       (TXWL > 1) )
       _muoManagTerms.set(236);

  //  mtm 237
  //  mu2ptxutxx
  if ( (SXST == 1 && TXST == 1) ||
       (SXST > 1) ||
       (TXST > 1) )
       _muoManagTerms.set(237);

  //  mtm 238
  //  mu2ptxuxtx
  if ( (SXWT == 1 && TXWT == 1) ||
       (SXWT > 1) ||
       (TXWT > 1) )
       _muoManagTerms.set(238);

  // Opposite-sign triggers :  Added to hardware on 04/29/04

  //  mtm 239
  //  mu1pt1clxo
  if ( C1SLP > 0 && C1SLN > 0 ) 
    _muoManagTerms.set(239);

  //  mtm 240
  //  mu1pt1cllo
  if ( C1LLP > 0 && C1LLN > 0 )
    _muoManagTerms.set(240);

  //  mtm 241
  //  mu1pt2clxo
  if ( C2SLP > 0 && C2SLN > 0 )
    _muoManagTerms.set(241);

  //  mtm 242
  //  mu1pt2cllo
  if ( C2LLP > 0 && C2LLN > 0 )
    _muoManagTerms.set(242);

  //  mtm 243
  //  mu1ptxoxxe
  //;

  //  mtm 244
  //  mu1ptxpxxe
  //;

  //  mtm 245
  //  mu1ptxsxxe
  //;

  //  mtm 246
  //  mu1ptxcxlb
  if (CXWC == 1 ||  CXWC == 3) _muoManagTerms.set(246);
 

  //  mtm 247
  //  mu1ptxcxlc
  // condition is: (CXWC == 2 || CXWC == 3)
  if (CXWC > 1) _muoManagTerms.set(247);

  //  mtm 248
  //  mu1ptxattt
  //  BOT or
  //  Trigger is defined after term 255 (once individual BOTs are defined)

  //  mtm 249
  //  mu1ptxclxt
  //  cf05 BOT
  if (CXSX == 1 || CXSX == 3 ) _muoManagTerms.set(249);

  //  mtm 250
  //  mu1ptxcxlt
  //  cf10 BOT
  if (CXWX == 1 || CXWX == 3 ) _muoManagTerms.set(250);

  //  mtm 251
  //  mu1ptxplxt
  //  n ef05 BOT
  if (NXSX == 1 || NXSX == 3 ) _muoManagTerms.set(251);

  //  mtm 252
  //  mu1ptxpxlt
  //  n ef10 BOT
  if (NXWX == 1 || NXWX == 3 ) _muoManagTerms.set(252);

  //  mtm 253
  //  mu1ptxulxt
  //  s ef05 BOT
  if (SXSX == 1 || SXSX == 3 ) _muoManagTerms.set(253);

  //  mtm 254
  //  mu1ptxuxlt
  //  s ef10 BOT
  if (SXWX == 1 || SXWX == 3 ) _muoManagTerms.set(254);

  //  mtm 255
  //  mu2ptxallt
  //  BOT and
  if (_muoManagTerms.test(249) && _muoManagTerms.test(250) &&
      _muoManagTerms.test(251) && _muoManagTerms.test(252) &&
      _muoManagTerms.test(253) && _muoManagTerms.test(254) 
      ) _muoManagTerms.set(255);

  //mtm 248
  //  mu1ptxattt
  // BOT or
  if (_muoManagTerms.test(249) || _muoManagTerms.test(250) ||
      _muoManagTerms.test(251) || _muoManagTerms.test(252) ||
      _muoManagTerms.test(253) || _muoManagTerms.test(254) 
      ) _muoManagTerms.set(248);


  // --------------------------------------------------------------------
  //
  // 1mu triggers
  //

  //  mtm 37
  //  mu1pt4wxxx
  if (C4XX > 0) _muoManagTerms.set(37);

  //  mtm 40
  //  mu1ptxctxx
  if (CXST > 0) _muoManagTerms.set(40);

  //  mtm 85
  //  mu2pt4wxxx
  if (C4XX > 1) _muoManagTerms.set(85);

  //  mtm 90
  //  mu2ptxctxx
  if (CXST > 1) _muoManagTerms.set(90);

  //  mtm 0
  // mu1ptxaxxy -- always on
     _muoManagTerms.set(0);

  //  mtm 1
  //  mu1pt1cllx
  if (C1LLP > 0 || C1LLN > 0)
    _muoManagTerms.set(1);

  // mtm 2
  // mu1pt2cllx
  if (C2LLP > 0 || C2LLN > 0)
    _muoManagTerms.set(2);

  // mtm 3
  // mu1pt3cllx
  if (C3LL > 0)
    _muoManagTerms.set(3);

  // mtm 4
  // mu1pt4cllx
  if (C4LL > 0)
    _muoManagTerms.set(4);
  
  // mtm 5
  // mu1ptxottx
  if (OXTT > 0 )
    _muoManagTerms.set(5);

  // mtm 6
  // mu1pt2cttx
  if (C2TT > 0)
    _muoManagTerms.set(6);
  
  // mtm 7
  // mu1pt3cttx
  if (C3TT > 0)
    _muoManagTerms.set(7);

  // mtm 8
  // mu1pt4cttx
  if (C4TT > 0)
    _muoManagTerms.set(8);
 
  //mtm 9
  //mu1ptxctlx -- was labeled as mu1pt1ctlx
  if (CXTL > 0)
    _muoManagTerms.set(9);

  // mtm 10
  // mu1pt2ctlx
  if (C2TL > 0)
    _muoManagTerms.set(10);

  // mtm 11
  // mu1pt3ctlx
  if (C3TL > 0)
    _muoManagTerms.set(11);

  // mtm 12
  // mu1pt4ctlx
  if (C4TL > 0)
    _muoManagTerms.set(12);
 
  // mtm 13
  // mu1pt1wllx
  if (_muoManagTerms.test(1) || N1LL > 0 || S1LL > 0)
    _muoManagTerms.set(13);
  
  // mtm 14
  // mu1pt2wllx
  if (_muoManagTerms.test(2) || N2LL > 0 || S2LL > 0)
    _muoManagTerms.set(14);

  // mtm 15
  // mu1pt3wllx
  if (_muoManagTerms.test(3) || N3LL > 0 || S3LL > 0)
    _muoManagTerms.set(15);
 
  // mtm 16
  // mu1pt4wllx
  if (_muoManagTerms.test(4) || N4LL > 0 || S4LL > 0)
    _muoManagTerms.set(16);
  
  //mtm 17
  //mu1ptxtttx -- was labeled as mu1pt1tttx
  if (TXTT > 0 ) 
    _muoManagTerms.set(17);

  // mtm 18
  // mu1pt2wttx
  if ( _muoManagTerms.test(6) || N2TT > 0 || S2TT > 0)
    _muoManagTerms.set(18);

  // mtm 19
  // mu1pt3wttx
  if ( _muoManagTerms.test(7) || N3TT > 0 || S3TT > 0)
    _muoManagTerms.set(19);
  
  // mtm 20
  // mu1pt4wttx
  if ( _muoManagTerms.test(8) || N4TT > 0 || S4TT > 0)
    _muoManagTerms.set(20);

  // mtm 21
  // mu1ptxwtlx
  if ( _muoManagTerms.test(9) || NXTL > 0 || SXTL > 0)
    _muoManagTerms.set(21);

  // mtm 22
  // mu1pt2wtlx
  if ( _muoManagTerms.test(10) || N2TL > 0 || S2TL > 0)
    _muoManagTerms.set(22);

  // mtm 23
  // mu1pt3wtlx
  if ( _muoManagTerms.test(11) || N3TL > 0 || S3TL > 0)
    _muoManagTerms.set(23);

  // mtm 24
  // mu1pt4wtlx
  if ( _muoManagTerms.test(12) || N4TL > 0 || S4TL > 0)
    _muoManagTerms.set(24);

  // mtm 25
  // mu1pt1allx
  if ( _muoManagTerms.test(13) || OXLL > 0 || TXLL > 0)
    _muoManagTerms.set(25);
 
  // mtm 26
  // mu1pt2allx
  if ( _muoManagTerms.test(14) || OXLL > 0 || TXLL > 0)  
   _muoManagTerms.set(26);

  // mtm 27
  // mu1pt3allx
  if ( _muoManagTerms.test(15) || OXLL > 0 || TXLL > 0)
   _muoManagTerms.set(27);

  // mtm 28
  // mu1pt4allx
  if ( _muoManagTerms.test(16) || OXLL > 0 || TXLL > 0)
    _muoManagTerms.set(28);

  // mtm 29
  // mu1ptxotlx
  if (OXTL > 0)
    _muoManagTerms.set(29);

  // mtm 30
  // mu1pt2attx
  if ( _muoManagTerms.test(18) || OXTT > 0 || TXTT > 0)
    _muoManagTerms.set(30);
 
  // mtm 31
  // mu1pt3attx
  if ( _muoManagTerms.test(19) || OXTT > 0 || TXTT > 0)
    _muoManagTerms.set(31);

  // mtm 32
  // mu1pt4attx
  if ( _muoManagTerms.test(20) || OXTT > 0 || TXTT > 0)
    _muoManagTerms.set(32);
 
  // mtm 33
  // mu1ptxatlx
  if ( _muoManagTerms.test(21) || OXTL > 0 || TXTL > 0)
    _muoManagTerms.set(33);
  // mtm 34
  // mu1pt2atlx
  if ( _muoManagTerms.test(22) || OXTL > 0 || TXTL > 0)
    _muoManagTerms.set(34);

  // mtm 35
  // mu1pt3atlx
  if ( _muoManagTerms.test(23) || OXTL > 0 || TXTL > 0)
    _muoManagTerms.set(35);

  // mtm 36
  // mu1pt4atlx
  if ( _muoManagTerms.test(24) || OXTL > 0 || TXTL > 0)
    _muoManagTerms.set(36);
 
 //  stopped editing here NBW starts thanks KJ..
 // mtm 38
  // mu1ptxcllx
  if ( CXLL > 0 )
    _muoManagTerms.set(38);

  // mtm 37 is after mtm 255 above
 
  // mtm 39
  // mu1ptxcttx
  if ( CXTT > 0 )
    _muoManagTerms.set(39);

  //  mtm 40 is after mtm 255 above

  // mtm 41
  // mu1ptxwllx
  if (_muoManagTerms.test(38) || NXLL > 0 || SXLL > 0 )
    _muoManagTerms.set(41);

  // mtm 42
  // mu1ptxwttx
  if ( _muoManagTerms.test(39) || NXTT > 0 || SXTT > 0 )
    _muoManagTerms.set(42);

  // mtm 43
  // mu1ptxwtxx
  if ( _muoManagTerms.test(40) || NXST > 0 || SXST > 0 )
      _muoManagTerms.set(43);
  
  // mtm 44
  // mu1ptxallx
  if ( _muoManagTerms.test(41) || OXLL > 0 || TXLL > 0 )
    _muoManagTerms.set(44);

  // mtm 45
  // mu1ptxattx
  if ( _muoManagTerms.test(42) || OXTT > 0 || TXTT > 0 )
    _muoManagTerms.set(45);

  // mtm 46
  // mu1ptxatxx
  if ( _muoManagTerms.test(43) || OXST > 0 || TXST > 0 ) 
      _muoManagTerms.set(46);

  // mtm 47
  // mu1ptxbllx
  if ( NXLL > 0 || SXLL > 0 || OXLL > 0 || TXLL > 0)
    _muoManagTerms.set(47);

  // mtm 48
  // mu1ptxbttx
  if ( NXTT > 0 || SXTT > 0 || OXTT > 0 || TXTT > 0 )
    _muoManagTerms.set(48);

  // mtm 49
  // mu1ptxbtxx
  if ( NXST > 0 || SXST > 0 || OXST > 0 || TXST > 0 )
    _muoManagTerms.set(49);

  // mtm 50
  // mu1ptxttlx
  // South far-forward ('t' region) tight-loose trigger
  if (TXTL > 0)
    _muoManagTerms.set(50);

  //
  // 2mu triggers
  //

  // mtm 51
  // mu2pt1cllx
  if (C1LLP > 1 || C1LLN > 1 || (C1LLP == 1 && C1LLN == 1))
    _muoManagTerms.set(51);
 
  // mtm 52
  // mu2pt2cllx
  if (C2LLP > 1 || C2LLN > 1 || (C2LLP == 1 && C2LLN == 1))
    _muoManagTerms.set(52);
 
  // mtm 53
  // mu2pt3cllx
  if ( C3LL > 1 )
    _muoManagTerms.set(53);
 
  // mtm 54
  // mu2pt4cllx
  if ( C4LL > 1 )
    _muoManagTerms.set(54);

  // Terms 55-58 appear at end of file
 
  // mtm 59
  // mu2pt1ctlz
  //;

  // mtm 60
  // mu2pt2ctlx
 if ( C2TL > 1 )
    _muoManagTerms.set(60);
 
  // mtm 61
  // mu2pt3ctlx
 if (C3TL > 1 )
    _muoManagTerms.set(61);

  // mtm 62
  // mu2pt4ctlx
 if (C4TL > 1 )
    _muoManagTerms.set(62);

  // mtm 63
  // mu2pt1wllx
 if ((_muoManagTerms.test(51) || N1LL > 1 || S1LL > 1)
     || (_muoManagTerms.test(1) && N1LL == 1)
     || (_muoManagTerms.test(1) && S1LL == 1)
     || ( N1LL == 1 && S1LL == 1))
    _muoManagTerms.set(63);

  // mtm 64
  // mu2pt2wllx
 if ((_muoManagTerms.test(52) || N2LL > 1 || S2LL > 1)
     || (_muoManagTerms.test(2) && N2LL == 1)
     || (_muoManagTerms.test(2) && S2LL == 1)
     || ( N2LL == 1 && S2LL == 1))
    _muoManagTerms.set(64);

  // mtm 65
  // mu2pt3wllx
 if ((_muoManagTerms.test(53) || N3LL > 1 || S3LL > 1)
     || (_muoManagTerms.test(3) && N3LL == 1)
     || (_muoManagTerms.test(3) && S3LL == 1)
     || ( N3LL == 1 && S3LL == 1))
    _muoManagTerms.set(65);

  // mtm 66
  // mu2pt4wllx
 if ((_muoManagTerms.test(54) || N4LL > 1 || S4LL > 1)
     || (_muoManagTerms.test(4) && N4LL == 1)
     || (_muoManagTerms.test(4) && S4LL == 1)
     || ( N4LL == 1 && S4LL == 1))
    _muoManagTerms.set(66);

  // mtm 67
  // mu2ptxntxx
  // see after mtm 211

  // mtm 68
  // mu2pt2wtxx
 if ((_muoManagTerms.test(199) || N2ST > 1 || S2ST > 1)
     || (_muoManagTerms.test(119) && N2ST == 1)
     || (_muoManagTerms.test(119) && S2ST == 1)
     || ( N2ST == 1 && S2ST == 1))
    _muoManagTerms.set(68);

  // mtm 69
  // mu2pt3wtxx
 if ((_muoManagTerms.test(200) || N3ST > 1 || S3ST > 1)
     || (_muoManagTerms.test(120) && N3ST == 1)
     || (_muoManagTerms.test(120) && S3ST == 1)
     || ( N3ST == 1 && S3ST == 1))
    _muoManagTerms.set(69);

  // mtm 70
  // mu2pt4wtxx
 if ((_muoManagTerms.test(201) || N4ST > 1 || S4ST > 1)
     || (_muoManagTerms.test(121) && N4ST == 1)
     || (_muoManagTerms.test(121) && S4ST == 1)
     || ( N4ST == 1 && S4ST == 1))
    _muoManagTerms.set(70);

  // mtm 71
  // mu2ptxstxx
  // see after mtm 229

  // mtm 72
  // mu2pt2wtlx
 if ((_muoManagTerms.test(60) || N2TL > 1 || S2TL > 1)
     || (_muoManagTerms.test(10) && N2TL == 1)
     || (_muoManagTerms.test(10) && S2TL == 1)
     || ( N2TL == 1 && S2TL == 1))
    _muoManagTerms.set(72);

  // mtm 73
  // mu2pt3wtlx
 if ((_muoManagTerms.test(61) || N3TL > 1 || S3TL > 1)
     || (_muoManagTerms.test(11) && N3TL == 1)
     || (_muoManagTerms.test(11) && S3TL == 1)
     || ( N3TL == 1 && S3TL == 1))
    _muoManagTerms.set(73);

  // mtm 74
  // mu2pt4wtlx
 if ((_muoManagTerms.test(62) || N4TL > 1 || S4TL > 1)
     || (_muoManagTerms.test(12) && N4TL == 1)
     || (_muoManagTerms.test(12) && S4TL == 1)
     || ( N4TL == 1 && S4TL == 1))
    _muoManagTerms.set(74);

  // mtm 75
  // mu2pt1wlxx
 if ((_muoManagTerms.test(190) || N1SL > 1 || S1SL > 1)
     || (_muoManagTerms.test(110) && N1SL == 1)
     || (_muoManagTerms.test(110) && S1SL == 1)
     || ( N1SL == 1 && S1SL == 1))
    _muoManagTerms.set(75);

  // mtm 76
  // mu2pt2wlxx
 if ((_muoManagTerms.test(191) || N2SL > 1 || S2SL > 1)
     || (_muoManagTerms.test(111) && N2SL == 1)
     || (_muoManagTerms.test(111) && S2SL == 1)
     || ( N2SL == 1 && S2SL == 1))
    _muoManagTerms.set(76);

   // mtm 77
   // mu2pt3wlxx
 if ((_muoManagTerms.test(192) || N3SL > 1 || S3SL > 1)
     || (_muoManagTerms.test(112) && N3SL == 1)
     || (_muoManagTerms.test(112) && S3SL == 1)
     || ( N3SL == 1 && S3SL == 1))
    _muoManagTerms.set(77);

  // mtm 78
  // mu2pt4wlxx
 if ((_muoManagTerms.test(193) || N4SL > 1 || S4SL > 1)
     || (_muoManagTerms.test(113) && N4SL == 1)
     || (_muoManagTerms.test(113) && S4SL == 1)
     || ( N4SL == 1 && S4SL == 1))
    _muoManagTerms.set(78);


  // mtm 79
  // mu2pt2atxx
 if ((_muoManagTerms.test(68) || OXST > 1 || TXST > 1)
     || (_muoManagTerms.test(129) && OXST == 1)
     || (_muoManagTerms.test(129) && TXST == 1)
     || ( OXST == 1 && TXST == 1))
   _muoManagTerms.set(79);

  // mtm 80
  // mu2pt3atxx
 if ((_muoManagTerms.test(69) || OXST > 1 || TXST > 1)
     || (_muoManagTerms.test(130) && OXST == 1)
     || (_muoManagTerms.test(130) && TXST == 1)
     || ( OXST == 1 && TXST == 1))
   _muoManagTerms.set(80);

  // mtm 81
  // mu2pt4atxx
 if ((_muoManagTerms.test(70) || OXST > 1 || TXST > 1)
     || (_muoManagTerms.test(131) && OXST == 1)
     || (_muoManagTerms.test(131) && TXST == 1)
     || ( OXST == 1 && TXST == 1))
   _muoManagTerms.set(81);

  // mtm 82
  // mu2pt2atlx
 if ((_muoManagTerms.test(72) || OXTL > 1 || TXTL > 1)
     || (_muoManagTerms.test(22) && OXTL == 1)
     || (_muoManagTerms.test(22) && TXTL == 1)
     || ( OXTL == 1 && TXTL == 1))
    _muoManagTerms.set(82);

  // mtm 83
  // mu2pt3atlx
 if ((_muoManagTerms.test(73) || OXTL > 1 || TXTL > 1)
     || (_muoManagTerms.test(23) && OXTL == 1)
     || (_muoManagTerms.test(23) && TXTL == 1)
     || ( OXTL == 1 && TXTL == 1))
    _muoManagTerms.set(83);

  // mtm 84
 // mu2pt4atlx
  if ((_muoManagTerms.test(74) || OXTL > 1 || TXTL > 1)
     || (_muoManagTerms.test(24) && OXTL == 1)
     || (_muoManagTerms.test(24) && TXTL == 1)
     || ( OXTL == 1 && TXTL == 1))
    _muoManagTerms.set(84);
  //  mtm 85
  //  mu2pt4wxxx
  //   see after mtm 255 above

  // mtm 86
  // mu2ptxcllx
 if ( CXLL >1 )
    _muoManagTerms.set(86);

  // mtm 87
  // mu2ptxcllz -- reserved for future use

  // mtm 88
  // mu2ptxcttx
 if ( CXTT > 1 )
    _muoManagTerms.set(88);

  // mtm 89
  // mu2ptxcttl
 if ( _muoManagTerms.test(86) && _muoManagTerms.test(39)) 
    _muoManagTerms.set(89);

  //  mtm 90
  //  mu2ptxctxx
  //  see after mtm 255 above

  // mtm 91
  // mu2ptxctxl
 if ( _muoManagTerms.test(194) && _muoManagTerms.test(40) )
    _muoManagTerms.set(91);

  // mtm 92
  // mu2ptxctlx
 if ( CXTL > 1 )
    _muoManagTerms.set(92); 

  // mtm 93
  // mu2ptxwllx
 if ((_muoManagTerms.test(86) || NXLL > 1 || SXLL > 1)
     || (_muoManagTerms.test(38) && NXLL == 1)
     || (_muoManagTerms.test(38) && SXLL == 1)
     || (NXLL == 1 && SXLL == 1))
    _muoManagTerms.set(93);

  // mtm 94
  // mu2ptxwlxx
 if (( _muoManagTerms.test(194) || NXSL > 1 || SXSL > 1)
     || (_muoManagTerms.test(114) && NXSL == 1 )
     || (_muoManagTerms.test(114) && SXSL == 1)
     || (NXSL == 1 && SXSL == 1 ) )
    _muoManagTerms.set(94);

  // mtm 95
  // mu2ptxwttx
 if ((_muoManagTerms.test(88) || NXTT > 1 || SXTT > 1)
     || (_muoManagTerms.test(39) && NXTT == 1)
     || (_muoManagTerms.test(39) && SXTT == 1)
     || (NXTT == 1 && SXTT == 1))
    _muoManagTerms.set(95);

  // mtm 96
  // mu2ptxwttl
 if ( _muoManagTerms.test(93) && _muoManagTerms.test(42))
    _muoManagTerms.set(96);

  // mtm 97
  // mu2ptxwtxx
 if ( (_muoManagTerms.test(90) || NXST > 1 || SXST > 1)
      || (_muoManagTerms.test(40) && NXST == 1)
      || (_muoManagTerms.test(40) && SXST == 1)
      || ( NXST ==1 && SXST == 1) )
    _muoManagTerms.set(97);

  // mtm 98
  // mu2ptxwtxl
 if (_muoManagTerms.test(94) && _muoManagTerms.test(43))
   _muoManagTerms.set(98);

  // mtm 99
  // mu2ptxwtlx
 if ((_muoManagTerms.test(92) || NXTL > 1 || SXTL > 1)
     || (_muoManagTerms.test(9) && NXTL == 1)
     || (_muoManagTerms.test(9) && SXTL == 1)
     || (NXTL == 1 && SXTL == 1))
    _muoManagTerms.set(99);

  // mtm 100
  // mu2ptxallx
 if ((_muoManagTerms.test(93) || OXLL > 1 || TXLL > 1)
     || (_muoManagTerms.test(41) && OXLL == 1)
     || (_muoManagTerms.test(41) && TXLL == 1)
     || (OXLL == 1 && TXLL == 1))
    _muoManagTerms.set(100);

  // mtm 101
  // mu2ptxalxx
 if  ( ( _muoManagTerms.test(94) || OXSL > 1 || TXSL > 1 )
      || (_muoManagTerms.test(127) && OXSL == 1 )
      || (_muoManagTerms.test(127) && TXSL == 1 )
      || ( OXSL ==1 && TXSL == 1 ))
    _muoManagTerms.set(101);

  // mtm 102
  // mu2ptxattx
 if ((_muoManagTerms.test(95) || OXTT > 1 || TXTT > 1)
     || (_muoManagTerms.test(42) && OXTT == 1)
     || (_muoManagTerms.test(42) && TXTT == 1)
     || (OXTT == 1 && TXTT == 1))
    _muoManagTerms.set(102);

   // mtm 103
  // mu2ptxattl
 if ( _muoManagTerms.test(100) && _muoManagTerms.test(45))
    _muoManagTerms.set(103);

  // mtm 104
  // mu2ptxatxx
 if ( ( _muoManagTerms.test(97) || OXST > 1 || TXST > 1)
      || (_muoManagTerms.test(43) && OXST == 1 )
      || (_muoManagTerms.test(43) && TXST == 1 )
      || (OXST == 1 && TXST == 1) )
    _muoManagTerms.set(104);

  // mtm 105
  // mu2ptxatxl
 if (_muoManagTerms.test(101) && _muoManagTerms.test(46))
     _muoManagTerms.set(105);

  // mtm 106
  // mu2ptxatlx
 if ( (_muoManagTerms.test(99) || OXTL > 1 || TXTL > 1) 
      || (_muoManagTerms.test(21) && OXTL == 1)
      || (_muoManagTerms.test(21) && TXTL == 1)
      || (OXTL == 1 && TXTL == 1) )
     _muoManagTerms.set(106);

  // mtm 107
  // mu2pt1allx
 if ( (_muoManagTerms.test(63) || OXLL > 1 || TXLL > 1) 
      || (_muoManagTerms.test(13) && OXLL == 1)
      || (_muoManagTerms.test(13) && TXLL == 1)
      || (OXLL == 1 && TXLL == 1) )
    _muoManagTerms.set(107);

  // mtm 108
  // mu2pt2allx
 if ( (_muoManagTerms.test(64) || OXLL > 1 || TXLL > 1) 
      || (_muoManagTerms.test(14) && OXLL == 1)
      || (_muoManagTerms.test(14) && TXLL == 1)
      || (OXLL == 1 && TXLL == 1) )
    _muoManagTerms.set(108);

  // mtm 109
  // mu2pt4allx
 if ( (_muoManagTerms.test(66) || OXLL > 1 || TXLL > 1) 
      || (_muoManagTerms.test(16) && OXLL == 1)
      || (_muoManagTerms.test(16) && TXLL == 1)
      || (OXLL == 1 && TXLL == 1) )
    _muoManagTerms.set(109);

 // Terms 55-58

 

  // mtm 55
  // mu2pt1alxx
 if ((_muoManagTerms.test(75) || OXSL > 1 || TXSL > 1) ||
      (_muoManagTerms.test(123) && OXSL ==1 ) ||
      (_muoManagTerms.test(123) && TXSL == 1) ||
      (OXSL ==1 && TXSL == 1))
   _muoManagTerms.set(55);

  // mtm 56
  // mu2pt2alxx
 if ((_muoManagTerms.test(76) || OXSL > 1 || TXSL > 1) ||
     (_muoManagTerms.test(124) && OXSL ==1 ) ||
     (_muoManagTerms.test(124) && TXSL == 1) ||
     (OXSL ==1 && TXSL == 1))
   _muoManagTerms.set(56);

 
  // mtm 57
 // mu2pt3alxx
 if ((_muoManagTerms.test(77) || OXSL > 1 || TXSL > 1) ||
     (_muoManagTerms.test(125) && OXSL ==1 ) ||
     (_muoManagTerms.test(125) && TXSL == 1) ||
     (OXSL ==1 && TXSL == 1))
   _muoManagTerms.set(57);

  // mtm 58
  // mu2pt4alxx
 if ((_muoManagTerms.test(78) || OXSL > 1 || TXSL > 1) ||
     (_muoManagTerms.test(126) && OXSL ==1 ) ||
     (_muoManagTerms.test(126) && TXSL == 1) ||
     (OXSL ==1 && TXSL == 1))
   _muoManagTerms.set(58);

 // mtm 195
 //  mu2ptxbtxx
  if (_muoManagTerms.test(219) || _muoManagTerms.test(237) 
      || (_muoManagTerms.test(166) && _muoManagTerms.test(188)))
    _muoManagTerms.set(195);


  // Version 2.32 of the MTM firmware simulation ends here.
  return;

} 

int L1MuTermsClass::get_mtm_named(const std::string& termName)
{

   return this->get_mtm(this->get_mtm_number(termName));

}

bool L1MuTermsClass::match_trigger_named(int region, int octant, 
					 std::string name){

   // Parse the trigger name and use the requiremnent maps to translate 
   // to integer arguements for match_trigger_requirements.  Return 
   // false if no matching requirement is found

   // Trigger name must be of standard length 
   // (i.e., 10 characters - mu?pt????x)
   if (name.size()!=10) return false;

   // Track requirement (e.g. pt2) 3 characters from position 3 to 5
   std::string cttReq = name.substr(3,3);
   std::map<std::string, _cttRequirements>::const_iterator ctt_it = 
      _cttReqMap.find(cttReq);
   if (ctt_it == _cttReqMap.end())
      return false;
   int icttReq = ctt_it->second;
   
   // One character for eta range (i.e., c, w, a, or b) in position 6
   std::string etaReq = name.substr(6,1);
   std::map<std::string, _etaRequirements>::const_iterator eta_it = 
      _etaReqMap.find(etaReq);
   if (eta_it == _etaReqMap.end())
      return false;
   int ietaReq = eta_it->second;

   // One character for scintillator requirement (i.e. t or l) in position 7
   std::string scintReq = name.substr(7,1);
   std::map<std::string, _scintRequirements>::const_iterator scint_it = 
      _scintReqMap.find(scintReq);
   if (scint_it == _scintReqMap.end())
      return false;
   int iscintReq = scint_it->second;

   // One character for wire requirement (i.e. t or l) in position 8
   std::string wireReq = name.substr(8,1);
   std::map<std::string, _wireRequirements>::const_iterator wire_it = 
      _wireReqMap.find(wireReq);
   if (wire_it == _wireReqMap.end())
      return false;
   int iwireReq = wire_it->second;

   return match_trigger_requirements(region, octant, ietaReq,
				     icttReq, iscintReq, iwireReq);

}

bool L1MuTermsClass::match_trigger_requirements(
   int region, int octant, int eta, int track, int scint, int wire) {

   // The trick:  generate list of counters to test
   // This is done using the arguments to search the counter maps
   // Use maps appropriate to region 
   switch (region) {
      case 0: // Central 
      {
         // Need separate vectors for 05 & 10 counters
         // Final answer will be the AND of the results
         // of ORing the counters in each vector
	 std::vector<int> counters05, counters10;

	 // Fetch 05 counters
	 std::pair<int,int> key05(track, scint);
	 fetch_Counters(counters05,_mtc05CentralMap,key05);

	 // Fetch 10 counter (there is always only one but use
	 // a vector anyway - it automatically deals with case 
	 // in which there are no matching counters...)
	 fetch_Counters(counters10,_mtc10CentralMap,wire);

	 // Check counters
	 // This gets a bit tricky.  Begin with separate bools for 05 
	 // and 10 requirements.  Initialize these to true when 
	 // the respective counter list is empty (required for final AND)
	 bool answer05 = counters05.size()==0;
	 bool answer10 = counters10.size()==0;
	 
	 // Loop over 05 counters, need OR of these
	 for (int icount=0; icount < counters05.size(); ++icount) {
	    answer05 |= (_MTCxxCentral[octant][counters05[icount]] != 0);
	 }

	 // Loop over 10 counters, need OR of these   
	 for (int icount=0; icount < counters10.size(); ++icount) {
	    answer10 |= (_MTCxxCentral[octant][counters10[icount]] != 0);
	 }

	 // Answer is AND of 05 and 10 answers (only if a non-zero number
	 // of counters were tested...
	 return ((counters05.size()!=0 || counters10.size()!=0) &&
		 (answer05 && answer10));
      }
	 
      break;

      case 1: // North
      {
	 // Don't check forward counters for central region
	 if (eta==0) return false;

	 // Forward differs from central in that we can simply 
	 // AND all of the counters in a given subregion
	 // (we don't have to worry about ORing 05 counters because
	 // there are never more than one for a given constraint set)
	 // Consequently, only one vector of counters is needed for
	 // each of the two subregions (forward and far)
	 std::vector<int> countersForward, countersFar; 

	 // Fetch 05 Forward counters
	 std::pair<int,int> key05(track, scint);
	 fetch_Counters(countersForward,_mtc05ForwardMap,key05);

	 // Fetch 10 Forward counters
	 fetch_Counters(countersForward,_mtc10ForwardMap,wire);

	 // If eta is 'all' or 'b', fetch far counters
	 if (eta==2 || eta==3) {
	    
	    // Fetch 05 Far counters
	    std::pair<int,int> key05_far(track, scint);
	    fetch_Counters(countersFar,_mtc05FarMap,key05_far);

	    // Fetch 10 Far counters
	    fetch_Counters(countersFar,_mtc10FarMap,wire);
	 }

	 // Now we AND all of the counters in each subregion
	 bool answerForward = countersForward.size()!=0;
	 for (int icount=0; icount < countersForward.size(); ++icount) {
	    answerForward &= (_MTCxxNorth[octant][countersForward[icount]]!=0);
	 }

	 bool answerFar = countersFar.size()!=0;
	 for (int icount=0; icount < countersFar.size(); ++icount) {
	    answerFar &= (_MTCxxNorth[octant][countersFar[icount]]!=0);
	 }

	 // OR the answers for the two subregions
	 return (answerForward || answerFar);

      }	    

      break;

      case 2: // South
      {
	 // Don't check forward counters for central region
	 if (eta==0) return false;

	 // Forward differs from central in that we can simply 
	 // AND all of the counters in a given subregion
	 // (we don't have to worry about ORing 05 counters because
	 // there are never more than one for a given constraint set)
	 // Consequently, only one vector of counters is needed for
	 // each of the two subregions (forward and far)
	 std::vector<int> countersForward, countersFar; 

	 // Fetch 05 Forward counters
	 std::pair<int,int> key05(track, scint);
	 fetch_Counters(countersForward,_mtc05ForwardMap,key05);

	 // Fetch 10 Forward counters
	 fetch_Counters(countersForward,_mtc10ForwardMap,wire);

	 // If eta is 'all' or 'b', fetch far counters
	 if (eta==2 || eta==3) {
	    
	    // Fetch 05 Far counters
	    std::pair<int,int> key05_far(track, scint);
	    fetch_Counters(countersFar,_mtc05FarMap,key05_far);

	    // Fetch 10 Far counters
	    fetch_Counters(countersFar,_mtc10FarMap,wire);
	 }

	 // Now we AND all of the counters in each subregion
	 bool answerForward = countersForward.size()!=0;
	 for (int icount=0; icount < countersForward.size(); ++icount) {
	    answerForward &= (_MTCxxSouth[octant][countersForward[icount]]!=0);
	 }

	 bool answerFar = countersFar.size()!=0;
	 for (int icount=0; icount < countersFar.size(); ++icount) {
	    answerFar &= (_MTCxxSouth[octant][countersFar[icount]]!=0);
	 }

	 // OR the answers for the two subregions
	 return (answerForward || answerFar);

      }	    

      break;

      default:
	 
	 return false;

   }
   

   // Test counters
   return false;

}

/************************************************************************/
int L1MuTermsClass::OctantCounterCombine(int counter1, int counter2)
{
  // a simple truth table for combining the octant counters

  //  in1     in0    out
  //   0       X      0
  //   X       0      0   in1 = 0 or in0 = 0
  //   1      !=0     1
  //  !=0      1      1   in1 = 1 or in0 = 1
  //   2       2      2
  //   3       2      2   else 
  //   2       3      2
  //   3       3      2

  if(counter1 < 1 || counter2 < 1) return(0); 
  if(counter1 == 1 || counter2 == 1) return(1);
  return(2);
} 
