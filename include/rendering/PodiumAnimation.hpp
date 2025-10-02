#ifndef PODIUM_ANIMATION_HPP
#define PODIUM_ANIMATION_HPP

#include <string>
#include <vector>
#include "../utils/CSVManager.hpp"

namespace PodiumAnimation {
    // Funciones para la animación del podio
    void printAtPosition(int x, int y, const std::string& text);
    void waitMs(int ms);
    void drawColumn(const std::vector<std::string>& column, int x, const std::string& name);
    void drawConfettiOver(int frames = 10, int width = 90, int height = 25, int safeTop = 6);
    void showPodiumAnimation(const std::vector<PlayerScore>& scores);
}

#endif // PODIUM_ANIMATION_HPP