#ifndef FOOD_THREAD_HPP
#define FOOD_THREAD_HPP

#include "../core/Food.hpp"
#include "../core/Snake.hpp"
#include "../core/ThreadSharedData.hpp"
#include "SFXThread.hpp"

struct FoodThreadData {
    Food* food;
    Snake* snake1;
    Snake* snake2;
    SharedGameData* sharedData;
    bool* running;
    SFXData* sfxData;
};

void* foodThreadFunction(void* arg);

#endif