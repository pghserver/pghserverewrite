#define _POSIX_C_SOURCE 200809L

#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "typing.h"
#include "args.h"
#include "server.h"

volatile sig_atomic_t running = true;

void pgh_shutdown(int signal)
{
    running = false;
}

int main(int argc, const char *argv[])
{
    struct sigaction action = {0};
    action.sa_handler = pgh_shutdown;
    sigaction(SIGINT, &action, NULL);

    PghArgs args = args_parse(args_new(80, "."), argc, argv);
    if (strlen(args.error) != 0)
    {
        printf("%s\n", args.error);
        return ERROR;
    }

    int server = pgh_listen(args);
    if (server < 0)
    {
        fprintf(stderr, "Unable to start PghServer on port %i!\n", args.port);
        return ERROR;
    }

    printf("PghServer started on port %i!\n", args.port);
    while (running)
    {
        int client = accept(server, NULL, NULL);
        if (client < 0)
        {
            if (errno == EINTR)
                continue;

            break;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, pgh_handle, (void *)(intptr_t)client);
        pthread_detach(thread);
    }

    printf("Shutting down...\n");
    close(server);
    args_free(&args);
    return OK;
}
