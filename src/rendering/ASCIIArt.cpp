#include "../../include/rendering/ASCIIArt.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <iomanip>

namespace ASCIIArt {
    
    void drawMainMenu(int selectedOption) {
        WindowsConsole::clearScreen();
        WindowsConsole::hideCursor();
        WindowsConsole::setConsoleTitle("Snake Game - Menu Principal");

        std::cout << std::endl;

        // 🔹 Marco superior
        drawMenuBorder();

        // 🔹 Título del juego
        drawGameTitle();


        // 🔹 Opciones del menú con selector
        std::cout << WindowsConsole::Colors::BRIGHT_WHITE;

        std::string topFrame    = "                       ╔══════════════════════════════════╗";
        std::string bottomFrame = "                       ╚══════════════════════════════════╝";

        printCenteredLine(topFrame);

        std::vector<std::string> options = {
            (selectedOption == 0 ? "        ║           ➤  Jugar               ║" : "       ║              Jugar               ║"),
            (selectedOption == 1 ? "        ║        ➤  Instrucciones          ║" : "       ║           Instrucciones          ║"),
            (selectedOption == 2 ? "        ║          ➤  Puntajes             ║" : "       ║             Puntajes             ║"),
            (selectedOption == 3 ? "        ║           ➤  Salir               ║" : "       ║              Salir               ║")
        };

        for (const auto& option : options) {
            printCenteredLine(option);
        }

        printCenteredLine(bottomFrame);
        std::cout << WindowsConsole::Colors::RESET << std::endl;


        // 🔹 Marco inferior
        drawMenuBorder();

        WindowsConsole::showCursor();
    }

// Pantallas simples
void drawGame() {
    system("clear");
    int score = 10;
    std::vector<std::vector<std::string>> pantalla(CONSOLE_HEIGHT, std::vector<std::string>(CONSOLE_WIDTH, " "));
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    WindowsConsole::setConsoleTitle("Snake game - Playing");
    std::cout<<std::endl;
    
    drawBorder_PS(pantalla);
    
    //Cuerpo de la serpiente
    drawObject(pantalla, 15,20, "◯");
    drawObject(pantalla, 16,20, "◯");
    drawObject(pantalla, 17,20, "◯");
    drawObject(pantalla, 18,20, "◯");
    drawObject(pantalla, 19,20, "◯");
    drawObject(pantalla, 19,21, "◯");
    drawObject(pantalla, 19,22, "◯");
    drawObject(pantalla, 19,22, "@");
    
    //Cuerpo de la serpiente
    drawObject(pantalla, 45,20, "@");
    drawObject(pantalla, 46,20, "⦿");
    drawObject(pantalla, 47,20, "⦿");
    drawObject(pantalla, 48,20, "⦿");
    drawObject(pantalla, 49,20, "⦿");
    drawObject(pantalla, 49,21, "⦿");
    drawObject(pantalla, 49,22, "⦿");
    drawObject(pantalla, 49,22, "⦿");
    
    //Comida
    drawObject(pantalla, 30,23, "¤");
    
    system("cls");
    
    std::cout << "\n\n=== JUGANDO ===\n";
    std::cout << WindowsConsole::Colors::BRIGHT_WHITE;
    std::string scoreText = "PUNTUACIÓN: " + std::to_string(score);
    std::cout << centerString(scoreText, CONSOLE_WIDTH) << std::endl;
    std::cout << WindowsConsole::Colors::RESET;

    //Se dibujan todos los elementos de la matriz
    for (const auto& linea : pantalla) {
        for (const auto& sym : linea) {
            if (sym == "▓") std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
            else if (sym == "◯") std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
            else if (sym == "@") std::cout << WindowsConsole::Colors::BRIGHT_BLUE;
            else if (sym == "⦿") std::cout << WindowsConsole::Colors::BRIGHT_YELLOW;
            else if (sym == "¤") std::cout << WindowsConsole::Colors::BRIGHT_RED;
            else std::cout << WindowsConsole::Colors::RESET;

            std::cout << sym;
        }
        std::cout << std::endl;
    }
    std:: cout << "\nESC para volver\n";
}

void drawInstructions() {
    system("clear");  
    std::cout << "\n\n=== INSTRUCCIONES ===\n\nESC para volver\n";
}

void drawScoreboard() {
    system("clear");
    std::cout << "\n\n=== PUNTAJES ===\n\nESC para volver\n";  
}
void drawMenuBorder() {
        std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
        std::string border = "╔" + std::string(CONSOLE_WIDTH - 2, '═') + "╗";
        printCenteredLine(border);
        std::cout << WindowsConsole::Colors::RESET;
    }
std::string centerString(const std::string& text, int width) {
        int padding = (width - text.length()) / 2;
        return std::string(padding, ' ') + text + std::string(width - text.length() - padding, ' ');
    }   
 void printCenteredLine(const std::string& text) {
        int padding = (CONSOLE_WIDTH - text.length()) / 2;
        if (padding > 0) {
            std::cout << std::string(padding, ' ');
        }
        std::cout << text << std::endl;
    }
    void drawGameTitle() {
        std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
        
        // Arte ASCII para "SNAKE GAME"
        std::vector<std::string> title = {
            "               ",
            "               ",
            "                    ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗",
            "                    ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝",
            "                    ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ",
            "                    ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ",
            "                    ███████║██║ ╚████║██║  ██║██║  ██╗███████╗",
            "                    ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝",
            "",
            "                       ██████╗  █████╗ ███╗   ███╗███████╗",
            "                      ██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
            "                      ██║  ███╗███████║██╔████╔██║█████╗  ",
            "                      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
            "                      ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
            "                     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"
        };
        
        for (const auto& line : title) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }
    //Bordes del escenario
    void drawBorder_PS(std::vector<std::vector<std::string>>& pantalla){
        std:: cout << WindowsConsole::Colors::BRIGHT_GREEN;
        for (int x = 0; x < CONSOLE_WIDTH; ++x) {
            pantalla[0][x] = pantalla[CONSOLE_HEIGHT - 1][x] = "▓";
        }
        for (int y = 0; y < CONSOLE_HEIGHT; ++y) {
            pantalla[y][0] = pantalla[y][CONSOLE_WIDTH - 1] = "▓";
        }
        std::cout << WindowsConsole::Colors::RESET;
    }

    void drawObject(std::vector<std::vector<std::string>>& pantalla, int x, int y, const std::string& sym){
        if(x>0&& x<CONSOLE_WIDTH && y>0 && y<CONSOLE_HEIGHT) //Verifica que está en los límites del escenario
            pantalla[y][x] = sym; //Agrega el objeto dentro del espacio de la matríz
    }


}