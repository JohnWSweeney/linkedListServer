#pragma once
#include <iostream>
#include <string>
#include <vector>

struct cmd
{
	int serverPort;
	std::string function;
	int input1;
};

int populateCmd(std::vector<std::string> tokens, cmd &cmd);