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
#include "../include/threads/TimerThread.hpp"
#include "../include/threads/CollisionThread.hpp"
#include "../include/threads/AudioThread.hpp"
#include "../include/threads/SFXThread.hpp"
#include "../include/threads/ScoreThread.hpp"
#include "../include/threads/ScoreThreads.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h>

int main() {
    system("stty -icanon -echo");
    
    SharedGameData sharedData;
    pthread_t inputThread;
    pthread_create(&inputThread, nullptr, inputThreadFunction, &sharedData);
    //Efectos de sonido
    SFXData sfxData;
    sfxData.running.store(true);
    
    pthread_t sfxThread;
    pthread_create(&sfxThread, nullptr, sfxThreadFunction, &sfxData);

    //Audio
    AudioThreadData audioData;
    audioData.currentTrack.store(AUDIO_MENU);
    audioData.running.store(true);
    audioData.shouldChange.store(false);

    pthread_t audioThread;
    pthread_create(&audioThread, nullptr, audioThreadFunction, &audioData);

    //temporizador
    TimerThreadData timerData;
    timerData.running.store(true);
    timerData.counting.store(false);
    timerData.totalSeconds.store(0);

    pthread_t timerThread;
    pthread_create(&timerThread, nullptr, timerThreadFunction, &timerData);

    //Puntajes
    ScoreThreadData scoreData;
    scoreData.running.store(true);
    scoreData.needsUpdate.store(false);

    pthread_t scoreThread;
    pthread_create(&scoreThread, nullptr, scoreThreadFunction, &scoreData);
    
    const int MENU_OPCIONES = 6;
    const int SPEED_OPTION = 4; 
    int selectedOption = 0;
    int screen = 0;
    int lastScreen = -1;
    int speedIndex = 1; // 0=Lento,1=Medio,2=Rápido
    int velocidad = 150000; // default value (Medio)

    // helper para actualizar velocidad desde speedIndex
    auto updateVelFromIndex = [&](int idx) {
        switch(idx) {
            case 0: velocidad = 250000; break; // Lento
            case 1: velocidad = 80000; break; // Medio
            case 2: velocidad = 40000;  break; // Rápido
            default: velocidad = 150000; break;
        }
    };
    updateVelFromIndex(speedIndex);

    // Preparar datos para hilos de movimiento
    struct ThreadData {
        Snake* snake;
        SharedGameData* sharedData;
        int playerId;
        bool* runningMovement;
        int velocidad;
    };
    
    // Dibujar menú inicial
    system("clear");
    ASCIIArt::drawMainMenu(selectedOption, speedIndex);
    
    while (true) {
        int key1 = sharedData.getKey();
        int key2 = sharedData.getKey2();
        
        int key = (key1 != InputHandler::KEY_NONE) ? key1 : key2; // Prioriza key1 si existe
        // Cambiar audio según pantalla
        if(screen != lastScreen) {
            if(screen == 1) {
                audioData.currentTrack.store(AUDIO_GAME);
            } else {
                audioData.currentTrack.store(AUDIO_MENU);
            }
            audioData.shouldChange.store(true);
            lastScreen = screen;
        }
        
        if(key != InputHandler::KEY_NONE) {
            std::cout << "[MAIN] Tecla recibida: " << key << std::endl;
        }
        
        if (key != InputHandler::KEY_NONE) {
            if (screen == 0) {
                // Menu principal
                if (key == InputHandler::KEY_UP) {
                    selectedOption = (selectedOption - 1 + MENU_OPCIONES) % MENU_OPCIONES;
                }
                else if (key == InputHandler::KEY_DOWN) {
                    selectedOption = (selectedOption + 1) % MENU_OPCIONES;
                }
                else if (key == InputHandler::KEY_LEFT && selectedOption == SPEED_OPTION) {
                    speedIndex = (speedIndex - 1 + 3) % 3;
                    updateVelFromIndex(speedIndex);
                }
                else if (key == InputHandler::KEY_RIGHT && selectedOption == SPEED_OPTION) {
                    speedIndex = (speedIndex + 1) % 3;
                    updateVelFromIndex(speedIndex);
                }
                else if (key == InputHandler::KEY_ENTER) {
                    if (selectedOption == MENU_OPCIONES - 1) break;
                    screen = selectedOption + 1;
                }
                
                // Redibujar menú
                system("clear");
                if (screen == 0) {
                    ASCIIArt::drawMainMenu(selectedOption, speedIndex);
                } 
                else if (screen == 1) {
                    sharedData.getKey();
                    sharedData.getKey2();
                    Snake snake1(10,8);
                    // Iniciar cronómetro
                    timerData.totalSeconds.store(0);
                    timerData.counting.store(true);
                    Food food;

                    ThreadData snake1Data = { &snake1, &sharedData, 1, nullptr, velocidad };
                    bool runningMovement = true;
                    bool runningRender = true;
                    bool gameOver = false;
                    
                    RenderThreadData renderData = { &snake1, nullptr, &food, &sharedData, &runningRender };
                    
                    snake1Data.runningMovement = &runningMovement;

                    FoodThreadData foodData = { &food, &snake1, nullptr, &sharedData, &runningMovement, &sfxData};
                    CollisionThreadData collisionData = { &snake1, nullptr, &sharedData, &runningMovement, &gameOver, &sfxData};

                    pthread_t renderThread, snake1Thread, foodThread, collisionThread;

                    pthread_create(&snake1Thread, nullptr, snakeMovementThread, &snake1Data);
                    pthread_create(&foodThread, nullptr, foodThreadFunction, &foodData);
                    pthread_create(&collisionThread, nullptr, collisionThreadFunction, &collisionData);
                    pthread_create(&renderThread, nullptr, renderThreadFunction, &renderData);

                    bool escPressed = false;
                    while(screen == 1 && !gameOver) {
                        {
                            std::lock_guard<std::mutex> lock(sharedData.mtx);
                            if(sharedData.keyPlayer1 == InputHandler::KEY_ESC) {
                                escPressed = true;
                                sharedData.keyPlayer1 = InputHandler::KEY_NONE;
                            }
                        }
                        usleep(16000);
                    }
                    if(escPressed) screen = 0;
                    runningMovement = false;
                    runningRender = false;

                    pthread_join(snake1Thread, nullptr);
                    pthread_join(foodThread, nullptr);
                    pthread_join(collisionThread, nullptr);
                    pthread_join(renderThread, nullptr);

                    if(gameOver) {
                        timerData.counting.store(false);
                        int finalTime = timerData.totalSeconds.load();
                        GAME::renderGameOver(snake1, snake1, finalTime);
                        int lowestTop = getLowestTopScore(&scoreData);
                        if(snake1.getPuntuacion() > lowestTop){
                            std::string nombre;
                            std::cout << "Nueva puntuacion alta, ingrese el nombre: ";
                            std::cin >> nombre;

                            // Convertir segundos a mm:ss
                            int segundos = finalTime;
                            int minutos = segundos / 60;
                            segundos = segundos % 60;
                            char tiempoStr[6];
                            snprintf(tiempoStr, sizeof(tiempoStr), "%02d:%02d", minutos, segundos);

                            // Crear datos para el hilo
                            ScoreThreadsData* scoreData = new ScoreThreadsData{nombre, snake1.getPuntuacion(), tiempoStr, "assets/scores.csv"};

                            pthread_t scoreThread;
                            pthread_create(&scoreThread, nullptr, writeScoreThread, scoreData);
                            pthread_detach(scoreThread); // No bloquea el main
                        }
                        sleep(5);
                        screen = 0;
                    }
                }
                else if (screen == 2) {
                    sharedData.getKey();
                    sharedData.getKey2();
                    Snake snake1(10,8);
                    Snake snake2(10,16);
                    // Iniciar cronómetro
                    timerData.totalSeconds.store(0);
                    timerData.counting.store(true);
                    Food food;

                    ThreadData snake1Data = { &snake1, &sharedData, 1, nullptr, velocidad };
                    ThreadData snake2Data = { &snake2, &sharedData, 2, nullptr, velocidad };
                    bool runningMovement = true;
                    bool runningRender = true;
                    bool gameOver = false;
                    
                    RenderThreadData renderData = { &snake1, &snake2, &food, &sharedData, &runningRender };
                    
                    snake1Data.runningMovement = &runningMovement;
                    snake2Data.runningMovement = &runningMovement;

                    FoodThreadData foodData = { &food, &snake1, &snake2, &sharedData, &runningMovement };
                    CollisionThreadData collisionData = { &snake1, &snake2, &sharedData, &runningMovement, &gameOver };

                    pthread_t renderThread, snake1Thread, snake2Thread, foodThread, collisionThread;

                    pthread_create(&snake1Thread, nullptr, snakeMovementThread, &snake1Data);
                    pthread_create(&snake2Thread, nullptr, snakeMovementThread, &snake2Data);
                    pthread_create(&foodThread, nullptr, foodThreadFunction, &foodData);
                    pthread_create(&collisionThread, nullptr, collisionThreadFunction, &collisionData);
                    pthread_create(&renderThread, nullptr, renderThreadFunction, &renderData);

                    bool escPressed = false;
                    while(screen == 2 && !gameOver) {
                        {
                            std::lock_guard<std::mutex> lock(sharedData.mtx);
                            if(sharedData.keyPlayer1 == InputHandler::KEY_ESC || 
                               sharedData.keyPlayer2 == InputHandler::KEY_ESC) {
                                escPressed = true;
                                sharedData.keyPlayer1 = InputHandler::KEY_NONE;
                                sharedData.keyPlayer2 = InputHandler::KEY_NONE;
                            }
                        }
                        usleep(16000);
                    }
                    if(escPressed) screen = 0;
                    runningMovement = false;
                    runningRender = false;

                    pthread_join(snake1Thread, nullptr);
                    pthread_join(snake2Thread, nullptr);
                    pthread_join(foodThread, nullptr);
                    pthread_join(collisionThread, nullptr);
                    pthread_join(renderThread, nullptr);

                    if(gameOver) {
                        timerData.counting.store(false);
                        int finalTime = timerData.totalSeconds.load();
                        GAME::renderGameOver(snake1, snake2, finalTime);
                        int lowestTop = getLowestTopScore(&scoreData);
                        if(snake1.getPuntuacion() > lowestTop){
                            std::string nombre;
                            std::cout << "Nueva puntuacion alta para el jugador 1, ingrese el nombre: ";
                            std::cin >> nombre;

                            // Convertir segundos a mm:ss
                            int segundos = finalTime;
                            int minutos = segundos / 60;
                            segundos = segundos % 60;
                            char tiempoStr[6];
                            snprintf(tiempoStr, sizeof(tiempoStr), "%02d:%02d", minutos, segundos);

                            // Crear datos para el hilo
                            ScoreThreadsData* scoreData = new ScoreThreadsData{nombre, snake1.getPuntuacion(), tiempoStr, "assets/scores.csv"};

                            pthread_t scoreThread;
                            pthread_create(&scoreThread, nullptr, writeScoreThread, scoreData);
                            pthread_detach(scoreThread); // No bloquea el main
                        }
                        if(snake2.getPuntuacion() > lowestTop){
                            std::string nombre;
                            std::cout << "Nueva puntuacion alta para el jugador 2, ingrese el nombre: ";
                            std::cin >> nombre;

                            // Convertir segundos a mm:ss
                            int segundos = finalTime;
                            int minutos = segundos / 60;
                            segundos = segundos % 60;
                            char tiempoStr[6];
                            snprintf(tiempoStr, sizeof(tiempoStr), "%02d:%02d", minutos, segundos);

                            // Crear datos para el hilo
                            ScoreThreadsData* scoreData = new ScoreThreadsData{nombre, snake2.getPuntuacion(), tiempoStr, "assets/scores.csv"};

                            pthread_t scoreThread;
                            pthread_create(&scoreThread, nullptr, writeScoreThread, scoreData);
                            pthread_detach(scoreThread); // No bloquea el main
                        }
                        sleep(5);
                        screen = 0;
                    }
                }
                else if (screen == 3) {
                    ASCIIArt::drawInstructions();
                } else if (screen == 4) {
                    ASCIIArt::drawScoreboard(&scoreData);
                }
            }
            else {
                if (key == InputHandler::KEY_ESC) {
                    screen = 0;
                    system("clear");
                    ASCIIArt::drawMainMenu(selectedOption, speedIndex);
                }
            }
        }
        usleep(16000);
    }
    
    sharedData.stop();
    audioData.running.store(false);
    sfxData.running.store(false);
    timerData.running.store(false);
    scoreData.running.store(false);



    pthread_join(inputThread, nullptr);
    pthread_join(audioThread, nullptr);
    pthread_join(sfxThread, nullptr);
    pthread_join(timerThread, nullptr);
    pthread_join(scoreThread, nullptr);


    system("stty icanon echo");
    
    return 0;
}
