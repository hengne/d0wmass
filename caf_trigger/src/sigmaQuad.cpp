//file: sigmaQuad.cpp {Probability Calculations .cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Calculates the quadrature based on the values you input
//
//Usage:    Call the constructor at the beginning of your code and call
//          the method addQuadrature(double addthis); then call
//          getQuadrature();
//
//Example:

//Header file for this class
#include "caf_trigger/sigmaQuad.hpp"

void sigmaQuad::sigmaAddQuad(double quadValue)
{
    //Since quadTotal is already squared, we add quadValue^2 to quadTotal
    _quadTotal += quadValue*quadValue;

    //and increment the counter
    ++_quadCounter;
}

double sigmaQuad::sigmaGetQuad()
{
    //Here we create an output variable
    double sigmaOutQuad;

    //And set it to the quadrature calculated
    sigmaOutQuad = sqrt(_quadTotal/_quadCounter);

    return sigmaOutQuad;
}
