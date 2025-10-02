#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "../core/Snake.hpp"
#include "../core/Food.hpp"

namespace GAME{
    const int CONSOLE_WIDTH = 80;
    const int CONSOLE_HEIGHT = 25;
    void renderGameScreen(const Snake& snake1, const Food& food, const Snake* snake2 = nullptr);
    void renderGameOver(const Snake& snake1, const Snake* snake2);
    
    // Nuevas funciones para el diálogo de guardado
    bool showSaveDialog();
    std::string getPlayerName();
    void savePlayerScore(const std::string& playerName, int score, int timeMs);
}

#endif