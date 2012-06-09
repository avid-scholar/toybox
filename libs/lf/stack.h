#ifndef AEON__LIBS_LF_STACK_H
#define AEON__LIBS_LF_STACK_H 1

#include "int_stack.h"

namespace lf2
{

template <typename T>
struct stack_node : public flink <tagged_ptr <stack_node <T> > >, public shared_count
{
   typedef tagged_ptr <stack_node <T> > next_type;
   typedef flink <next_type> next_holder;

   stack_node (T const &t) : next_holder (next_type::mk (0, 0)), shared_count (1), data (t) {}
   
   operator T & () { return data; }

   T data;
};

template <typename T, typename A = new_delete_factory>
struct stack
{
   typedef stack_node <T> node_t;

   stack (A a = A ()) : impl (a) {}

   void push (T const &t)
   {
      impl.fpush (t); 
   }

   bool pop (T &t)
   {
      return impl.fpop (t);
   }

private:
   typedef int_stack <node_t, A> impl_t;
   impl_t impl;
};

} //namespace lf2

#endif //AEON__LIBS_LF_STACK_H
