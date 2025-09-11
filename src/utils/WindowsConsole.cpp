#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>
#endif

namespace WindowsConsole {
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void setCursorPosition(int x, int y) {
        #ifdef _WIN32
            COORD coord;
            coord.X = x;
            coord.Y = y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
            std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
        #endif
    }
    
    void hideCursor() {
        #ifdef _WIN32
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
            cursorInfo.bVisible = false;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        #else
            std::cout << "\033[?25l";
        #endif
    }
    
    void showCursor() {
        #ifdef _WIN32
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
            cursorInfo.bVisible = true;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        #else
            std::cout << "\033[?25h";
        #endif
    }
    
    void setConsoleTitle(const std::string& title) {
        #ifdef _WIN32
            SetConsoleTitleA(title.c_str());
        #else
            std::cout << "\033]0;" << title << "\007";
        #endif
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