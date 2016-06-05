//file: objectProbabilities.cpp {objectProbabilities.hpp}
//
//Author:   Kevin Chan
//
//Purpose:  Calculates object probabilities to pass the trigger requirement.
//          This using an interface to eff_utils.
//History: 
//2008.04.01 Liang Li: Added JES conversion tool which converts final JES jet back to preliminary JES jet so we can apply jet trigger turn-ons (measured with preliminary JES jets)
//2008.03.10 Liang Li: Implemented "JetActAs" switch, also included Run2a final vs. preliminary JES correction
//2007.10.16 Liang Li: Implemented Run2b switch (to decide whether or not to use p20 jet eta definition and more...), also added Prolay's "absdeta" eta definition 
//2007.06.25 Liang Li: Fixed a bug when mSigma.find() returns a null pointer, also added many debugging routines  (to be integrated with Probability_* processors' debugging output)
//2006.09.23 LSC: Included uncertainty calculation.
//Usage:
//
//Example:

//Header file for this class
#include "caf_trigger/objectProbabilities.hpp"
#include "jetcorr/CalTool.hpp"
#include "eff_utils/BinnedEfficiency.hpp"
#include "TRandom.h"

using namespace eff_utils;
using namespace std;

objectProbabilities::objectProbabilities(EffInfo &effInfoObj, const std::string &path,
					 bool ignoreOverflow, bool ignoreUnderflow, bool isRun2b) : 
  _effTool(0), _PrelCTable(0)
{
  
  //First, we request the efficiency object using the EffTool
  //This set of exception handling provided by Slava.
  try {
    //    std::cout << "Making Tool" << std::endl;
    _effTool = new EffTool( effInfoObj, path );
    //    std::cout << "Done Making Tool" << std::endl;
  }
  catch (eff_utils::EffException& errEffTool) {

    //If it's not created, spit out an error and exit
    cout << endl;
    std::cout   << "caf_trigger::objectProbabilities" << std::endl;
    std::cout << "Could not create an EffTool" << std::endl;
    cout << "ErrEffTool message: " << errEffTool._message << std::endl;
    cout << "caf_trigger:\tThe request:" << std::endl;
    cout << effInfoObj << std::endl;    
    exit(1);
  }
    
    
  //And make sure that this is valid
  if( !_effTool->isValid() ) {
    std::cout << "caf_trigger::objectProbabilities" << endl;
    std::cout << "No exception was caught, but the tool is not valid" << endl;
    exit(1);
  }


  // set ignore Over(under)flow mode
  if (ignoreOverflow || ignoreUnderflow) {
    const BinnedEfficiency* beff = dynamic_cast<const BinnedEfficiency*> (&_effTool->EffObj()) ;
    if (beff) {
      if (ignoreOverflow && ignoreUnderflow) 
	beff->setExeptionMode(BinnedEfficiency::IGNORE_UNDEROVERFLOW) ;
      else if (ignoreOverflow ) 
	beff->setExeptionMode(BinnedEfficiency::IGNORE_OVERFLOW) ;
      else if (ignoreUnderflow) 
	beff->setExeptionMode(BinnedEfficiency::IGNORE_UNDERFLOW) ;
    }
  }
  

  //if ( path.find("jetid_eff/p17.09.03") != string::npos ) {
  if(!isRun2b){
 // load in Run2a preliminary to final JES correction table
        if ( _PrelCTable == 0 ) _PrelCTable = new PrelCorr("caf_trigger/parameters/RunIIa_PrelC_ratio.table");
	if ( _PrelCTable == 0 ) {
	   std::cout << "caf_trigger::objectProbabilities, error:" << std::endl;
	   std::cout << "Could not load preliminary to final JES correction table from caf_trigger/parameters/RunIIa_PrelC_ratio.table!" << std::endl;
	   std::cout << "Path = " << path << std::endl;
	   std::cout << "Exit." << std::endl;
	   exit(1);
	}
	//cout << (*_PrelCTable)(100,-3) << endl;
	//cout <<  "caf_trigger::objectProbabilities, path = "<< path << ", got table!" << endl;
  }else{
    if ( _PrelCTable != 0 ) delete _PrelCTable;
    _PrelCTable = 0;
  }
  
}

void objectProbabilities::setSigma(std::map<std::string, float> Sigma)
{
  mSigma.clear();

  mSigma = Sigma;
}

//The probability of one of N objects to fire the trigger
double objectProbabilities::getProb1Objects(
					    const cafe::Collection<TMBEMCluster> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill this variable with the result of getProbability as
  //a temporary variable to allow us to calculate the final probability.
  double tmpProb1 = 1.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 1) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Loop over whatever object is passed
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);

  }

  //Take the negative of the final probability if it is not out of bounds
  //and return it
  probCalc = 1.0 - tmpProb1;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability of two objects of N to fire the trigger
double objectProbabilities::getProb2Objects(
					    const cafe::Collection<TMBEMCluster> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 2) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }


  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for three of N objects to fire the trigger
double objectProbabilities::getProb3Objects(
					    const cafe::Collection<TMBEMCluster> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 3) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for four of N objects to fire the trigger
double objectProbabilities::getProb4Objects(
					    const cafe::Collection<TMBEMCluster> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;
  double tmpProb4 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 4) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)

    //Probability of four objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    double tmpForProb4 = 1.0;
        
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= probArray[kobj];

	    //and the fourth object
	    for(unsigned int lobj = 0; lobj < object.size(); ++lobj) {

	      //If the four objects aren't equal..
	      if(lobj != iobj && lobj != jobj && lobj != kobj) {
		tmpForProb4 *= (1.0 - probArray[lobj]);
	      } //endif

	    } //endfor(lobj)
                        
	  } //endif
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb4 += tmpForProb1 * tmpForProb2 * tmpForProb3 * tmpForProb4;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3 - tmpProb4;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}


//The probability of one of N objects to fire the trigger
double objectProbabilities::getProb1Objects(
					    const cafe::Collection<TMBMuon> &object) const
{

  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill this variable with the result of getProbability as
  //a temporary variable to allow us to calculate the final probability.
  double tmpProb1 = 1.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 1) {

    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }


  //Loop over whatever object is passed
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);

  }

  //Take the negative of the final probability if it is not out of bounds
  //and return it
  probCalc = 1.0 - tmpProb1;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability of two objects of N to fire the trigger
double objectProbabilities::getProb2Objects(
					    const cafe::Collection<TMBMuon> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 2) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }


  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for three of N objects to fire the trigger
double objectProbabilities::getProb3Objects(
					    const cafe::Collection<TMBMuon> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 3) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for four of N objects to fire the trigger
double objectProbabilities::getProb4Objects(
					    const cafe::Collection<TMBMuon> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;
  double tmpProb4 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 4) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)

    //Probability of four objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    double tmpForProb4 = 1.0;
        
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= probArray[kobj];

	    //and the fourth object
	    for(unsigned int lobj = 0; lobj < object.size(); ++lobj) {

	      //If the four objects aren't equal..
	      if(lobj != iobj && lobj != jobj && lobj != kobj) {
		tmpForProb4 *= (1.0 - probArray[lobj]);
	      } //endif

	    } //endfor(lobj)
                        
	  } //endif
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb4 += tmpForProb1 * tmpForProb2 * tmpForProb3 * tmpForProb4;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3 - tmpProb4;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}


//The probability of one of N objects to fire the trigger
double objectProbabilities::getProb1Objects(
					    const cafe::Collection<TMBJet> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill this variable with the result of getProbability as
  //a temporary variable to allow us to calculate the final probability.
  double tmpProb1 = 1.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 1) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Loop over whatever object is passed
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);

  }

  //Take the negative of the final probability if it is not out of bounds
  //and return it
  probCalc = 1.0 - tmpProb1;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability of two objects of N to fire the trigger
