#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "../core/Snake.hpp"

namespace GAME{
    const int CONSOLE_WIDTH = 80;
    const int CONSOLE_HEIGHT = 25;
    void renderGameScreen(const Snake& snake1, int comidaX = 65, int comidaY = 20,const Snake* snake2 = nullptr);
}

#endif