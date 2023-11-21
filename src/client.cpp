#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#include <string>
#include <array>

#include "include/constants.hpp"
#include "include/error.hpp"

int main()
{
    std::string buffer;
    sockaddr_in servaddr;
    int sockfd;

    // 1. Socket
    errchk( sockfd = socket(AF_INET, SOCK_STREAM, 0), "socket");

    // 2. Connect
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    errchk( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr), "inet_pton");

    errchk( connect(sockfd, (sockaddr*) &servaddr, sizeof(servaddr)), "connect");
    printf("Connected on on port %d: FD: %d\n", PORT, sockfd);

    for (;;)
    {
        // 3A. Read input
        std::cout << "Client: ";
        std::getline(std::cin, buffer);
        std::cout << "[DEBUG CLIENT] \'" << buffer.data() << "\'\n";
        
        // 3B. Write to server
        errchk( write(sockfd, buffer.data(), buffer.length()), "write");

        // 3C. Read from server
        errchk( read(sockfd, buffer.data(), buffer.length()), "read");

        std::cout << "[DEBUG SERVER] \'" << buffer.data() << "\'\n";
    }

    // N. Close
    close(sockfd);

    return 0;
}
