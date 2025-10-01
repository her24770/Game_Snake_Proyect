#include "../../include/threads/AudioThread.hpp"
#include <iostream>
#include <unistd.h>

AudioManager::AudioManager() : mh(nullptr), dev(nullptr), initialized(false) {
    if (mpg123_init() == MPG123_OK) {
        ao_initialize();
        initialized = true;
    }
}

AudioManager::~AudioManager() {
    if (mh) {
        mpg123_close(mh);
        mpg123_delete(mh);
    }
    if (dev) {
        ao_close(dev);
    }
    if (initialized) {
        mpg123_exit();
        ao_shutdown();
    }
}

bool AudioManager::playSound(const std::string& filename) {
    if (!initialized) return false;

    // Crear handle para este sonido
    mpg123_handle* soundHandle = mpg123_new(nullptr, nullptr);
    if (!soundHandle) return false;

    // Abrir archivo de sonido
    if (mpg123_open(soundHandle, filename.c_str()) != MPG123_OK) {
        mpg123_delete(soundHandle);
        return false;
    }

    // Configurar formato
    mpg123_format_none(soundHandle);
    mpg123_format(soundHandle, 44100, MPG123_STEREO, MPG123_ENC_SIGNED_16);

    // Obtener formato
    long rate;
    int channels, encoding;
    if (mpg123_getformat(soundHandle, &rate, &channels, &encoding) != MPG123_OK) {
        mpg123_close(soundHandle);
        mpg123_delete(soundHandle);
        return false;
    }

    // Configurar dispositivo de audio
    ao_sample_format format;
    format.bits = mpg123_encsize(encoding) * 8;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = nullptr;

    ao_device* audioDev = ao_open_live(ao_default_driver_id(), &format, nullptr);
    if (!audioDev) {
        mpg123_close(soundHandle);
        mpg123_delete(soundHandle);
        return false;
    }

    // Reproducir sonido
    unsigned char buffer[4096];
    size_t bytes_read;

    while (mpg123_read(soundHandle, buffer, sizeof(buffer), &bytes_read) == MPG123_OK) {
        if (bytes_read > 0) {
            ao_play(audioDev, (char*)buffer, bytes_read);
        }
    }

    // Limpiar recursos de este sonido
    ao_close(audioDev);
    mpg123_close(soundHandle);
    mpg123_delete(soundHandle);

    return true;
}

void* audioThreadFunction(void* arg) {
    AudioThreadData* data = (AudioThreadData*)arg;
    AudioManager audioManager;

    while (*(data->running)) {
        std::string soundFile;
        
        {
            std::unique_lock<std::mutex> lock(*(data->queueMutex));
            
            // Esperar hasta que haya sonidos en la cola o se detenga el hilo
            data->queueCondition->wait(lock, [data]() {
                return !data->soundQueue->empty() || !*(data->running);
            });

            if (!*(data->running)) break;

            if (!data->soundQueue->empty()) {
                soundFile = data->soundQueue->front();
                data->soundQueue->pop();
            }
        } // Liberar el mutex

        // Reproducir el sonido (sin lock para no bloquear otros hilos)
        if (!soundFile.empty()) {
            audioManager.playSound(soundFile);
        }
    }

    return nullptr;
}