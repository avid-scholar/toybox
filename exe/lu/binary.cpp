#include "binary.h"
#include "load.h"
#include <cassert>

struct binary_node
{
    long use;
    loader_node * l;
};

binary_node *
binary_node_construct (loader_node * l)
{
    binary_node * n = new binary_node ();
    n->l = l;
    n->use = 1;
    return n;
}

void
binary_node_score (binary_node * b, long du)
{
    assert (b);

#ifdef LU_BINARY_MT
    long u = __sync_add_and_fetch (b->use, du);
    assert (u >= 0);
#else
    b->use += du;
    assert (b->use >= 0l);
#endif

    if (b->use == 0)
    {
        unload (b->l);
        delete b;
    }
}

user_function
binary_node_user_function (binary_node * b)
{
    return loader_user_function (b->l);
}
