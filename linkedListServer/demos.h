#pragma once
#include <mutex>
#include <condition_variable>
#include "commands.h"

void sDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void dDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void csDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void cdDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void stackDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void queueDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);
void dequeDemo(std::mutex &m, std::condition_variable &cv, cmd &cmd);