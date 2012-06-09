#ifndef AEON__LIBS_LF_INT_STOCK_H
#define AEON__LIBS_LF_INT_STOCK_H 1

#include "aux.h"
#include "utils/cxx.h"
#include "utils/thin_holder.h"
#include "utils/new_delete_factory.h"

namespace lf2
{

template <typename T, typename A = new_delete_factory>
class int_stock : noncopyable, public thin_holder <A>
{
   T *head;

public:

   int_stock (A a = A ()) : thin_holder <A> (a), head (0) {}

   bool push (T *b) { return push (b, b); }
   bool push (T *b, T *e) { return push_chain (&head, b, e); }
   T *swap (T *b) { return swap_chains (&head, b); }
   T *grab () { return swap (0); }

   bool fpush (T const &t) { return push (this->thin_get ().produce (sig <T> (), t)); }

   bool tpush (T *b) { return trace_push_chain (&head, b); }

   T *top () { return head; }
   T const *top () const { return head; }

   bool empty () const { return top () == 0; }

   ~int_stock () { tdrop (head); }

   void drop (T *p) { dispose_chain (p, p->next, this->thin_get ()); }
   void tdrop (T *p) { dispose_chain (p, this->thin_get ()); }
};

} //namespace lf2

#endif //AEON__LIBS_LF_INT_STOCK_H
