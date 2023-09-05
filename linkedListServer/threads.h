#pragma once
#pragma once
#include <iostream>
#include <thread>
#include <WinSock2.h>

void startServerThread();
void startSessionThread(SOCKET socket);