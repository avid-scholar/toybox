#ifndef AEON__LIBS_IO_READ_LINES_H
#define AEON__LIBS_IO_READ_LINES_H 1

#include <unistd.h>
#include <fcntl.h>
#include <cassert>
#include <algorithm>
#include "../sys/except.h"

template <typename Func>
void
read_lines_aux (int fd, Func &f, char *buf, size_t bs)
{
   ssize_t head = 0;
   bool skip = false;

   for ( ; ; )
   {
      //read
      ssize_t n = read (fd, buf + head, bs - head);
      if (n == -1)
         throw system_error ();
         
      if (n == 0)
         return;

      //extract_all
      char *b = buf, *c = buf + head, *e = c + n;
      for ( ; ; b = ++c)
      {
         c = std::find (c, e, '\n');

         if (skip)
         {
            if (c == e)
            {
               f.skip (b, c, false);
               head = 0;
               break;
            }
            else
            {
               f.skip (b, c, true);
               skip = false;
            }
         }
         else if (c == e)
         {
            if (b == buf)
            {
               f.skip (b, e, false);
               skip = true;
               head = 0;
            }
            else if (b == e)
               head = 0;
            else
            {
               std::copy (b, e, buf);
               head = e - b;
            }

            break;
         }
         else
            f (b, c);
      }
   }
}


template <typename Func>
void
read_lines (int fd, Func &f, int max_line)
{
   char buf [max_line];
   read_lines_aux (fd, f, buf, max_line);
}


template <typename Func>
void
read_file (char const *name, Func &f, int max_line)
{
   int fd = open (name, O_RDONLY);
   if (fd == -1)
      throw file_error ("cant open file", name);

   read_lines (fd, f, max_line);
}

#endif //AEON__LIBS_IO_READ_LINES_H
