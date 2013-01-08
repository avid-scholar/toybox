#include "core.h"
#include "utils/reverse_chain.h"
#include "lf/futex_queue.h"

#include <map>

struct core
{
    typedef std::map <std::string, binary_node *> node_map; 
    node_map nodes;

    void * queue;

    core () : queue (0) {}
};

struct core_event
{
    core_event * next;

    enum type { quit, act } t;

    core_event () : next (0), t (quit) {};
};

struct core_event_act : public core_event
{
    void * opaque;
    void (* func) (void *);
};

core *
core_construct ()
{
    return new core ();
}

bool
core_insert (core * c, bytes s, binary_node * b)
{
    bool r = c->nodes.insert (std::make_pair (s, b)).second;
    if (!r)
        binary_node_score (b, -1);

    return r;
}

void
core_destruct (core * c)
{
    for (core::node_map::iterator it = c->nodes.begin (); it != c->nodes.end (); ++it)
        binary_node_score (it->second, -1);
    
    delete c;
}

bool
core_dispatch (core * c, bytes s, data arg, data * result)
{
    core::node_map::const_iterator it = c->nodes.find (s);
    if (it == c->nodes.end ())
        return false;

    user_function uf = binary_node_user_function (it->second);
    *result = uf.method (uf.object, arg);
    return true;
}

void
core_shutdown (core * c)
{
    core_event * e = new core_event ();
    futex_queue_push ((void **) & c->queue, e, (void **) & e->next);
}

void
core_run_event_loop (core * c)
{
    bool quit = false;

    for ( ; ; )
    {
        core_event * e = (core_event *) futex_queue_pop ((void **) & c->queue, ! quit);

        if (quit && ! e )
            return;

        e = ut::reverse_chain (e);

        for ( ; e ; )
        {
            core_event * n = e->next;
            if (e->t == core_event::quit)
            {
                quit = true;
                delete e;
            }
            else if (e->t == core_event::act)
            {
                core_event_act * a = (core_event_act *) e;
                a->func (a->opaque);
                delete a;
            }

            e = n;
        }
    }
}
