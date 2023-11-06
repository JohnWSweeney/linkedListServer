#include "session.h"
#include "threads.h"
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
	cmd.input2 = tempJSON["input2"].template get<int>();
	cmd.input3 = tempJSON["input3"].template get<int>();
	cmd.isAscending = tempJSON["isAscending"].template get<bool>();
}

void Session::run(SOCKET socket, cmd &cmd)
{
	std::cout << "Session started.\n";
	std::mutex m;
	std::condition_variable cv;
	tcp listen;
	int result;

	std::unique_lock<std::mutex> lk(m);
	do {
		msg newMsg;
		result = listen.rx(socket, newMsg.buffer, newMsg.bufferLen);
		if (result > 0) // new commands received.
		{
			convertBufferToCmd(newMsg.buffer, cmd);

			if (cmd.demoStatus == "start") // start demo.
			{
				if (demoStatus == false)
				{
					startDemoThread(std::ref(m), std::ref(cv), std::ref(cmd));
					cv.wait(lk);
				}
				else
				{
					std::cout << "Only one demo can run at a time.\n";
				}
			}
			else if (cmd.demoStatus == "stop") // stop demo.
			{
				cmd.function = {};
				demoStatus = false;
				cv.notify_one();
				cv.wait(lk);
			}
			else // demo running, update commands.
			{
				cv.notify_one();
				cv.wait(lk);
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