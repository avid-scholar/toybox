#ifndef LIBS_LF_INT_STACK_H
#define LIBS_LF_INT_STACK_H 1

#include "tool_ptr.h"
#include "utils/flink.h"
#include "utils/thin_holder.h"

namespace lf2
{

template <typename T, typename A = new_delete_factory, long Multiplier = 2 /*if in doubt, go away*/>
class int_stack : thin_holder <A>
{
   typedef tool_ptr <T> impl_t;
   typedef typename impl_t::ptr_t ptr_t;
   impl_t impl;

public:

   int_stack (A a = A ()) : thin_holder <A> (a) {}

   ~int_stack () { tdrop (grab ()); }

// + void push (T *); //new object
//   void tpush (T *); //new traced chain
//   void cpush (T *b, T *e); //new chain
//
// + T * pop ();
// + void drop (T *) const; //drop object previusly popped object
// + void tdrop (T *) const; //drop previusly popped chain (traced)
//   void cdrop (T *b, T *e) const; //drop previusly popped chain
//
// + T * grab (); //take whole chain
// + T * swap (T *); //replace whole chain with another
//
// + void fpush (T const &T); //'factory' push
// + bool fpop (T &out); //'factory' pop

   void push (T *t) { assert (t->c & 1); impl.alter (typename impl_t::push_func (t)); }

   template <typename U>
   void fpush (U const &u)
   {
      push (this->thin_get ().produce (sig <T> (), u));
   }

   typedef typename impl_t::template pop_func <A, Multiplier> pop_func;

   ptr_t rpop ()
   {
      ptr_t res;
      return impl.alter (pop_func (&res, this->thin_get ())) ? res : ptr_t::mk ();
   }

   T * pop ()
   {
      ptr_t res = rpop ();
      score_dispose (res.ptr (), res.tag * Multiplier, this->thin_get ());
      return res.ptr ();
   }

   template <typename U>
   bool fpop (U &u)
   {
      ptr_t res;
      bool success = impl.alter (pop_func (&res, this->thin_get ()));
      if (!success)
         return false;

      u = *res.ptr ();
      score_dispose (res.ptr (), res.tag * Multiplier - 1, this->thin_get ());
      return true;
   }

   void rdrop (ptr_t p) const { score_dispose (p.ptr (), p.tag * Multiplier - 1, this->thin_get ()); }

   void drop (T *p) const { score_dispose (p, -1, this->thin_get ()); }

   void tdrop (T *p)
   {
      for (long d = -1; p; )
      {
         ptr_t next = p->next;
         score_dispose (p, d, this->thin_get ());
         d = next.tag * Multiplier - 1;
         p = next.ptr ();
      }
   }

   T * grab () { return swap (0); }

   T * swap (T *p)
   {
      ptr_t res;
      impl.alter (typename impl_t::swap_func (&res, ptr_t::mk (p)));
      score_dispose (res.ptr (), res.tag * Multiplier, this->thin_get ());
      return res.ptr ();
   }
};

} //namespace lf2


#endif //LIBS_LF_INT_STACK_H
