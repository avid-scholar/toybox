#ifndef AEON__EXE_LU_MODULE_H
#define AEON__EXE_LU_MODULE_H 1

//to be included by module .so

#include "data.h"
#include "error.h"
#include "user_function.h"

struct module_node; //different in every module

typedef void (module_node_destructor) (module_node *);

struct module
{
    user_function uf;
    module_node * node;
    module_node_destructor * destroy_node;
};

user_function module_node_user_function (module_node *);

typedef module (module_constructor) (error_pusher *, data *);

#endif //AEON__EXE_LU_MODULE_H
