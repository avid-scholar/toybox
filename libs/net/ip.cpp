#include "ip.h"
#include <boost/lexical_cast.hpp>

namespace ip
{

point::point (std::string const &l, std::string const &r)
{
   port = boost::lexical_cast <unsigned short> (r);
   addr = invalid_address;
   host = l;
}

point::point (std::string const &s)
{
   addr = invalid_address;
   size_t c = s.find (':');
   if (c == std::string::npos)
   {
      host = s;
      port = 80;
   }
   else
   {
      host.assign (s.begin (), s.begin () + c);
      port = scan_throw <unsigned short> (bits::const_char_buf (s.data () + c + 1, s.size () - c - 1));
   }
}

}
