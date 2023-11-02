#pragma once
#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "commands.h"

void startServerThread(cmd &cmd);
void startSessionThread(SOCKET socket, cmd &cmd);
void startDemoThread(std::mutex &m, std::condition_variable &cv, cmd &cmd);