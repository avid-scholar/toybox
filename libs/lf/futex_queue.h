#ifndef AEON__LIBS_LF_FUTEX_QUEUE_H
#define AEON__LIBS_LF_FUTEX_QUEUE_H 1

#include <cassert>

void *
futex_queue_pop (void ** head, bool block);

void
futex_queue_push (void ** head, void * n, void ** nnext);

bool
futex_queue_wake (void ** head);

void
futex_queue_sleep (void ** head);

bool
futex_queue_test_empty (void * head);

bool
futex_queue_test_sleepy (void * head);

bool
futex_queue_try_lock (void ** head);

void
futex_queue_unlock (void ** head);

#define QUEUE_SLEEP_MARK (void *) 1l
#define QUEUE_LOCK_MARK (void *) 2l

bool
futex_queue_test_empty (void * head)
{
    return head == 0 || head == QUEUE_SLEEP_MARK;
}

bool
futex_queue_test_sleepy (void * head)
{
    return head == QUEUE_SLEEP_MARK;
}

inline
void *
futex_queue_pop (void ** head, bool block)
{
    for ( ; ; )
    {
        void * p = *head;
        if (p == 0 || p == QUEUE_SLEEP_MARK)
        {
            if (!block)
                return 0;

            if (p || __sync_bool_compare_and_swap (head, 0, QUEUE_SLEEP_MARK))
                futex_queue_sleep (head);

            continue;
        }

        if (__sync_bool_compare_and_swap (head, p, 0))
            return p;
    }
}

inline
void
futex_queue_push (void ** head, void * n, void ** nnext)
{
    for ( ; ; )
    {
        void * h = *head;
        bool wake = h == QUEUE_SLEEP_MARK;
        *nnext = wake ? 0 : h;
        if (__sync_bool_compare_and_swap (head, h, n))
        {
            if (wake)
                futex_queue_wake (head);

            return;
        }
    }
}

bool
futex_queue_try_lock (void ** head)
{
    for ( ; ; )
    {
        void * h = *head;
        if ((long) h & (long) QUEUE_LOCK_MARK)
            return false;

        if (__sync_bool_compare_and_swap (head, h, (long) h | (long) QUEUE_SLEEP_MARK))
            return true;
    }
}

void
futex_queue_unlock (void ** head)
{
    for ( ; ; )
    {
        void * h = *head;
        assert (((long) h & (long) QUEUE_LOCK_MARK) == 0);

        if (__sync_bool_compare_and_swap (head, h, (void*) ((long) h & (~(long) QUEUE_LOCK_MARK))))
            return;
    }
}

#endif //AEON__LIBS_LF_FUTEX_QUEUE_H
