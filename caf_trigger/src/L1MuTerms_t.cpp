// L1MuTerms_t.cpp
//
// code by Stefan Anderson, Arizona State University
//
#include "caf_trigger/L1MuTerms.hpp"

#include <iostream>
#include <string>
#include <cassert>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

//**********************************************************************

int main( ) {

  string component = "L1MuTerms";
  string ok_prefix = component + " (I): ";
  string error_prefix = component + " test (E): ";

  cout << ok_prefix
       << "---------- Testing component " + component
          + ". ----------" << endl;

  // Make sure assert is enabled.
  bool assert_flag = false;
  assert ( ( assert_flag = true, assert_flag ) );
  if ( ! assert_flag ) {
    cerr << "Assert is disabled" << endl;
    return 1;
  }

  //********************************************************************

  //********************************************************************

  cout << ok_prefix
       << "------------- All tests passed. -------------" << endl;
  return 0;

  //********************************************************************

}

