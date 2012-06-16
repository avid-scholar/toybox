#include <iostream>
#include <iomanip>

struct hilo
{
   long *data () { return (long *) (long) hi; }
   long hi : 48;
   unsigned long lo : 16;
};

union u
{
   hilo hl;
   long raw;
};

int main (int argc, char *argv [])
{
   u u;
   u.raw = 0;
   u.raw = ~u.raw;
   std::cout << u.hl.lo << std::endl;

   std::cout << std::hex << u.hl.data () << std::endl;
   u.hl.lo = 0;
   std::cout << std::hex << u.hl.data () << std::endl;
}
