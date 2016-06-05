#include "cafe/StatSample.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace cafe ;
using namespace std ;

int main()
{
    StatSample sample("test");
    vector<string> tags ;
    tags.push_back("tag1") ;
    tags.push_back("tag2") ;
    sample.AddTags(tags) ;
    sample.Clear() ;
}
