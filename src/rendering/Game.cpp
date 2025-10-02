#include "../../include/rendering/Game.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include "../../include/utils/InputHandler.hpp"
#include "../../include/core/Food.hpp"
#include <iostream>
#include <iomanip>

namespace GAME {

     std::string formatTime(int totalSeconds) {
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << minutes 
            << ":" << std::setw(2) << seconds;
        return oss.str();
    }
    
    //Crea toda la vista incluyendo las serpientes, bordes y la comida
    void renderGameScreen(const Snake& snake1, const Food& food, const Snake* snake2) {
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
        if(food.isActive()) {
            auto foodPos = food.getPosition();
            int comidaX = foodPos.first;
            int comidaY = foodPos.second;
            if(comidaX>0 && comidaX<CONSOLE_WIDTH && comidaY>0 && comidaY<CONSOLE_HEIGHT)
                pantalla[comidaY][comidaX] = "¤";
        }

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



void GAME::renderGameOver(const Snake& snake1, const Snake& snake2, int totalSeconds) {
    using namespace GAME;
    std::vector<std::vector<std::string>> pantalla(GAME::CONSOLE_HEIGHT, std::vector<std::string>(GAME::CONSOLE_WIDTH, " "));
    // Dibujar bordes
    for (int x = 0; x < CONSOLE_WIDTH; ++x) {
        pantalla[0][x] = pantalla[CONSOLE_HEIGHT-1][x] = "▓";
    }
    for (int y = 0; y < CONSOLE_HEIGHT; ++y) {
        pantalla[y][0] = pantalla[y][CONSOLE_WIDTH-1] = "▓";
    }

    // Mensaje GAME OVER centrado
    std::vector<std::string> gameOverText = {
        "   @@@@@@     @@      @@     @@ @@@@@@@@",
        "  @@         @@@@@    @@ @@@ @@ @@      ",
        " @@         @@   @@   @@  @  @@ @@@@@@@ ",
        " @@   @@@@  @@@@@@@   @@     @@ @@      ",
        "  @@    @@ @@     @@  @@     @@ @@      ",
        "   @@@@@@  @@     @@  @@     @@ @@@@@@@@",
        "",
        "   @@@@@@   @@   @@  @@@@@@@@  @@@@@@  ",
        "  @@    @@  @@   @@  @@        @@   @@ ",
        " @@      @@  @@ @@   @@@@@@@@  @@@@@@  ",
        " @@      @@  @@ @@   @@        @@   @@ ",
        "  @@    @@    @@@    @@        @@   @@ ",
        "   @@@@@@     @@@    @@@@@@@@  @@   @@ "
    };

    int startY = (CONSOLE_HEIGHT - gameOverText.size()) / 2;
    for(size_t i = 0; i < gameOverText.size(); ++i) {
        int startX = (CONSOLE_WIDTH - gameOverText[i].length()) / 2;
        for(size_t j = 0; j < gameOverText[i].length(); ++j) {
            if(startX + j > 0 && startX + j < GAME::CONSOLE_WIDTH-1 &&
                startY + i > 0 && startY + i < GAME::CONSOLE_HEIGHT-1) {
                pantalla[startY + i][startX + j] = std::string(1, gameOverText[i][j]);
            }
        }
    }

    // Renderizar pantalla
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    
    for(const auto& fila : pantalla){
        for(const auto& celda : fila){
            if(celda == "▓") std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
            else std::cout << WindowsConsole::Colors::BRIGHT_RED;
            std::cout << celda;
        }
        std::cout << std::endl;
    }

    std::cout << WindowsConsole::Colors::BRIGHT_WHITE
          << "\nPuntaje Final Jugador 1: " << snake1.getPuntuacion()
          << "\nPuntaje Final Jugador 2: " << snake2.getPuntuacion()
          << "\nTiempo de Juego: " << formatTime(totalSeconds)
          << WindowsConsole::Colors::RESET << std::endl;
    std::cout << WindowsConsole::Colors::RESET << std::endl;
}