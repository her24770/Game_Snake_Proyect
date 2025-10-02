#include "../../include/threads/ScoreThread.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unistd.h>

void loadScoresFromCSV(std::vector<ScoreEntry>& scores) {
    scores.clear();
    std::ifstream file("assets/scores.csv");
    
    if(!file.is_open()) return;
    
    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, time;
        int score;
        
        std::getline(ss, name, ',');
        ss >> score;
        ss.ignore();
        std::getline(ss, time);
        
        scores.push_back({name, score, time});
    }
    
    file.close();
    
    // Ordenar por puntuación descendente
    std::sort(scores.begin(), scores.end(), 
              [](const ScoreEntry& a, const ScoreEntry& b) {
                  return a.score > b.score;
              });
}

void saveScoresToCSV(const std::vector<ScoreEntry>& scores) {
    std::ofstream file("assets/scores.csv");
    
    for(const auto& entry : scores) {
        file << entry.name << "," << entry.score << "," << entry.time << "\n";
    }
    
    file.close();
}

void saveScore(ScoreThreadData* data, const std::string& name, int score, const std::string& time) {
    std::lock_guard<std::mutex> lock(data->scoreMutex);
    data->scores.push_back({name, score, time});
    
    std::sort(data->scores.begin(), data->scores.end(),
              [](const ScoreEntry& a, const ScoreEntry& b) {
                  return a.score > b.score;
              });
    
    // Mantener solo top 10
    if(data->scores.size() > 10) {
        data->scores.resize(10);
    }
    
    saveScoresToCSV(data->scores);
    data->needsUpdate.store(true);
}

void* scoreThreadFunction(void* arg) {
    ScoreThreadData* data = (ScoreThreadData*)arg;
    
    // Cargar scores al inicio
    {
        std::lock_guard<std::mutex> lock(data->scoreMutex);
        loadScoresFromCSV(data->scores);
    }
    
    while(data->running.load()) {
        if(data->needsUpdate.load()) {
            std::lock_guard<std::mutex> lock(data->scoreMutex);
            loadScoresFromCSV(data->scores);
            data->needsUpdate.store(false);
        }
        sleep(1);
    }
    
    return nullptr;
}

int getLowestTopScore(ScoreThreadData* data) {
    std::lock_guard<std::mutex> lock(data->scoreMutex);
    if(data->scores.empty()) return 0;
    return data->scores.back().score;
}
void addScoreImmediate(ScoreThreadData* data, const std::string& name, int score, const std::string& time) {
    std::lock_guard<std::mutex> lock(data->scoreMutex);
    data->scores.push_back({name, score, time});

    std::sort(data->scores.begin(), data->scores.end(),
              [](const ScoreEntry& a, const ScoreEntry& b) {
                  return a.score > b.score;
              });

    if(data->scores.size() > 10)
        data->scores.resize(10);
    saveScoresToCSV(data->scores);
    data->needsUpdate.store(true);
}