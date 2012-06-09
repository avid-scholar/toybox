#ifndef AEON__LIBS_UTILS_CXX_H
#define AEON__LIBS_UTILS_CXX_H 1

template <bool b, typename Then, typename Else>
struct if_
{
   typedef Then type;
};

template <typename Then, typename Else>
struct if_ <false, Then, Else>
{
   typedef Else type;
};

template <typename T>
struct remove_const 
{
   typedef T type;   
};

template <typename T>
struct remove_const <T const>
{
   typedef T type; 
};

class noncopyable {};

template <bool b> struct static_assert_test;
template <> struct static_assert_test <true> { typedef void type; };

#define REQUIRE(c) typedef static_assert_test <c>::type static_assert_impl_typedef;

template <typename T, T t>
struct val
{
   static const T value = t;
   typedef val type;

   static val mk () { return val (); }
};

typedef val <bool, false> false_;
typedef val <bool, true> true_;

template <typename T> struct thin_probe : public T { char c; };
template <typename T> struct is_thin : public val <bool, sizeof (thin_probe <T>) == 1> {};

template <typename T> struct sig { static sig mk () { return sig <T> (); } typedef T type; };

template <typename C, typename T = void>
struct enable_if
{
   typedef T type;
};

#endif //AEON__LIBS_UTILS_CXX_H
