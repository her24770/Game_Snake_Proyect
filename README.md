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

```text
snake_game/
│
├── docs/                           # Documentación del proyecto
│   ├── Fase1_Planificacion.pdf
│   ├── Fase2_EntornoGrafico.pdf
│   └── Fase3_Final.pdf
│
├── include/                        # Headers
│   ├── core/                       # Lógica principal del juego
│   │   ├── GameConstants.hpp       # Constantes y configuraciones
│   │   ├── GameState.hpp           # Estructuras de datos del juego
│   │   └── ThreadSharedData.hpp    # Datos compartidos entre hilos
│   │
│   ├── rendering/                  # Sistema de visualización
│   │   ├── ASCIIArt.hpp            # Menús y pantallas ASCII
│   │   └── RenderEngine.hpp        # Renderizado del juego
│   │
│   ├── utils/                      # Utilidades
│   │   ├── WindowsConsole.hpp      # Control de consola Windows
│   │   ├── RandomGenerator.hpp     # Generación de números aleatorios
│   │   └── InputHandler.hpp        # Manejo de entrada de teclado
│   │
│   └── threads/                    # Sistema de concurrencia
│       ├── InputThread.hpp         # Hilo de entrada de teclado
│       ├── RenderThread.hpp        # Hilo de renderizado
│       ├── GameThreads.hpp         # Hilos de lógica del juego
│       └── Synchronization.hpp     # Utilidades de sincronización
│
├── src/                            # Implementación
│   ├── core/                       # Implementación de la lógica
│   ├── rendering/                  # Implementación visual
│   ├── utils/                      # Implementación de utilidades
│   ├── threads/                    # Implementación de hilos
│   └── main.cpp                    # Punto de entrada principal
│
├── assets/                         # Recursos
│   └── scores.txt                  # Almacenamiento de puntuaciones
│
├── Makefile                        # Compilación para Linux
├── build.bat                       # Compilación para Windows
└── README.md                       # Este archivo
```
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


