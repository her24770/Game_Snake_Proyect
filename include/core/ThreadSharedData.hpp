#ifndef THREAD_SHARED_DATA_HPP
#define THREAD_SHARED_DATA_HPP

#include <mutex>
#include "../../include/utils/InputHandler.hpp"

struct SharedGameData {
    int keyPlayer1 = InputHandler::KEY_NONE;
    int keyPlayer2 = InputHandler::KEY_NONE;
    bool running;
    std::mutex mtx;
    
    SharedGameData() : keyPlayer1(0), keyPlayer2(0),  running(true) {}
    
    void setKey(int key);
    int getKey();
    void setKey2(int key);
    int getKey2();
    void stop();
};

#endif