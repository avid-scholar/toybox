#ifndef AEON__EXE_LU_LOAD_H
#define AEON__EXE_LU_LOAD_H 1

#include "user_function.h"

struct loader_node;

loader_node *
load (
    bytes const * file,
    bytes const * symbol,
    data const * args);

void
unload (loader_node *);

user_function loader_user_function (loader_node *);

#endif //AEON__EXE_LU_LOAD_H
