#ifndef AUDIO_THREAD_HPP
#define AUDIO_THREAD_HPP

#include <string>
#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>

// Solo declaraciones forward o estructuras simples
struct AudioThreadData {
    std::atomic<bool>* running;
    std::queue<std::string>* soundQueue;
    std::mutex* queueMutex;
    std::condition_variable* queueCondition;
};

void* audioThreadFunction(void* arg);

#endif