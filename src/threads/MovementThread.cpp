#include <pthread.h>
#include <unistd.h>
#include <mutex>
#include "../../include/core/Snake.hpp"
#include "../../include/core/ThreadSharedData.hpp"
#include "../../include/utils/InputHandler.hpp"

void* snakeMovementThread(void* arg) {
    struct ThreadData {
        Snake* snake;
        SharedGameData* sharedData;
        int playerId; 
        bool* runningMovement;
    };

    ThreadData* data = (ThreadData*)arg;

    while (*(data->runningMovement)) {
        int key = (data->playerId == 1) ? data->sharedData->getKey() 
                                        : data->sharedData->getKey2();

        if(key != InputHandler::KEY_NONE) {
            data->snake->updateDirectionFromKey(key, data->playerId);
        }

        {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            data->snake->mover();
        }

        usleep(150000); // velocidad del juego
    }

    return nullptr;
}
