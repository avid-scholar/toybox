#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>

void
futex_queue_sleep (void ** head)
{
    syscall (SYS_futex, head, FUTEX_WAIT, -1u, NULL, NULL, 0);
}

void
futex_queue_wake (void ** head)
{
    syscall (SYS_futex, head, FUTEX_WAKE, 1, NULL, NULL, 0);
}
