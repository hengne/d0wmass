#include <iostream>
#include <stdexcept>
#include "cafe/Trigger.hpp"

int main()
{
  try {
    cafe::Trigger test("test");
  }
  catch(std::runtime_error x) {
    std::cout << x.what() << std::endl;
  }
  return 0;
}
