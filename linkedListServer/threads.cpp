#include "threads.h"
#include "server.h"
#include "session.h"
#include "atomicBool.h"
#include "demos.h"

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

// define function pointer.
void (*ptr)(std::mutex &m, std::condition_variable &cv, cmd &cmd);

void startDemoThread(std::mutex &m, std::condition_variable &cv, cmd &cmd)
{
	// assign function pointer to chosen list type function.
	if (cmd.demoType == "sList")
	{
		ptr = sDemo;
	}

	try {
		status = true;
		std::thread newThread(ptr, std::ref(m), std::ref(cv), std::ref(cmd));
		newThread.detach();
	}
	catch (...)
	{
		sessionStatus = false;
		std::cout << "Session failed to start " << cmd.demoType << " demo.\n";
	}
}