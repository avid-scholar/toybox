#ifndef AEON__LIBS_SYS_EXCEPT_H
#define AEON__LIBS_SYS_EXCEPT_H 1

#include <string>
#include <unistd.h>
#include <stdexcept>
#include <cerrno>
#include <cstring>

struct system_error : public std::runtime_error
{
   system_error (int er = errno) : std::runtime_error (gen_msg (er)) {}

protected:

   system_error (std::string const &s) : std::runtime_error (s) {}
   
   static
   std::string
   gen_msg (int er)
   {
      std::string s = "system error: ";
      char buf [3000];
#if defined (__FreeBSD__)
      strerror_r (er, buf, sizeof (buf));
      s += buf;
#else
      s += strerror_r (er, buf, sizeof (buf));
#endif
      return s;
   }
};

struct file_error : public system_error
{
   file_error (char const *op, char const *name, int er = errno) :
      system_error (std::string (op) + " '" + name + "': " + gen_msg (er))
   {}
};

#endif //AEON__LIBS_SYS_EXCEPT_H
