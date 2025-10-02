#include "../../include/rendering/GameDialog.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <string>

namespace GameDialog {

const int CONSOLE_WIDTH = 80;

bool showSaveDialog() {
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    
    std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
    std::cout << "\n\n" << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "╔══════════════════════════════════════╗\n";
    std::cout << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "║                                      ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "║        ¿Guardar tu puntaje?          ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "║                                      ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "║        [S] Sí    [N] No              ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "║                                      ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 40) / 2, ' ') << "╚══════════════════════════════════════╝\n";
    std::cout << WindowsConsole::Colors::RESET;
    
    char choice;
    while (true) {
        std::cin >> choice;
        if (choice == 's' || choice == 'S') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        }
    }
}

std::string getPlayerName() {
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    
    std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
    std::cout << "\n\n" << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "╔════════════════════════════════════════════════╗\n";
    std::cout << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "║                                                ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "║            Ingresa tu nombre:                  ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "║                                                ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "║  > ";
    std::cout << WindowsConsole::Colors::BRIGHT_WHITE;
    
    std::string playerName;
    std::getline(std::cin, playerName); // Limpiar buffer
    std::getline(std::cin, playerName); // Obtener nombre real
    
    // Limitar longitud del nombre
    if (playerName.length() > 15) {
        playerName = playerName.substr(0, 15);
    }
    if (playerName.empty()) {
        playerName = "Jugador";
    }
    
    std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
    std::cout << "\n" << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "║                                                ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 50) / 2, ' ') << "╚════════════════════════════════════════════════╝\n";
    std::cout << WindowsConsole::Colors::RESET;
    
    return playerName;
}

void showSaveConfirmation() {
    WindowsConsole::clearScreen();
    std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
    std::cout << "\n\n" << std::string((CONSOLE_WIDTH - 30) / 2, ' ') << "╔════════════════════════════╗\n";
    std::cout << std::string((CONSOLE_WIDTH - 30) / 2, ' ') << "║                            ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 30) / 2, ' ') << "║    ¡Puntaje guardado!      ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 30) / 2, ' ') << "║                            ║\n";
    std::cout << std::string((CONSOLE_WIDTH - 30) / 2, ' ') << "╚════════════════════════════╝\n";
    std::cout << WindowsConsole::Colors::RESET;
}

} // namespace GameDialog