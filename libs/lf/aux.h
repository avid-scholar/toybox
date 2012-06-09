#ifndef AEON__LIBS_LF_AUX_H
#define AEON__LIBS_LF_AUX_H 1

#include <cassert>
#include "utils/cxx.h"
#include "utils/chain.h"

REQUIRE (sizeof (long) == 8)

namespace lf2
{

namespace impl
{

template <typename V, typename R>
union shell
{
   V value;
   R raw;
};

template <typename T>
struct cas_raw
{
   typedef 
      typename if_ <sizeof (T) / 9, void,
      typename if_ <sizeof (T) / 5, long,
      typename if_ <sizeof (T) / 3, int,
      typename if_ <sizeof (T) / 2, short,
      typename if_ <sizeof (T) / 1, char,
            void>::type>::type>::type>::type>::type type;

   REQUIRE (255u == (unsigned char) -1) //CHAR_BIT == 8
};

} //namespace impl

template <typename T>
inline
bool
atomic_cas (T *t, T o, T n)
{
   typedef typename impl::cas_raw <T>::type raw_t;
   impl::shell <T, raw_t> os = {o}, ns = {n};
   impl::shell <T *, raw_t *> p = {t};
   return __sync_bool_compare_and_swap (p.raw, os.raw, ns.raw); 
}

template <typename T, typename A>
inline
void
score_dispose (T *p, long dn, A a)
{
   if (p && p->score (dn) == 0)
      a.dispose (p);
}

template <typename T>
inline
void
score_dispose (T *p, long dn)
{
   score_dispose (p, dn, new_delete_factory ());
}

template <typename H, typename T>
inline
H
push_chain (H *h, T *b, T *e)
{
   for ( ; ; ) 
   {
      H head = *h;
      e->next = head;
      if (atomic_cas (h, head, H (b)))
         return head;
   }
}

template <typename H, typename T>
inline
H
swap_chains (H *h, T *b)
{
   for ( ; ; )
   {
      H head = *h;
      if (atomic_cas (h, head, H (b)))
         return head;
   }
}

template <typename H, typename T>
inline
H
trace_push_chain (H *h, T *b)
{
   for ( ; ; )
      if (H head = *h)
         break;
      else if (atomic_cas (h, head, H (b)))
         return head;

   for (T *e = b; ; e = e->next)
      if (e->next == 0)
         return push_chain (h, b, e);
}

} //namespace lf2

#endif //AEON__LIBS_LF_AUX_H
