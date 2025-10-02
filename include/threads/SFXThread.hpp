#ifndef SFX_THREAD_HPP
#define SFX_THREAD_HPP

#include <atomic>
#include <queue>
#include <mutex>

enum SoundEffect {
    SFX_NONE = 0,
    SFX_WALL_COLLISION = 1,
    SFX_SELF_COLLISION = 2,
    SFX_SNAKE_COLLISION = 3,
    SFX_EAT_FOOD = 4            
};

struct SFXData {
    std::queue<SoundEffect> sfxQueue;
    std::mutex sfxMutex;
    std::atomic<bool> running;
};

void* sfxThreadFunction(void* arg);

void playSoundEffect(SFXData* data, SoundEffect sfx);

#endif