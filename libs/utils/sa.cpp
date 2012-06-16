#include "sa.hxx"

namespace sa
{

bool split_half (mstring_ref in, mstring const &sep, mstring &beg, mstring &end)
{
   byte in_buf [32];
   byte sep_buf [32];
   mrange_const i = in.extract (in_buf +to_range);
   mrange_const f = find_substr (i, sep.extract (sep_buf));
   if (f.b == i.e)
      return beg.swap (i), true;

   in.extract_ms (beg, 0, f.b - i.b);
   if (f.e != i.e)
      in.extract_ms (end, f.e - i.b);
}

}
