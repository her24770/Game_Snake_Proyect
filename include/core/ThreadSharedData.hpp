#ifndef THREAD_SHARED_DATA_HPP
#define THREAD_SHARED_DATA_HPP

#include <mutex>

struct SharedGameData {
    int lastKey;
    bool running;
    std::mutex mtx;
    
    SharedGameData() : lastKey(0), running(true) {}
    
    void setKey(int key);
    int getKey();
    void stop();
};

#endif