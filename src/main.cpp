#include "../include/rendering/ASCIIArt.hpp"
#include "../include/utils/WindowsConsole.hpp"
#include <iostream>

int main() {
    try {
        // Configurar la consola para mostrar caracteres UTF-8/Unicode
        #ifdef _WIN32
            system("chcp 65001 > nul");
        #endif
        
        // Mostrar el menú principal
        ASCIIArt::drawMainMenu();
        
        WindowsConsole::pauseExecution();

        ASCIIArt::drawPrincipalStagePreview();

        // Mensaje informativo para el usuario
        std::cout << WindowsConsole::Colors::BRIGHT_WHITE;
        std::cout << "\n\n";
        ASCIIArt::printCenteredLine("═══════════════════════════════════════════════");
        ASCIIArt::printCenteredLine("   VISTA PREVIA - FASE 2: ENTORNO GRÁFICO");
        ASCIIArt::printCenteredLine("        (Sin funcionalidad por ahora)");
        ASCIIArt::printCenteredLine("═══════════════════════════════════════════════");
        std::cout << WindowsConsole::Colors::RESET;
        
        // Pausa para que el usuario pueda ver el menú
        WindowsConsole::pauseExecution();
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}