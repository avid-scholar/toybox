#ifndef AEON__EXE_LU_ERROR_H
#define AEON__EXE_LU_ERROR_H 1

#include "data.h"

typedef void (error_pusher) (data);

void error_push (data);

data error_pop ();

long error_count ();

#endif //AEON__EXE_LU_ERROR_H
