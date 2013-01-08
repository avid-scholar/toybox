#include <boost/thread.hpp>
#include <cstring>
#include <cstdio>
#include "lf/futex_queue.h"

struct node
{
    node * next;
    char * data;
};

node * list;

bool quit = false;

long const thread_count = 3;

long sent = 0;

void
prod ()
{
    long s = 0;
    while (!quit)
    {
        node * n = (node *) malloc (sizeof (node));
        n->data = strdup ("hello");
        futex_queue_push ((void **) &list, (void *) n, (void **) & n->next);
        ++s;
    }

    __sync_fetch_and_add (&sent, s);
}

long got = 0;
long ok = 0;
long got_times = 0;

void
dispose (node * n)
{
    if (!n)
        return;

    ++got_times;

    for ( ; n; )
    {
        ++got;
        node * nn = n->next;
        if (strcmp (n->data, "hello") == 0)
            ++ok;

        free (n->data);
        free (n);
        n = nn;
    }
}

bool block = false;

void
cons ()
{
    while (!quit)
    {
        node * n = (node *) futex_queue_pop ((void **) &list, block); 

        dispose (n);
    }
}

int main (int argc, char *argv [])
{
    if (argc > 1)
        block = true;

    boost::thread *t1 [thread_count];
    for (long i = 0; i < thread_count; ++i)
        t1 [i] = new boost::thread (prod);

    boost::thread t2 (cons);
    
    long dt = 10;
    sleep (dt);
    quit = true;
  
    for (long i = 0; i < thread_count; ++i)
        t1[i]->join ();

    if (block)
        futex_queue_wake ((void **) &list);

    t2.join ();
    dispose (list);

    printf ("abs sent=%10ld got=%10ld got_times=%10ld got_ok=%10ld\n", sent, got, got_times, ok);
    printf ("ps  sent=%10.2f got=%10.2f got_times=%10.2f got_ok=%10.2f\n", 
        sent * .1 / dt,
        got * .1 / dt,
        got_times * .1 / dt,
        ok * .1 / dt);
    return 0;
}
