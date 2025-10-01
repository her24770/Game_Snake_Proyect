#include "../../include/core/ThreadSharedData.hpp"

void SharedGameData::setKey(int key) {
    std::lock_guard<std::mutex> lock(mtx);
    keyPlayer1 = key;
}

int SharedGameData::getKey() {
    std::lock_guard<std::mutex> lock(mtx);
    int key = keyPlayer1;
    keyPlayer1 = 0;
    return key;
}

void SharedGameData::setKey2(int key) {
    std::lock_guard<std::mutex> lock(mtx);
    keyPlayer2 = key;
}

int SharedGameData::getKey2() {
    std::lock_guard<std::mutex> lock(mtx);
    int key = keyPlayer2;
    keyPlayer2 = 0;
    return key;
}

void SharedGameData::stop() {
    std::lock_guard<std::mutex> lock(mtx);
    running = false;
}