#include "../../include/rendering/Game.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include "../../include/utils/InputHandler.hpp"
#include <iostream>
#include <iomanip>

namespace GAME {
    //Crea toda la vista incluyendo las serpientes, bordes y la comida
    void renderGameScreen(const Snake& snake1, int comidaX, int comidaY, const Snake* snake2) {
        std::vector<std::vector<std::string>> pantalla(CONSOLE_HEIGHT, std::vector<std::string>(CONSOLE_WIDTH, " "));

        // Dibujar bordes
        for (int x = 0; x < CONSOLE_WIDTH; ++x) {
            pantalla[0][x] = pantalla[CONSOLE_HEIGHT-1][x] = "▓";
        }
        for (int y = 0; y < CONSOLE_HEIGHT; ++y) {
            pantalla[y][0] = pantalla[y][CONSOLE_WIDTH-1] = "▓";
        }

        // Dibujar serpientes
        auto drawSnakeOnScreen = [&](const Snake& snake, const std::string& cabezaSym, const std::string& cuerpoSym){
            const auto& cuerpo = snake.getCuerpo();
            auto cabeza = snake.getCabeza();
            for(size_t i=0; i<cuerpo.size(); ++i){
                int x = cuerpo[i].first;
                int y = cuerpo[i].second;
                if(x>0 && x<CONSOLE_WIDTH && y>0 && y<CONSOLE_HEIGHT){
                    pantalla[y][x] = (i==0) ? cabezaSym : cuerpoSym;
                }
            }
        };
        drawSnakeOnScreen(snake1, "@", "◯");
        if(snake2) drawSnakeOnScreen(*snake2, "@", "⦿");

        // Dibujar comida
        if(comidaX>0 && comidaX<CONSOLE_WIDTH && comidaY>0 && comidaY<CONSOLE_HEIGHT)
            pantalla[comidaY][comidaX] = "¤";

        // Limpiar consola y dibujar
        WindowsConsole::clearScreen();
        WindowsConsole::hideCursor();
        WindowsConsole::setConsoleTitle("Snake Game - Jugando");

        for(const auto& fila : pantalla){
            for(const auto& celda : fila){
                if(celda=="▓") std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
                else if(celda=="◯") std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
                else if(celda=="@") std::cout << WindowsConsole::Colors::BRIGHT_BLUE;
                else if(celda=="⦿") std::cout << WindowsConsole::Colors::BRIGHT_YELLOW;
                else if(celda=="¤") std::cout << WindowsConsole::Colors::BRIGHT_RED;
                else std::cout << WindowsConsole::Colors::RESET;

                std::cout << celda;
            }
            std::cout << std::endl;
        }

        std::cout << WindowsConsole::Colors::BRIGHT_WHITE
                << "\nPuntaje Jugador 1: " << snake1.getPuntuacion() << std::endl;
        if(snake2) std::cout << "Puntaje Jugador 2: " << snake2->getPuntuacion() << std::endl;
        std::cout << WindowsConsole::Colors::RESET;
        std::cout << "\nESC para volver\n";
    }
}