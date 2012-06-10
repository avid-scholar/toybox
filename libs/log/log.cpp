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
   char buf [40];
   strftime (buf, sizeof (buf), "%F %T", &ttmp);
   printf ("%s <%lx> %s\n", buf, (long) pthread_self (), s.c_str ());
}
