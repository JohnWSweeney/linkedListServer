#include "session.h"
#include "tcp.h"
#include "atomicBool.h"
#include <nlohmann/json.hpp>

struct cmd
{
	std::string function;
	int integer;
};

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

			std::string s(newMsg.buffer);
			std::cout << s << '\n';
			nlohmann::json j = nlohmann::json::parse(s);

			cmd fdsa{
				j["function"].template get<std::string>(),
				j["integer"].template get<int>()
			};

			std::cout << "fdsa.function: " << fdsa.function << '\n';
			std::cout << "fdsa.integer: " << fdsa.integer << '\n';
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