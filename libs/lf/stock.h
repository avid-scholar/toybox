#ifndef LIBS_LF_STOCK_H
#define LIBS_LF_STOCK_H 1

#include "utils/cxx.h"
#include "utils/slist.h"
#include "int_stock.h"

namespace lf2
{

template <typename T, typename A = new_delete_factory>
struct stock
{
   typedef slist <T, A> slist_t;
   typedef typename slist_t::node_t node_t;

   stock (A a = A ()) : impl (a) {}

   void grab (slist_t &out)
   {
      slist_t r (impl.thin_get ());
      r.get_impl ().tpush (impl.grab ());
      e.swap (out);
   }

   void swap (slist_t &io)
   {
      io.get_impl ().swap (impl.swap (io.get_impl ().grab ()));
   }

   bool push (slist_t &in)
   {
      impl.tpush (in.get_impl ().grab ());
      return in.empty ();
   }

   bool push (T const &t)
   {
      return impl.push (impl.thin_get ().produce (sig <node_t> (), t));
   }

private:

   typedef int_stock <node_t, A> impl_t;
   impl_t impl;
};

} //namespace lf2

#endif //LIBS_LF_STOCK_H
