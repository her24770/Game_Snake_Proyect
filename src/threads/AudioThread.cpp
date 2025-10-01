#include "../../include/threads/AudioThread.hpp"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <cstring>
#include <sys/resource.h>

static pid_t currentMpg123Pid = -1;

void stopCurrentAudio() {
    if(currentMpg123Pid > 0) {
        kill(currentMpg123Pid, SIGTERM);
        waitpid(currentMpg123Pid, nullptr, 0);
        currentMpg123Pid = -1;
    }
}

void playAudio(const char* filename) {
    stopCurrentAudio();
    
    currentMpg123Pid = fork();
    
    if(currentMpg123Pid == 0) {
        // Proceso hijo: ejecutar mpg123
        execl("/usr/bin/mpg123", "mpg123", "-q", "--loop", "-1", filename, (char*)nullptr);
        _exit(1); // Si execl falla
    }
}

void* audioThreadFunction(void* arg) {
    AudioThreadData* data = (AudioThreadData*)arg;

    nice(10);

    int lastTrack = AUDIO_NONE;
    
    while(data->running.load()) {
        int currentTrack = data->currentTrack.load();
        
        // Si cambió la pista o se solicitó cambio
        if(currentTrack != lastTrack || data->shouldChange.load()) {
            stopCurrentAudio();
            
            switch(currentTrack) {
                case AUDIO_MENU:
                    playAudio("assets/audio/menu.mp3");
                    break;
                case AUDIO_GAME:
                    playAudio("assets/audio/juego.mp3");
                    break;
                case AUDIO_INSTRUCTIONS:
                    playAudio("assets/audio/instrucciones.mp3");
                    break;
                case AUDIO_SCOREBOARD:
                    playAudio("assets/audio/puntajes.mp3");
                    break;
                case AUDIO_NONE:
                    stopCurrentAudio();
                    break;
            }
            
            lastTrack = currentTrack;
            data->shouldChange.store(false);
        }
        
        usleep(500000); // 500ms
    }
    
    stopCurrentAudio();
    return nullptr;
}