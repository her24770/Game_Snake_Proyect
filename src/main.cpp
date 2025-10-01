#include "../include/rendering/ASCIIArt.hpp"
#include "../include/rendering/Game.hpp"
#include "../include/utils/InputHandler.hpp"
#include "../include/core/ThreadSharedData.hpp"
#include "../include/core/Snake.hpp"
#include "../include/threads/InputThread.hpp"
#include "../include/threads/MovementThread.hpp"
#include "../include/threads/RenderThread.hpp"
#include "../include/core/Food.hpp"
#include "../include/threads/FoodThread.hpp"
#include "../include/threads/CollisionThread.hpp"
#include "../include/threads/AudioThread.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include <mutex>

int main() {
    system("stty -icanon -echo");
    
    SharedGameData sharedData;
    pthread_t inputThread;
    pthread_create(&inputThread, nullptr, inputThreadFunction, &sharedData);
    
    int selectedOption = 0;
    int screen = 0;

    
    // Preparar datos para hilos de movimiento
    struct ThreadData {
        Snake* snake;
        SharedGameData* sharedData;
        int playerId;
        bool* runningMovement;
    };
    
    std::queue<std::string> soundQueue;
    std::mutex audioMutex;
    std::condition_variable audioCondition;
    bool runningAudio = true;
    
    AudioThreadData audioData = {
        &runningAudio,
        &soundQueue,
        &audioMutex,
        &audioCondition
    };
    
    pthread_t audioThread;
    pthread_create(&audioThread, nullptr, audioThreadFunction, &audioData);
    
    // Dibujar menú inicial
    system("clear");
    ASCIIArt::drawMainMenu(selectedOption);
    
    while (true) {
        int key1 = sharedData.getKey();
        int key2 = sharedData.getKey2();
        
        int key = (key1 != InputHandler::KEY_NONE) ? key1 : key2; // Prioriza key1 si existe
        
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
                    sharedData.getKey();
                    sharedData.getKey2();
                    //Se crean las serpientes con una coordenada inicial
                    Snake snake1(10,8);
                    Snake snake2(10,16);
                    Food food;
                    //Se almacenan los parametros par alos hilos de movimiento 
                    ThreadData snake1Data = { &snake1, &sharedData, 1 };
                    ThreadData snake2Data = { &snake2, &sharedData, 2 };
                    bool runningMovement = true;
                    bool runningRender = true;
                    bool gameOver = false;
                    
                    RenderThreadData renderData = { &snake1, &snake2, &food, &sharedData, &runningRender };
                    
                    snake1Data.runningMovement = &runningMovement;
                    snake2Data.runningMovement = &runningMovement;
                    //Se crean hilos para el movimiento de las serpientes y reescritura del escenario
                    FoodThreadData foodData = { &food, &snake1, &snake2, &sharedData, &runningMovement };
                    CollisionThreadData collisionData = { &snake1, &snake2, &sharedData, &runningMovement, &gameOver, &audioData };

                    pthread_t renderThread, snake1Thread, snake2Thread, foodThread, collisionThread;

                    pthread_create(&snake1Thread, nullptr, snakeMovementThread, &snake1Data);
                    pthread_create(&snake2Thread, nullptr, snakeMovementThread, &snake2Data);
                    pthread_create(&foodThread, nullptr, foodThreadFunction, &foodData);
                    pthread_create(&collisionThread, nullptr, collisionThreadFunction, &collisionData);
                    pthread_create(&renderThread, nullptr, renderThreadFunction, &renderData);

                    // Bucle de control de pantalla (para ESC y Game Over)
                    bool escPressed = false;
                    while(screen == 1 && !gameOver) {
                        {
                            std::lock_guard<std::mutex> lock(sharedData.mtx);
                            if(sharedData.keyPlayer1 == InputHandler::KEY_ESC || 
                               sharedData.keyPlayer2 == InputHandler::KEY_ESC) {
                                escPressed = true;
                                // Limpiar ESC para que no interfiera
                                sharedData.keyPlayer1 = InputHandler::KEY_NONE;
                                sharedData.keyPlayer2 = InputHandler::KEY_NONE;
                            }
                        }
                        usleep(16000);
                    }
                    if(escPressed) screen = 0;
                    // Mostrar pantalla Game Over si hubo colisión
                    runningMovement = false;
                    runningRender = false;

                    // Esperar a que terminen los hilos antes de mostrar Game Over
                    pthread_join(snake1Thread, nullptr);
                    pthread_join(snake2Thread, nullptr);
                    pthread_join(foodThread, nullptr);
                    pthread_join(collisionThread, nullptr);
                    pthread_join(renderThread, nullptr);

                    // Ahora sí mostrar Game Over
                    if(gameOver) {
                        GAME::renderGameOver(snake1, snake2);
                        sleep(5);
                        screen = 0;
                    }
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