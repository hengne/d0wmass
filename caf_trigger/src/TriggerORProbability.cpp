/* File TriggerORProbability.hpp
 *
 * Created       : Wed Aug 16 07:46:01 CDT 2006
 * Author        : filthaut
 * Purpose       : 
 * Last modified : 
 * Comments      : 
 */

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"

#include "caf_trigger/TriggerORProbability.hpp"

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// Constructor, destructor: 
TriggerORProbability::TriggerORProbability(const char *name) : probProcessor(name) {
  cafe::Config config(name);

  cout << "\nTriggerORProbability [" << name << "] initialization:" << endl;

  //------------------------------------
  // Get the list of trigger versions
  //------------------------------------
  _trigger_version = config.getVString("TriggerVersions", ",");

  //------------------------------------
  // Channel name
  // This is the value specified to combine in the config file
  //------------------------------------
  _channel = config.get("ChannelName", "TriggerORProbability");
  cout << "\tOutput Channel name:\t" << _channel << endl;

  //------------------------------------
  // Debug
  //------------------------------------
  setDebug(config.get("Debug", 0));

  //------------------------------------
  // Triggers to combine in an OR
  //------------------------------------
  _inputChannels = config.getVString("ChannelNames", " ,");
  //assert(_inputChannels.size() == 3);
  cout << "\tInput Channel names:\t";
  for (int c = 0; c < _inputChannels.size(); ++c)
    cout << " " << _inputChannels[c];
  cout << endl;

  bool foundAND = false;
  string triggerAND;
  for (int tr = 0; tr < _inputChannels.size(); ++tr) {
    stringstream prescName;
    prescName << _inputChannels[tr] << "PrescaleFractions";
    vector<float> fractions = config.getVFloat(prescName.str().c_str(), " ,");
    assert(fractions.size() == _trigger_version.size());
    cout << "\tPresc fract for channel " << _inputChannels[tr] << ":\t";
    for (int f = 0; f < fractions.size(); ++f) cout << " " << fractions[f];
    cout << endl;
    // Make some sanity checks: one channel should correspond to the AND of the
    // triggers, and this should be characterized by negative prescale factors.
    if (foundAND) {
      for (int vers = 0; vers < _trigger_version.size(); ++vers)
	assert(fractions[vers] >= 0);
    } else {
      bool foundPositive = false;
      bool foundNegative = false;
      for (int vers = 0; vers < _trigger_version.size(); ++vers) {
	if (fractions[vers] == 0) continue;
	if (fractions[vers] > 0) foundPositive = true;
	if (fractions[vers] < 0) foundNegative = true;
      }
      assert(!(foundPositive && foundNegative));
      foundAND = foundNegative;
      triggerAND = _inputChannels[tr];
    }
    map<string, double> fracts;
    for (int vers = 0; vers < _trigger_version.size(); ++vers)
      fracts[_trigger_version[vers]] = fractions[vers];
    _prescaleFractions[_inputChannels[tr]] = fracts;
  }

  for (int vers = 0; vers < _trigger_version.size(); ++vers) {
    stringstream refName;
    refName << "LumiRefTrigger_" << _trigger_version[vers];
    _lumiRefTrigger[_trigger_version[vers]] = config.get(refName.str().c_str(), "");
    assert(find(_inputChannels.begin(), _inputChannels.end(), _lumiRefTrigger[_trigger_version[vers]]) != _inputChannels.end());
  }

  // print our configuration
  cout << "\nTriggerORProbability[" << name << "] initialization:\n"
       << "\ttrigger versions:";
  for (int vers = 0; vers < _trigger_version.size(); ++vers)
    cout << " " << _trigger_version[vers];
  cout << "\n\tInput \"channels\" and corresponding prescale fractions:";
  for (int tr = 0; tr < _inputChannels.size(); ++tr) {
    cout << "\n\t" << _inputChannels[tr];
    for (int vers = 0; vers < _trigger_version.size(); ++vers)
      cout << " " << _prescaleFractions[_inputChannels[tr]][_trigger_version[vers]];
  }
  cout << "\n\tluminosity references:";
  for (int vers = 0; vers < _trigger_version.size(); ++vers)
    cout << " " << _lumiRefTrigger[_trigger_version[vers]];
  cout << "\n\tAssuming AND channel = " << triggerAND << "\n" << endl;
}

TriggerORProbability::~TriggerORProbability() {

}

void TriggerORProbability::eventWeight(std::map<std::string, double> &mRefEvtw) {
  assert(_triggerPeriod != "none");

  double combinedProbability = 0;
  for (int tr = 0; tr < _inputChannels.size(); ++tr) {
    string channel = _inputChannels[tr];
    // Note: the prescale fraction for the AND channel is supposed to be negative!
    combinedProbability += _prescaleFractions[channel][_triggerPeriod] * mRefEvtw[channel];
  }
  if (debug() > 2) {
    cout << "TriggerORProbability[" << name() << "] input probabilities:";
    for (int tr = 0; tr < _inputChannels.size(); ++tr) {
      string channel = _inputChannels[tr];
      cout << " " << channel << "(" << mRefEvtw[channel] << ","
	   << _prescaleFractions[channel][_triggerPeriod] << ")";
    }
    cout << endl;
  }

  // Finally, correct for the average prescale factor of the reference channel
  std::string refTrigger = _lumiRefTrigger[_triggerPeriod];
  combinedProbability /= _prescaleFractions[refTrigger][_triggerPeriod];

  if (debug() > 1)
    cout << "TriggerORProbability[" << name() << "] result: "
	 << combinedProbability << endl;
  if (combinedProbability > 1) {
    if (debug() > 0) {
      cout << "TriggerORProbability[" << name() << "] input probabilities:";
      for (int tr = 0; tr < _inputChannels.size(); ++tr) {
	string channel = _inputChannels[tr];
	cout << " " << channel << "(" << mRefEvtw[channel] << ","
	     << _prescaleFractions[channel][_triggerPeriod] << ")";
      }
      cout << " result = " << combinedProbability << ", set to 1" << endl;
    }
    combinedProbability = 1;
  }

  mRefEvtw[_channel] = combinedProbability;

}

ClassImp(TriggerORProbability);
