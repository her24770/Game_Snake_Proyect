# Game_Snake_Proyect

## Descripción General
Este proyecto implementa el clásico juego Snake utilizando programación multihilo con Pthreads en entorno Windows. El juego cuenta con dos modos: un jugador y dos jugadores, con gráficos ASCII en consola y mecanismos de sincronización para gestionar el estado del juego de forma concurrente.


## Equipo de desarrollo
- Josué Hernández Gonzales - 24770
- René Oswaldo Abella González - 24290
- Jackelyn Nicolle Girón Villacinda - 24737
- Sergio Estuardo Tan Coromac - 24759
Estudiantes de Universidad del Valle de Guatemala
Facultad de Ingeniería
CC3086 - Programación de Microprocesadores
Ciclo 2, 2025


## Caracteristicas
- Modo un jugador y dos jugadores
- Gràficos ASCII-Art en consola
- Sistema de puntuación y records
- 10+ hilos concurrentes para diferentes funcionalidades
- Menú navegable con instrucciones y puntajes
- Sonidos mediante Beep() de Windows API

## Estructura del Proyecto

snake_game/
│
├── docs/                       # Documentación
│   ├── Fase1_Planificacion.pdf
│   ├── Fase2_EntornoGrafico.pdf
│   └── Fase3_Final.pdf
│
├── include/                    # Headers
│   ├── core/
│   │   ├── GameConstants.hpp   # Constantes (ANCHO, ALTO, SÍMBOLOS ASCII)
│   │   ├── GameState.hpp       # Structs: Snake, Food, GameState
│   │   └── ThreadSharedData.hpp # Datos compartidos + mutex/cond vars
│   │
│   ├── rendering/              # VISUALIZACIÓN
│   │   ├── ASCIIArt.hpp        # Menús, instrucciones, puntajes (ASCII)
│   │   └── RenderEngine.hpp    # Dibujar tablero, serpiente, comida
│   │
│   ├── utils/                  # Utilidades
│   │   ├── WindowsConsole.hpp  # Control de consola Windows (cursor, color)
│   │   ├── RandomGenerator.hpp # Generar números aleatorios (comida)
│   │   └── InputHandler.hpp    # Lectura de teclado no bloqueante
│   │
│   └── threads/                # HILOS
│       ├── InputThread.hpp     # Hilo: leer teclado
│       ├── RenderThread.hpp    # Hilo: dibujar en consola
│       ├── GameThreads.hpp     # Hilos: movimiento, comida, colisiones
|       |── Synchronization.hpp # Mutex, condition variables
│       └── ... (Demas hilos) ...
│
├── src/                        # Código fuente
│   ├── core/
│   │   ├── GameState.cpp
│   │   └── ThreadSharedData.cpp
│   │
│   ├── rendering/              # IMPLEMENTACIÓN VISUAL 
│   │   ├── ASCIIArt.cpp        # Implementación menús ASCII
│   │   └── RenderEngine.cpp    # Implementación dibujo juego
│   │
│   ├── utils/
│   │   ├── WindowsConsole.cpp  # Implementación funciones consola
│   │   ├── RandomGenerator.cpp
│   │   └── InputHandler.cpp
│   │
│   ├── threads/                #  IMPLEMENTACIÓN HILOS 
│   │   ├── InputThread.cpp
│   │   ├── RenderThread.cpp
│   │   ├── GameThreads.cpp
│   │   |── Synchronization.cpp
|   |   └── ... (demas hilos) ...
│   │
│   └── main.cpp                # Punto de entrada principal
│
├── assets/                     # Recursos
│   └── scores.txt              # Archivo para guardar puntuaciones
│
├── Makefile                    # Compilación
└── README.md                   # Guía de uso


## Requisitos del Sistema
- Sistema Operativo: Windows 10/11
- Compilador: MinGW-w64 o MSVC
- RAM: 4GB mínimo
- Consola: Terminal de Windows con soporte para ASCII


## Planificación de desarrollo
- Fase 1: Planificación
  * Análisis del juego
  * Investigación técnica
  * Calendarización
- Fase 2: Entorno Gráfico
  * Menús y pantallas ASCII
  * Renderizado del tablero
  * Sistema de visualización
- Fase 3: Implementación Final
  * Sistema de hilos concurrentes
  * Mecanismos de sincronización
  * Integración completa


