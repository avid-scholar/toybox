#ifndef AEON__LIBS_UTILS_IPTR_H
#define AEON__LIBS_UTILS_IPTR_H 1

#include "utils/cxx.h"

template <typename T>
struct iptr : public noncopyable
{
   iptr () : p (0) {}

   ~iptr ();

   T *p;
};

#endif //AEON__LIBS_UTILS_IPTR_H
