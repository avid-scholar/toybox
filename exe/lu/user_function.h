#ifndef AEON__EXE_LU_USER_FUNCTION_H
#define AEON__EXE_LU_USER_FUNCTION_H 1

#include "data.h"

typedef void * opaque_pointer;

typedef data (user_c_function_pointer) (opaque_pointer, data *);

struct user_function
{
    opaque_pointer object;
    user_c_function_pointer * method;
};

#endif //AEON__EXE_LU_USER_FUNCTION_H
