#include "commands.h"
#include "atomicBool.h"

int getInteger(std::string token, int &integer)
{
	if (token.empty())
	{
		std::cout << "No integer entered.\n";
		return 1;
	}

	try {
		integer = std::stoi(token);
		return 0;
	}
	catch (std::invalid_argument)
	{
		std::cout << "Invalid integer.\n";
		return 1;
	}
	catch (std::out_of_range)
	{
		std::cout << "Integer out of range.\n";
		return 1;
	}
}

int populateCmd(std::vector<std::string> tokens, cmd &cmd)
{
	int result;
	// check if user is starting a new server or ...
	if (tokens[0] == "start")
	{
		// check if a demo is currently running.
		if (serverStatus == false)
		{
			// get server port number.
			result = getInteger(tokens[1], cmd.serverPort);
			if (result == 1)
			{
				std::cout << "Invalid server port number.\n";
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			std::cout << "Only one server can run at a time.\n";
			return 1;
		}
		
	}
}