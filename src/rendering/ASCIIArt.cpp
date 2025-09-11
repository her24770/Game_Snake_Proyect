#include "../../include/rendering/ASCIIArt.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <iomanip>

namespace ASCIIArt {
    
    void drawMainMenu() {
        WindowsConsole::clearScreen();
        WindowsConsole::hideCursor();
        WindowsConsole::setConsoleTitle("Snake Game - Menu Principal");
        
        std::cout << std::endl;
        drawMenuBorder();
        drawGameTitle();
        drawSnakeArt();
        drawMenuOptions();
        drawFooter();
        drawMenuBorder();
        
        WindowsConsole::showCursor();
    }
    
    void drawGameTitle() {
        std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
        
        // Arte ASCII para "SNAKE GAME"
        std::vector<std::string> title = {
            "  ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗",
            "  ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝",
            "  ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ",
            "  ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ",
            "  ███████║██║ ╚████║██║  ██║██║  ██╗███████╗",
            "  ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝",
            "",
            "   ██████╗  █████╗ ███╗   ███╗███████╗",
            "  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
            "  ██║  ███╗███████║██╔████╔██║█████╗  ",
            "  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
            "  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
            "   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"
        };
        
        for (const auto& line : title) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }
    
    void drawMenuBorder() {
        std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
        std::string border = "╔" + std::string(CONSOLE_WIDTH - 2, '═') + "╗";
        printCenteredLine(border);
        std::cout << WindowsConsole::Colors::RESET;
    }
    
    void drawSnakeArt() {
        std::cout << WindowsConsole::Colors::BRIGHT_YELLOW << std::endl;
        
        // Arte ASCII de una serpiente
        std::vector<std::string> snake = {
            "                    ╭─────╮",
            "              ╭─────┤ ◉ ◉ ├─╮",
            "        ╭─────┤     ╰─┬─┬─╯ │",
            "  ╭─────┤       ╭─────┤ │   │",
            "  │     ╰─────────┤   ╰─╯   │",
            "  ╰─────────────────╯       │",
            "                          ╭─╯",
            "                        ╭─╯",
            "                      ╭─╯",
            "                    ╭─╯"
        };
        
        for (const auto& line : snake) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }
    
    void drawMenuOptions() {
        std::cout << WindowsConsole::Colors::BRIGHT_WHITE;
        
        // Marco para las opciones
        std::string topFrame = "╔══════════════════════════════════╗";
        std::string bottomFrame = "╚══════════════════════════════════╝";
        std::string sideFrame = "║";
        
        printCenteredLine(topFrame);
        
        // Opciones del menú con formato
        std::vector<std::string> options = {
            "║           MENU PRINCIPAL          ║",
            "║                                  ║",
            "║  ➤  1. Jugar                     ║",
            "║                                  ║",
            "║  ➤  2. Instrucciones             ║",
            "║                                  ║",
            "║  ➤  3. Ver Puntajes              ║",
            "║                                  ║",
            "║  ➤  4. Salir del Juego           ║",
            "║                                  ║"
        };
        
        for (const auto& option : options) {
            printCenteredLine(option);
        }
        
        printCenteredLine(bottomFrame);
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }
    
    void drawFooter() {
        std::cout << WindowsConsole::Colors::BRIGHT_MAGENTA;
        
        std::vector<std::string> footer = {
            "",
            "┌─────────────────────────────────────────────┐",
            "│        Proyecto SnakeGame-CPP-Multihilo     │",
            "│              Fase 2: Entorno Gráfico       │",
            "└─────────────────────────────────────────────┘",
            ""
        };
        
        for (const auto& line : footer) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET;
    }
    
    void drawHorizontalLine(int width, char character) {
        std::cout << std::string(width, character) << std::endl;
    }
    
    void drawVerticalBorder(const std::string& content, int totalWidth) {
        int padding = (totalWidth - content.length()) / 2;
        std::cout << "║" << std::string(padding, ' ') << content 
                  << std::string(totalWidth - content.length() - padding, ' ') << "║" << std::endl;
    }
    
    std::string centerString(const std::string& text, int width) {
        int padding = (width - text.length()) / 2;
        return std::string(padding, ' ') + text + std::string(width - text.length() - padding, ' ');
    }
    
    std::string padString(const std::string& text, int width, char padChar) {
        if (text.length() >= width) return text;
        int leftPad = (width - text.length()) / 2;
        int rightPad = width - text.length() - leftPad;
        return std::string(leftPad, padChar) + text + std::string(rightPad, padChar);
    }
    
    void drawDecorations() {
        std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
        printCenteredLine("◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇");
        std::cout << WindowsConsole::Colors::RESET;
    }
    
    std::vector<std::string> getSnakeTitleArt() {
        return {
            "███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗",
            "██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝",
            "███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ",
            "╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ",
            "███████║██║ ╚████║██║  ██║██║  ██╗███████╗",
            "╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝"
        };
    }
    
    std::vector<std::string> getMenuFrameArt() {
        return {
            "╔════════════════════════════════════════════╗",
            "║                                            ║",
            "║                                            ║",
            "╚════════════════════════════════════════════╝"
        };
    }
    
    void printCenteredLine(const std::string& text) {
        int padding = (CONSOLE_WIDTH - text.length()) / 2;
        if (padding > 0) {
            std::cout << std::string(padding, ' ');
        }
        std::cout << text << std::endl;
    }
    
    void printColoredCenteredLine(const std::string& text, const std::string& color) {
        std::cout << color;
        printCenteredLine(text);
        std::cout << WindowsConsole::Colors::RESET;
    }
}