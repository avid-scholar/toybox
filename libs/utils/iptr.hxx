#include "iptr.h"

template <typename T>
inline
~iptr::iptr ()
{
   if (p)
      delete p;
}
