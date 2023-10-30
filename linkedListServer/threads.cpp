#include "threads.h"
#include "server.h"
#include "session.h"
#include "atomicBool.h"

void startServerThread(int serverPort)
{
	try {
		serverStatus = true;
		//int portNum = 123;
		std::thread serverThread(startServer, serverPort);
		serverThread.detach();
	}
	catch (...)
	{
		std::cout << "Server start failed.\n";
	}
}

void startSessionThread(SOCKET socket)
{
	try {
		sessionStatus = true;
		std::thread sessionThread(startSession, socket);
		sessionThread.detach();
	}
	catch (...)
	{
		std::cout << "Session start failed.\n";
	}
}