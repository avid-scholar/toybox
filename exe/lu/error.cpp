#include "error.h"
#include <iostream>

void error_push (data d)
{
    std::cout << "error: " << d << std::endl;
    data_free (d);
}

data error_pop ()
{
    data d = data_construct ();
    return d;
}

long error_count ()
{
    return 0;
}
