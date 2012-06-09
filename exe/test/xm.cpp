#include <iostream>
#include <string>

#include "mem/mrange.h"
#include "utils/type_name.h"
#include "mem/mstdio.h"

template <typename T>
std::string pretty_ugly (T const &)
{
   return __PRETTY_FUNCTION__;
}

int main (int argc, char *argv [])
{
   char buf [] = "sunny day";
  
   std::cout << "type: " << pretty_ugly (buf +to_range) << std::endl;
   std::cout << (buf +to_range) << std::endl;

   //std::cout << (buf +to_range) << std::endl;
   return 0;
}
