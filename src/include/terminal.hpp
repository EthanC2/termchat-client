#pragma once

#include <string>

#include <sys/ioctl.h>

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
};
