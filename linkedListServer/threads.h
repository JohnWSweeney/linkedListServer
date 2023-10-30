#pragma once
#pragma once
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include "commands.h"

void startServerThread(cmd &cmd);
void startSessionThread(SOCKET socket, cmd &cmd);