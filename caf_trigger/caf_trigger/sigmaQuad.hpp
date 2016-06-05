//file: sigmaQuad.hpp {sigmaQuad.cpp}
//
//Author:   Kevin Chan
//
//Purpose:  Header file for sigmaQuad.hpp
//
//Usage:
//
//Example:

//C++ Objects and interfaces
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>


#ifndef SIGMA_QUAD_H
#define SIGMA_QUAD_H

class sigmaQuad
{
public:
    //Constructor
    //Initializes the main quadtotal value to 0 and the counter to 0
    sigmaQuad();

    //Destructor
    ~sigmaQuad() {}
    //Adds the given value with the total value, squared.
    void sigmaAddQuad(double quadValue);

    //Retrieves the quadrature calculated
    double sigmaGetQuad();

private:
    double  _quadTotal;
    int     _quadCounter;
};

inline
sigmaQuad::sigmaQuad() 
{
    _quadTotal = 0.0;
    _quadCounter = 0;
}

#endif
//endfile:
