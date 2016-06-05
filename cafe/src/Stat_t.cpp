#include "cafe/Stat.hpp"
#include <iostream>

using namespace cafe ;

int main()
{
    using std::cout;
    Stat stat("test");
    stat.begin() ;
    stat.finish() ;
    stat.print_html(cout) ;
    StatPointer pointer(&stat) ;
}
