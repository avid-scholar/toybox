#ifndef AEON__LIBS_LOG_LOG_H
#define AEON__LIBS_LOG_LOG_H 1

#include "bindata/bstring.h"
#include <sstream>

struct command__convert_to_string {} C2S __attribute__ ((weak));

namespace lg
{

struct fmt
{
   template <typename T>
   fmt &
   operator<< (T const &t)
   {
      buf << t;
      return *this;
   }

   std::string operator<< (command__convert_to_string const &) { return str (); }
   operator std::string () const { return str (); }
   std::string str () const { return buf.str (); }

private:
   std::ostringstream buf;
};

struct lfmt
{
   template <typename T>
   lfmt &
   operator<< (T const &t)
   {
      f << t;
      return *this;
   }

   ~lfmt ();

private:
   fmt f;
};


typedef lfmt trc;
typedef lfmt dbg;
typedef lfmt inf;
typedef lfmt wrn;
typedef lfmt err;
typedef lfmt ftl;

}

#endif //AEON__LIBS_LOG_LOG_H
