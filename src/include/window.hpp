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
        void setTop(const char *TopMessage);

    private:
        WINDOW *top;
        WINDOW *body;
        WINDOW *bottom;
};
