#ifndef TIMER_THREAD_HPP
#define TIMER_THREAD_HPP

#include <atomic>
#include <string>

struct TimerThreadData {
    std::atomic<bool> running;
    std::atomic<bool> counting;
    std::atomic<int> totalSeconds;
};

void* timerThreadFunction(void* arg);
std::string formatTime(int totalSeconds);

#endif