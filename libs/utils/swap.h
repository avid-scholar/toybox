#ifndef LIBS_UTILS_SWAP_H
#define LIBS_UTILS_SWAP_H 1

#include "cxx.h"

namespace ut
{

template <typename T, typename V = void>
struct sfinae_swap
{
   typedef false_ type;
};

template <typename T>
struct sfinae_swap <T, typename enable_if <val <void (T::*) (T &), &T::swap> >::type>
{
   typedef true_ type;
};

template <typename T>
inline
void
swap_dispatch (T &a, T &b, false_)
{
   T tmp = a;
   a = b;
   b = tmp;
}

template <typename T>
inline
void
swap_dispatch (T &a, T &b, true_)
{
   a.swap (b);
}

template <typename T>
inline
void
swap (T &a, T &b)
{
   swap_dispatch (a, b, sfinae_swap <T>::type::mk ()); 
}

} //namespace ut 

#endif //LIBS_UTILS_SWAP_H
