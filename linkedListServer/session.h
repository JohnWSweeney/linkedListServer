#pragma once
#include <iostream>
#include <WinSock2.h>

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(SOCKET socket) {}
	~Session() {}
	void run(SOCKET socket);
};

void startSession(SOCKET socket);