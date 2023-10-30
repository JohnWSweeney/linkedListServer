#pragma once
#include <iostream>
#include "commands.h"

class Server
{
public:
	Server() {};
	~Server() {}
	void run(cmd &cmd);
};

void startServer(cmd &cmd);