#include "../../include/threads/CollisionThread.hpp"
#include "../../include/rendering/Game.hpp"
#include <unistd.h>
#include <mutex>

void* collisionThreadFunction(void* arg) {
    CollisionThreadData* data = (CollisionThreadData*)arg;
    
    while (*(data->running)) {
        bool collision = false;
        std::pair<int,int> head1;
        std::pair<int,int> head2;
        std::vector<std::pair<int,int>> body1;
        std::vector<std::pair<int,int>> body2;

        {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            head1 = data->snake1->getCabeza();
            body1 = data->snake1->getCuerpo();
            if (data->snake2) {
                head2 = data->snake2->getCabeza();
                body2 = data->snake2->getCuerpo();
            }
        }

        // Colisión snake1 con borde
        if (head1.first <= 0 || head1.first >= GAME::CONSOLE_WIDTH-1 ||
            head1.second <= 0 || head1.second >= GAME::CONSOLE_HEIGHT-1) {
            collision = true;
        }

        // Colisión snake1 consigo misma
        for (size_t i = 1; i < body1.size(); ++i) {
            if (head1 == body1[i]) { collision = true; break; }
        }

        if (data->snake2) {
            // Colisión snake2 con bordes
            if (head2.first <= 0 || head2.first >= GAME::CONSOLE_WIDTH-1 ||
                head2.second <= 0 || head2.second >= GAME::CONSOLE_HEIGHT-1) {
                collision = true;
            }

            // Colisión snake2 consigo misma
            for (size_t i = 1; i < body2.size(); ++i) {
                if (head2 == body2[i]) { collision = true; break; }
            }

            // Colisiones cruzadas
            for (auto& seg : body2) if (head1 == seg) collision = true;
            for (auto& seg : body1) if (head2 == seg) collision = true;

            if (head1 == head2) collision = true;
        }

        if (collision) {
            std::lock_guard<std::mutex> lock(data->sharedData->mtx);
            *(data->gameOver) = true;
            *(data->running) = false;
        }

        usleep(50000);
    }
    
    return nullptr;
}