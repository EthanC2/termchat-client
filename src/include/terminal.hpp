#pragma once

#include <string>

class Terminal
{
    public:
        Terminal(const std::string &channel_);
        ~Terminal();

    private:
        std::string channel;
};
