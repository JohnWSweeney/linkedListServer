#pragma once
#include <iostream>
#include <WinSock2.h>
#include "commands.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(SOCKET socket, cmd &cmd) {}
	~Session() {}
	void run(SOCKET socket, cmd &cmd);
};

void startSession(SOCKET socket, cmd &cmd);