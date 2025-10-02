#include "../../include/threads/FoodThread.hpp"
#include <unistd.h>
#include <mutex>

void* foodThreadFunction(void* arg) {
    FoodThreadData* data = (FoodThreadData*)arg;
    
    // Generar primera fruta
    {
        std::lock_guard<std::mutex> lock(data->sharedData->mtx);
        if (data->snake2) {
            data->food->generate(data->snake1->getCuerpo(), data->snake2->getCuerpo());
        } else {
            data->food->generate(data->snake1->getCuerpo(), {}); // solo con snake1
        }
    }
    
    while (*(data->running)) {
        bool needsRegenerate = false;
        {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            if (data->food->isActive()) {
                auto foodPos = data->food->getPosition();
                auto head1 = data->snake1->getCabeza();

                if (head1 == foodPos) {
                    data->snake1->crecer();
                    data->snake1->sumarPuntos(10);
                    data->food->consume();
                    needsRegenerate = true;
                }

                if (data->snake2) {
                    auto head2 = data->snake2->getCabeza();
                    if (head2 == foodPos) {
                        data->snake2->crecer();
                        data->snake2->sumarPuntos(10);
                        data->food->consume();
                        needsRegenerate = true;
                    }
                }
            } else {
                needsRegenerate = true;
            }
        }

        if (needsRegenerate) {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            if (data->snake2) {
                data->food->generate(data->snake1->getCuerpo(), data->snake2->getCuerpo());
            } else {
                data->food->generate(data->snake1->getCuerpo(), {});
            }
        }

        usleep(50000);
    }
    return nullptr;
}