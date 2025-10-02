#ifndef AUDIO_THREAD_HPP
#define AUDIO_THREAD_HPP

#include <string>
#include <atomic>

enum AudioTrack {
    AUDIO_NONE = 0,
    AUDIO_MENU = 1,
    AUDIO_GAME = 2,
    AUDIO_INSTRUCTIONS = 3,
    AUDIO_SCOREBOARD = 4
};

struct AudioThreadData {
    std::atomic<int> currentTrack;
    std::atomic<bool> running;
    std::atomic<bool> shouldChange;
};

void* audioThreadFunction(void* arg);
void stopCurrentAudio();

#endif