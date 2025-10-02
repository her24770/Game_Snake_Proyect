#include "../../include/rendering/ASCIIArt.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include "../../include/utils/InputHandler.hpp"
#include "../../include/utils/CSVManager.hpp"
#include "../../include/rendering/PodiumAnimation.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace ASCIIArt {

    void drawMainMenu(int selectedOption, int speedIndex) {
        WindowsConsole::clearScreen();
        WindowsConsole::hideCursor();
        WindowsConsole::setConsoleTitle("Snake Game - Menu Principal");

        std::cout << std::endl;

        // 🔹 Marco superior
        drawMenuBorder();

        // 🔹 Título del juego
        drawGameTitle();


        // 🔹 Opciones del menú con selector
        std::cout << WindowsConsole::Colors::BRIGHT_WHITE;

        std::string topFrame    = "                       ╔══════════════════════════════════╗";
        std::string bottomFrame = "                       ╚══════════════════════════════════╝";

        printCenteredLine(topFrame);

        std::string speedLabel = (speedIndex == 0) ? "Lento " : (speedIndex == 1) ? "Medio " : "Rápido";
        std::string speedText = "Velocidad: " + speedLabel;

        std::vector<std::string> options = {
            (selectedOption == 0 ? "        ║      ➤  Jugar (1 jugador)        ║" : "       ║         Jugar (1 jugador)        ║"),
            (selectedOption == 1 ? "        ║     ➤  Jugar (2 jugadores)       ║" : "       ║        Jugar (2 jugadores)       ║"),
            (selectedOption == 2 ? "        ║        ➤  Instrucciones          ║" : "       ║           Instrucciones          ║"),
            (selectedOption == 3 ? "        ║          ➤  Puntajes             ║" : "       ║             Puntajes             ║"),
            (selectedOption == 4 ? "         ║      ➤  "+ speedText +"        ║" : "       ║        " + speedText+"         ║"),
            (selectedOption == 5 ? "        ║           ➤  Salir               ║" : "       ║              Salir               ║")
        };

        for (const auto& option : options) {
            printCenteredLine(option);
        }

        printCenteredLine(bottomFrame);
        std::cout << WindowsConsole::Colors::RESET << std::endl;


        // 🔹 Marco inferior
        drawMenuBorder();

        WindowsConsole::showCursor();
    }

void drawInstructions() {
    system("clear");
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    WindowsConsole::setConsoleTitle("Snake Game - Instrucciones");
    std::cout << std::endl;

    //Borde superior
    drawMenuBorder();

    //Título de instrucciones
    drawInstructionsTitle();
    std::cout << WindowsConsole::Colors::BRIGHT_WHITE;

    //Instrucciones del juego
    std::vector<std::string> snakeInstruccion = {
        "     __           1.Usa las flechas del teclado para mover la serpiente.             ",
        "    {0O}          2.Para un segundo jugador, usar las teclas W,A,S,D.                ",
        "    \\__/          3. Come la comida ¤ para crecer y ganar puntos.                  ",
        "    /^/           4. Evita chocar contra las paredes ▓ o con la serpiente ◯, ⦿, @. ",
        "   ( (           5.Cada comida vale 10 puntos.                               ",
        "    \\_\\_____      6. Come todo lo que puedas y alcanza la puntuacion mas alta     ",
        "   (_______)                                                                         ",
        "   (_________()Oo                                                                    "
    };

    for (const auto& line : snakeInstruccion) {
        printCenteredLine(line);
    }


    //Borde inferior
    drawMenuBorder();


    std::cout << "\n\nESC para volver\n";
}
void drawScoreboardTitle(){
        std::cout << WindowsConsole::Colors::BRIGHT_CYAN;

        // Arte ASCII para titulo Scoreboard
        std::vector<std::string> title = {
            "               ",
            "               ",
            "   ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
            "   █ ▄▄▄ ██ ▄▄▀██ ▄▄▄ ██ ▄▄▀██ ▄▄▄██ ▄▄▄▀██ ▄▄▄ █▀▄▄▀██ ▄▄▀██ ▄▄▀██",               
            "   █▄▄▄▀▀██ █████ ███ ██ ▀▀▄██ ▄▄▄██ ▄▄▀▀██ ███ █ ▀▀ ██ ▀▀▄██ ███ █",
            "   █ ▀▀▀ ██ ▀▀▄██ ▀▀▀ ██ ██ ██ ▀▀▀██ ▀▀▀ ██ ▀▀▀ █ ██ ██ ██ ██ ▀▀▄██",
            "   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"         
        };
        
        for (const auto& line : title) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }

