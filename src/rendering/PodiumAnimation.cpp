#include "../../include/rendering/PodiumAnimation.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

namespace PodiumAnimation {

// Diseños únicos para cada columna del podio
const std::vector<std::string> PODIO_CENTRAL = {
    "       ╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓x,      ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "      ░░░░░░░░░███║░░░░░░░░░     ",
    "      ░░░░░░░░████║░░░░░░░░░     ",
    "      ░░░░░░░░░░██║░░░░░░░░░     ",
    "      ░░░░░░░░░░██║░░░░░░░░░     ",
    "      ░░░░░░░░██████║░░░░░░░     ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "▄▄▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▄▄ "
};

const std::vector<std::string> PODIO_IZQUIERDO = {
    "       ╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓x,      ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",          
    "      ░░░░░░░░█████░░░░░░░░░     ",               
    "      ░░░░░░░███████║░░░░░░░     ",                    
    "      ░░░░░░██╓░░░██║░░░░░░░     ",                  
    "      ░░░░░░░░░░███║░░░░░░░░     ",                   
    "      ░░░░░░░░████╓░░░░░░░░░     ",                 
    "      ░░░░░░░███████║░░░░░░░     ",                   
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "▄▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▄▄  "
};

const std::vector<std::string> PODIO_DERECHO = {
    "       ╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓x,      ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "      ░░░░░░░░░███║░░░░░░░░░     ",
    "      ░░░░░░░███╓████║░░░░░░     ",
    "      ░░░░░░░██╓░░┘██║░░░░░░     ",
    "      ░░░░░░░░░░████║░░░░░░░     ",
    "      ░░░░░░░██╙K╙ ██║░░░░░░     ",
    "      ░░░░░░░░█████║░░░░░░░░     ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "▄▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▄   "
};

void printAtPosition(int x, int y, const std::string& text) {
    std::cout << "\033[" << y << ";" << x << "H" << text << std::flush;
}

void waitMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// Dibujo gradual por línea (columna emerge)
void drawColumn(const std::vector<std::string>& column, int x, const std::string& name) {
    int total = column.size();
    int termBottom = 30;
    int startY = termBottom - total + 1;

    // Mostrar el nombre justo encima del podio
    printAtPosition(x + 3, startY - 1, "\033[1;36m" + name + "\033[0m");

    // Mostrar línea por línea desde abajo hacia arriba
    for (int i = 0; i < total; ++i) {
        printAtPosition(x, startY + i, column[i]);
        waitMs(80);
    }
}

// Confeti animado SIN borrar pantalla
void drawConfettiOver(int frames, int width, int height, int safeTop) {
    std::vector<char> confettiChars = {'*', '+', 'x', '@', '#'};
    for (int f = 0; f < frames; ++f) {
        for (int i = safeTop; i < height; ++i) {  // Evita líneas superiores (safeTop)
            for (int j = 0; j < width; ++j) {
                if (rand() % 15 == 0) {
                    char ch = confettiChars[rand() % confettiChars.size()];
                    int color = 31 + rand() % 7;
                    printAtPosition(j + 1, i + 1, "\033[1;" + std::to_string(color) + "m" + ch + "\033[0m");
                }
            }
        }
        waitMs(200);
    }
}

void showPodiumAnimation(const std::vector<PlayerScore>& scores) {
    srand(time(0));
    WindowsConsole::clearScreen();
    std::cout << "\033[?25l"; // Ocultar cursor
    
    // Obtener los nombres del top 3
    std::string first = scores.size() > 0 ? scores[0].name : "Jugador1";
    std::string second = scores.size() > 1 ? scores[1].name : "Jugador2";
    std::string third = scores.size() > 2 ? scores[2].name : "Jugador3";
    
    // 1. Centro (1er lugar)
    drawColumn(PODIO_CENTRAL, 35, first);
    
    // 2. Izquierda (2do lugar)
    drawColumn(PODIO_IZQUIERDO, 5, second);
    
    // 3. Derecha (3er lugar)
    drawColumn(PODIO_DERECHO, 65, third);
    
    waitMs(1000);
    
    // 4. Confeti y mensaje sobrepuestos
    drawConfettiOver(15, 90, 30, 6);  // frames, width, height, safeTop
    printAtPosition(30, 3, "\033[1;33m ¡Felicidades a los ganadores! \033[0m");
    
    waitMs(3000);
    std::cout << "\033[?25h"; // Mostrar cursor
}

} // namespace PodiumAnimation