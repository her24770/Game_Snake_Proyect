#include "../../include/core/Food.hpp"
#include "../../include/rendering/Game.hpp"
#include <cstdlib>
#include <ctime>

Food::Food() : position({0, 0}), exists(false) {
    srand(time(nullptr));
}

void Food::generate(const std::vector<std::pair<int, int>>& snake1Body,
                    const std::vector<std::pair<int, int>>& snake2Body) {
    bool validPosition = false;
    int x, y;
    
    while(!validPosition) {
        x = (rand() % (GAME::CONSOLE_WIDTH - 2)) + 1;
        y = (rand() % (GAME::CONSOLE_HEIGHT - 2)) + 1;
        
        validPosition = true;
        
        // Verificar que no esté en snake1
        for(const auto& segment : snake1Body) {
            if(segment.first == x && segment.second == y) {
                validPosition = false;
                break;
            }
        }
        
        // Verificar que no esté en snake2
        if(validPosition) {
            for(const auto& segment : snake2Body) {
                if(segment.first == x && segment.second == y) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
    
    position = {x, y};
    exists = true;
}

std::pair<int, int> Food::getPosition() const {
    return position;
}

bool Food::isActive() const {
    return exists;
}

void Food::consume() {
    exists = false;
}