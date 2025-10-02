#include "../../include/threads/InputThread.hpp"
#include "../../include/utils/InputHandler.hpp"
#include <unistd.h>
#include <string.h>
#include <cstdio>

void* inputThreadFunction(void* arg) {
    SharedGameData* data = (SharedGameData*)arg;

    while(true) {
        bool shouldRun;
        {
            std::lock_guard<std::mutex> lock(data->mtx);
            shouldRun = data->running;
        }
        
        if(!shouldRun) break;

        int key = InputHandler::getUserInputNonBlocking();
        if(key != InputHandler::KEY_NONE) {
            // Debug
            char buffer[100];
            sprintf(buffer, "[HILO] Tecla capturada: %d\n", key);
            write(STDOUT_FILENO, buffer, strlen(buffer));

            // CORRECCIÓN: Invertir las asignaciones
            if(key == InputHandler::KEY_W || key == InputHandler::KEY_A ||
               key == InputHandler::KEY_S || key == InputHandler::KEY_D) {
                data->setKey2(key); // WASD → setKey2 (para playerId 2)
            } else if(key == InputHandler::KEY_UP || key == InputHandler::KEY_DOWN ||
                      key == InputHandler::KEY_LEFT || key == InputHandler::KEY_RIGHT) {
                data->setKey(key); // Flechas → setKey (para playerId 1)
            } else if(key == InputHandler::KEY_ENTER || key == InputHandler::KEY_ESC) {
                // Global: poner en ambos
                data->setKey(key);
                data->setKey2(key);
            }
        }

        usleep(5000); // Reducir de 10ms a 5ms para mejor respuesta
    }

    return nullptr;
}