#ifndef pparameterreader_hpp
#define pparameterreader_hpp

#include "TEnv.h"
#include "TOrdCollection.h"
#include "TObjArray.h"
#include "TString.h"
#include "TObjString.h"
#include "THashList.h"
#include "TDirectory.h"
#include "TSystem.h"

#include <memory>
#include <iostream>
#include <set>
#include <cstdlib>
#include <stdexcept>

class PParameterReader
{
public:
  PParameterReader(const char *file);
  ~PParameterReader();

  void Print() { _env->Print(); };

  //Methods without a dflt parameter will casue an
  //assertion if name isn't found.

  Float_t  GetFloat(const char *name);
  Float_t  GetFloat(const char *name, const Float_t dflt);

  Double_t GetDouble(const char *name);
  Double_t GetDouble(const char *name, Double_t dflt);

  Bool_t   GetBool(const char *name);
  Bool_t   GetBool(const char *name, Bool_t dflt);

  Int_t    GetInt(const char *name);
  Int_t    GetInt(const char *name, Int_t dflt);

  const char* GetChar(const char *name);
  const char* GetChar(const char *name, const char *dflt);

  // Code copied from cafe/src/Config.cpp
  // Get string value from config DB.
  std::string get(const std::string& key, const std::string& def);
  
  // Get list of floats from config DB.
  std::vector<float> GetVFloat(const std::string& key, const std::string& delim = ", ");

  // Get list of doubles from config DB.
  std::vector<double> GetVDouble(const std::string& key, const std::string& delim = ", ");

  // Get list of strings of config DB.
  std::vector<std::string> GetVString(const std::string& key, const std::string& delim = ", ");

  // Get list of integers from config DB.
  std::vector<int> GetVInt(const std::string& key, const std::string& delim = ", ");

private:
  TEnv *_env;
  void _Assert(const char *name);

};

#endif
