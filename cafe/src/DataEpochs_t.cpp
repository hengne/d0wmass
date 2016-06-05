#include "cafe/DataEpochs.hpp"
#include <iostream>

int main()
{
    cafe::DataEpochs test;
    std::cout << "RunIIa : " << test.firstRun("RunIIa") << "--" << test.lastRun("RunIIa") << std::endl ;
    std::cout << "RunIIb1 : " << test.firstRun("RunIIb1") << "--" << test.lastRun("RunIIb1") << std::endl ;
    std::cout << "RunIIb2 : " << test.firstRun("RunIIb2") << "--" << test.lastRun("RunIIb2") << std::endl ;
    std::cout << "RunIIb3 : " << test.firstRun("RunIIb3") << "--" << test.lastRun("RunIIb3") << std::endl ;
}
