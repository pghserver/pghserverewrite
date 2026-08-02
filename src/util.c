#include "util.h"
#include <stdlib.h>
#include <string.h>

char *pgh_strdup(const char *string)
{
    size_t length = strlen(string) + 1;
    char *dup = malloc(length);
    if (dup == NULL)
        return NULL;

    memcpy(dup, string, length);
    return dup;
}

char *pgh_abspath(const char *path)
{
    return realpath(path, NULL);
}
