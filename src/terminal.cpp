#include <iostream>

#include <ncurses.h>

#include "include/terminal.hpp"

Terminal::Terminal()
{
    initscr();  // initialize ncurses screen
    raw();      // disable line buffering
    noecho();   // disable character echoing
}

Terminal::~Terminal()
{
    endwin();
}
