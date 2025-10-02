#ifndef TIMER_THREAD_HPP
#define TIMER_THREAD_HPP

#include <pthread.h>
#include <chrono>
#include <mutex>
#include <atomic>
#include <string>
#include "../core/ThreadSharedData.hpp"

struct TimerThreadData {
    std::atomic<bool> running;
    std::atomic<int> elapsedMilliseconds;
    SharedGameData* sharedData;
    
    TimerThreadData() : running(false), elapsedMilliseconds(0), sharedData(nullptr) {}
    
    // Función para obtener el tiempo formateado mm:ss.SSS
    std::string getFormattedTime() const;
    
    // Función para reiniciar el timer
    void reset();
};

// Función del hilo de timer
void* timerThreadFunction(void* arg);

#endif