#include <iostream>
#include <string>

#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <ncurses.h>

#include "include/terminal.hpp"

Terminal::Terminal(const std::string &channel_)
{
    channel = channel_;
    update_dimensions();

    // Initialize NCurses
    initscr();  // initialize ncurses screen
    raw();      // disable line buffering
    noecho();   // disable character echoing
}

Terminal::~Terminal()
{
    // Deinitialize NCurses
    endwin();
}

void Terminal::update_dimensions()
{
    struct winsize dimensions;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &dimensions);

    rows = dimensions.ws_row;
    columns = dimensions.ws_col;

    #ifdef DEBUG
    std::cout << "Updated window dimensions to " << rows << 'x' << columns << '\n';
    #endif
}
