#include "../include/rendering/ASCIIArt.hpp"
#include "../include/utils/InputHandler.hpp"
#include <iostream>

int main() {
    system("stty -icanon -echo");  // Configurar terminal Linux
    
    int selectedOption = 0;
    int screen = 0; // 0=menu, 1=jugar, 2=instrucciones, 3=puntajes
    
    while (true) {
        if (screen == 0) {
            system("clear");  // 🔹 LIMPIAR PANTALLA ANTES DE DIBUJAR MENÚ
            ASCIIArt::drawMainMenu(selectedOption);  
            
            int key = InputHandler::getUserInput();
            
            if (key == InputHandler::KEY_UP) {
                selectedOption = (selectedOption - 1 + 4) % 4;
            }
            else if (key == InputHandler::KEY_DOWN) {
                selectedOption = (selectedOption + 1) % 4;  
            }
            else if (key == InputHandler::KEY_ENTER) {
                if (selectedOption == 3) break; // Salir
                screen = selectedOption + 1; // Ir a pantalla
            }
        }
        else {
            system("clear");  // LIMPIAR PANTALLA ANTES DE MOSTRAR SUBPANTALLAS
            if (screen == 1) ASCIIArt::drawGame();
            else if (screen == 2) ASCIIArt::drawInstructions(); 
            else if (screen == 3) ASCIIArt::drawScoreboard();
            
            int key = InputHandler::getUserInput();
            if (key == InputHandler::KEY_ESC) screen = 0; // Volver al menú
        }
    }
    
    system("stty icanon echo");  // Restaurar terminal
    return 0;
}
