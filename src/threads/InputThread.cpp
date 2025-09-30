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
        
        int key = InputHandler::getUserInput();
        if(key != InputHandler::KEY_NONE) {
            data->setKey(key);
        }

        // AGREGAR ESTAS LÍNEAS DE DEBUG
        if(key != InputHandler::KEY_NONE) {
            char buffer[100];
            sprintf(buffer, "[HILO] Tecla capturada: %d\n", key);
            write(STDOUT_FILENO, buffer, strlen(buffer));
            data->setKey(key);
        }
        
        usleep(10000);
    }
    
    return nullptr;
}