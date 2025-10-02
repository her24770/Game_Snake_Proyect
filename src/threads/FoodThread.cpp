#include "../../include/threads/FoodThread.hpp"
#include "../../include/threads/SFXThread.hpp"
#include <unistd.h>
#include <mutex>

void* foodThreadFunction(void* arg) {
    FoodThreadData* data = (FoodThreadData*)arg;
    
    // Generar primera fruta
    {
        std::lock_guard<std::mutex> lock(data->sharedData->mtx);
        data->food->generate(data->snake1->getCuerpo(), 
                            data->snake2->getCuerpo());
    }
    
    while(*(data->running)) {
        bool needsRegenerate = false;
        
        // Bloque 1: Verificar colisiones (lock corto)
        {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            
            if(data->food->isActive()) {
                auto foodPos = data->food->getPosition();
                auto head1 = data->snake1->getCabeza();
                auto head2 = data->snake2->getCabeza();
                
                if(head1.first == foodPos.first && head1.second == foodPos.second) {
                    data->snake1->crecer();
                    data->snake1->sumarPuntos(10);
                    data->food->consume();
                    needsRegenerate = true;
                    
                    if(data->sfxData) {
                        playSoundEffect(data->sfxData, SFX_EAT_FOOD);
                    }
                }
                
                if(head2.first == foodPos.first && head2.second == foodPos.second) {
                    data->snake2->crecer();
                    data->snake2->sumarPuntos(10);
                    data->food->consume();
                    needsRegenerate = true;
                    if(data->sfxData) {
                        playSoundEffect(data->sfxData, SFX_EAT_FOOD);
                    }
                }
            } else {
                needsRegenerate = true;
            }
        } // Aquí se libera el mutex
        
        // Bloque 2: Regenerar si es necesario (lock corto)
        if(needsRegenerate) {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            data->food->generate(data->snake1->getCuerpo(),
                                data->snake2->getCuerpo());
        }
        
        usleep(25000);
    }
    
    return nullptr;
}