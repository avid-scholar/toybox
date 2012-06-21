#ifndef AEON__LIBS_MEM_MSTRING_HXX
#define AEON__LIBS_MEM_MSTRING_HXX 1

#include "mstring.h"
#include "maf.h"
#include <cassert>

inline void mstring::destroy ()
{
   if (!packed () && !empty ())
      free (p.ptr ());
}

inline bool mstring::packed () const
{
   return p.tag != 0;
}

inline bool mstring::empty () const
{
   return p.tag == 0 && p.pointer == 0;
}

inline mstring::mstring (mstring const &r)
{
   assert (&r != this);
   init ();
   assign (r);
}

// tag -- 16 bit
//
// 0000 0xxx   0  8  8-bit
// 0000 1000   8  1  7-bit
// 001x        9  2  6-bit
// 010x       11  2  5-bit
// 011x       13  2  4-bit
// 1000       15  1  4-bit
// 1001       20  1  3-bit
// 11xx       21  4  3-bit
//
// 1011 0xxx  xxxx xxxx static external string, 2048 bytes max 
// 1011 10xx  xxxx xxxx dynamic external string, exact size
//                      block is x8 aligned 1024 bytes max
//                      sizes below 7 indicate external size:
//                         110 -- external static string, 8 byte node, size under 65535 + 1024 (adjusted)
//                         101 -- external static string, 16 byte node, size unlimited
//                         100 -- external dynamic string, 8 byte header, 4 bytes for allocated, 4 byte for used
//                         0xx -- unused

struct mstring_package_type
{
   enum e
   {
      p8, //8-bit
//      p7, //7-bit ascii
//      p6, //6-bit a-z A-Z 0-9 _ space
//      p5, //5-bit a-z
//      p4, //4-bit decimal digits
//      p3, //3-bit ?! 0-7
      s,  //static, size packed
      d,  //dynamic, size packed
      dn, //dynamic, node packed
   };
};

inline void mstring::assign (mstring const &r)
{
   if (&r == this)
      return;

   destroy ();
   if (r.packed () || r.empty ())
   {
      p = r.p;
      return;
   }

   p = ptr_t::mk (ma <byte> (r.size ()), 0);
}

#if 0
   mstring (mrange_const, tag__static);
   mstring (mrange_const);
   mstring (mstring_ref mr) { init_empty (); mr.move_to (*this); }
   mstring& operator= (mstring const &r);
   bool operator== (mstring const &r) const;
   bool operator!= (mstring const &r) const {return ! (*this == r); }
   bool operator< (mstring const &r);

   mstring & swap (mstring &r) { ut::swap (r.p, p); return *this; }
   mstring & clear () { this->~mstring (); p = impl_t::mk (); return *this; }

   length size () const;

   bool empty () const;
   bool packed () const; //empty () => !packed ()

   mrange_const bytes () const;
   mrange_const extract (mrange mr = mrange (), offset start = 0) const;
#endif

#endif //AEON__LIBS_MEM_MSTRING_HXX
