#ifndef AEON__LIBS_UTILS_TYPE_NAME_H
#define AEON__LIBS_UTILS_TYPE_NAME_H 1

#include "mem/mrange.h"

template <typename T>
mrange_const
type_name ()
{
   static mrange_const m = __PRETTY_FUNCTION__;
   return m;
}

#endif //AEON__LIBS_UTILS_TYPE_NAME_H
