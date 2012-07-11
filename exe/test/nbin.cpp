#include "utils/cxx.h"
#include <iostream>

#define DUP(a) # a ": " << (a) << std::endl;

int main ()
{
   std::cout << DUP (nbin <101>::value);
   std::cout << DUP (nbin <1100>::value);
   std::cout << DUP (nbin <1101>::value);
   std::cout << DUP (nbin <1001101>::value);
   std::cout << DUP (nbin <100000000000>::value);
}
