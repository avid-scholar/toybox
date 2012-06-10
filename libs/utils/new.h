#ifndef AEON__LIBS_UTILS_NEW_H
#define AEON__LIBS_UTILS_NEW_H 1

#include "types.h"

#if 0
inline void* operator new (ulong, void *p) throw () { return p; }
inline void* operator new[] (ulong, void *p) throw () { return p; }

inline void  operator delete (void *, void *) throw () {}
inline void  operator delete[] (void *, void *) throw () {}
#endif

#endif //AEON__LIBS_UTILS_NEW_H
