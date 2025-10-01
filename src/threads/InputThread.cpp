#include "../../include/threads/InputThread.hpp"
#include "../../include/utils/InputHandler.hpp"
#include <unistd.h>
#include <string.h>

void* inputThreadFunction(void* arg) {
        SharedGameData* data = (SharedGameData*)arg;

    while(true) {
        bool shouldRun;
        {
            std::lock_guard<std::mutex> lock(data->mtx);
            shouldRun = data->running;
        }
        
        if(!shouldRun) break;

        int key = InputHandler::getUserInputNonBlocking
        ();
        if(key != InputHandler::KEY_NONE) {
            // Debug
            char buffer[100];
            sprintf(buffer, "[HILO] Tecla capturada: %d\n", key);
            write(STDOUT_FILENO, buffer, strlen(buffer));

            // Asignar a jugador correspondiente
            if(key == InputHandler::KEY_W || key == InputHandler::KEY_A ||
               key == InputHandler::KEY_S || key == InputHandler::KEY_D) {
                data->setKey(key); // jugador 1 (WASD)
            } else if(key == InputHandler::KEY_UP || key == InputHandler::KEY_DOWN ||
                      key == InputHandler::KEY_LEFT || key == InputHandler::KEY_RIGHT) {
                data->setKey2(key); // jugador 2 (flechas)
            }else if(key == InputHandler::KEY_ENTER || key == InputHandler::KEY_ESC) {
                // lo tratamos como "global" → meterlo en keyPlayer1
                data->setKey(key);
            }
        }

        usleep(10000);
    }

    return nullptr;
}