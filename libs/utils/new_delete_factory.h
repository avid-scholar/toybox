#ifndef LIBS_UTILS_NEW_DELETE_FACTORY_H
#define LIBS_UTILS_NEW_DELETE_FACTORY_H 1

#include "utils/cxx.h"

struct new_delete_factory
{
   template <typename T>
   static
   T *
   produce (sig <T>)
   {
      return new T;
   }

   template <typename T, typename A1>
   static
   T *
   produce (sig <T>, A1 const &a1)
   {
      return new T (a1);
   }

   template <typename T>
   static
   void
   dispose (T *t)
   {
      delete t;
   }
};


#endif //LIBS_UTILS_NEW_DELETE_FACTORY_H
