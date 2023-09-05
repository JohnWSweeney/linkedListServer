#pragma once
#include <iostream>

class Server
{
public:
	Server() {};
	~Server() {}
	void run(int portNum);
};

void startServer(int portNum);