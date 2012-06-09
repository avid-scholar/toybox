#ifndef AEON__LIBS_NET_TCP_CLIENT_H
#define AEON__LIBS_NET_TCP_CLIENT_H 1
#include "ip.h"
#include <boost/shared_ptr.hpp>

namespace ip
{

struct session
{
   ip::target const & remote ();
   ip::target const & local ();

   void query (request_ptr const &, response_processor const &, timestamp const &);
   void reply (response_ptr const &);
   void serve (request_processor const &, timestamp const &);
   void close ();

private:
   typedef boost::shared_ptr <struct session_impl> impl_ptr;
   impl_ptr impl;
};

struct tcp_client
{
   tcp_client ();

private:
   boost::shared_ptr <struct tcp_client_impl> ();
};

}
#endif //AEON__LIBS_NET_TCP_CLIENT_H
