#include <iostream>
#include <cstdlib>
#include <string>

#include "include/window.hpp"

Window::Window(int height, int width, int start_y, int start_x)
{

    top = newwin(1, width, start_y, start_x);
    body = newwin(height - 3, width, start_y + 1, start_x);
    bottom = newwin(2, width, start_y + height - 2, start_x);
    //box(window, 0, 0);
    //wrefresh(window);
}

Window::~Window()
{
    //wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    delwin(top);
    delwin(body);
    delwin(bottom);
}

void Window::write(const char *message)
{
    wclear(body);
    waddstr(body, message);
    wrefresh(body);
}
void Window::setTop(const char *TopMessage)
{
    // Clear the header section
    wclear(top);

    // Write content in the header
    mvwprintw(top, 0, 0, TopMessage);

    // Refresh the header section
    wrefresh(top);
}

void Window::read(char *buffer)
{
    wclear(bottom);

    getstr(buffer);
}
