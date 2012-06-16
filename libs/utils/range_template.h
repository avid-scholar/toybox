#ifndef AEON__LIBS_UTILS_RANGE_TEMPLATE_H
#define AEON__LIBS_UTILS_RANGE_TEMPLATE_H 1

#include "xm.h"
#include "types.h"

template <typename It>
struct range_template
{
   typedef It iterator;

   It b, e;

   range_template () : b (It ()), e (It ()) {}

   range_template (It b, It e) : b (b), e (e) {}

   template <typename C>
   range_template (C &c) : b (c.begin ()), e (c.end ()) {}

   template <typename Mit>
   range_template (range_template <Mit> const &r) :
      b (r.b),
      e (r.e)
   {}

   ulong size () const { return e - b; }
};

template <int N, typename T>
inline
range_template <T const *>
operator+ (T const (&buf) [N], xm__to_range)
{
   return range_template <T const *> (N ? buf : 0, N ? buf + N : 0);
}

template <int N, typename T>
inline
range_template <T *>
operator+ (T (&buf) [N], xm__to_range)
{
   return range_template <T *> (N ? buf : 0, N ? buf + N : 0);
}

#endif //AEON__LIBS_UTILS_RANGE_TEMPLATE_H
