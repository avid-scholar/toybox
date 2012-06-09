#ifndef AEON__LIBS_MEM_MSTRING_H
#define AEON__LIBS_MEM_MSTRING_H 1

#include "mrange.h"
#include "utils/new.h"
#include "utils/types.h"
#include "utils/tags.h"
#include "utils/swap.h"
#include "utils/tagged_ptr.h"

struct mstring_ref;

struct mstring
{
   typedef tagged_ptr <mstring_impl> impl_t;

   mstring () : data (impl_t::mk ()) {};
   mstring (mstring const &);
   mstring (mrange_const, tag__static);
   mstring (mrange_const);
   mstring (mstring_ref &);

   template <int N> mstring (char const (&a)[N])

   mstring& operator= (mstring const &r) const;
   bool operator== (mstring const &r) const;
   bool operator!= (mstring const &r) const {return ! *this == r; }
   bool operator< (mstring const &r);

   mstring & swap (mstring &r) { ut::swap (r.data, data); return *this; }
   mstring & clear () const { ~mstring (); data = impl_t::mk (); return *this; }

   length size () const;

   bool empty () const;
   bool packed () const; //empty () is always false if packed () is true

   //these two will throw if range is packed
   mrange_const bytes () const;

   mstring & unpack ();
   mstring & pack ();

   void extract (mrange mr, offset start = 0) const; //does not throw

   impl_t & raw () __attribute__ ((deprecated)) { return data; }

private:
   impl_t data;
};

struct mstring_ref
{
   mstring_ref (mstring const &ms) { s.c = &ms; is_recyclable = false; }
   mstring_ref (mstring &ms, tag__recyclable) { s.m = &ms; is_recyclable = true; } 

   void copy_to (mstring &m) { if (is_recyclable) s.m->swap (m); s.m->clear (); is_recyclable; }
   mstring const * operator-> () const { return s.c; }

private:

   union
   {
      mstring *m;
      mstring const *c;
   } s;

   bool is_recyclable : 1;
};

inline mstring::mstring (mstring_ref &ref)
{
   data = impl_t::mk ();
   ref.copy_to (*this);
}

#endif //AEON__LIBS_MEM_MSTRING_H
