#ifndef AEON__LIBS_UTILS_TAGGED_DATA_H
#define AEON__LIBS_UTILS_TAGGED_DATA_H 1

#include "cxx.h"

template <typename T>
struct tagged_traits
{
   typedef T *  data_type;
   typedef long tag_type;
   typedef long data_raw_type;
   typedef long tag_raw_type;
   enum { data_bits = 48, tag_bits = 16 };
};

template <typename T>
struct tagged_data
{
   typedef tagged_traits <T> traits_type;
   typedef typename traits_type::data_type data_type;
   typedef typename traits_type::tag_type tag_type;
   typedef typename traits_type::data_raw_type data_raw_type;
   typedef typename traits_type::tag_raw_type tag_raw_type;

   enum
   {
      tag_bits = traits_type::tag_bits,
      data_bits = traits_type::data_bits,
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
