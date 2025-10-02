#include "../../include/threads/SFXThread.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

void playSFX(const char* filename, int volume = 60) {
    pid_t sfxPid = fork();
    
    if(sfxPid == 0) {
        // Proceso hijo, reproducir sonido una vez
        freopen("/dev/null", "w", stderr); 
        std::string volStr = std::to_string(volume);
        execl("/usr/bin/mpg123", "mpg123", "-q", filename, (char*)nullptr);
        _exit(1);
    }
    // El padre sigue inmediatamente, para multiples sonidos simultaneos
}

// Sonido a la cola
void playSoundEffect(SFXData* data, SoundEffect sfx) {
    std::lock_guard<std::mutex> lock(data->sfxMutex);
    data->sfxQueue.push(sfx);
}

// Hilo para la cola de sonidos
void* sfxThreadFunction(void* arg) {
    SFXData* data = (SFXData*)arg;
    nice(-10);
    
    while(data->running.load()) {
        SoundEffect sfx = SFX_NONE;
        
        {
            std::lock_guard<std::mutex> lock(data->sfxMutex);
            if(!data->sfxQueue.empty()) {
                sfx = data->sfxQueue.front();
                data->sfxQueue.pop();
            }
        }
        
        // Reproducir sonido segun tipo de colision o comer
        if(sfx != SFX_NONE) {
            switch(sfx) {
                case SFX_WALL_COLLISION:
                    playSFX("assets/efectos/ColisionMuro.mp3", 100);
                    break;
                case SFX_SELF_COLLISION:
                    playSFX("assets/efectos/ColisionEllamisma.mp3", 100);
                    break;
                case SFX_SNAKE_COLLISION:
                    playSFX("assets/efectos/ColisionEntre2.mp3", 100);
                    break;
                case SFX_EAT_FOOD:
                    playSFX("assets/efectos/Comer.mp3", 100);
                    break;
                default:
                    break;
            }
        }
        
        usleep(1000);
    }
    
    return nullptr;
}