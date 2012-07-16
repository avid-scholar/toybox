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
//                       + 101 -- external static string, 16 byte node, size unlimited
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
      dn, //dynamic (or static), node packed
   };
};

template <mstring_package_type::e pt> struct mstring_package_mask;

struct mstring_package_mask <mstring_package_type::p8> { enum { bits = 5, mask = 0, sw = 3, sb = 0 }; };

struct mstring_node
{
   bool static_node : 1;
   int8 size : 63;
   byte [] more;
};

struct mstring_static_node : public mstring_node
{
   void set (byte *b, int8 sz)
   {
      static_node = true;
      size = sz;
      data = b; 
   }

   byte *data;
};

template <int8 N>
struct nbin;

template <> struct nbin <0l>
{
   static const int8 w = 0;
   static const int8 v = 0;
};

template <int8 N>
struct nbin
{
   static const int8 w = 1 + nbin <N / 10>::w;
   static const int8 v = N % 10 + 2 * nbin <N / 10>::value;
};

template <int8 N>
inline
int8
operator| (nbin <N> nb, int8 sz)
{
   return (nb.v << (16 - nb.w)) | sz; //**
}

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

   if (pack_xss (r))
      return;

   int8 sz = r.size ();
   bool can_use_xss = sz < max_packed_dynamic_size;
   byte *b = alloc_bytes (can_use_xss ? sz : sz + 8);
   mrange_const mr = r.extract (mrange_const ());
   if (!can_use_xss)
   {
      std::copy (mr.b, mr.e, b + 8);
      (mstring_node*)b->static_node = false;
      (mstring_node*)b->size = sz;
      p = ptr_t::mk (b, bin <101110> % 4);
      return;
   }

   std::copy (mr.b, mr.e, b);
   p = ptr_t::mk (b, bin <101110> % sz);
}

mstring::mstring (mrange_const r, tag__static)
{
   int8 rs = r.size ();
   if (rs == 0)
   {
      p = ptr_t::mk (0, 0);
      return;
   }

   if (rs < mstring::max_packed_static_size)
   {
      p = ptr_t::mk (r.b, nbin <10110> | rs);
      return;
   }

   mstring_static_node *n = alloc_obj <mstring_static_node> ();
   n->set (r.b, rs);
   p = ptr_t::mk (n, nbin <101110> | nbin <101>::value);
}

mstring::mstring (mrange_const r)
{
   int8 rs = r.size ();
   if (rs < 8)
   {
      int8 str = *(int8*) r.b;
      p = ptr_t::mk ((void*) (str / 256), rs + str % 256 * 256);
      return;
   }

   if (pack_xss (r))
      return;
      

   if (rs < mstring::max_packed_dynamic_size)
   {
      pack_xd ();
      return;
   }
}

mstring::mstring (mstring &r)
{
   init_empty ();
   swap (r);
}

mstring::mstring (mstring const &r)
{
   init_empty ();
   assign (r);
}

mstring& mstring::operator= (mstring const &r)
{
   assign (r);
}

#if 0
bool mstring::operator== (mstring const &r) const
{
   
}
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
