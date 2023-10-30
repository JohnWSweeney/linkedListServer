#pragma once
#pragma once
#include <iostream>
#include <thread>
#include <WinSock2.h>

void startServerThread(int serverPort);
void startSessionThread(SOCKET socket);