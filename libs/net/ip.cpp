#include "ip.h"
#include <boost/lexical_cast.hpp>

namespace ip
{

point::point (mstring_ref l, mstring_ref r)
{
   port = boost::lexical_cast <unsigned short> (r);
   addr = invalid_address;
   host = l;
}

//ip -- at max 15 4-bit digits //16 digits at most,
//255.255.255.255, 16 - 1 = 15m, 15 * 4 = 60 bit + 4 control bits, everything on x64
//ip consists of [0-9.], except for dots all meaningfull, we may also need total length

point::point (mstring_ref s)
{
   mstring m (s);
   parse_impl (m);
}

point::parse_impl (mstring &s)
{
   addr = invalid_address;
   size_t c = s.find (':');
   mstring rest;
   if (sa::split (s, ":", &rest))
   {
      host = s;
      port = 80;
   }
   else
   {
      host.assign (s.begin (), s.begin () + c);
      port = scan_throw <unsigned short> (mrange_const (s.data () + c + 1, s.size () - c - 1));
   }
}

}
