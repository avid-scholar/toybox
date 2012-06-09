#ifndef AEON__LIBS_MEM_MSTDIO_H
#define AEON__LIBS_MEM_MSTDIO_H 1

#include <iostream>
#include "mrange.h"

inline
std::ostream &
operator<< (std::ostream &out, mrange_const r)
{
   return out << std::string (r.b, r.e);
}

#endif //AEON__LIBS_MEM_MSTDIO_H
