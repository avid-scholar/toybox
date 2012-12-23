#ifndef AEON__EXE_LU_CORE_H
#define AEON__EXE_LU_CORE_H 1

#include "binary.h"
#include <map>

struct core
{
    std::map <std::string, binary_node *> core_node_map; 
    
    bool add (std::string s, binary_node * bn)
    {
        bool r = nodes.insert (std::make_pair (s, bn)).second;
        if (!r)
            binary_node_score (bn, -1);

        return r;
    }

    ~core ()
    {
        for (core_node_map::iterator it = nodes.begin (); it != node.end (); ++it)
            binary_node_score (it->second, -1);
    }
};

#endif //AEON__EXE_LU_CORE_H
