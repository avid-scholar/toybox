#ifndef AEON__LIBS_BINDATA_BSTRING_H
#define AEON__LIBS_BINDATA_BSTRING_H 1

#include "brange.h"
#include "utils/swap.h"

struct bstring
{
   bstring ();
   bstring (bstring const &);
   bstring (const_brange);
   bstring& operator= (bstring const &);
   void swap (bstring &r) { ut::swap (r, data); }

   ulong size () const;
   const_brange bytes () const;

private:
   char *data;
};

#endif //AEON__LIBS_BINDATA_BSTRING_H
