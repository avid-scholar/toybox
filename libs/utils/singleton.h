#ifndef LIBS_UTILS_SINGLETON_H
#define LIBS_UTILS_SINGLETON_H 1

template <typename T>
T &
singleton ()
{
   static T t;
   return t;
}

#endif //LIBS_UTILS_SINGLETON_H
