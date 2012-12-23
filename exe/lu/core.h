#ifndef AEON__EXE_LU_CORE_H
#define AEON__EXE_LU_CORE_H 1

#include "binary.h"

struct core;

core *
core_construct ();

void
core_destruct (core *);

bool
core_insert (core *, bytes s, binary_node * b);

bool
core_dispatch (core *, bytes s, data arg, data * result);

#endif //AEON__EXE_LU_CORE_H
