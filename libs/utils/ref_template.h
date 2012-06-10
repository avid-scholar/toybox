#ifndef AEON__LIBS_UTILS_REF_TEMPLATE_H
#define AEON__LIBS_UTILS_REF_TEMPLATE_H 1

#include "tagged_ptr.h"

template <typename T>
struct ref_template 
{
   ref_template (T const &ms) : p (ptr_t::mk (&ms, 0)) {}
   ref_template (T &ms, tag__recyclable) : p (ptr_t::mk (&ms, 1)) {} 

   void move_to (T &t) { if (p.tag) p.ptr ()->swap (t); p = ptr_t::mk (); }
   T const * operator-> () const { return p.ptr (); }

private:

   typedef tagged_ptr <T> ptr_t;
   ptr_t p;
};

#endif //AEON__LIBS_UTILS_REF_TEMPLATE_H
