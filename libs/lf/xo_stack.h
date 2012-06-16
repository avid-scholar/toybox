#ifndef AEON__LIBS_LF_XO_STACK_H
#define AEON__LIBS_LF_XO_STACK_H 1

#include "int_stack.h"

//stack with elements shared between stack and external entity

namespace lf2
{

template <typename X>
struct xo_node : public flink <tagged_data <xo_node <X> > >, public shared_count
{
   xo_node (X *x = 0) : external (x) {}
   X *external; 
};

template <typename X, typename A = new_delete_factory>
struct xo_stack
{
   typedef xo_node <X> node_t;
   typedef int_stack <node_t, A, mul> impl_t;
   typedef typename impl_t::ptr_t ptr_t;

   enum { owned = 1, claimed = 2, marked = 4, mul = 8, mul_mask = mul - 1 };

   xo_stack (A a = A ()) : impl (a) {}

   void push (X *x)
   {
      node_t * n = impl.thin_get ().produce (sig <node_t> (), x);
      n->shared_count::c = owned;
      impl.push (n);
   }

   template <typename C>
   X * pop (C const &claim_func)
   {
      for ( ; ; )
      {
         ptr_t h = impl.rpop ();

         if (!h)
            return 0;

         node_t *n = h.data ();
         long dn = h.tag () * mul;
         for ( ; ; )
         {
            long c = n->score (0);
            if (c & claimed)
            {
               score_dispose (n, dn - (c & mul_mask), impl.thin_get ());
               break;
            }
            
            if (!n->score_cas (c, c | claimed))
               continue;

            assert ((c & marked) == 0);
            bool xc = claim_func (n->external);
            for ( ; ; )
            {
               if (!xc)
               {
                  if (n->score_cas (c, c | marked))
                  {
                     score_dispose (n, dn, impl.thin_get ())
                     break;
                  }
                  
                  c = n->score (0);
               }

               if (xc || c & marked)
               {
                  X * x = n->external;
                  score_dispose (n, dn - (c & mul_mask), impl.thin_get ())
                  return x;
               }
            }
         }
      }
   }

   bool claim (node_t *n)
   {
      for ( ; ; )
      {
         long c = n->score (0);
         if (c & claimed)
         {
            if (c & marked)
            {
               score_dispose (n, -(c & mul_mask), this->thin_get ()); 
               return true;
            }

            if (n->score_cas (c, c | marked))
               return false;

            continue;
         }

         if (n->score_cas (c, c | claimed))
            return true; //score_dispose ??
      }
   }

   impl_t impl;
};

} //namespace lf2

#endif //AEON__LIBS_LF_XO_STACK_H