double objectProbabilities::getProb2Objects(
					    const cafe::Collection<TMBJet> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 2) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }


  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for three of N objects to fire the trigger
double objectProbabilities::getProb3Objects(
					    const cafe::Collection<TMBJet> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 3) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for four of N objects to fire the trigger
double objectProbabilities::getProb4Objects(
					    const cafe::Collection<TMBJet> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;
  double tmpProb4 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 4) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)

    //Probability of four objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    double tmpForProb4 = 1.0;
        
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= probArray[kobj];

	    //and the fourth object
	    for(unsigned int lobj = 0; lobj < object.size(); ++lobj) {

	      //If the four objects aren't equal..
	      if(lobj != iobj && lobj != jobj && lobj != kobj) {
		tmpForProb4 *= (1.0 - probArray[lobj]);
	      } //endif

	    } //endfor(lobj)
                        
	  } //endif
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb4 += tmpForProb1 * tmpForProb2 * tmpForProb3 * tmpForProb4;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3 - tmpProb4;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}
/// Tau probabilities (based on jets above but uses TMBTau)

//The probability of one of N objects to fire the trigger
double objectProbabilities::getProb1Objects(
					    const cafe::Collection<TMBTau> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill this variable with the result of getProbability as
  //a temporary variable to allow us to calculate the final probability.
  double tmpProb1 = 1.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 1) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Loop over whatever object is passed
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);

  }

  //Take the negative of the final probability if it is not out of bounds
  //and return it
  probCalc = 1.0 - tmpProb1;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability of two objects of N to fire the trigger
double objectProbabilities::getProb2Objects(
					    const cafe::Collection<TMBTau> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 2) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }


  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for three of N objects to fire the trigger
double objectProbabilities::getProb3Objects(
					    const cafe::Collection<TMBTau> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 3) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}

//The probability for four of N objects to fire the trigger
double objectProbabilities::getProb4Objects(
					    const cafe::Collection<TMBTau> &object) const
{
  //This variable will be multiplied several times and ultimately
  //returned from whence it came.
  double probCalc = 0.0;

  //We shall fill these variables with the result of getProbability as
  //temporary variables to allow us to calculate the final probability.
  double tmpProb1 = 1.0;
  double tmpProb2 = 0.0;
  double tmpProb3 = 0.0;
  double tmpProb4 = 0.0;

  //Passing a sigma through to the probability
  double sig = 0.0;

  //We setup an array to simplify the code and check that the number
  //of objects is valid
  std::vector<double> probArray;
  if(object.size() < 4) {
    return 0.0;
  }
    
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
    probArray.push_back( getProbability(object[iobj], sig) );
  }

  //Probability of a single object to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {

    //Get the individual probability for the 
    tmpProb1 *= (1.0 - probArray[iobj]);
  }

  //Probability of two objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the second object to fire the trigger
    //if it is NOT the same object as the first
    double tmpForProb2 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= (1.0 - probArray[jobj]);
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb2 += tmpForProb1 * tmpForProb2;

  } //endfor(iobj)

    //Probability of three objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= (1.0 - probArray[kobj]);
	  }
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb3 += tmpForProb1 * tmpForProb2 * tmpForProb3;

  } //endfor(iobj)

    //Probability of four objects to fire the trigger
  for(unsigned int iobj = 0; iobj < object.size(); ++iobj) {
        
    //Get the probability for one object
    double tmpForProb1 = probArray[iobj];
        
    //Then the probability for the third object to fire the trigger
    //if it is NOT the same object as the first or second
    double tmpForProb2 = 1.0;
    double tmpForProb3 = 1.0;
    double tmpForProb4 = 1.0;
        
    for(unsigned int jobj = 0; jobj < object.size(); ++jobj) {
            
      //If the two objects are different, get the probability
      //of the second object
      if(jobj != iobj) {
	tmpForProb2 *= probArray[jobj];

	//and the third object
	for(unsigned int kobj = 0; kobj < object.size(); ++kobj) {

	  //If the three objects aren't equal..
	  if(kobj != iobj && kobj != jobj) {
	    tmpForProb3 *= probArray[kobj];

	    //and the fourth object
	    for(unsigned int lobj = 0; lobj < object.size(); ++lobj) {

	      //If the four objects aren't equal..
	      if(lobj != iobj && lobj != jobj && lobj != kobj) {
		tmpForProb4 *= (1.0 - probArray[lobj]);
	      } //endif

	    } //endfor(lobj)
                        
	  } //endif
                    
	} //endfor(kobj)
                
      } //endif

    } //endfor(jobj)
        
    //Now we finish this little calculation by multiplying these
    //temporary probabilities
    tmpProb4 += tmpForProb1 * tmpForProb2 * tmpForProb3 * tmpForProb4;

  } //endfor(iobj)


    //Take the negative of the final probability if it is not out of bounds
    //and return it
  probCalc = 1.0 - tmpProb1 - tmpProb2 - tmpProb3 - tmpProb4;

  if(probCalc > 1.0) {
    probCalc = 1.0;
  }
  else if(probCalc < 0.0) {
    probCalc = 0.0;
  }

  return probCalc;
}
/// end Tau Probability calculations (from one to four objects)

double objectProbabilities::getProbability(const TMBTrack &iObject, double &stat) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,true,false);
}

double objectProbabilities::getProbability(const TMBTrack &iObject, double &stat, bool isRun2b) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBTrack &iObject, double &stat, bool isRun2b, bool debug) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,debug);
}

double objectProbabilities::getProbability(const TMBTrack &iObject, double &stat, EffVal &eff) const
{
  return getProbability(iObject,stat,eff,true,false);
}

