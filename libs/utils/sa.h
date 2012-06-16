#ifndef AEON__LIBS_UTILS_SA_H
#define AEON__LIBS_UTILS_SA_H 1

#include "mem/mstring.h"

namespace sa
{

bool split_half (mstring_ref input, mstring const &sep, mstring &beg, mstring &end);

template <typename R1, typename R2> R1 find_substr (R1 s, R2 pat);

}

#endif //AEON__LIBS_UTILS_SA_H
