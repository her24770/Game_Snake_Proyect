#include "../include/rendering/ASCIIArt.hpp"
#include "../include/utils/InputHandler.hpp"
#include "../include/core/ThreadSharedData.hpp"
#include "../include/threads/InputThread.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h>

int main() {
    system("stty -icanon -echo");
    
    SharedGameData sharedData;
    pthread_t inputThread;
    pthread_create(&inputThread, nullptr, inputThreadFunction, &sharedData);
    
    int selectedOption = 0;
    int screen = 0;
    
    // Dibujar menú inicial
    system("clear");
    ASCIIArt::drawMainMenu(selectedOption);
    
    while (true) {
        int key = sharedData.getKey();

        // AGREGAR ESTA LÍNEA
    if(key != InputHandler::KEY_NONE) {
        std::cout << "[MAIN] Tecla recibida: " << key << std::endl;
    }
        
        if (key != InputHandler::KEY_NONE) {
            if (screen == 0) {
                // Menu principal
                if (key == InputHandler::KEY_UP) {
                    selectedOption = (selectedOption - 1 + 4) % 4;
                }
                else if (key == InputHandler::KEY_DOWN) {
                    selectedOption = (selectedOption + 1) % 4;
                }
                else if (key == InputHandler::KEY_ENTER) {
                    if (selectedOption == 3) break;
                    screen = selectedOption + 1;
                }
                
                // Redibujar menú
                system("clear");
                if (screen == 0) {
                    ASCIIArt::drawMainMenu(selectedOption);
                } else if (screen == 1) {
                    ASCIIArt::drawGame(key);
                } else if (screen == 2) {
                    ASCIIArt::drawInstructions();
                } else if (screen == 3) {
                    ASCIIArt::drawScoreboard();
                }
            }
            else {
                // Subpantallas
                if (key == InputHandler::KEY_ESC) {
                    screen = 0;
                    system("clear");
                    ASCIIArt::drawMainMenu(selectedOption);
                }
            }
        }
        
        usleep(16000);
    }
    
    sharedData.stop();
    pthread_join(inputThread, nullptr);
    system("stty icanon echo");
    
    return 0;
}