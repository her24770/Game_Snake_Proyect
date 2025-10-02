#ifndef RENDER_THREAD_HPP
#define RENDER_THREAD_HPP

#include <pthread.h>
#include <mutex>
#include "../core/Snake.hpp"
#include "../core/ThreadSharedData.hpp"
#include "../core/Food.hpp"

struct RenderThreadData {
    Snake* snake1;
    Snake* snake2 = nullptr;
    Food* food;
    SharedGameData* sharedData;
    bool* runningRender;
};

// Función del hilo de renderizado
void* renderThreadFunction(void* arg);

#endif
