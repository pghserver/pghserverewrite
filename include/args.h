#pragma once

#include "typing.h"

typedef struct
{
    char *error;

    u16 port;
    char *directory;
} PghArgs;

PghArgs args_new(u16 port, char *directory);

PghArgs args_parse(const PghArgs defaults, int argc, const char *argv[]);

void args_free(PghArgs *args);
