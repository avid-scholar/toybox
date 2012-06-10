#ifndef AEON__LIBS_UTILS_IPTR_HXX
#define AEON__LIBS_UTILS_IPTR_HXX 1

#include "iptr.h"

template <typename T>
inline
~iptr::iptr ()
{
   if (p)
      delete p;
}

#endif //AEON__LIBS_UTILS_IPTR_HXX
