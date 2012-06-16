#ifndef AEON__LIBS_MEM_MRANGE_H
#define AEON__LIBS_MEM_MRANGE_H 1

#include "utils/range_template.h"
#include "utils/types.h"

typedef range_template <byte *> mrange;
typedef range_template <byte const *> mrange_const;

#endif //AEON__LIBS_MEM_MRANGE_H
