#ifndef AEON__LIBS_LF_FUTEX_QUEUE_H
#define AEON__LIBS_LF_FUTEX_QUEUE_H 1

void *
futex_queue_pop (void ** head, bool block);

void
futex_queue_push (void ** head, void ** n);

void
futex_queue_wake (void ** head);

void
futex_queue_sleep (void ** head);

inline
void *
futex_queue_pop (void ** head, bool block)
{
    for ( ; ; )
    {
        void * p = *head;
        if (p == 0 || p == (void *) -1)
        {
            if (p || __sync_bool_compare_and_swap (head, 0, (void *) -1))
            {
                if (block)
                    futex_queue_sleep (head);
                else
                    return 0;
            }

            continue;
        }

        if (__sync_bool_compare_and_swap (head, p, 0))
            return p;
    }
}

inline
void
futex_queue_push (void ** head, void ** n)
{
    for ( ; ; )
    {
        void * h = *head;
        bool wake = h == (void *) -1l;
        *n = wake ? 0 : h;
        if (__sync_bool_compare_and_swap (head, h, n))
        {
            if (wake)
                futex_queue_wake (head);

            return;
        }
    }
}

#endif //AEON__LIBS_LF_FUTEX_QUEUE_H
