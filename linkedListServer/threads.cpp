#include "threads.h"
#include "server.h"
#include "session.h"
#include "atomicBool.h"

void startServerThread(cmd &cmd)
{
	try {
		serverStatus = true;
		std::thread serverThread(startServer, std::ref(cmd));
		serverThread.detach();
	}
	catch (...)
	{
		serverStatus = false;
		std::cout << "Server start failed.\n";
	}
}

void startSessionThread(SOCKET socket, cmd &cmd)
{
	try {
		sessionStatus = true;
		std::thread sessionThread(startSession, socket, std::ref(cmd));
		sessionThread.detach();
	}
	catch (...)
	{
		sessionStatus = false;
		std::cout << "Session start failed.\n";
	}
}