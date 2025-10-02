#ifndef SCORE_THREADS_HPP
#define SCORE_THREADS_HPP

#include <string>

struct ScoreThreadsData {
    std::string nombre;
    int puntuacion;
    std::string tiempo;
    std::string rutaCSV;
};

void* writeScoreThread(void* arg);

#endif