#ifndef AEON__EXE_LU_CORE_H
#define AEON__EXE_LU_CORE_H 1

#include "user_function.h"

struct core_node;

user_function core_node_user_function (core_node *);

void core_node_score (core_node *, long delta);

#endif //AEON__EXE_LU_CORE_H
