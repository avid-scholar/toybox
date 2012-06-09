#ifndef AEON__LIBS_LF_XO_STACK_FRAME_H
#define AEON__LIBS_LF_XO_STACK_FRAME_H 1

#include "lf/xo_stack.h"
#include "lf/block_stock.h"

namespace lf2
{

template <typename X, typename A, typename Cs, typename Gc>
void
xo_push (xo_stack <X, A> &xs, X *x, Cs seg, Gc &gc)
{
   push_result::e pr = x->bs.push (seg, x->tmax ());
   if (pr == push_result::first)
      xs.push (x); //TODO: may need immediate pop
   else if (pr == push_result::claimed)
   {
      xo_stack <X, A>::node_t *n = x->stack_node;
      if (xs.claim (x))
         gc.push (x);
   }
}

template <typename X, typename A, typename Gc>
X *
xo_pop (xo_stack <X, A> &xs, Gc &gc)
{
   X *x = xs.pop ();
   if (x == 0)
      return gc.pop ();

   return x;
}

} //namespace lf2

#endif //AEON__LIBS_LF_XO_STACK_FRAME_H
