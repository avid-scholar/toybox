#ifndef AEON__LIBS_UTILS_TAGGED_DATA_H
#define AEON__LIBS_UTILS_TAGGED_DATA_H 1

#include "cxx.h"
#include "types.h"

template <typename T> struct tagged_traits_data_type     {  typedef T *  type;   };
template <typename T> struct tagged_traits_data_raw_type {  typedef int8 type;   };
template <typename T> struct tagged_traits_tag_type      {  typedef int8 type;   };
template <typename T> struct tagged_traits_tag_raw_type  {  typedef int8 type;   };
template <typename T> struct tagged_traits_bits          {  enum { data = 16 };  };

template <typename T>
struct tagged_data
{
   typedef typename tagged_traits_data_type <T>::type       data_type;
   typedef typename tagged_traits_data_raw_type <T>::type   data_raw_type;
   typedef typename tagged_traits_tag_type <T>::type        tag_type;
   typedef typename tagged_traits_tag_raw_type <T>::type    tag_raw_type;

   enum
   {
      tag_bits = tagged_traits_bits::data,
      data_bits = 64 - tag_bits,
      tag_max = (tag_raw_type) (1 << (tag_bits - !((tag_raw_type) -1 > 0)))
   };

   data_type data () const { return (data_type) (data_raw_type) data_raw; }
   tag_type tag () const { return (tag_type) (tag_raw_type) tag_raw; }
   tagged_data add (tag_type dt) const { return mk (data (), tag_raw + dt); }

   //no constructor because of lf::shell
   static tagged_data mk (data_type d = data_type (), tag_type t = tag_type ())
   {
      tagged_data p;
      p.tag_raw = (tag_raw_type) t;
      p.data_raw = (data_raw_type) d;
      return p;
   }

   data_raw_type data_raw : data_bits;
   tag_raw_type tag_raw : tag_bits;
};

#endif //AEON__LIBS_UTILS_TAGGED_DATA_H
