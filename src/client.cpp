#include <iostream>
#include <string>
#include <thread>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <ncurses.h>

#include "include/constants.hpp"
#include "include/terminal.hpp"
#include "include/error.hpp"

void read_server(int sockfd)
{
    char buffer[MSG_MAX_LEN];
    ssize_t nread;

    for (;;)
    {
        // 1. Read message from server
        errchk( nread = read(sockfd, buffer, MSG_MAX_LEN), "read");
        buffer[nread] = '\0';

        std::cout << "[READ] \'" << buffer << "\'\n";
    }
}

void write_server(int sockfd)
{
    std::string buffer;

    for (;;)
    {
        // 1. Read from STDIN
        std::cout << "Client: ";
        std::getline(std::cin, buffer);
        std::cout << "[WRITE] \'" << buffer.data() << "\'\n";
        
        // 2. Write message to server
        errchk( write(sockfd, buffer.data(), buffer.length()), "write");
    }
}

int main()
{
    Terminal terminal;
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

    // 3. Spawn threads to read and write from the server
    //std::thread(write_server, sockfd).join();
    //std::thread(read_server, sockfd).join();

    // N. Close
    close(sockfd);

    return 0;
}
