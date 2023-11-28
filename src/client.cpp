#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <ncurses.h>

#include "include/constants.hpp"
#include "include/window.hpp"
#include "include/error.hpp"

#define LOCALHOST "127.0.0.1"
#define BUFLEN 512

void read_server(int rows, int columns, int sockfd)
{
    Window messages(rows/2, columns, 0, 0);
    char buffer[BUFLEN];
    ssize_t nread;

    for (;;)
    {
        // 1. Read message from server
        errchk( nread = read(sockfd, buffer, MSG_MAX_LEN), "read");
        buffer[nread] = '\0';
    
        // 2. Write the message to the messages window
        messages.write(buffer);
    }
}

void write_server(int rows, int columns, int sockfd)
{
    Window input(rows/2, columns, rows/2, 0);
    char buffer[BUFLEN];

    for (;;)
    {
        // 1. Read string from input window
        input.read(buffer);

        #ifdef DEBUG
        std::cout << "[DEBUG]: read \"" << buffer << "\"\n";
        #endif
        
        // 2. Write message to server
       errchk( write(sockfd, buffer, strlen(buffer)), "write");
    }
}

int main()
{
    std::vector<std::thread> threads;
    sockaddr_in servaddr;
    int sockfd = 0;
    struct winsize dimensions;

    // 1. Configure NCurses
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &dimensions);
    initscr();
    //cbreak();

    // 2. Socket
    errchk( sockfd = socket(AF_INET, SOCK_STREAM, 0), "socket");

    // 3. Connect
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    errchk( inet_pton(AF_INET, LOCALHOST, &servaddr.sin_addr), "inet_pton");

    errchk( connect(sockfd, (sockaddr*) &servaddr, sizeof(servaddr)), "connect");

    // 4. Spawn threads to read and write from the server
    threads.push_back( std::thread(read_server,  dimensions.ws_row, dimensions.ws_col, sockfd) );
    threads.push_back( std::thread(write_server, dimensions.ws_row, dimensions.ws_col, sockfd) );

    // 5. Wait for threads to finish
    for (auto& t : threads)
    {
        t.join();
    }

    // 6. End NCurses and close socket
    endwin();
    close(sockfd);

    return 0;
}
