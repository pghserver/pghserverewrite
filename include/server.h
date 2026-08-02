#pragma once

#include "typing.h"
#include "args.h"

int pgh_listen(const PghArgs args);

void *pgh_handle(void *arg);
