#include "session.h"
#include "tcp.h"
#include "atomicBool.h"

void Session::run(SOCKET socket)
{
	this->list(socket);
}

void Session::list(SOCKET socket)
{
	tcp listen;
	int result;
	do {
		msg newMsg;
		result = listen.rx(socket, newMsg.buffer, newMsg.bufferLen);
		if (result > 0) // message received.
		{
			std::cout << "Server received: " << newMsg.buffer << '\n';
		}
		else if (result == -1) // peer closed connection gracefully.
		{
			std::cout << "Server: listen peer gracefully closed connection.\n";
		}
		else if (result < -1) // error.
		{
			std::cout << "Server: listen.rx failed.\n";
		}
	} while (result > -1);

	// gracefully close connection.
	result = listen.closeConnection(socket, false);
	if (result != 0)
	{
		std::cout << "Server: listen.closeConnection failed.\n";
		return;
	}
	std::cout << "Server: listen session ended.\n";
}

void startSession(SOCKET socket)
{
	Session newSession(socket);
	newSession.run(socket);
}