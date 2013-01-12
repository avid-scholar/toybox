#include "thread.h"

namespace
{

struct task_node
{
    thread_task * next;
    core * c;
    data d;
};

struct thread_node
{
    thread_node * next;
    void * tasks;

    thread () :
        next (0),
        tasks (0)
    {}
};

struct thread_pool
{
    thread_pool () : 
        threads (0),
        tasks (0),
        thread_count (0),
        excessive_threads (0),
    {}

    void * threads;
    void * tasks;
    long thread_count;
    long excessive_threads;

    void resize (long n);

    static void post_task (thread_pool *, data *);

    void stop ();
};

//TODO: try_lock or post approach
inline void thread_pool::resize (long n)
{
    long tc = thread_count;

    if (n <= 0 || n == tc)
        return;

    if (tc > n)
    {
        __sync_add_and_fetch (& excessive_threads, tc - n);
        //actually wake some threads (or otherwize how do i expect to do it in future anyway)
    }
    else
    {
        for (long i = n; i < tc; ++i)
        {
             
        }

        return;
    }

    for (long i = thread_count; i < n; )
    {
    
    }

    else
}

void destroy_thread_pool (module_node * node)
{
    thread_pool * p = (thread_pool *) node;
    p->stop (); //blocks
    delete p;
}

module lu_thread_impl (error_pusher * er, data * d)
{
    module mod;
    mod.node = (module_node) new thread_pool;
    mod.destroy_node = destroy_thread_pool;
    return mod;
}

} //namespace

extern "C"
{

module lu_thread (error_pusher * er, data * d)
{
    return lu_thread_impl (er, d);
}

}
