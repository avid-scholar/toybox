#ifndef AEON__LIBS_MEM_MSTRING_H
#define AEON__LIBS_MEM_MSTRING_H 1

#include "mrange.h"
#include "utils/new.h"
#include "utils/types.h"
#include "utils/marks.h"
#include "utils/swap.h"
#include "utils/tagged_data.h"
#include "utils/ref_template.h"

typedef ref_template <struct mstring> mstring_ref;

struct mstring_impl;

template <>
struct tagged_traits <mstring_impl>
{
   typedef mstring_impl * data_type;
   typedef int8 data_raw_type;
   typedef uint2 tag_type;
   typedef uint2 tag_raw_type;
   enum { data_bits = 48, tag_bits = 16 };
};

struct mstring
{
   typedef tagged_data <mstring_impl> impl_t;

   mstring () { init (); }
   mstring (mstring const &);
   mstring (mrange_const, mark__static);
   mstring (mrange_const);
   mstring (mstring_ref r) { init (); r.move_to (*this); }
   ~mstring ();

   mstring& operator= (mstring const &r) { assign (r); return *this; }
   bool operator== (mstring const &r) const;
   bool operator!= (mstring const &r) const {return ! (*this == r); }
   bool operator< (mstring const &r);

   mstring & swap (mstring &r) { ut::swap (r.p, p); return *this; }
   mstring & clear () { destroy (); p = ptr_t::mk (); return *this; }

   offset len () const;

   bool empty () const;
   bool packed () const; //empty () => !packed ()

   mrange_const bytes () const;
   mrange_const extract (mrange mr = mrange (), offset start = 0) const;

private:

   void init () { p = ptr_t::mk (); }
   void destroy ();
   void assign (mstring const &);

   impl_t impl;
};

#endif //AEON__LIBS_MEM_MSTRING_H
