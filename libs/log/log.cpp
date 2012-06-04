#include <pthread.h>
#include <cstdio>
#include <time.h>

#include "log.h"

lg::lfmt::~lfmt ()
{
   std::string s = f.str ();
   struct tm ttmp;
   time_t t = time (NULL);
   localtime_r (&t, &ttmp);
   std::string out;
   size_t n = strftime (&out[0], out.size (), "%F %T", &ttmp);
   out.resize (n);
   printf ("%s <%lx> %s\n", out.c_str (), (long) pthread_self (), s.c_str ());
}
