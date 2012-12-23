#ifndef AEON__EXE_LU_BINARY_H
#define AEON__EXE_LU_BINARY_H 1

#include "user_function.h"

struct binary_node;

user_function binary_node_user_function (binary_node *);

struct loader_node;

binary_node * binary_node_construct (loader_node * n);

void binary_node_score (binary_node *, long du);

#endif //AEON__EXE_LU_BINARY_H
