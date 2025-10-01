#include "../../include/threads/RenderThread.hpp"
#include "../../include/rendering/Game.hpp"
#include <unistd.h>
#include <iostream>

void* renderThreadFunction(void* arg) {
    RenderThreadData* data = (RenderThreadData*)arg;
    //Mientras se esté ejecutando el escenario principal estará recargando la matriz donde se encuentran todos los objetos
    while (*(data->runningRender)) {
        GAME::renderGameScreen(*data->snake1, *data->food, data->snake2);
        usleep(16000); //Timeout entre refrescos
    }

    return nullptr;
}
