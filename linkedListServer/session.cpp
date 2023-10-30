#include "session.h"
#include "tcp.h"
#include "atomicBool.h"
#include <nlohmann/json.hpp>

void Session::run(SOCKET socket, cmd &cmd)
{
	std::cout << "Session started.\n";
	tcp listen;
	int result;

	while (sessionStatus)
	{
		do {
			msg newMsg;
			result = listen.rx(socket, newMsg.buffer, newMsg.bufferLen);
			if (result > 0) // message received.
			{
				std::cout << "Server received: " << newMsg.buffer << '\n';

				std::string s(newMsg.buffer);
				std::cout << s << '\n';
				nlohmann::json j = nlohmann::json::parse(s);

				cmd.function = j["function"].template get<std::string>();
				cmd.input1 = j["integer"].template get<int>();

				std::cout << "cmd.function: " << cmd.function << '\n';
				std::cout << "cmd.input1: " << cmd.input1 << '\n';
			}
			else if (result == -1) // peer closed connection gracefully.
			{
				std::cout << "Server: listen peer gracefully closed connection.\n";
				sessionStatus = false;
			}
			else if (result < -1) // error.
			{
				std::cout << "Server: listen.rx failed.\n";
				sessionStatus = false;
			}
		} while (result > -1);
	}

	// gracefully close connection.
	result = listen.closeConnection(socket, false);
	if (result != 0)
	{
		std::cout << "Server: listen.closeConnection failed.\n";
		return;
	}
	std::cout << "Server: listen session ended.\n";
}

void startSession(SOCKET socket, cmd &cmd)
{
	Session newSession(socket, cmd);
	newSession.run(socket, cmd);
}