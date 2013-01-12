#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "futex_queue.h"

void
futex_queue_sleep (void ** head)
{
    syscall (SYS_futex, head, FUTEX_WAIT, (int)(long) QUEUE_SLEEP_MARK, NULL, NULL, 0);
}

bool
futex_queue_wake (void ** head)
{
    if (!futex_queue_test_sleepy (*head))
        return false;

    syscall (SYS_futex, head, FUTEX_WAKE, 1, NULL, NULL, 0);
    return true;
}