double objectProbabilities::getProbability(const TMBTrack &iObject, double &stat, EffVal &eff, bool isRun2b) const
{
  return getProbability(iObject,stat,eff,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBTrack &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const
{
  //Liang Li: debugging info begins	
  if ( debug ) {
	cout << "\tobjectProbabilities::getProbability TMBTrack debugging info starts:" << endl;
        if ( isRun2b) {
		cout << "\t\tEvent is Run2b" << endl;
        }
	else {
		cout << "\t\tEvent is Run2a" << endl;
	}
  }
	  
  //We create a local EffInfo object
  const EffInfo &effInfoObj = _effTool->Info();
    
  //We grab the variable names as a vector of strings from the info object
  //and the number of objects
  std::vector< std::string > axisNames = effInfoObj.EffVarNames();
  unsigned int nAxisNames = effInfoObj.EffNVars();

  if ( debug ) cout << "\t\tTrack axis size: " << axisNames.size() << endl;
	  
  //Error checks
  if( nAxisNames != axisNames.size() ) {
    std::cout << "objectProbabilities::getProbability" << std::endl
	      << "- Error: Number of variables in the efficiency" << std::endl
	      << "-        is inconsistent" << std::endl;
  }

  //A series of if statements which I don't really like. This takes
  //the retrieved x-axis name and grabs the appropriate value.
  std::vector< float > xEval;
  if ( axisNames.size() == 0 ) {
    xEval.push_back( -1000.0 );
  }
  else {
    for ( int i = 0; i < axisNames.size(); i++ ) {
	
        //We want the strings in lower case
        std::transform(axisNames[i].begin(), axisNames[i].end(), axisNames[i].begin(), (int(*)(int))std::tolower);

      if ( axisNames[i] == "eta" ) {
	xEval.push_back(iObject.Eta());
	if ( debug ) cout << "\t\tTrack eta: " << iObject.Eta() << endl;	      
      }
      else if ( axisNames[i] == "z" ) {
	xEval.push_back(iObject.z());
	if ( debug ) cout << "\t\tTrack z: " << iObject.z() << endl;	      
      }
      else if ( axisNames[i] == "cfteta" ) {
	xEval.push_back(iObject.det_etaCFT());
	if ( debug ) cout << "\t\tTrack cfteta: " << iObject.det_etaCFT() << endl;	      
      }
      else if ( axisNames[i] == "cft_eta" ) {
	xEval.push_back(iObject.det_etaCFT());
	if ( debug ) cout << "\t\tTrack cfteta: " << iObject.det_etaCFT() << endl;	 	      
      }
      else if ( axisNames[i] == "phi" ) {
	xEval.push_back(iObject.Phi());
	if ( debug ) cout << "\t\tTrack phi: " << iObject.Phi() << endl;	 	      
      }
      else if ( axisNames[i] == "pt" ) {
	xEval.push_back(iObject.Pt());
      }
      else {
	std::cout << "objectProbabilities::getProbability Error: Invalid variable - " << axisNames[i].c_str() << std::endl;
      }
    }
  }
    
    
  //Now we get the values we require
  //Condense xEval to a single value'd vector
  EffVal values;
  if ( debug ) cout << "\t\txEval size: " << xEval.size() << endl;	  
  try {        
    if ( xEval.size() == 1 ) {
      values = _effTool->EffObj().Eff( xEval[0] );
    }
    else if ( xEval.size() == 2 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1] );
    }
    else if ( xEval.size() == 3 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1], xEval[2] );
    }
    else {
      std::cout << "objectProbabilities::getProbability Error: caf_trigger only supports 1-3 variables but you give " << xEval.size() << " variable(s)" << std::endl;
      exit(1);
    }
  }
  catch (const EffException& ex) {

    //We caught an exception from the EffTool, so we'll return 0
    std::cout << "objectProbabilities WARNING: eff_utils exception " << endl
	      << ex._message << endl
	      << "TMBTrack with";
    for (int i=0; i<xEval.size(); i++) {
      std::cout << "  " << axisNames[i] << "=" << xEval[i];
    }
    std::cout << std::endl;
    eff.val=0;
    eff.binno=-1;
    eff.elo=0;
    eff.ehi=0;
    return 0.0;
  }
    
  //And create local variables for them
  //LSC: These are my modifications or really a patch to deal with systematics errors.
  //double grabbedProb  = values.val;
  double grabbedProb = 0.0;

  double effNom       = values.val;
  double effHigh      = values.ehi;
  double effLow       = values.elo;
  eff                 = values;

  if (stat==1.0)  grabbedProb = effNom + effHigh;
  if (stat==0.0)  grabbedProb = effNom;
  if (stat==-1.0) grabbedProb = effNom - effLow;

  if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  else if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  
  if ( debug ) {
	cout << "\t\teffNom: " << effNom <<endl;
	cout << "\t\teffHigh: " << effHigh << endl;
	cout << "\t\teffLow: " << effLow << endl;
	cout << "\t\tstat: " << stat << endl;
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
  }
  
  //Not sure what to do at this point so how about we just set the high or
  //low as some sort of error?
  double error = 0.0;

  if( fabs(effHigh) >= fabs(effLow) ) {
    error = fabs(effHigh); //FIX ME
  }
  else {
    error = fabs(effLow); //FIX ME
  }

  // LSC: The initial uncertainty calculation will assume Gaussian uncertainties.
  // Some variables are for later implementation of asymmetric errors.
  double uncertainty_high = 0.0;
  double uncertainty_low = 0.0;
  double uncertainty = 0.0;
  // Monte Carlo an uncertainty value inside the one sigma frequentist interpretation.
  TRandom interval;
  if (effHigh>=effLow) {
    //uncertainty_high = interval.Gaus(0,effHigh);
    uncertainty = fabs( interval.Gaus(0,effHigh) );
    while ( effHigh < uncertainty ) uncertainty = fabs( interval.Gaus(0,effHigh) );
  } else {
    //uncertainty_low  = interval.Gaus(0,effLow);
    uncertainty  = fabs( interval.Gaus(0,effLow) );
    while ( effLow < uncertainty ) uncertainty = fabs( interval.Gaus(0,effLow) );
  }
  stat = uncertainty;
  
  if ( debug ) {
	cout << "\t\tStatistical uncertainty is = " << stat << endl;  
        cout << "\t\tUpper uncertainty is = " << effHigh << endl;  
        cout << "\t\tLower uncertainty is = " << effLow  << endl;  
  }


  //And this is where the sigma variations are applied if there are any with the sigma map mSigma
  //NOT WORKING!!!
  std::string type = "";
  std::string level = "";
    
  type = effInfoObj.ObjType();
    
  if ( effInfoObj.EffName().find("L1") < effInfoObj.EffName().size()
       || effInfoObj.EffName().find("l1") < effInfoObj.EffName().size() ) {
    level = "L1";
  }
  else if ( effInfoObj.EffName().find("L2") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l2") < effInfoObj.EffName().size() ) {
    level = "L2";
  }
  else if ( effInfoObj.EffName().find("L3") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l3") < effInfoObj.EffName().size() ) {
    level = "L3";
  }

  std::string key = type + " " + level;

  if ( debug ) {
	cout << "\t\tObjType: " << type << endl;
	cout << "\t\tEffName: " << effInfoObj.EffName() << endl;
	cout << "\t\tLevel: " << level << endl;
  }	
  
  //Now we check the probability with the sigma
  //Liang Li: mSigma may be obsolete, deal with null pointer exception!
  std::map<std::string, float>::const_iterator it = mSigma.find(key) ;
  if (it != mSigma.end()) grabbedProb += error * it->second;
	  
  if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  else if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  
  if ( debug ) {
	cout << "\t\tkey: " << key << endl;
	cout << "\t\terror: " << error << endl;
	cout << "\t\tmSigma size: " << mSigma.size() << endl;  
	std::map<std::string, float>::const_iterator iter;
	for ( iter = mSigma.begin(); iter != mSigma.end(); iter++ ) {
		cout << "\t\tmSigma key: " << iter->first << " , value: " << iter->second << endl;
	}	
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
	cout << "\tobjectProbabilities::getProbability TMBTrack debugging info ends." << endl;
  }	  
    
  return grabbedProb;
}


double objectProbabilities::getProbability(const TMBEMCluster &iObject, double &stat) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,true,false);
}

double objectProbabilities::getProbability(const TMBEMCluster &iObject, double &stat, bool isRun2b) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBEMCluster&iObject, double &stat, bool isRun2b, bool debug) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,debug);
}

double objectProbabilities::getProbability(const TMBEMCluster &iObject, double &stat, EffVal &eff) const
{
  return getProbability(iObject,stat,eff,true,false);
}

