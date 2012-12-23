#include "binary.h"
#include "core.h"
#include "config.h"

int main (int argc, char const * argv [])
{
    core * c = core_construct ();
    for (int i = 1; i < argc; ++i)
        do_lua_config (c, argv [i]);

    while (core_event_wait (c))
        core_event_process_all (c);
}
