#include <iostream>
#include <cstdlib>
#include <string>

#include "include/window.hpp"

Window::Window(int height, int width, int start_y, int start_x)
{
    window = newwin(height, width, start_y, start_x);
    //box(window, 0, 0);
    //wrefresh(window);
}

Window::~Window()
{
    //wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    delwin(window);
}

void Window::write(const char *message)
{
    wclear(window);
    waddstr(window, message);
    wrefresh(window);
}

void Window::read(char *buffer)
{
    wclear(window);
    getstr(buffer);
}
