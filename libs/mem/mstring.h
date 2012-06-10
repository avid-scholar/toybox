#ifndef AEON__LIBS_MEM_MSTRING_H
#define AEON__LIBS_MEM_MSTRING_H 1

#include "mrange.h"
#include "utils/new.h"
#include "utils/types.h"
#include "utils/tags.h"
#include "utils/swap.h"
#include "utils/tagged_ptr.h"
#include "utils/ref_template.h"

typedef ref_template <struct mstring> mstring_ref;

struct mstring
{
   typedef tagged_ptr <struct mstring_impl> impl_t;

   mstring () { init_empty (); }
   mstring (mstring const &);
   mstring (mrange_const, tag__static);
   mstring (mrange_const);
   mstring (mstring_ref mr) { init_empty (); mr.move_to (*this); }
   mstring& operator= (mstring const &r);
   bool operator== (mstring const &r) const;
   bool operator!= (mstring const &r) const {return ! (*this == r); }
   bool operator< (mstring const &r);

   mstring & swap (mstring &r) { ut::swap (r.data, data); return *this; }
   mstring & clear () { this->~mstring (); data = impl_t::mk (); return *this; }

   length size () const;

   bool empty () const;
   bool packed () const; //empty () is always false when packed () is true

   mrange_const bytes () const;

   mstring & unpack ();
   mstring & pack ();

   void extract (mrange mr, offset start = 0) const; //does not throw

private:

   void init_empty () { data = impl_t::mk (); }

   impl_t data;
};

#endif //AEON__LIBS_MEM_MSTRING_H
