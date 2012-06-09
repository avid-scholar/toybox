#ifndef AEON__LIBS_NET_IP_H
#define AEON__LIBS_NET_IP_H 1

#include "mem/mstring.h"

namespace ip
{

enum { invalid_address = -1 };

struct point
{
   point (unsigned long a, unsigned short p) : addr (a), port (p) {}
   point (mstring const &h, unsigned short p) : host (h), port (p) {}
   point (mstring const &h, mstring const &port);
   point (mstring const &hp);
   point (unsigned short p) : host ("0.0.0.0"), port (p), addr (invalid_address) {}

   mstring host;
   long addr;
   unsigned short port;

   bool operator== (point const &r) const { return host == r.host && port == r.port; }
   bool operator< (point const &r) const { return host == r.host ? port < r.port : host < r.host; }
};

}

#endif //AEON__LIBS_NET_IP_H
