#pragma once
//#ifndef TERMCHAT_TERMINAL_USER_INTERFACE_H
//#define TERMCHAT_TERMINAL_USER_INTERFACE_H

#include <string>
#include <vector>
#include <ncurses.h>

class TerminalUserInterface
{
    public:
	TerminalUserInterface();
	~TerminalUserInterface();

    private:
	std::string channel;
	std::vector<std::string> messages;
	std::vector<std::string> commands;
};

//#endif
