#ifndef LIBS_LF_BLOCK_STOCK_H
#define LIBS_LF_BLOCK_STOCK_H 1

#include "tool_ptr.h"

namespace lf2
{

template <typename T>
struct chain_seg
{
   T *b, *e;
   long size;

   chain_seg (T *bb = 0) { init (bb, bb, 1); }
   chain_seg (T *bb, T *ee, long sz = 0) { init (bb, ee, sz); }

   void init (T *bb, T *ee, long sz)
   {
      b = bb;
      e = ee;
      if (sz)
         size = sz;
      else if (bb)
         for (size = 1; bb != ee; bb = bb->next, ++size);
      else
         size = 0;
   }
};

struct push_result
{
   enum e { regular, first, claimed };
};

template <typename T>
struct claimable_block_stock
{
   typedef tool_ptr <T> impl_t;
   typedef typename impl_t::ptr_t ptr_t;

   enum e { raw_mark = 1, claimed_mark = 2, count_step = 4, mark_mask = 3, count_mask = ~mark_mask };

   claimable_block_stock () : p (ptr_t::mk ()) {}

   struct push_func : public impl_t::never_cancel, public impl_t::dont_pick
   {
      chain_seg <T> cs;
      push_result::e *result;
      long tmax;

      push_func (chain_seg <T> cs, int *result, long tmax) : cs (cs), result (result), tmax (tmax) { }

      ptr_t propose (ptr_t p) const
      {
         cs.e->next = p.ptr ();
         long rt = (p.tag & count_mask) + count_step * cs.size;
         bool first = !p;
         bool last = (rt / count_step == tmax) && (rt & claimed_mark) == 0;
         if (first)
            *result = push_result::first;
         else if (last)
         {
            rt |= claimed_mark; //full block, attempt to claim
            *result = push_result::claimed;
         }
         else
            *result = push_result::regular;

         return ptr_t::mk (cs.b, rt);
      }
   };

   push_result::e push (chain_seg <T> cs, long tmax)
   {
      push_result res;
      impl.alter (push_func (cs, &res, tmax));
      return res;
   }

   template <bool do_claim>
   struct grab_claim_func : public impl_t::dont_pick
   {
      ptr_t *res;
      grab_claim_func (ptr_t *res) : res (res) {}
      bool cancel (ptr_t p) const { if (do_claim) return p.tag & claimed_mark; assert (p.tag & claimed_mark); return false; }
      ptr_t propose (ptr_t p) const { return ptr_t::mk (0, do_claim ? p.tag & raw_mark | claimed_mark : mark_mask); }
      ptr_t score_removed (ptr_t p, long) const { *res = p; }
   };

   ptr_t grab_claim ()
   {
      ptr_t res;
      return impl.alter (grab_claim_func <true> (&res)) ? res : ptr_t::mk ();
   }

   ptr_t grab ()
   {
      ptr_t res;
      return impl.alter (grab_claim_func <false> (&res)) ? res : ptr_t::mk ();
   }

   impl_t impl;
};

} //namespace lf2


#endif //LIBS_LF_BLOCK_STOCK_H
