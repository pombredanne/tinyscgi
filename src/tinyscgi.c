#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include "request.h"

#define MAX_REQUEST_SIZE (4096)

void error(char *msg)
{
    perror(msg);
    abort();
}

void memzero(void *mem, size_t len)
{
    memset(mem, 0, len);
}

int xsocket(int domain, int type, int protocol)
{
     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
         error("failed to open socket");
     return sockfd;
}

int xaccept(int socket, const struct sockaddr *address, socklen_t *address_len)
{
    int retval = accept(socket, (struct sockaddr *) address, address_len);
    if (retval < 0)
        error("failed to accept socket");
    return retval;
}

int xbind(int socket, const struct sockaddr *address, socklen_t address_len)
{
    int retval = bind(socket, address, address_len);
    if (retval < 0)
        error("failed to bind address");
    return retval;
}

int write_str(int fd, const char *str)
{
    return write(fd, str, strlen(str));
}

int main(int argc, char **argv)
{
     int sockfd;
     struct sockaddr_in server_address, client_address;
     int n;

     sockfd = xsocket(AF_INET, SOCK_STREAM, 0);
     memzero(&server_address, sizeof(server_address));

     server_address.sin_family = AF_INET;
     server_address.sin_addr.s_addr = INADDR_ANY;
     server_address.sin_port = htons(10086);

     xbind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address));
     listen(sockfd, 50);

     while (1)
     {
         socklen_t client_address_len;
         pid_t worker_pid;
         int sockfd2, wait_st;
         FILE *socket_stream;
         struct request request;
         struct header_list *h;

         sockfd2 = xaccept(sockfd, (struct sockaddr *) &client_address,
                           &client_address_len);
         printf("* creating worker process...\n");
         worker_pid = fork();

         if (worker_pid == 0)
         {
             socket_stream = fdopen(sockfd2, "r+");
             if (!socket_stream)
                 error("failed to open socket fd");
             setlinebuf(socket_stream);

             /* parse scgi request */
             printf("* prepared to parse request...\n");
             parse_request(socket_stream, &request, MAX_REQUEST_SIZE);

             /* send response header */
             printf("* prepared to send response...\n");
             write_str(sockfd2, "Status: 200 OK\r\n"
                 "Content-Type: text/plain\r\n" "\r\n");

             /* send response body */
             write_str(sockfd2, "== SCGI REQUEST HEADERS ==\n");
             for (h=request.headers; h != NULL; h=h->next)
             {
                 write_str(sockfd2, "\t");
                 write_str(sockfd2, h->item.name);
                 write_str(sockfd2, ": ");
                 write_str(sockfd2, h->item.value);
                 write_str(sockfd2, "\n");
             }

             write_str(sockfd2, "== SCGI REQUEST BODY ==\n");
             write_str(sockfd2, request.body);

             shutdown(sockfd2, SHUT_RDWR);

             close(sockfd2);
             printf("* closed socket [fd=%d]...\n", sockfd2);

             exit(0);
         }
         else if (worker_pid > 0)
         {
             printf("* created worker process [pid=%d]...\n", worker_pid);
         }
     }

     close(sockfd);

     return EXIT_SUCCESS;
}
