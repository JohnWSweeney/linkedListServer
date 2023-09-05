#include "server.h"
#include "tcp.h"
#include "threads.h"
#include "atomicBool.h"

void Server::run(int portNum)
{
	tcp server;
	SOCKET listenSocket = INVALID_SOCKET;
	SOCKET acceptSocket = INVALID_SOCKET;
	int result = server.openServerSocket(portNum, listenSocket);
	if (result != 0)
	{
		closesocket(listenSocket);
		WSACleanup();
		return;
	}
	else
	{
		std::cout << "Server started on port " << portNum << ".\n";
	}

	// listen for client connections, start new session thread on connection acceptance.
	do {
		result = server.socketReadStatus(listenSocket);
		if (result > 0)
		{
			int acceptResult = server.acceptConnection(listenSocket, acceptSocket);
			if (acceptResult != 0)
			{
				closesocket(listenSocket);
				closesocket(acceptSocket);
				WSACleanup();
				return;
			}
			else
			{
				startSessionThread(std::move(acceptSocket));
			}
		}
	} while (serverStatus);
	closesocket(listenSocket);
	closesocket(acceptSocket);
	WSACleanup();
	std::cout << "Server terminated on port " << portNum << ".\n";
}
void startServer(int portNum)
{
	Server newServer;
	newServer.run(portNum);
}