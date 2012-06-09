#ifndef AEON__LIBS_UTILS_NEW_H
#define AEON__LIBS_UTILS_NEW_H 1

#include "types.h"

inline void* operator new (ulong, void *) throw () { return p; }
inline void* operator new[] (ulong, void *) throw () { return p; }

inline void  operator delete (void *, void *) throw () {}
inline void  operator delete[] (void *, void *) throw () {}

#endif //AEON__LIBS_UTILS_NEW_H
