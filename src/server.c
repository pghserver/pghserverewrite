#include "server.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <picohttpparser.h>

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

    char buffer[8192];
    ssize_t length = read(client, buffer, sizeof(buffer) - 1);
    if (length <= 0)
    {
        close(client);
        return NULL;
    }

    buffer[length] = '\0';

    const char *method;
    size_t method_length;

    const char *path;
    size_t path_length;

    int minor_version;

    struct phr_header headers[32];
    size_t num_headers = 32;

    int result = phr_parse_request(buffer, length, &method, &method_length, &path, &path_length, &minor_version, headers, &num_headers, 0);
    if (result < 0)
    {
        fprintf(stderr, "Invalid HTTP request!\n");
        close(client);
        return NULL;
    }

    printf("%.*s %.*s HTTP/1.%d\n", (int)method_length, method, (int)path_length, path, minor_version);
    close(client);
    return NULL;
}
