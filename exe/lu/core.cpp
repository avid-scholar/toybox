#include "core.h"

#include <map>

struct core
{
    typedef std::map <std::string, binary_node *> node_map; 
    node_map nodes;
};

core *
core_create ()
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
