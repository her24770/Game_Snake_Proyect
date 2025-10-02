#include "../../include/threads/TimerThread.hpp"
#include <unistd.h>
#include <sstream>
#include <iomanip>

std::string formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes 
        << ":" << std::setw(2) << seconds;
    return oss.str();
}

void* timerThreadFunction(void* arg) {
    TimerThreadData* data = (TimerThreadData*)arg;
    
    while(data->running.load()) {
        if(data->counting.load()) {
            data->totalSeconds.fetch_add(1);
            sleep(1); // 1 segundo
        } else {
            usleep(100000); // 100ms cuando no cuenta
        }
    }
    
    return nullptr;
}