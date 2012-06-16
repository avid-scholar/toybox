#ifndef AEON__LIBS_UTILS_SA_HXX
#define AEON__LIBS_UTILS_SA_HXX 1

#include "sa.h"

namespace sa
{

template <typename R1, typename R2>
R1
find_substr (R1 s, R2 pat)
{
   if (pat.b == pat.e)
      return s.b;

   for ( ; ; ++s.b)
   {
      if (s.b == s.e)
         return s.b;

      if (*s.b == *pat.b)
      {
         R1 out (s.b, s.b);
         typename R2::iterator pb = pat.b;
         for ( ; ; )
         {
            ++pb;
            ++out.e;
            if (out.e == s.e)
               return R1 (s.e, s.e);

            if (pb == pat.e)
               return out;

            if (*pb != *out.e)
               break;
         }
      }
   }
}

}

#endif //AEON__LIBS_UTILS_SA_HXX
