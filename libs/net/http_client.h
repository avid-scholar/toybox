#ifndef AEON__LIBS_NET_HTTP_CLIENT_H
#define AEON__LIBS_NET_HTTP_CLIENT_H 1

#include "ip.h"
#include <boost/optional.hpp>

namespace http
{

typedef boost::shared_ptr <struct session> session_ptr;
typedef boost::shared_ptr <struct request> request_ptr;
typedef boost::shared_ptr <struct response> response_ptr;
typedef function <void (response_ptr const &)> response_processor;
typedef function <void (request_ptr const &)> request_processor;

struct request
{
   request () : post (false), http_minor (1) {}

   bool post;
   string path;
   unsigned http_minor;
   std::string headers;
   string body;
};

struct response
{
   error_code err;
   unsigned status;
   unsigned http_minor;
   std::string headers;
   string body;
};

typedef function <void (session_ptr const &)> connect_processor;

struct client 
{
   void connect (connect_processor const &r, ip::target const &dest, ip::target const &src = ip::target ());

private:
   typedef boost::shared_ptr <struct client_impl> impl_ptr;
   impl_ptr impl;
};

struct server
{
   server (connect_processor const &, ip::target const &);

   void shutdown ();

private:
   typedef boost::shared_ptr <struct server_impl> impl_ptr;
   impl_ptr impl;
};

} //namespace http

#endif //AEON__LIBS_NET_HTTP_CLIENT_H
