#ifndef SCORE_THREAD_HPP
#define SCORE_THREAD_HPP

#include <string>

struct ScoreThreadData {
    std::string nombre;
    int puntuacion;
    std::string tiempo;
    std::string rutaCSV;
};

void* writeScoreThread(void* arg);

#endif