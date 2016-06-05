
#include "cafe/FilePattern.hpp"
#include <iostream>

int main()
{
    using namespace cafe;
    using namespace std;

    FilePattern a("%d/%r-new.root");
    FilePattern b("%d/%r-%n.root");
    string result = a.replace("/home/rhauser/test.root");
    cout << result << endl;
    if(result != "/home/rhauser/test-new.root") return 1;
    
    result = b.replace("/home/rhauser/test.root");
    cout << result << endl;
    if(result != "/home/rhauser/test-0.root") return 1;

    return 0;
}
