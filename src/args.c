#include "args.h"
#include <stdlib.h>
#include <string.h>
#include "util.h"

PghArgs args_new(u16 port, char *directory)
{
    char *absolute = pgh_abspath(directory);
    if (absolute == NULL)
        return (PghArgs){.error = pgh_strdup("Directory does not exist!")};

    return (PghArgs){.error = pgh_strdup(""), .port = port, .directory = absolute};
}

PghArgs args_parse(const PghArgs defaults, int argc, const char *argv[])
{
    u16 port = defaults.port;
    char *directory = pgh_strdup(defaults.directory);

    for (int i = 1; i < argc; i++)
    {
        const char *arg = argv[i];

        if (strcmp(arg, "--port") == 0 || strcmp(arg, "-p") == 0)
        {
            if (i + 1 >= argc)
                return (PghArgs){.error = pgh_strdup("Value of --port flag must exist and be of type u16!")};

            int port_raw = atoi(argv[++i]);
            if (port_raw >= 0 && port_raw <= UINT16_MAX)
                port = (u16)port_raw;
            else
                return (PghArgs){.error = pgh_strdup("Value of --port flag must be of type u16!")};
        }
        else if (strcmp(arg, "--directory") == 0 || strcmp(arg, "-d") == 0)
        {
            if (i + 1 >= argc)
                return (PghArgs){.error = pgh_strdup("Value of --directory flag must exist!")};

            free(directory);
            directory = pgh_strdup(argv[++i]);
        }
    }

    return args_new(port, directory);
}

void args_free(PghArgs *args)
{
    free(args->error);
    free(args->directory);
}
