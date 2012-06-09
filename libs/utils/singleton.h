#ifndef AEON__LIBS_UTILS_SINGLETON_H
#define AEON__LIBS_UTILS_SINGLETON_H 1

template <typename T>
T &
singleton ()
{
   static T t;
   return t;
}

#endif //AEON__LIBS_UTILS_SINGLETON_H
