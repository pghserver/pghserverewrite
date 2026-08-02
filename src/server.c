#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

int pgh_listen(const PghArgs args)
{
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {.sin_family = AF_INET, .sin_port = htons(args.port), .sin_addr.s_addr = INADDR_ANY};
    bind(server, (struct sockaddr *)&address, sizeof(address));
    listen(server, 128);
    return server;
}

void *pgh_handle(void *arg)
{
    int client = (intptr_t)arg;
    close(client);
    return NULL;
}
