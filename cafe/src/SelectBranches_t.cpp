
#include "cafe/SelectBranches.hpp"

#include <vector>

int main()
{
    using namespace cafe;
    using namespace std;

    static const char *n[] = { "JCCA.fX", "JCCA.fY" };

    BranchNames branches("EMscone.fX");
    BranchNames branches1("EMscone.fX", "EMscone.fY");
    BranchNames branches2("EMscone.fX", "EMscone.fY", "EMscone.fZ");
    BranchNames branches3("EMscone.fX", "EMscone.fY", "EMscone.fZ", "EMscone.fM");

    vector<string> names(n, n + sizeof(n)/sizeof(n[0]));

}
