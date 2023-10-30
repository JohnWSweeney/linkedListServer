#pragma once
#include <iostream>
#include <string>
#include <vector>

struct cmd
{
	int serverPort;
};

int populateCmd(std::vector<std::string> tokens, cmd &cmd);