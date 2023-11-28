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

    // Initialize NCurses
    initscr();  // initialize ncurses screen
    raw();      // disable line buffering
    noecho();   // disable character echoing
    
    // Create windows
    update_dimensions();

    int height = 5;
    int width = 20;
    messages = Window(height, width, (rows - height)/2, (columns - width)/2);
    messages.write("foobar!!");

    #ifdef DEBUG
    std::cout << "[DEBUG] Exited " << __FUNCTION__ << '\n';
    #endif
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
    std::cout << "Set window dimensions to " << rows << 'x' << columns << '\n';
    #endif
}
