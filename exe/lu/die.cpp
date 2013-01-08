#include "die.h"

#include <cstdio>
#include <cstdarg>

void
die_actually (char const * file, long line, char const *fmt, ...)
{
    printf ("error in %s:%ld : ", file, line);
    va_list ap;
    va_start (ap, fmt);
    vprintf (fmt, ap);
    puts ("");
}
