#include "load.h"
#include "module.h"
#include "error.h"

#include <dlfcn.h>

typedef void * dl_handle;

struct loader_node
{
    module mod;
    dl_handle handle;
};

loader_node *
load (
    bytes * file,
    bytes * symbol,
    data * args)
{
    dl_handle handle = dlopen (bytes_cstr (*file), RTLD_NOW);
    if (!handle)
        return NULL;

    void * sym = dlsym (handle, bytes_cstr (*symbol));
    if (!sym)
    {
        dlclose (handle);
        return NULL;
    }

    module_constructor * mprod = *(module_constructor**) (&sym);
    module mod = mprod (&error_push, args);

    if (mod.uf.method == NULL)
        return NULL;

    loader_node * n = new loader_node ();
    n->mod = mod;
    n->handle = handle;
    return n;
}

void
unload (loader_node *n)
{
    n->mod.destroy_node (n->mod.node);
    dlclose (n->handle);
    delete n;
}