void drawScoreboard() {
    // Leer puntajes desde archivo CSV
    std::vector<PlayerScore> scores = CSVManager::readScoresFromCSV("scores.csv");
    
    // Ordenar por puntaje descendente y por tiempo ascendente
    std::sort(scores.begin(), scores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        if (a.score != b.score)
            return a.score > b.score;
        return a.time < b.time;
    });

    // Mostrar animación del podio primero
    PodiumAnimation::showPodiumAnimation(scores);
    
    // Después mostrar la tabla detallada
 // Después mostrar el scoreboard tradicional
    system("clear");
    std::cout << "\n\n=== PUNTAJES ===\n\nESC para volver\n";  
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    WindowsConsole::setConsoleTitle("Snake Game - Puntajes");
    std::cout << std::endl;
    //Borde superior
    drawMenuBorder();

    //Título de scoreboard
    drawScoreboardTitle();
    std::cout << WindowsConsole::Colors::BRIGHT_WHITE;
    
    // Trofeo en ASCII
    std::vector<std::string> trophy = {
        "       _____________   ",
        "      '._==_==_=_=_.'  ",
        "      .-\\:       /-. ",
        "     | (|:.      |)| ",
        "      '-|:.      |-'  ",
        "        \\::.    /   ",
        "         '::. .'     ",
        "           ) (       ",
        "         _.' '._     ",
        "        `\"\"\"\"\"\"\"`    "
};


    const int TROPHY_WIDTH = 26;
    const int SPACE_BETWEEN = 4;
    const int TABLE_WIDTH = 40;
    const int CONSOLE_WIDTH = 80;
    size_t maxScoreLen = 5;   // mínimo "SCORE"
    size_t maxTimeLen  = 4;   // mínimo "TIME"

    //  Calcular el ancho máximo del nombre del jugador
    size_t maxNameLength = 0;
    for (const auto& score : scores) {
        if (score.name.length() > maxNameLength) {
            maxNameLength = score.name.length();
        }
    }

    // Medallas para los 3 primeros puestos
    std::vector<std::string> medals = { "★     ", "✦     ", "☆     "};

  // Encabezado de la tabla
  std::ostringstream headerStream;
    headerStream << std::setw(6) << std::left << "RANK"
                 << " | " << std::setw(maxNameLength) << std::left << "PLAYER"
                 << " | " << std::setw(maxScoreLen) << "SCORE"
                 << " | " << std::setw(maxTimeLen) << "TIME";
    std::vector<std::string> scoreboardLines;
    scoreboardLines.push_back(headerStream.str());
    scoreboardLines.push_back(std::string(headerStream.str().length(), '-'));

    // Mostrar solo los primeros 10
    for (size_t i = 0; i < std::min<size_t>(10, scores.size()); ++i) {
        std::ostringstream lineStream;
        std::string rank = (i < medals.size()) ? medals[i] : std::to_string(i + 1);

        lineStream << std::setw(6) << std::left << rank
                   << " | " << std::setw(maxNameLength) << std::left << scores[i].name
                   << " | " << std::setw(maxScoreLen) << scores[i].score
                   << " | " << std::setw(maxTimeLen) << scores[i].time;
        scoreboardLines.push_back(lineStream.str());
    };
    // Centramos el trofeo verticalmente con respecto a la tabla
    int trophyLines = trophy.size();
    int tableLines = scoreboardLines.size();
    int totalLines = std::max(trophyLines, tableLines);
    int trophyOffsetTop = std::max(0, (totalLines - trophyLines) / 2 - 2);//
    int tableOffsetTop = (totalLines - tableLines) / 2; 

    //  Alineación vertical
    size_t maxLines = std::max(trophy.size(), scoreboardLines.size());
    while (trophy.size() < maxLines)
        trophy.insert(trophy.begin(), std::string(trophy[0].length(), ' '));
    while (scoreboardLines.size() < maxLines)
        scoreboardLines.push_back("");

    //  Cálculo para alinear todo horizontalmente en el centro
    int trophyWidth = trophy[0].length();
    int scoreboardWidth = headerStream.str().length();
    int spaceBetween = 6;
    int contentWidth = trophyWidth + spaceBetween + scoreboardWidth;
    int leftPadding = (CONSOLE_WIDTH - contentWidth) / 2;
    if (leftPadding < 0) leftPadding = 0;

    //  Imprimir trofeo + tabla
    for (int i = 0; i < totalLines; ++i) {
        // Padding izquierdo
        int leftPad = (CONSOLE_WIDTH - (TROPHY_WIDTH + SPACE_BETWEEN + TABLE_WIDTH)) / 2;
        std::cout << std::string(leftPad, ' ');

        // Trofeo (con relleno en líneas sin contenido con base en el ancho asignado)
        if (i >= trophyOffsetTop && i < trophyOffsetTop + trophyLines)
            std::cout << std::setw(TROPHY_WIDTH) << std::left << trophy[i - trophyOffsetTop];
        else
            std::cout << std::string(TROPHY_WIDTH, ' ');

        std::cout << std::string(SPACE_BETWEEN, ' ');

        // Tabla (con relleno en líneas sin contenido con base en el ancho asignado)
        if (i >= tableOffsetTop && i < tableOffsetTop + tableLines)
            std::cout << scoreboardLines[i - tableOffsetTop];

        std::cout << std::endl;
    }
    //Borde inferior
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    drawMenuBorder();

    std::cout << "\n\nESC para volver\n";
}



// Funciones auxiliares
void printCenteredLine(const std::string& text) {
    const int CONSOLE_WIDTH = 80;
    int padding = (CONSOLE_WIDTH - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << std::endl;
}

std::string padString(const std::string& text, size_t width) {
    if (text.length() >= width) return text.substr(0, width);
    size_t padding = width - text.length();
    return text + std::string(padding, ' ');
}

void drawMenuBorder() {
    std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
    std::string border = "╔" + std::string(78, '=') + "╗";
    printCenteredLine(border);
    std::cout << WindowsConsole::Colors::RESET;
}

} 