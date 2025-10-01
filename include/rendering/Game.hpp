#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "../core/Snake.hpp"

namespace GAME{
    const int CONSOLE_WIDTH = 80;
    const int CONSOLE_HEIGHT = 25;

    std::string centerString(const std::string& text, int width);

    void drawSnake(const Snake& snake, std::vector<std::vector<std::string>>& pantalla, int id);
    void drawBorder_PS(std::vector<std::vector<std::string>>& pantalla);
    void drawObject(std::vector<std::vector<std::string>>& pantalla, int x, int y, const std::string& sym);

    void drawGame(const Snake& snake, int lastKey = 0, const Snake* snake2 = nullptr);

    void renderGameScreen(const Snake& snake1, int comidaX = 65, int comidaY = 20,const Snake* snake2 = nullptr);
}

#endif