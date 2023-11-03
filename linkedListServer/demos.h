#pragma once
#include <mutex>
#include <condition_variable>
#include "commands.h"

void sDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void dDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);