#include "../../include/threads/RenderThread.hpp"
#include "../../include/rendering/Game.hpp"
#include <unistd.h>
#include <iostream>

void* renderThreadFunction(void* arg) {
    RenderThreadData* data = (RenderThreadData*)arg;

    while (*(data->runningRender)) {
        GAME::renderGameScreen(*data->snake1, 30, 23, data->snake2);
        usleep(16000);
    }

    return nullptr;
}
