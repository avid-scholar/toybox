#ifndef AEON__LIBS_LF_TOOL_PTR_H
#define AEON__LIBS_LF_TOOL_PTR_H 1

#include "aux.h"
#include "utils/tagged_data.h"

namespace lf2
{

template <typename T>
struct tool_ptr
{
   typedef tagged_data <T> ptr_t;

   ptr_t p_;

   tool_ptr (T *p = 0) : p_ (ptr_t::mk (p)) {}

   template <typename Func>
   bool
   alter (Func f)
   {
      return alter (f, p_);
   }

   template <typename Func>
   bool
   alter (Func f, ptr_t t) throw ()
   {
      for ( ; ; )
      {
         if (f.cancel (t))
            return false;

         long picked = t.data () ? f.pick (t) : 0;
         if (picked)
         {
            assert (picked + t.tag () < ptr_t::tag_max);
            ptr_t t2 = t.add (picked);
            if (!atomic_cas (&p_, t, t2))
            {
               t = p_;
               continue;
            }
         
            t = t2;
         }

         for ( ; ; )
         {
            ptr_t n = f.propose (t);

            if (atomic_cas (&p_, t, n))
            {
               f.score_removed (t, -picked);
               return true;
            }

            ptr_t told = t;
            t = p_;
            if (told.data () == t.data ())
               continue;

            if (picked)
               f.score (told.data (), -picked);

            break;
         }
      }
   }

   struct never_cancel { bool cancel (ptr_t) const { return false; } };

   struct dont_pick
   {
      long pick (ptr_t) const { return 0; }
      void score_removed (ptr_t, long) const {}
      void score (T *, long) const {} 
   };

   struct swap_func : public never_cancel, public dont_pick
   {
      ptr_t *out, in;
      swap_func (ptr_t *out, ptr_t in) : out (out), in (in) {}

      ptr_t propose (ptr_t) { return in; }
      void score_removed (ptr_t p, long) { *out = p; }
   };

   struct push_func : public never_cancel, public dont_pick
   {
      T *n;
      push_func (T *t) : n (t) {}

      ptr_t propose (ptr_t p) { n->next = p; return ptr_t::mk (n, 0); }
   };

   template <typename A, long Multiplier>
   struct pop_func : thin_holder <A>
   {
      ptr_t *result;

      pop_func (ptr_t *res, A a = A ()) : thin_holder <A> (a), result (res) { }

      bool cancel (ptr_t p) const { return p.data () == 0; }

      long pick (ptr_t) const { return 1; }

      ptr_t propose (ptr_t p) const { return p.data ()->next; }

      void score (T *p, long dn) { score_dispose (p, Multiplier * dn, this->thin_get ()); }

      void score_removed (ptr_t p, long dn) const { *result = p.add (dn); }
   };

};

} //namespace lf2

#endif //AEON__LIBS_LF_TOOL_PTR_H
