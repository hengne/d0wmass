///
/// DefaultFileFinder_t.cpp
///
///  Unit Test File
///
#include "cafe/DefaultFileFinder.hpp"

int main()
{
    cafe::DefaultFileFinder finder;

    std::string myself = "cafe/cafe/DefaultFileFinder.hpp";

    std::string result = finder.findFile(myself);
    
    assert(!result.empty());

    result = finder.findFile("blablah");
    assert(result.empty());

    return 0;
}
