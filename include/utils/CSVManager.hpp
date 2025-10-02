#ifndef CSV_MANAGER_HPP
#define CSV_MANAGER_HPP

#include <string>
#include <vector>

// Estructura para almacenar puntajes de jugadores
struct PlayerScore {
    std::string name;
    int score;
    int time;
};

namespace CSVManager {
    // Funciones para manejo de CSV
    std::vector<PlayerScore> readScoresFromCSV(const std::string& filename);
    void saveScoreToCSV(const std::string& filename, const std::string& playerName, int score, int time);
    
    // Función auxiliar para generar datos de ejemplo
    std::vector<PlayerScore> getExampleScores();
}

#endif // CSV_MANAGER_HPP