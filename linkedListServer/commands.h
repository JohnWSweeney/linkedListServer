#pragma once
#include <iostream>
#include <string>
#include <vector>

struct cmd
{
	int serverPort;
	std::string demoType;
	std::string demoStatus;
	std::string function;
	int input1;
	int input2;
	int input3;
	bool isAscending;
	int output;
};

int populateCmd(std::vector<std::string> tokens, cmd &cmd);