double objectProbabilities::getProbability(const TMBEMCluster &iObject, double &stat, EffVal &eff, bool isRun2b) const
{
  return getProbability(iObject,stat,eff,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBEMCluster &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const
{
  //Liang Li: debugging info begins	
  if ( debug ) {
	cout << "\tobjectProbabilities::getProbability TMBEMCluster debugging info starts:" << endl;
        if ( isRun2b) {
		cout << "\t\tEvent is Run2b" << endl;
        }
	else {
		cout << "\t\tEvent is Run2a" << endl;
	}
  }	  
	
  //We create a local EffInfo object
  const EffInfo &effInfoObj = _effTool->Info();
    
  //We grab the variable names as a vector of strings from the info object
  //and the number of objects
  std::vector< std::string > axisNames = effInfoObj.EffVarNames();
  unsigned int nAxisNames = effInfoObj.EffNVars();

  if ( debug ) cout << "\t\tEM axis size: " << axisNames.size() << endl;
  
  //Error checks
  if( nAxisNames != axisNames.size() ) {
    std::cout << "objectProbabilities::getProbability" << std::endl
	      << "- Error: Number of variables in the efficiency" << std::endl
	      << "-        is inconsistent" << std::endl;
  }

  //A series of if statements which I don't really like. This takes
  //the retrieved x-axis name and grabs the appropriate value.
  std::vector< float > xEval;
  if ( axisNames.size() == 0 ) {
    xEval.push_back( -1000.0 );
  }
  else {
    for ( int i = 0; i < axisNames.size(); i++ ) {
	
        //We want the strings in lower case
        std::transform(axisNames[i].begin(), axisNames[i].end(), axisNames[i].begin(), (int(*)(int))std::tolower);
        
      if ( axisNames[i] == "eta" ) {
	if ( debug ) cout << "\t\tEM eta: " << iObject.Eta() << endl;
	xEval.push_back(iObject.Eta());
      }
      else if ( axisNames[i] == "deteta" ) {
	if ( debug ) cout << "\t\tEM deteta: " << iObject.CalDetectorEta() << endl;	      
	xEval.push_back(iObject.CalDetectorEta());
      }
      else if ( axisNames[i] == "phi" ) {
	if ( debug ) cout << "\t\tEM phi: " << iObject.Phi() << endl;
	xEval.push_back(iObject.Phi());
      }
      else if ( axisNames[i] == "pt" ) {
	if ( debug ) cout << "\t\tEM pt: " << iObject.Pt() << endl;
	xEval.push_back(iObject.Pt());
      }
      else {
	std::cout << "objectProbabilities::getProbability Error: Invalid variable - " << axisNames[i].c_str() << std::endl;
      }
      
      if ( debug ) cout << "\t\tEM axis " << i << " : " << axisNames[i] << ", xEVal: " << xEval[i] << endl;
	      
    }
  }
    
    
  //Now we get the values we require
  //Condense xEval to a single value'd vector
  if ( debug ) cout << "\t\txEval size: " << xEval.size() << endl;  
  EffVal values;
  try {        
    if ( xEval.size() == 1 ) {
      values = _effTool->EffObj().Eff( xEval[0] );
    }
    else if ( xEval.size() == 2 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1] );
    }
    else if ( xEval.size() == 3 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1], xEval[2] );
    }
    else {
      std::cout << "objectProbabilities::getProbability Error: caf_trigger only supports 1-3 variables but you give " << xEval.size() << " variable(s)" << std::endl;
      exit(1);
    }
  }
  catch (const EffException& ex) {

    //We caught an exception from the EffTool, so we'll return 0
    std::cout << "objectProbabilities WARNING: eff_utils exception " << endl
	      << ex._message << endl
	      << "TMBEMCluster with";
    for (int i=0; i<xEval.size(); i++) {
      std::cout << "  " << axisNames[i] << "=" << xEval[i];
    }
    std::cout << std::endl;
    eff.val=0;
    eff.binno=-1;
    eff.elo=0;
    eff.ehi=0;
    return 0.0;
  }
    
  //And create local variables for them
  //LSC: These are my modifications or really a patch to deal with systematics errors.
  //double grabbedProb  = values.val;
  double grabbedProb = 0.0;

  double effNom       = values.val;
  double effHigh      = values.ehi;
  double effLow       = values.elo;
  eff                 = values;

  if (stat==1.0)  grabbedProb = effNom + effHigh;
  if (stat==0.0)  grabbedProb = effNom;
  if (stat==-1.0) grabbedProb = effNom - effLow;


  if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  else if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  
  if ( debug ) {
	cout << "\t\teffNom: " << effNom <<endl;
	cout << "\t\teffHigh: " << effHigh << endl;
	cout << "\t\teffLow: " << effLow << endl;
	cout << "\t\tstat: " << stat << endl;
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
  }
  
  //Not sure what to do at this point so how about we just set the high or
  //low as some sort of error?
  double error = 0.0;

  if( fabs(effHigh) >= fabs(effLow) ) {
    error = fabs(effHigh); //FIX ME
  }
  else {
    error = fabs(effLow); //FIX ME
  }

  //LSC: The initial uncertainty calculation will assume Gaussian uncertainties.
  //Some variables are for later implementation of asymmetric errors.
  double uncertainty_high = 0.0;
  double uncertainty_low = 0.0;
  double uncertainty = 0.0;
  // Monte Carlo an uncertainty value inside the one sigma frequentist interpretation.
  TRandom interval;
  if (effHigh>=effLow) {
    //uncertainty_high = interval.Gaus(0,effHigh);
    uncertainty = fabs( interval.Gaus(0,effHigh) );
    while ( effHigh < uncertainty ) uncertainty = fabs( interval.Gaus(0,effHigh) );
  } else {
    //uncertainty_low  = interval.Gaus(0,effLow);
    uncertainty  = fabs( interval.Gaus(0,effLow) );
    while ( effLow < uncertainty ) uncertainty = fabs( interval.Gaus(0,effLow) );
  }
  stat = uncertainty;
  
  if ( debug ) {
	cout << "\t\tStatistical uncertainty is = " << stat << endl;  
        cout << "\t\tUpper uncertainty is = " << effHigh << endl;  
        cout << "\t\tLower uncertainty is = " << effLow  << endl;  
  }

  
  //And this is where the sigma variations are applied if there are any
  //with the sigma map mSigma
  // NOT WORKING !!!!!!!!! //  
  std::string type = "";
  std::string level = "";
    
  type = effInfoObj.ObjType();
    
  if ( effInfoObj.EffName().find("L1") < effInfoObj.EffName().size()
       || effInfoObj.EffName().find("l1") < effInfoObj.EffName().size() ) {
    level = "L1";
  }
  else if ( effInfoObj.EffName().find("L2") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l2") < effInfoObj.EffName().size() ) {
    level = "L2";
  }
  else if ( effInfoObj.EffName().find("L3") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l3") < effInfoObj.EffName().size() ) {
    level = "L3";
  }
  
  if ( debug ) {
	cout << "\t\tObjType: " << type << endl;
	cout << "\t\tEffName: " << effInfoObj.EffName() << endl;
	cout << "\t\tLevel: " << level << endl;
  }	
  
  std::string key = type + " " + level;

  //Now we check the probability with the sigma
  //Liang Li: mSigma may be obsolete, deal with null pointer exception!
  std::map<std::string, float>::const_iterator it = mSigma.find(key) ;
  if (it != mSigma.end()) grabbedProb += error * it->second;

  if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  else if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  
  if ( debug ) {
	cout << "\t\tkey: " << key << endl;
	cout << "\t\terror: " << error << endl;
	cout << "\t\tmSigma size: " << mSigma.size() << endl;  
	std::map<std::string, float>::const_iterator iter;
	for ( iter = mSigma.begin(); iter != mSigma.end(); iter++ ) {
		cout << "\t\tmSigma key: " << iter->first << " , value: " << iter->second << endl;
	}	
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
	cout << "\tobjectProbabilities::getProbability TMBEMCluster debugging info ends." << endl;
  }	
  
  return grabbedProb;
}

double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,true,false,0);
}

double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, bool isRun2b) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,false,0);
}

double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, bool isRun2b, bool debug) 
const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,debug,0);
}

double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, EffVal &eff) const
{
  return getProbability(iObject,stat,eff,true,false,0);
}

double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b) const
{
  return getProbability(iObject,stat,eff,isRun2b,false,0,1.0);
}

double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const
{
  return getProbability(iObject,stat,eff,isRun2b,debug,0,1.0);

}


 double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug, int njets) const
{
  return getProbability(iObject,stat,eff,isRun2b,debug,njets,1.0);
}



