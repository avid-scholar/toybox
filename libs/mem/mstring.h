#ifndef AEON__LIBS_MEM_MSTRING_H
#define AEON__LIBS_MEM_MSTRING_H 1

#include "mrange.h"
#include "utils/new.h"
#include "utils/types.h"
#include "utils/marks.h"
#include "utils/swap.h"
#include "utils/tagged_data.h"

struct mstring_impl;

struct mstring
{
   enum e { max_packed_string = 64, max_packed_static_size = 2048, max_packed_dynamic_size = 1024 };

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

struct mstring_view
{
   mstring_view (mstring &s) : r (s.extract (buf)), s (&s) {};
   mrange bytes () const { return r; };

   void drop () { s = 0; }
   void writeback () { if (s) { s.assign (); } }
   ~mstring_view () { writeback (); }

private:

   mrange r;
   mstring *s;
   char buf [mstring::max_packed_string];
};


struct mstring_view_const
{
   mstring_view_const (mstring const &m) : r (m.extract (buf)) {};
   mrange_const bytes () const { return r; }

private:

   mrange_const r;
   char buf [mstring::max_packed_string];
};

#endif //AEON__LIBS_MEM_MSTRING_H
