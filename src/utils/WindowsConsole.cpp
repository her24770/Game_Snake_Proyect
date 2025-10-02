#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

namespace WindowsConsole {
    
    void clearScreen() {

        system("clear");
    }
    
    void setCursorPosition(int x, int y) {

        std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
        
    }
    
    void hideCursor() {
      
        std::cout << "\033[?25l";
        
    }
    
    void showCursor() {
        std::cout << "\033[?25h";
    }
    
    void setConsoleTitle(const std::string& title) {
        std::cout << "\033]0;" << title << "\007";
    }
    
    void pauseExecution() {
        std::cout << "\nPresiona Enter para continuar...";
        std::cin.get();
    }
    
    void setTextColor(const std::string& color) {
        std::cout << color;
    }
    
    void resetTextColor() {
        std::cout << Colors::RESET;
    }
    
    std::string colorText(const std::string& text, const std::string& color) {
        return color + text + Colors::RESET;
    }
    
    void centerText(const std::string& text, int consoleWidth) {
        int padding = (consoleWidth - text.length()) / 2;
        if (padding > 0) {
            std::cout << std::string(padding, ' ');
        }
        std::cout << text << std::endl;
    }
    
    void printAtPosition(int x, int y, const std::string& text) {
        setCursorPosition(x, y);
        std::cout << text;
    }
    
    void printColoredAtPosition(int x, int y, const std::string& text, const std::string& color) {
        setCursorPosition(x, y);
        std::cout << colorText(text, color);
    }
}