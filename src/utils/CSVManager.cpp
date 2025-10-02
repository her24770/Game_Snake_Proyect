#include "../../include/utils/CSVManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace CSVManager {

std::vector<PlayerScore> getExampleScores() {
    return {
        {"Cristi", 150, 50}, {"Wong", 120, 40}, {"Strange", 100, 30},
        {"Ancestral", 80, 90}, {"Dormamu", 60, 70}, {"Tony", 100, 25},
        {"Peter", 80, 89}, {"Natasha", 60, 68}, {"Steve", 60, 60},
        {"Bruce", 40, 45}, {"Rocket", 40, 30}, {"Thor", 30, 100},
        {"Loki", 20, 99}, {"Gamora", 10, 88}, {"Groot", 5, 10}
    };
}

std::vector<PlayerScore> readScoresFromCSV(const std::string& filename) {
    std::vector<PlayerScore> scores;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo " << filename << ". Usando datos de ejemplo.\n";
        return getExampleScores();
    }
    
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line)) {
        // Saltar la línea de encabezados
        if (firstLine && (line.find("name") != std::string::npos || 
                         line.find("Name") != std::string::npos || 
                         line.find("PLAYER") != std::string::npos)) {
            firstLine = false;
            continue;
        }
        firstLine = false;
        
        if (line.empty()) continue;
        
        // Parsear la línea CSV
        std::istringstream ss(line);
        std::string name, scoreStr, timeStr;
        
        // Leer nombre (hasta la primera coma)
        if (std::getline(ss, name, ',')) {
            // Leer puntaje (hasta la segunda coma)
            if (std::getline(ss, scoreStr, ',')) {
                // Leer tiempo (resto de la línea)
                if (std::getline(ss, timeStr)) {
                    try {
                        // Limpiar espacios en blanco
                        name.erase(0, name.find_first_not_of(" \t"));
                        name.erase(name.find_last_not_of(" \t") + 1);
                        scoreStr.erase(0, scoreStr.find_first_not_of(" \t"));
                        scoreStr.erase(scoreStr.find_last_not_of(" \t") + 1);
                        timeStr.erase(0, timeStr.find_first_not_of(" \t"));
                        timeStr.erase(timeStr.find_last_not_of(" \t") + 1);
                        
                        int score = std::stoi(scoreStr);
                        int time = std::stoi(timeStr);
                        
                        scores.push_back({name, score, time});
                    } catch (const std::exception& e) {
                        // Si hay error en la conversión, saltar esta línea
                        continue;
                    }
                }
            }
        }
    }
    
    file.close();
    
    // Si no se pudieron leer datos válidos, usar datos de ejemplo
    if (scores.empty()) {
        return getExampleScores();
    }
    
    return scores;
}

void saveScoreToCSV(const std::string& filename, const std::string& playerName, int score, int time) {
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        file << playerName << "," << score << "," << time << std::endl;
        file.close();
    }
}

} // namespace CSVManager