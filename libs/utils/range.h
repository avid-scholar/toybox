#ifndef AEON__LIBS_UTILS_RANGE_H
#define AEON__LIBS_UTILS_RANGE_H 1

#include "xm.h"
#include "types.h"

template <typename It>
struct range
{
   typedef It iterator;

   It b, e;

   range () : b (It ()), e (It ()) {}

   range (It b, It e) : b (b), e (e) {}

   template <typename C>
   range (C &c) : b (c.begin ()), e (c.end ()) {}

   template <typename Mit>
   range (range <Mit> const &r) :
      b (r.b),
      e (r.e)
   {}

   int8 size () const { return e - b; }
};

#endif //AEON__LIBS_UTILS_RANGE_H
