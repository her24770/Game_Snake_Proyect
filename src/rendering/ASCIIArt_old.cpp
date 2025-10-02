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

// Función para guardar un nuevo puntaje en el archivo CSV
void saveScoreToCSV(const std::string& filename, const std::string& playerName, int score, int time) {
    std::ofstream file(filename, std::ios::app); // Abrir en modo append
    
    if (file.is_open()) {
        file << playerName << "," << score << "," << time << std::endl;
        file.close();
    }
}

} // namespace ASCIIArt

// Función para leer puntajes desde un archivo CSV
std::vector<PlayerScore> readScoresFromCSV(const std::string& filename) {
    std::vector<PlayerScore> scores;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        // Si no se puede abrir el archivo, crear datos de ejemplo
        std::cout << "No se pudo abrir el archivo " << filename << ". Usando datos de ejemplo.\n";
        return {
            {"Cristi", 150, 50}, {"Wong", 120, 40}, {"Strange", 100, 30},
            {"Ancestral", 80, 90}, {"Dormamu", 60, 70}, {"Tony", 100, 25},
            {"Peter", 80, 89}, {"Natasha", 60, 68}, {"Steve", 60, 60},
            {"Bruce", 40, 45}, {"Rocket", 40, 30}, {"Thor", 30, 100},
            {"Loki", 20, 99}, {"Gamora", 10, 88}, {"Groot", 5, 10}
        };
    }
    
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line)) {
        // Saltar la línea de encabezados
        if (firstLine && (line.find("name") != std::string::npos || 
                         line.find("Name") != std::string::npos || 
                         line.find("PLAYER") != std::string::npos)) {
            firstLine = false;
            continue;
        }
        firstLine = false;
        
        if (line.empty()) continue;
        
        // Parsear la línea CSV
        std::istringstream ss(line);
        std::string name, scoreStr, timeStr;
        
        // Leer nombre (hasta la primera coma)
        if (std::getline(ss, name, ',')) {
            // Leer puntaje (hasta la segunda coma)
            if (std::getline(ss, scoreStr, ',')) {
                // Leer tiempo (resto de la línea)
                if (std::getline(ss, timeStr)) {
                    try {
                        // Limpiar espacios en blanco
                        name.erase(0, name.find_first_not_of(" \t"));
                        name.erase(name.find_last_not_of(" \t") + 1);
                        scoreStr.erase(0, scoreStr.find_first_not_of(" \t"));
                        scoreStr.erase(scoreStr.find_last_not_of(" \t") + 1);
                        timeStr.erase(0, timeStr.find_first_not_of(" \t"));
                        timeStr.erase(timeStr.find_last_not_of(" \t") + 1);
                        
                        int score = std::stoi(scoreStr);
                        int time = std::stoi(timeStr);
                        
                        scores.push_back({name, score, time});
                    } catch (const std::exception& e) {
                        // Si hay error en la conversión, saltar esta línea
                        continue;
                    }
                }
            }
        }
    }
    
    file.close();
    
    // Si no se pudieron leer datos válidos, usar datos de ejemplo
    if (scores.empty()) {
        return {
            {"Cristi", 150, 50}, {"Wong", 120, 40}, {"Strange", 100, 30},
            {"Ancestral", 80, 90}, {"Dormamu", 60, 70}, {"Tony", 100, 25},
            {"Peter", 80, 89}, {"Natasha", 60, 68}, {"Steve", 60, 60},
            {"Bruce", 40, 45}, {"Rocket", 40, 30}, {"Thor", 30, 100},
            {"Loki", 20, 99}, {"Gamora", 10, 88}, {"Groot", 5, 10}
        };
    }
    
    return scores;
}

// Funciones para la animación del podio
void printAtPosition(int x, int y, const std::string& text) {
    std::cout << "\033[" << y << ";" << x << "H" << text << std::flush;
}

void waitMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// Diseños únicos para cada columna del podio
const std::vector<std::string> PODIO_CENTRAL = {
    "       ╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓x,      ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "      ░░░░░░░░░███║░░░░░░░░░     ",
    "      ░░░░░░░░████║░░░░░░░░░     ",
    "      ░░░░░░░░░░██║░░░░░░░░░     ",
    "      ░░░░░░░░░░██║░░░░░░░░░     ",
    "      ░░░░░░░░██████║░░░░░░░     ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "▄▄▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▄▄ "
};

const std::vector<std::string> PODIO_IZQUIERDO = {
    "       ╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓x,      ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",          
    "      ░░░░░░░░█████░░░░░░░░░     ",               
    "      ░░░░░░░███████║░░░░░░░     ",                    
    "      ░░░░░░██╓░░░██║░░░░░░░     ",                  
    "      ░░░░░░░░░░███║░░░░░░░░     ",                   
    "      ░░░░░░░░████╓░░░░░░░░░     ",                 
    "      ░░░░░░░███████║░░░░░░░     ",                   
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "▄▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▄▄  "
};

const std::vector<std::string> PODIO_DERECHO = {
    "       ╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓╓x,      ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "      ░░░░░░░░░███║░░░░░░░░░     ",
    "      ░░░░░░░███╓████║░░░░░░     ",
    "      ░░░░░░░██╓░░┘██║░░░░░░     ",
    "      ░░░░░░░░░░████║░░░░░░░     ",
    "      ░░░░░░░██╙K╙ ██║░░░░░░     ",
    "      ░░░░░░░░█████║░░░░░░░░     ",
    "      ░░░░░░░░░░░░░░░░░░░░░░     ",
    "▄▄▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▄▄   "
};

