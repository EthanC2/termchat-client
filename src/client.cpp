#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "core/include/constants.h"

#define BUFLEN 1000
#define REPLY_BUFLEN 2000
#define LOCALHOST "127.0.0.1"

#define errchk(expr, msg)       \
    do                          \
    {                           \
        if ((expr) == -1)       \
        {                       \
            perror(msg);        \
            exit(errno);        \
        }                       \
    } while (0)                 \

int main()
{
	int sock;
	struct sockaddr_in server;
	char message[BUFLEN], reply[REPLY_BUFLEN];

	// 1. Create a socket
	errchk(sock = socket(AF_INET /* IPV4 */, SOCK_STREAM /* TCP */, 0), "socket");
	if (sock == -1)
	{
		printf("Could not create socket");
	}

	// 2. Connect to remote server
	server.sin_addr.s_addr = inet_addr(LOCALHOST);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

    errchk(connect(sock , (struct sockaddr *)&server , sizeof(server)), "connect");

	// 3. Send messages to the server
	for(;;)
	{
		printf("Enter message: ");
		scanf("%s", message);

        // 3A. Send data to the server
		errchk( send(sock, message, strlen(message), 0), "send");

		// 3B. Receive a reply from the server
		errchk( recv(sock , reply , REPLY_BUFLEN , 0), "recv");

        // 3C. Print reply from the server
		fprintf(stdout, "Server reply: ");
        puts(reply);
	}

	close(sock);
	return 0;
}
