#ifndef AEON__LIBS_UTILS_REVERSE_CHAIN_H
#define AEON__LIBS_UTILS_REVERSE_CHAIN_H 1

namespace ut
{

template <typename T>
inline
T *
reverse_chain (T *n)
{
   for (T *p = 0, *c = n; ; )
   {
      T *next = c->next;
      c->next = p;

      if (next == 0)
         return c;

      p = c;
      c = next;
   }
}

} //namespace ut

#endif //AEON__LIBS_UTILS_REVERSE_CHAIN_H
