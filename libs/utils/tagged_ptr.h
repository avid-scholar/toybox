#ifndef AEON__LIBS_UTILS_TAGGED_PTR_H
#define AEON__LIBS_UTILS_TAGGED_PTR_H 1

#include "cxx.h"

template <typename T>
struct tagged_ptr
{
   T *ptr () const { return (T*) (long) p; }
   tagged_ptr add (long dt) const { return mk (ptr (), t + dt); }
   operator bool () const { return p; }

   enum
   {
      tag_bits = 16,
      char_bits = 8,
      ptr_bits = sizeof (void *) * char_bits - tag_bits,
      tag_max = (1 << (tag_bits - 1)) - 1,
      tag_half = tag_max / 2
   };

   static tagged_ptr mk (T *ptr = 0, int tag = 0)
   {
      tagged_ptr p = {(long) ptr, tag};
      return pointer;
   }

   long pointer : ptr_bits;
   long tag : tag_bits;
};

REQUIRE (sizeof (tagged_ptr <void>) == sizeof (long))

#endif //AEON__LIBS_UTILS_TAGGED_PTR_H
