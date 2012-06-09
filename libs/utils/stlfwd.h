#ifndef AEON__LIBS_UTILS_STLFWD_H
#define AEON__LIBS_UTILS_STLFWD_H 1

namespace std
{

template <typename T> class allocator;
template <typename C> class char_traits;
template <typename C, typename T, typename A> class basic_string;
typedef basic_string <char, char_traits <char>, allocator <char> > string;

template <typename F, typename S> class pair;

template <typename T, typename A> class list;
template <typename T, typename A> class vector;
template <typename T, typename A> class deque;
template <typename T, typename L, typename A> class set;
template <typename T, typename L, typename A> class multiset;
template <typename K, typename V, typename L, typename A> class map;
template <typename K, typename V, typename L, typename A> class multimap;

//TODO: unordered

template <typename T> class auto_ptr;

} //namespace std

#endif //AEON__LIBS_UTILS_STLFWD_H
