#ifndef FOOD_THREAD_HPP
#define FOOD_THREAD_HPP

#include "../core/Food.hpp"
#include "../core/Snake.hpp"
#include "../core/ThreadSharedData.hpp"

struct FoodThreadData {
    Food* food;
    Snake* snake1;
    Snake* snake2 = nullptr;
    SharedGameData* sharedData;
    bool* running;
};

void* foodThreadFunction(void* arg);

#endif