// Dibujo gradual por línea (columna emerge)
void drawColumn(const std::vector<std::string>& column, int x, const std::string& name) {
    int total = column.size();
    int termBottom = 30;
    int startY = termBottom - total + 1;

    // Mostrar el nombre justo encima del podio
    printAtPosition(x + 3, startY - 1, "\033[1;36m" + name + "\033[0m");

    // Mostrar línea por línea desde abajo hacia arriba
    for (int i = 0; i < total; ++i) {
        printAtPosition(x, startY + i, column[i]);
        waitMs(80);
    }
}

// Confeti animado SIN borrar pantalla
void drawConfettiOver(int frames = 10, int width = 90, int height = 25, int safeTop = 6) {
    std::vector<char> confettiChars = {'*', '+', 'x', '@', '#'};
    for (int f = 0; f < frames; ++f) {
        for (int i = safeTop; i < height; ++i) {  // Evita líneas superiores (safeTop)
            for (int j = 0; j < width; ++j) {
                if (rand() % 15 == 0) {
                    char ch = confettiChars[rand() % confettiChars.size()];
                    int color = 31 + rand() % 7;
                    printAtPosition(j + 1, i + 1, "\033[1;" + std::to_string(color) + "m" + ch + "\033[0m");
                }
            }
        }
        waitMs(200);
    }
}

// Función para mostrar animación del podio
void showPodiumAnimation(const std::vector<PlayerScore>& scores) {
    srand(time(0));
    WindowsConsole::clearScreen();
    std::cout << "\033[?25l"; // Ocultar cursor
    
    // Obtener nombres de los primeros 3 jugadores
    std::string first = (scores.size() > 0) ? scores[0].name : "Player 1";
    std::string second = (scores.size() > 1) ? scores[1].name : "Player 2";  
    std::string third = (scores.size() > 2) ? scores[2].name : "Player 3";

    // 1. Centro (1er lugar)
    drawColumn(PODIO_CENTRAL, 35, first);

    // 2. Izquierda (2do lugar)
    drawColumn(PODIO_IZQUIERDO, 5, second);

    // 3. Derecha (3er lugar)
    drawColumn(PODIO_DERECHO, 65, third);

    waitMs(1000);

    // 4. Confeti y mensaje sobrepuestos
    drawConfettiOver(15, 90, 30, 6);
    printAtPosition(30, 3, "\033[1;33m ¡Felicidades a los ganadores! \033[0m");
    
    waitMs(3000);
    std::cout << "\033[?25h"; // Mostrar cursor
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
    // Leer puntajes desde archivo CSV, debe estar en la misma carpeta que el ejecutable
    std::vector<PlayerScore> scores = CSVManager::readScoresFromCSV("scores.csv");
    
    // Ordenar por puntaje descendente y por tiempo ascendente
    std::sort(scores.begin(), scores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        if (a.score != b.score)
            return a.score > b.score;
        return a.time < b.time;
    });

    // Mostrar animación del podio primero
    PodiumAnimation::showPodiumAnimation(scores);
    
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

void drawMenuBorder() {
        std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
        std::string border = "╔" + std::string(CONSOLE_WIDTH - 2, '=') + "╗";
        printCenteredLine(border);
        std::cout << WindowsConsole::Colors::RESET;
    }
std::string centerString(const std::string& text, int width) {
        int padding = (width - text.length()) / 2;
        return std::string(padding, ' ') + text + std::string(width - text.length() - padding, ' ');
    }   
 void printCenteredLine(const std::string& text) {
        int padding = (CONSOLE_WIDTH - text.length()) / 2;
        if (padding > 0) {
            std::cout << std::string(padding, ' ');
        }
        std::cout << text << std::endl;
    }
    void drawGameTitle() {
        std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
        
        // Arte ASCII para "SNAKE GAME"
        std::vector<std::string> title = {
            "               ",
            "               ",
            "                    ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗",
            "                    ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝",
            "                    ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  ",
            "                    ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  ",
            "                    ███████║██║ ╚████║██║  ██║██║  ██╗███████╗",
            "                    ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝",
            "",
            "                       ██████╗  █████╗ ███╗   ███╗███████╗",
            "                      ██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
            "                      ██║  ███╗███████║██╔████╔██║█████╗  ",
            "                      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
            "                      ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
            "                       ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"
        };
        
        for (const auto& line : title) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }
    
    void drawInstructionsTitle(){
        std::cout << WindowsConsole::Colors::BRIGHT_GREEN;
        
        // Arte ASCII para titulo Instrucciones
        std::vector<std::string> title = {
            "               ",
            "               ",
            "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
            "█▄ ▄██ ▀██ ██ ▄▄▄ █▄▄ ▄▄██ ▄▄▀██ ██ ██ ▄▄▀██ ▄▄▀█▄ ▄██ ▄▄▄ ██ ▀██ ██ ▄▄▄██ ▄▄▄ █",
            "██ ███ █ █ ██▄▄▄▀▀███ ████ ▀▀▄██ ██ ██ █████ █████ ███ ███ ██ █ █ ██ ▄▄▄██▄▄▄▀▀█",
            "█▀ ▀██ ██▄ ██ ▀▀▀ ███ ████ ██ ██▄▀▀▄██ ▀▀▄██ ▀▀▄█▀ ▀██ ▀▀▀ ██ ██▄ ██ ▀▀▀██ ▀▀▀ █",
            "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"

        };
        
        for (const auto& line : title) {
            printCenteredLine(line);
        }
        
        std::cout << WindowsConsole::Colors::RESET << std::endl;
    }


}