#ifndef AEON__LIBS_UTILS_SLIST_H
#define AEON__LIBS_UTILS_SLIST_H 1

#include "flink.h"
#include "int_slist.h" 

template <typename T, typename A = new_delete_factory>
struct slist
{
   typedef slist_node <T> node_t;
   typedef int_slist <node_t, A> impl_t;

   slist (A a = A ()) : impl (a) {}

   bool empty () const { return impl.empty (); }
   T & top () const { return impl.top ()->value; }
  
   void pop () { if (node_t *n = impl.pop ()) impl.thin_get ().dispose (n); }
   void push (T const &val) { impl.push (impl.thin_get ().produce (sig <node_t> (), val)); }
   void swap (slist &r) { impl.swap (r.impl); }

   impl_t & get_impl () { return impl; }

private:
   impl_t impl;
};

#endif //AEON__LIBS_UTILS_SLIST_H
