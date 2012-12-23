#ifndef AEON__LIBS_LF_FUTEX_QUEUE_H
#define AEON__LIBS_LF_FUTEX_QUEUE_H 1

#include <linux/futex.h>
#include <sys/syscall.h>

template <typename T>
struct futex_queue
{
   futex_queue () : head (0) {}

   typedef T node;

   node *head;

   node *pop (bool block = true)
   {
      for ( ; ; )
      {
         node *p = head;
         if (p == 0 || p == (node *) -1)
         {
            if (p || __sync_bool_compare_and_swap (&head, 0, (node *) -1))
            {
               if (block)
                  syscall (SYS_futex, &head, FUTEX_WAIT, -1u, NULL, NULL, 0);
               else
                  return 0;
            }
         
            continue;
         }

         if (__sync_bool_compare_and_swap (&head, p, 0))
            return p; 
      }
   }

   void push (node *n)
   {
      for ( ; ; )
      {
         node *h = head;
         bool wake = h == (node *) -1l;
         n->next = wake ? 0 : h;
         if (__sync_bool_compare_and_swap (&head, h, n))
         {
            if (wake)
               this->wake ();

            return;
         }
      }
   }

   void wake () { syscall (SYS_futex, &head, FUTEX_WAKE, 1, NULL, NULL, 0); }
};

#endif //AEON__LIBS_LF_FUTEX_QUEUE_H
