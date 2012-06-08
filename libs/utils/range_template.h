#ifndef AEON__LIBS_UTILS_RANGE_TEMPLATE_H
#define AEON__LIBS_UTILS_RANGE_TEMPLATE_H 1

#include "utils/types.h"

template <typename It>
struct range_template
{
   It b, e;

   range_template () : b (It ()), e (It ()) {}

   range_template (It b, It e) : b (b), e (e) {}

   template <typename C>
   range_template (C &c) : b (c.begin ()), e (c.end ()) {}

   template <typename Mit>
   range_template (range_template <Mit> const &r) :
      b (r.b)
      e (r.e)
   {}

   ulong size () const { return e - b; }
};

#endif //AEON__LIBS_UTILS_RANGE_TEMPLATE_H
