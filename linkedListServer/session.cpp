#include "session.h"
#include "tcp.h"
#include "atomicBool.h"
#include <nlohmann/json.hpp>

void convertBufferToCmd(char *buffer, cmd &cmd)
{
	// convert buffer to JSON, then JSON to cmd struct.
	std::string tempStr(buffer);
	nlohmann::json tempJSON = nlohmann::json::parse(tempStr);
	cmd.demoType = tempJSON["demoType"].template get<std::string>();
	cmd.demoStatus = tempJSON["demoStatus"].template get<std::string>();
	cmd.function = tempJSON["function"].template get<std::string>();
	cmd.input1 = tempJSON["input1"].template get<int>();
}

void Session::run(SOCKET socket, cmd &cmd)
{
	std::cout << "Session started.\n";
	tcp listen;
	int result = 0;

	do {
		msg newMsg;
		result = listen.rx(socket, newMsg.buffer, newMsg.bufferLen);
		if (result > 0) // message received.
		{
			std::cout << "Server received: " << newMsg.buffer << '\n';
			convertBufferToCmd(newMsg.buffer, cmd);
			std::cout << cmd.demoType << '\n';
			std::cout << cmd.demoStatus << '\n';
			std::cout << cmd.function << '\n';
			std::cout << cmd.input1 << "\n\n";

			if (cmd.demoStatus == "stop")
			{
				sessionStatus = false;
			}
		}
		else if (result == -1) // peer closed connection gracefully.
		{
			std::cout << "Client gracefully closed connection.\n";
			sessionStatus = false;
		}
		else if (result < -1) // error.
		{
			std::cout << "Session rx failed.\n";
			sessionStatus = false;
		}
	} while (result > -1 and sessionStatus == true);
	
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