double objectProbabilities::getProbability(const TMBMuon &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug, int njets, double instlum) const
{  //Liang Li: debugging info begins	
  if ( debug ) {
	cout << "\tobjectProbabilities::getProbability TMBMuon debugging info starts:" << endl;
        if ( isRun2b) {
		cout << "\t\tEvent is Run2b" << endl;
        }
	else {
		cout << "\t\tEvent is Run2a" << endl;
	}
  }
	  
  //We create a local EffInfo object
  const EffInfo &effInfoObj = _effTool->Info();

  //We grab the variable names as a vector of strings from the info object
  //and the number of objects
  std::vector< std::string > axisNames = effInfoObj.EffVarNames();
  unsigned int nAxisNames = effInfoObj.EffNVars();

  if ( debug ) cout << "\t\tMuon axis size: " << axisNames.size() << endl;
	  
  //Error checks
  if( nAxisNames != axisNames.size() ) {
    std::cout << "objectProbabilities::getProbability" << std::endl
	      << "- Error: Number of variables in the efficiency" << std::endl
	      << "-        is inconsistent" << std::endl;
  }

  //A series of if statements which I don't really like. This takes
  //the retrieved x-axis name and grabs the appropriate value.
  std::vector< float > xEval;
  if ( axisNames.size() == 0 ) {
    xEval.push_back( -1000.0 );
  }
  else {
    for ( int i = 0; i < axisNames.size(); i++ ) {
	
        //We want the strings in lower case
        std::transform(axisNames[i].begin(), axisNames[i].end(), axisNames[i].begin(), (int(*)(int))std::tolower);

      if ( axisNames[i] == "eta" ) {
	if ( debug ) cout << "\t\tMuon eta: " << iObject.Eta() << endl;
	xEval.push_back(iObject.Eta());
      }
      else if ( axisNames[i] == "phi" ) {
	if ( debug ) cout << "\t\tMuon phi: " << iObject.Phi() << endl;
	xEval.push_back(iObject.Phi());
      }
      else if ( axisNames[i] == "pt" ) {
	if ( debug ) cout << "\t\tMuon pt: " << iObject.Pt() << endl;
	xEval.push_back(iObject.Pt());
      }
      else if ( axisNames[i] == "deteta" ) { 
	TMBTrack *track = iObject.GetChargedTrack() ;
	if (!track) throw EffConfigException("objectProbabilities: muon track reference is 0!");
	xEval.push_back(iObject.det_eta(track->Theta(), track->Phi(), track->z()) );
	if ( debug ) cout << "\t\tMuon deteta: " << iObject.det_eta(track->Theta(), track->Phi(), track->z()) << endl;
      }
      else if ( axisNames[i] == "z" ) {
        TMBTrack *track = iObject.GetChargedTrack() ;
        if (!track) throw EffConfigException("objectProbabilities: muon track reference is 0!");
        xEval.push_back(track->z());
	if ( debug ) cout << "\t\tMuon z: " << track->z() << endl;
      }
      else if ( axisNames[i] == "njet15" ) {
        xEval.push_back(njets);
	if ( debug ) cout << "\t\tNumber of jets: " << njets << endl;
      }
      else if ( axisNames[i] == "lumi" ) {
        xEval.push_back(instlum);
	if ( debug ) cout << "\t\tInstantaneous luminosity: " << instlum << endl;
      }

      else {
	std::cout << "objectProbabilities::getProbability Error: Invalid variable - " << axisNames[i].c_str() << std::endl;
      }

      if ( debug ) cout << "\t\tMuon axis " << i << " : " << axisNames[i] << ", xEVal: " << xEval[i] << endl;

    }
  }
    
    
  //Now we get the values we require
  //Condense xEval to a single value'd vector
  if ( debug ) cout << "\t\txEval size: " << xEval.size() << endl;
  EffVal values;
  try {    
    if ( xEval.size() == 1 ) {
      values = _effTool->EffObj().Eff( xEval[0] );
    }
    else if ( xEval.size() == 2 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1] );
    }
    else if ( xEval.size() == 3 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1], xEval[2] );
    }
    else {
      std::cout << "objectProbabilities::getProbability Error: caf_trigger only supports 1-3 variables but you give " << xEval.size() << " variable(s)" << std::endl;
      exit(1);
    }
  }
  catch (const EffException& ex) {
    std::cout << "objectProbabilities::getProbability WARNING: eff_utils exception " << endl
	      << ex._message << endl
	      << "TMBMuon with ";
    for (int i=0; i<xEval.size(); i++) {
      std::cout << "  " << axisNames[i] << "=" << xEval[i];
    }
    std::cout << std::endl;
    eff.val=0;
    eff.binno=-1;
    eff.elo=0;
    eff.ehi=0;
    return 0.0;
  }

 //And create local variables for them
  //LSC: These are my modifications or really a patch to deal with systematics errors.
  //double grabbedProb  = values.val;
  double grabbedProb = 0.0;

  double effNom       = values.val;
  double effHigh      = values.ehi;
  double effLow       = values.elo;
  eff                 = values;

  if (stat==1.0)  grabbedProb = effNom + effHigh;
  if (stat==0.0)  grabbedProb = effNom;
  if (stat==-1.0) grabbedProb = effNom - effLow;

  if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  else if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }

  if ( debug ) {
	cout << "\t\teffNom: " << effNom <<endl;
	cout << "\t\teffHigh: " << effHigh << endl;
	cout << "\t\teffLow: " << effLow << endl;
	cout << "\t\tstat: " << stat << endl;
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
  }
  
  //Not sure what to do at this point so how about we just set the high or
  //low as some sort of error?
  double error = 0.0;

  if( fabs(effHigh) >= fabs(effLow) ) {
    error = fabs(effHigh); //FIX ME
  }
  else {
    error = fabs(effLow); //FIX ME
  }

  //LSC: The initial uncertainty calculation will assume Gaussian uncertainties.
  //Some variables are for later implementation of asymmetric errors.
  double uncertainty_high = 0.0;
  double uncertainty_low = 0.0;
  double uncertainty = 0.0;
  // Monte Carlo an uncertainty value inside the one sigma frequentist interpretation.
  TRandom interval;
  if (effHigh>=effLow) {
    //uncertainty_high = interval.Gaus(0,effHigh);
    uncertainty = fabs( interval.Gaus(0,effHigh) );
    while ( effHigh < uncertainty ) uncertainty = fabs( interval.Gaus(0,effHigh) );
  } else {
    //uncertainty_low  = interval.Gaus(0,effLow);
    uncertainty  = fabs( interval.Gaus(0,effLow) );
    while ( effLow < uncertainty ) uncertainty = fabs( interval.Gaus(0,effLow) );
  }
  stat = uncertainty;
  
  if ( debug ) {
	cout << "\t\tStatistical uncertainty is = " << stat << endl;  
        cout << "\t\tUpper uncertainty is = " << effHigh << endl;  
        cout << "\t\tLower uncertainty is = " << effLow  << endl;  
  }

  //And this is where the sigma variations are applied if there are any
  //with the sigma map mSigma
  // NOT WORKING !!!!!!!!! //
  
  std::string type = "";
  std::string level = "";
    
  type = effInfoObj.ObjType();
    
  if ( effInfoObj.EffName().find("L1") < effInfoObj.EffName().size()
       || effInfoObj.EffName().find("l1") < effInfoObj.EffName().size() ) {
    level = "L1";
  }
  else if ( effInfoObj.EffName().find("L2") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l2") < effInfoObj.EffName().size() ) {
    level = "L2";
  }
  else if ( effInfoObj.EffName().find("L3") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l3") < effInfoObj.EffName().size() ) {
    level = "L3";
  }

  if ( debug ) {
	cout << "\t\tObjType: " << type << endl;
	cout << "\t\tEffName: " << effInfoObj.EffName() << endl;
	cout << "\t\tLevel: " << level << endl;
  }	
  
  std::string key = type + " " + level;

  //Now we check the probability with the sigma
  //grabbedProb += error * mSigma.find(key)->second;
  //Liang Li: mSigma may be obsolete, deal with null pointer exception!
  std::map<std::string, float>::const_iterator it = mSigma.find(key) ;
  if (it != mSigma.end()) grabbedProb += error * it->second;
	  
  if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  else if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }

  if ( debug ) {
	cout << "\t\tkey: " << key << endl;
	cout << "\t\terror: " << error << endl;
	cout << "\t\tmSigma size: " << mSigma.size() << endl;  
	std::map<std::string, float>::const_iterator iter;
	for ( iter = mSigma.begin(); iter != mSigma.end(); iter++ ) {
		cout << "\t\tmSigma key: " << iter->first << " , value: " << iter->second << endl;
	}	
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
	cout << "\tobjectProbabilities::getProbability TMBMuon debugging info ends." << endl;
  }	
  
  return grabbedProb;
}


