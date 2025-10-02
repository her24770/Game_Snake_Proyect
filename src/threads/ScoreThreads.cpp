#include "../../include/threads/ScoreThreads.hpp"
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <sstream>
#include <algorithm>

struct ScoreEntry {
    std::string nombre;
    int puntuacion;
    std::string tiempo;
};

// Comparador para ordenar de mayor a menor
bool compareScores(const ScoreEntry& a, const ScoreEntry& b) {
    return a.puntuacion > b.puntuacion;
}

void* writeScoreThread(void* arg) {
    ScoreThreadsData* data = (ScoreThreadsData*)arg;

    std::vector<ScoreEntry> scores;

    // Leer el CSV existente
    std::ifstream infile(data->rutaCSV);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string nombre, puntuacionStr, tiempo;
            if (std::getline(ss, nombre, ',') &&
                std::getline(ss, puntuacionStr, ',') &&
                std::getline(ss, tiempo, ',')) {
                int puntos = std::stoi(puntuacionStr);
                scores.push_back({nombre, puntos, tiempo});
            }
        }
        infile.close();
    }

    // Agregar nuevo score
    scores.push_back({data->nombre, data->puntuacion, data->tiempo});

    // Ordenar y mantener solo los 5 mejores
    std::sort(scores.begin(), scores.end(), compareScores);
    if (scores.size() > 5) scores.resize(5);

    // Escribir todo de nuevo en el CSV
    std::ofstream outfile(data->rutaCSV, std::ios::trunc); // sobreescribir
    if (!outfile.is_open()) {
        std::cerr << "Error al abrir el archivo CSV: " << data->rutaCSV << std::endl;
        delete data;
        return nullptr;
    }

    for (const auto& entry : scores) {
        outfile << entry.nombre << "," << entry.puntuacion << "," << entry.tiempo << "\n";
    }
    outfile.close();

    std::cout << "[SCORE] Puntuacion guardada" << std::endl;

    delete data;
    return nullptr;
}
