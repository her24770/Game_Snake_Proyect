#ifndef COLLISION_THREAD_HPP
#define COLLISION_THREAD_HPP

#include "../core/Snake.hpp"
#include "../core/ThreadSharedData.hpp"

struct CollisionThreadData {
    Snake* snake1;
    Snake* snake2 = nullptr;
    SharedGameData* sharedData;
    bool* running;
    bool* gameOver;
};

void* collisionThreadFunction(void* arg);

#endif