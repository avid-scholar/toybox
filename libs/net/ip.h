#ifndef AEON__LIBS_NET_IP_H
#define AEON__LIBS_NET_IP_H 1

#include "bindata/bstring.h"

namespace ip
{

enum { invalid_address = -1 };

struct point
{
   point (unsigned long a, unsigned short p) : addr (a), port (p) {}
   point (bstring const &h, unsigned short p) : host (h), port (p) {}
   point (bstring const &h, bstring const &port);
   point (bstring const &hp);
   point (unsigned short p) : host ("0.0.0.0"), port (p), addr (invalid_address) {}

   bstring host;
   long addr;
   unsigned short port;

   bool operator== (point const &r) const { return host == r.host && port == r.port; }
   bool operator< (point const &r) const { return host == r.host ? port < r.port : host < r.host; }
};

}

#endif //AEON__LIBS_NET_IP_H
