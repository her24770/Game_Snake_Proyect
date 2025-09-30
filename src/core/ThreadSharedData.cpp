#include "../../include/core/ThreadSharedData.hpp"

void SharedGameData::setKey(int key) {
    std::lock_guard<std::mutex> lock(mtx);
    lastKey = key;
}

int SharedGameData::getKey() {
    std::lock_guard<std::mutex> lock(mtx);
    int key = lastKey;
    lastKey = 0;
    return key;
}

void SharedGameData::stop() {
    std::lock_guard<std::mutex> lock(mtx);
    running = false;
}