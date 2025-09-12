#include "../../include/rendering/ASCIIArt.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <iomanip>

namespace ASCIIArt {
    
    void drawMainMenu(int selectedOption) {
    system("clear");
    
    std::cout << "\n\n";
    std::cout << "  ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗\n";
    std::cout << "  ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝\n"; 
    std::cout << "  ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  \n";
    std::cout << "  ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  \n";
    std::cout << "  ███████║██║ ╚████║██║  ██║██║  ██╗███████╗\n\n";

    // AQUÍ USA EL PARÁMETRO selectedOption
    std::cout << (selectedOption == 0 ? " > " : "   ") << "1. Jugar\n";
    std::cout << (selectedOption == 1 ? " > " : "   ") << "2. Instrucciones\n"; 
    std::cout << (selectedOption == 2 ? " > " : "   ") << "3. Puntajes\n";
    std::cout << (selectedOption == 3 ? " > " : "   ") << "4. Salir\n";
    
    std::cout << "\nUsa ↑↓ para navegar, ENTER para seleccionar\n";
}

// Pantallas simples
void drawGame() {
    system("clear");
    std::cout << "\n\n=== JUGANDO ===\n\nESC para volver\n";
}

void drawInstructions() {
    system("clear");  
    std::cout << "\n\n=== INSTRUCCIONES ===\n\nESC para volver\n";
}

void drawScoreboard() {
    system("clear");
    std::cout << "\n\n=== PUNTAJES ===\n\nESC para volver\n";  
}
}