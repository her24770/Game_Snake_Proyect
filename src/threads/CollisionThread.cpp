#include "../../include/threads/CollisionThread.hpp"
#include "../../include/rendering/Game.hpp"
#include "../../include/threads/SFXThread.hpp"
#include <unistd.h>
#include <mutex>

void* collisionThreadFunction(void* arg) {
    CollisionThreadData* data = (CollisionThreadData*)arg;
    
    while(*(data->running)) {
        bool collision = false;
        SoundEffect collisionType = SFX_NONE;
        // Lock corto: solo capturar datos
        std::pair<int, int> head1, head2;
        std::vector<std::pair<int, int>> body1, body2;
        
        {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            head1 = data->snake1->getCabeza();
            head2 = data->snake2->getCabeza();
            body1 = data->snake1->getCuerpo();
            body2 = data->snake2->getCuerpo();
        } // Mutex liberado aquí
        
        // Verificaciones SIN lock (usa copias locales)
        
        //Colision con muro
        if(head1.first <= 0 || head1.first >= GAME::CONSOLE_WIDTH-1 ||
           head1.second <= 0 || head1.second >= GAME::CONSOLE_HEIGHT-1) {
            collision = true;
            collisionType = SFX_WALL_COLLISION;
        }
        
        if(head2.first <= 0 || head2.first >= GAME::CONSOLE_WIDTH-1 ||
           head2.second <= 0 || head2.second >= GAME::CONSOLE_HEIGHT-1) {
            collision = true;
            collisionType = SFX_WALL_COLLISION;
        }
        //Colision con ella misma
        for(size_t i = 1; i < body1.size(); ++i) {
            if(head1.first == body1[i].first && head1.second == body1[i].second) {
                collision = true;
                collisionType = SFX_SELF_COLLISION;
                break;
            }
        }

        for(size_t i = 1; i < body2.size(); ++i) {
            if(head2.first == body2[i].first && head2.second == body2[i].second) {
                collision = true;
                collisionType = SFX_SELF_COLLISION;
                break;
            }
        }
        
        //Colision con otra serpiente 
        for(const auto& segment : body2) {
            if(head1.first == segment.first && head1.second == segment.second) {
                collision = true;
                collisionType = SFX_SNAKE_COLLISION;
                break;
            }
        }
        
        for(const auto& segment : body1) {
            if(head2.first == segment.first && head2.second == segment.second) {
                collision = true;
                collisionType = SFX_SNAKE_COLLISION;
                break;
            }
        }
        
        if(head1.first == head2.first && head1.second == head2.second) {
            collision = true;
            collisionType = SFX_SNAKE_COLLISION;
        }
        
        // Lock corto: actualizar estado si hay colisión
        if(collision) {
            if (data->sfxData && collisionType != SFX_NONE){
                playSoundEffect(data->sfxData, collisionType);
            }
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            *(data->gameOver) = true;
            *(data->running) = false;
        
        }
        usleep(25000);
    }
    
    return nullptr;
}