double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,-1,true,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, bool isRun2b) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,-1,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, bool isRun2b, bool debug) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,-1,isRun2b,debug);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, EffVal &eff) const
{
  return getProbability(iObject,stat,eff,-1,true,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, EffVal &eff, bool isRun2b) const
{
  return getProbability(iObject,stat,eff,-1,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, int JetActAs) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff, JetActAs,true,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, int JetActAs, bool isRun2b) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,JetActAs,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, int JetActAs, bool isRun2b, bool debug) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,JetActAs,isRun2b,debug);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, EffVal &eff, int JetActAs) const
{
  return getProbability(iObject,stat,eff,JetActAs,true,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, EffVal &eff, int JetActAs, bool isRun2b) const
{
  return getProbability(iObject,stat,eff,JetActAs,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBJet  &iObject, double &stat, EffVal &eff, int JetActAs, bool isRun2b, bool debug) const
{
  //Liang Li: debugging info begins	
  if ( debug ) {
	cout << "\tobjectProbabilities::getProbability TMBJet debugging info starts:" << endl;
        if ( isRun2b ) {
		cout << "\t\tEvent is Run2b" << endl;
        }
	else {
		cout << "\t\tEvent is Run2a" << endl;
	}
  }

  bool doActAs = false;
  int CurrentJES = iObject.CurrentlyActAs();
  if ( JetActAs != CurrentJES && JetActAs != -1 ) doActAs = true;
	  
  if ( debug ) {
	if ( doActAs ) {
		cout << "\t\tCurrent Jet ActAs Setting: " << CurrentJES << ", JetActAs = " << JetActAs << ", commit change" << endl;
	}
	else {
		cout << "\t\tCurrent Jet ActAs Setting: " << CurrentJES << ", JetActAs = " << JetActAs << ", no change" << endl;
	}
  }

  if ( doActAs ) iObject.SetActAs(JetActAs);
	
  //We create a local EffInfo object
  const EffInfo &effInfoObj = _effTool->Info();
    
  //We grab the variable names as a vector of strings from the info object
  //and the number of objects
  std::vector< std::string > axisNames = effInfoObj.EffVarNames();
  unsigned int nAxisNames = effInfoObj.EffNVars();
  
  if ( debug ) cout << "\t\tJet axis size: " << axisNames.size() << endl;
	  
  //Error checks
  if( nAxisNames != axisNames.size() ) {
    std::cout << "objectProbabilities::getProbability" << std::endl
	      << "- Error: Number of variables in the efficiency" << std::endl
	      << "-        is inconsistent" << std::endl;
  }

  //A series of if statements which I don't really like. This takes
  //the retrieved x-axis name and grabs the appropriate value.

  std::vector< float > xEval;
  if ( axisNames.size() == 0 ) {
    xEval.push_back( -1000.0 );
  }
  else {
    for ( int i = 0; i < axisNames.size(); i++ ) {
	
        //We want the strings in lower case
        std::transform(axisNames[i].begin(), axisNames[i].end(), axisNames[i].begin(), (int(*)(int))std::tolower);

      if ( axisNames[i] == "eta" ) {
	xEval.push_back(iObject.Eta());
	if ( debug ) cout << "\t\tJet eta: " << iObject.Eta() << endl;	      
      }
      else if ( axisNames[i] == "phi" ) {
	xEval.push_back(iObject.Phi());
	if ( debug ) cout << "\t\tJet phi: " << iObject.Phi() << endl;	      
      }
      else if ( axisNames[i] == "pt" ) {
	if ( isRun2b ) {
		xEval.push_back(iObject.Pt());
	}
	else {
        //Make a copy of iObject and set it to act as uncorrected to get raw pT
		TMBJet tmpJet(iObject);
		tmpJet.ActAsUnCorrected();
		double raw_pT = tmpJet.Pt();
		double deteta = 0.1*tmpJet.detEta();
		double C_factor = 1.0;
        //Grab correction factor from the "table" if needed
                if ( _PrelCTable != 0 ) C_factor = (*_PrelCTable)(raw_pT, deteta);
		if ( debug ) {
			cout << "\t\tJet raw pt: " << raw_pT << ", deteta : " << deteta << endl;
			cout << "\t\tWill implement preliminary to final JES correction factor in terms of raw_pT and deteta : " << C_factor << endl;
		}
		xEval.push_back(iObject.Pt()*C_factor);
	}
	if ( debug ) {
		cout << "\t\tJet pt: " << iObject.Pt() << endl;
	}
      }
      else if ( axisNames[i] == "deteta" ) {
        double deteta = 0.1*iObject.detEta();

       //For Run2a we use different jet eta definition
        if ( ! isRun2b ) deteta = EtaDToEtaDet(iObject.detEta());

	xEval.push_back(deteta);
	if ( debug ) cout << "\t\tJet deteta: " << deteta << endl;	      
      }
      else if ( axisNames[i] == "absdeta" ) {
	double absdeta = fabs(0.1*iObject.detEta());
        xEval.push_back(absdeta);
	if ( debug ) cout << "\t\tJet absolute deteta: " << absdeta << endl;	      
      }
      else {
	std::cout << "objectProbabilities::getProbability Error: Invalid variable - " << axisNames[i].c_str() << std::endl;
      }

      if ( debug ) cout << "\t\tJet axis " << i << " : " << axisNames[i] << ", xEVal: " << xEval[i] << endl;
	      
    }
  }
    
    
  //Now we get the values we require
  //Condense xEval to a single value'd vector
  if ( debug ) cout << "\t\txEval size: " << xEval.size() << endl;  
  EffVal values;
  try {     
    if ( xEval.size() == 1 ) {
      values = _effTool->EffObj().Eff( xEval[0] );
    }
    else if ( xEval.size() == 2 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1] );
    }
    else if ( xEval.size() == 3 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1], xEval[2] );
    }
    else {
      std::cout << "objectProbabilities::getProbability Error: caf_trigger only supports 1-3 variables but you give " << xEval.size() << " variable(s)" << std::endl;
      exit(1);
    }
  }
  catch (const EffException& ex) {

    //We caught an exception from the EffTool, so we'll return 0
    std::cout << "objectProbabilities WARNING: eff_utils exception " << endl
	      << ex._message << endl
	      << "TMBJet with";
    for (int i=0; i<xEval.size(); i++) {
      std::cout << "  " << axisNames[i] << "=" << xEval[i];
    }
    std::cout << std::endl;
    eff.val=0;
    eff.binno=-1;
    eff.elo=0;
    eff.ehi=0;
    return 0.0;
  }
    

  //And create local variables for them
  //LSC: These are my modifications or really a patch to deal with systematics errors.
  //double grabbedProb  = values.val;
  double grabbedProb = 0.0;

  double effNom       = values.val;
  double effHigh      = values.ehi;
  double effLow       = values.elo;
  eff                 = values;

  if (stat==1.0)  grabbedProb = effNom + effHigh;
  if (stat==0.0)  grabbedProb = effNom;
  if (stat==-1.0) grabbedProb = effNom - effLow;
    
  if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  else if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }

    if ( debug ) {
	cout << "\t\teffNom: " << effNom <<endl;
	cout << "\t\teffHigh: " << effHigh << endl;
	cout << "\t\teffLow: " << effLow << endl;
	cout << "\t\tstat: " << stat << endl;
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
  }
  
  //Not sure what to do at this point so how about we just set the high or
  //low as some sort of error?
  double error = 0.0;

  if( fabs(effHigh) >= fabs(effLow) ) {
    error = fabs(effHigh); //FIX ME
  }
  else {
    error = fabs(effLow); //FIX ME
  }


  //LSC: The initial uncertainty calculation will assume Gaussian uncertainties.
  //Some variables are for later implementation of asymmetric errors.
  double uncertainty_high = 0.0;
  double uncertainty_low = 0.0;
  double uncertainty = 0.0;
  // Monte Carlo an uncertainty value inside the one sigma frequentist interpretation.
  TRandom interval;
  if (effHigh>=effLow) {
    //uncertainty_high = interval.Gaus(0,effHigh);
    uncertainty = fabs( interval.Gaus(0,effHigh) );
    while ( effHigh < uncertainty ) uncertainty = fabs( interval.Gaus(0,effHigh) );
  } else {
    //uncertainty_low  = interval.Gaus(0,effLow);
    uncertainty  = fabs( interval.Gaus(0,effLow) );
    while ( effLow < uncertainty ) uncertainty = fabs( interval.Gaus(0,effLow) );
  }
  stat = uncertainty;
  
  if ( debug ) {
	cout << "\t\tStatistical uncertainty is = " << stat << endl;  
        cout << "\t\tUpper uncertainty is = " << effHigh << endl;  
        cout << "\t\tLower uncertainty is = " << effLow  << endl;  
  }



  //And this is where the sigma variations are applied if there are any
  //with the sigma map mSigma
  // NOT WORKING !!!!!!!!! //
  
  std::string type = "";
  std::string level = "";
    
  type = effInfoObj.ObjType();
    
  if ( effInfoObj.EffName().find("L1") < effInfoObj.EffName().size()
       || effInfoObj.EffName().find("l1") < effInfoObj.EffName().size() ) {
    level = "L1";
  }
  else if ( effInfoObj.EffName().find("L2") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l2") < effInfoObj.EffName().size() ) {
    level = "L2";
  }
  else if ( effInfoObj.EffName().find("L3") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l3") < effInfoObj.EffName().size() ) {
    level = "L3";
  }

  std::string key = type + " " + level;
  
  if ( debug ) {
	cout << "\t\tObjType: " << type << endl;
	cout << "\t\tEffName: " << effInfoObj.EffName() << endl;
	cout << "\t\tLevel: " << level << endl;
  }	
  
  
  //Now we check the probability with the sigma
  //Liang Li: mSigma may be obsolete, deal with null pointer exception!
  std::map<std::string, float>::const_iterator it = mSigma.find(key) ;
  if (it != mSigma.end()) grabbedProb += error * it->second;
	  
  if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  else if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  
  if ( debug ) {
	cout << "\t\tkey: " << key << endl;
	cout << "\t\terror: " << error << endl;
	cout << "\t\tmSigma size: " << mSigma.size() << endl;  
	std::map<std::string, float>::const_iterator iter;
	for ( iter = mSigma.begin(); iter != mSigma.end(); iter++ ) {
		cout << "\t\tmSigma key: " << iter->first << " , value: " << iter->second << endl;
	}	
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
	
	if ( doActAs ) {
		cout << "\t\tCurrent JetActAs Setting: " << iObject.CurrentlyActAs() << ", JetActAs = " << JetActAs << ", Original JetActAs Setting: " << CurrentJES << ", restore change" << endl;
	}	
	cout << "\tobjectProbabilities::getProbability TMBJet debugging info ends." << endl;
  }	

  if ( doActAs ) iObject.SetActAs(CurrentJES);
  
  return grabbedProb;
}
// Tau Probabilities

