#include "log/log.h"
#include <iostream>

int main ()
{
   std::string s;
   while (std::getline (std::cin, s))
   {
      lg::inf () << s; 
   }
}
