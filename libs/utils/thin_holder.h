#ifndef LIBS_UTILS_THIN_HOLDER_H
#define LIBS_UTILS_THIN_HOLDER_H 1

#include "cxx.h"

//mainly for storing allocators
template <typename A, bool thin = is_thin <A>::value>
struct thin_holder
{
   thin_holder (A a = A ()) : a (a) {}
   A thin_get () const { return a; } 

private:
   A a;
};

template <typename A>
struct thin_holder <A, true> 
{
   thin_holder (A = A ()) {}
   A thin_get () const { return A (); }
};

#endif //LIBS_UTILS_THIN_HOLDER_H