double objectProbabilities::getProbability(const TMBTau  &iObject, double &stat) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,true,false);
}

double objectProbabilities::getProbability(const TMBTau  &iObject, double &stat, bool isRun2b) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBTau  &iObject, double &stat, bool isRun2b, bool debug) const
{
  EffVal eff;
  return getProbability(iObject,stat,eff,isRun2b,debug);
}

double objectProbabilities::getProbability(const TMBTau  &iObject, double &stat, EffVal &eff) const
{
  return getProbability(iObject,stat,eff,true,false);
}

double objectProbabilities::getProbability(const TMBTau  &iObject, double &stat, EffVal &eff, bool isRun2b) const
{
  return getProbability(iObject,stat,eff,isRun2b,false);
}

double objectProbabilities::getProbability(const TMBTau  &iObject, double &stat, EffVal &eff, bool isRun2b, bool debug) const
{
  //Liang Li: debugging info begins	
  if ( debug ) {
	cout << "\tobjectProbabilities::getProbability TMBTau debugging info starts:" << endl;
        if ( isRun2b) {
		cout << "\t\tEvent is Run2b" << endl;
        }
	else {
		cout << "\t\tEvent is Run2a" << endl;
	}
  }

  //We create a local EffInfo object
  const EffInfo &effInfoObj = _effTool->Info();
    
  //We grab the variable names as a vector of strings from the info object
  //and the number of objects
  std::vector< std::string > axisNames = effInfoObj.EffVarNames();
  unsigned int nAxisNames = effInfoObj.EffNVars();
  
  if ( debug ) cout << "\t\tTau axis size: " << axisNames.size() << endl;
	  
  //Error checks
  if( nAxisNames != axisNames.size() ) {
    std::cout << "objectProbabilities::getProbability" << std::endl
	      << "- Error: Number of variables in the efficiency" << std::endl
	      << "-        is inconsistent" << std::endl;
  }

  //A series of if statements which I don't really like. This takes
  //the retrieved x-axis name and grabs the appropriate value.

  std::vector< float > xEval;
  if ( axisNames.size() == 0 ) {
    xEval.push_back( -1000.0 );
  }
  else {
    for ( int i = 0; i < axisNames.size(); i++ ) {
	
        //We want the strings in lower case
        std::transform(axisNames[i].begin(), axisNames[i].end(), axisNames[i].begin(), (int(*)(int))std::tolower);

      if ( axisNames[i] == "eta" ) {
	xEval.push_back(iObject.Eta());
	if ( debug ) cout << "\t\tTau eta: " << iObject.Eta() << endl;	      
      }
      else if ( axisNames[i] == "phi" ) {
	xEval.push_back(iObject.Phi());
	if ( debug ) cout << "\t\tTau phi: " << iObject.Phi() << endl;	      
      }
      else if ( axisNames[i] == "pt" ) {
	xEval.push_back(iObject.Pt());
	if ( debug ) cout << "\t\tTau pt: " << iObject.Pt() << endl;	      
      }
      else if ( axisNames[i] == "deteta" ) {
        Float_t deteta = iObject.etad();
		
	//For Run2a we use different tau eta definition (process given in code below)
        //if ( ! isRun2b ) deteta = EtaDToEtaDet(iObject.detEta());

	xEval.push_back(deteta);
	if ( debug ) cout << "\t\tTau deteta: " << deteta << endl;	      
      }
      else if ( axisNames[i] == "absdeta" ) {
	Float_t absdeta = fabs(iObject.etad());
        xEval.push_back(absdeta);
	if ( debug ) cout << "\t\tTau absolute deteta: " << absdeta << endl;	      
      }
      else {
	std::cout << "objectProbabilities::getProbability Error: Invalid variable - " << axisNames[i].c_str() << std::endl;
      }

      if ( debug ) cout << "\t\tTau axis " << i << " : " << axisNames[i] << ", xEVal: " << xEval[i] << endl;
	      
    }
  }
    
    
  //Now we get the values we require
  //Condense xEval to a single value'd vector
  if ( debug ) cout << "\t\txEval size: " << xEval.size() << endl;  
  EffVal values;
  try {     
    if ( xEval.size() == 1 ) {
      values = _effTool->EffObj().Eff( xEval[0] );
    }
    else if ( xEval.size() == 2 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1] );
    }
    else if ( xEval.size() == 3 ) {
      values = _effTool->EffObj().Eff( xEval[0], xEval[1], xEval[2] );
    }
    else {
      std::cout << "objectProbabilities::getProbability Error: caf_trigger only supports 1-3 variables but you give " << xEval.size() << " variable(s)" << std::endl;
      exit(1);
    }
  }
  catch (const EffException& ex) {

    //We caught an exception from the EffTool, so we'll return 0
    std::cout << "objectProbabilities WARNING: eff_utils exception " << endl
	      << ex._message << endl
	      << "TMBTau with";
    for (int i=0; i<xEval.size(); i++) {
      std::cout << "  " << axisNames[i] << "=" << xEval[i];
    }
    std::cout << std::endl;
    eff.val=0;
    eff.binno=-1;
    eff.elo=0;
    eff.ehi=0;
    return 0.0;
  }
    

  //And create local variables for them
  //LSC: These are my modifications or really a patch to deal with systematics errors.
  //double grabbedProb  = values.val;
  double grabbedProb = 0.0;

  double effNom       = values.val;
  double effHigh      = values.ehi;
  double effLow       = values.elo;
  eff                 = values;

  if (stat==1.0)  grabbedProb = effNom + effHigh;
  if (stat==0.0)  grabbedProb = effNom;
  if (stat==-1.0) grabbedProb = effNom - effLow;
    
  if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  else if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }

    if ( debug ) {
	cout << "\t\teffNom: " << effNom <<endl;
	cout << "\t\teffHigh: " << effHigh << endl;
	cout << "\t\teffLow: " << effLow << endl;
	cout << "\t\tstat: " << stat << endl;
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
  }
  
  //Not sure what to do at this point so how about we just set the high or
  //low as some sort of error?
  double error = 0.0;

  if( fabs(effHigh) >= fabs(effLow) ) {
    error = fabs(effHigh); //FIX ME
  }
  else {
    error = fabs(effLow); //FIX ME
  }


  //LSC: The initial uncertainty calculation will assume Gaussian uncertainties.
  //Some variables are for later implementation of asymmetric errors.
  double uncertainty_high = 0.0;
  double uncertainty_low = 0.0;
  double uncertainty = 0.0;
  // Monte Carlo an uncertainty value inside the one sigma frequentist interpretation.
  TRandom interval;
  if (effHigh>=effLow) {
    //uncertainty_high = interval.Gaus(0,effHigh);
    uncertainty = fabs( interval.Gaus(0,effHigh) );
    while ( effHigh < uncertainty ) uncertainty = fabs( interval.Gaus(0,effHigh) );
  } else {
    //uncertainty_low  = interval.Gaus(0,effLow);
    uncertainty  = fabs( interval.Gaus(0,effLow) );
    while ( effLow < uncertainty ) uncertainty = fabs( interval.Gaus(0,effLow) );
  }
  stat = uncertainty;
  
  if ( debug ) {
	cout << "\t\tStatistical uncertainty is = " << stat << endl;  
        cout << "\t\tUpper uncertainty is = " << effHigh << endl;  
        cout << "\t\tLower uncertainty is = " << effLow  << endl;  
  }



  //And this is where the sigma variations are applied if there are any
  //with the sigma map mSigma
  // NOT WORKING !!!!!!!!! //
  
  std::string type = "";
  std::string level = "";
    
  type = effInfoObj.ObjType();
    
  if ( effInfoObj.EffName().find("L1") < effInfoObj.EffName().size()
       || effInfoObj.EffName().find("l1") < effInfoObj.EffName().size() ) {
    level = "L1";
  }
  else if ( effInfoObj.EffName().find("L2") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l2") < effInfoObj.EffName().size() ) {
    level = "L2";
  }
  else if ( effInfoObj.EffName().find("L3") < effInfoObj.EffName().size()
	    || effInfoObj.EffName().find("l3") < effInfoObj.EffName().size() ) {
    level = "L3";
  }

  std::string key = type + " " + level;
  
  if ( debug ) {
	cout << "\t\tObjType: " << type << endl;
	cout << "\t\tEffName: " << effInfoObj.EffName() << endl;
	cout << "\t\tLevel: " << level << endl;
  }	
  
  
  //Now we check the probability with the sigma
  //Liang Li: mSigma may be obsolete, deal with null pointer exception!
  std::map<std::string, float>::const_iterator it = mSigma.find(key) ;
  if (it != mSigma.end()) grabbedProb += error * it->second;
	  
  if(grabbedProb > 1.0) {
    grabbedProb = 1.0;
  }
  else if(grabbedProb < 0.0) {
    grabbedProb = 0.0;
  }
  
  if ( debug ) {
	cout << "\t\tkey: " << key << endl;
	cout << "\t\terror: " << error << endl;
	cout << "\t\tmSigma size: " << mSigma.size() << endl;  
	std::map<std::string, float>::const_iterator iter;
	for ( iter = mSigma.begin(); iter != mSigma.end(); iter++ ) {
		cout << "\t\tmSigma key: " << iter->first << " , value: " << iter->second << endl;
	}	
	cout << "\t\tgrabbedProb: " << grabbedProb << endl;
	cout << "\tobjectProbabilities::getProbability TMBTau debugging info ends." << endl;
  }	
  
  return grabbedProb;
}

// end Tau probabilities

float objectProbabilities::EtaDToEtaDet(float const etaD) const
  {
    // EtaD is often described as the 'pT weighted eta location in terms of ieta'.
    // Note: EtaD runs from -37 to 37 (including zero!).

    float absEtaD = TMath::Abs(etaD);

    // Check input.
    assert(absEtaD >= 0.0);
    assert(absEtaD < 37.0);

    float etaDet = 0.0;
    float etaWidthNom = 0.1;
    int iEtaBase = 0;

    // First determine the absolute value of etaDet.
    if (absEtaD <= 32.0) {
      // 'Normal' part of the calorimeter.
      etaDet = absEtaD*etaWidthNom;
    } else {
      iEtaBase = TMath::Nint(TMath::Floor(absEtaD));
      etaDet = CalTool::CalTowerEtaCenter(iEtaBase) +
                                0.5*CalTool::CalTowerEtaWidth(iEtaBase) +
                                0.5*CalTool::CalTowerEtaWidth(iEtaBase+1);
    } // else

    // Now correct etaDet for the sign of etaD.
    etaDet = TMath::Sign(etaDet, etaD);

    return etaDet;

  } // EtaDToEtaDet


//endfile:
