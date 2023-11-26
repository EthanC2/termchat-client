#include <iostream>
#include <string>

#include <ncurses.h>

#include "include/terminal.hpp"

Terminal::Terminal(const std::string &channel_)
{
    channel = channel_;

    initscr();  // initialize ncurses screen
    raw();      // disable line buffering
    //noecho();   // disable character echoing
}

Terminal::~Terminal()
{
    endwin();
}
