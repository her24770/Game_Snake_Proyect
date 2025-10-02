#ifndef WINDOWS_CONSOLE_HPP
#define WINDOWS_CONSOLE_HPP

#include <iostream>
#include <string>

namespace WindowsConsole {
    
    // Códigos de color ANSI para consola
    namespace Colors {
        const std::string RESET = "\033[0m";
        const std::string BLACK = "\033[30m";
        const std::string RED = "\033[31m";
        const std::string GREEN = "\033[32m";
        const std::string YELLOW = "\033[33m";
        const std::string BLUE = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN = "\033[36m";
        const std::string WHITE = "\033[37m";
        
        // Colores brillantes
        const std::string BRIGHT_BLACK = "\033[90m";
        const std::string BRIGHT_RED = "\033[91m";
        const std::string BRIGHT_GREEN = "\033[92m";
        const std::string BRIGHT_YELLOW = "\033[93m";
        const std::string BRIGHT_BLUE = "\033[94m";
        const std::string BRIGHT_MAGENTA = "\033[95m";
        const std::string BRIGHT_CYAN = "\033[96m";
        const std::string BRIGHT_WHITE = "\033[97m";
    }
    
    // Funciones principales de control de consola
    void clearScreen();
    void setCursorPosition(int x, int y);
    void hideCursor();
    void showCursor();
    void setConsoleTitle(const std::string& title);
    void pauseExecution();
    
    // Funciones de utilidad para colores
    void setTextColor(const std::string& color);
    void resetTextColor();
    std::string colorText(const std::string& text, const std::string& color);
    
    // Funciones de utilidad para posicionamiento
    void centerText(const std::string& text, int consoleWidth = 80);
    void printAtPosition(int x, int y, const std::string& text);
    void printColoredAtPosition(int x, int y, const std::string& text, const std::string& color);
}

#endif // WINDOWS_CONSOLE_HPP