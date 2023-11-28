#pragma once

#include <string>
#include <ncurses.h>

class Window
{
    public:
        Window(int height, int width, int start_y, int start_x);
        ~Window();
        void write(const char *message);
        void read(char *buffer);

    private:
        WINDOW *window;
};
