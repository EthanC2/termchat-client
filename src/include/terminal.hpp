#pragma once

#include <string>

#include <sys/ioctl.h>

#include "window.hpp"

class Terminal
{
    public:
        Terminal(const std::string &channel_);
        ~Terminal();
        void update_dimensions();

    private:
        std::string channel;
        unsigned short rows;
        unsigned short columns;
        Window messages;
};
