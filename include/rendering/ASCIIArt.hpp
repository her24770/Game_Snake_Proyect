#ifndef ASCII_ART_HPP
#define ASCII_ART_HPP

#include <string>
#include <vector>

namespace ASCIIArt {
    
    // Constantes para dimensiones de pantalla
    const int CONSOLE_WIDTH = 80;
    const int CONSOLE_HEIGHT = 25;
    
    // Funciones principales de renderizado
    void drawMainMenu();
    void drawGameTitle();
    void drawMenuBorder();
    void drawMenuOptions();
    void drawFooter();
    void drawPrincipalStagePreview();
    
    // Funciones auxiliares de diseño
    void drawHorizontalLine(int width, char character = '=');
    void drawVerticalBorder(const std::string& content, int totalWidth);
    std::string centerString(const std::string& text, int width);
    std::string padString(const std::string& text, int width, char padChar = ' ');
    void drawBorder_PS(std::vector<std::string>& pantalla);
    void drawObject(std::vector<std::string>& pantalla, int x, int y, const std::string& sym);
    
    // Arte ASCII específico
    void drawSnakeTitle();
    void drawSnakeArt();
    void drawDecorations();
    
    // Utilidades de formato
    std::vector<std::string> getSnakeTitleArt();
    std::vector<std::string> getMenuFrameArt();
    void printCenteredLine(const std::string& text);
    void printColoredCenteredLine(const std::string& text, const std::string& color);
}

#endif // ASCII_ART_HPP