#include "../../include/rendering/ASCIIArt.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include "../../include/utils/InputHandler.hpp"
#include <iostream>
#include <iomanip>


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

void drawScoreboard(ScoreThreadData* scoreData) {
    WindowsConsole::clearScreen();
    WindowsConsole::hideCursor();
    WindowsConsole::setConsoleTitle("Snake Game - Puntajes");
    std::cout << std::endl;

    drawMenuBorder();
    drawScoreboardTitle();

    std::cout << WindowsConsole::Colors::BRIGHT_WHITE;

    std::vector<ScoreEntry> scores;
    if (scoreData) {
        std::lock_guard<std::mutex> lock(scoreData->scoreMutex);
        scores = scoreData->scores;
    }

    // Trofeo ASCII
    std::vector<std::string> trophy = {
        "       ___________   ",
        "      '._==_==_=_.'  ",
        "      .-\\:      /-. ",
        "     | (|:.      |) |",
        "      '-|:.      |-' ",
        "        \\::.    /    ",
        "         '::. .'     ",
        "           ) (       ",
        "         _.' '._     ",
        "        `\"\"\"\"\"\"\"`    "
    };

    // Tabla de puntajes
    std::vector<std::string> tableLines;
    tableLines.push_back("╔════╦══════════════════╦═══════╦═════════╗");
    tableLines.push_back("║ #  ║ JUGADOR          ║ PUNTOS║ TIEMPO  ║");
    tableLines.push_back(" ╠════╬══════════════════╬═══════╬═════════╣");

    auto formatCell = [](const std::string& text, int width, bool leftAlign=true) {
        std::string t = text.substr(0, width);
        if (t.length() < width) {
            if (leftAlign) t += std::string(width - t.length(), ' ');
            else t = std::string(width - t.length(), ' ') + t;
        }
        return t;
    };

    for (size_t i = 0; i < 10; ++i) {
        std::string line = "║ ";
        if (i < scores.size()) {
            line += formatCell(std::to_string(i+1), 2, false) + " ║ ";
            line += formatCell(scores[i].name, 16, true) + " ║ ";
            line += formatCell(std::to_string(scores[i].score), 5, false) + " ║ ";
            line += formatCell(scores[i].time, 7, true) + " ║";
        } else {
            line += "   ║                  ║       ║         ║";
        }
        tableLines.push_back(line);
    }

    tableLines.push_back("╚════╩══════════════════╩═══════╩═════════╝");

    // Alineación
    size_t maxLines = std::max(trophy.size(), tableLines.size());
    while (trophy.size() < maxLines)
        trophy.push_back(std::string(trophy[0].length(), ' '));
    while (tableLines.size() < maxLines)
        tableLines.push_back("");

    int trophyWidth = 21;
    int tableWidth = 46;
    int spaceBetween = 4;
    int contentWidth = trophyWidth + spaceBetween + tableWidth;
    int leftPadding = (CONSOLE_WIDTH - contentWidth) / 2;

    for (size_t i = 0; i < maxLines; ++i) {
        std::cout << std::string(leftPadding, ' ')
                  << trophy[i]
                  << std::string(spaceBetween, ' ')
                  << tableLines[i]
                  << std::endl;
    }

    drawMenuBorder();
    std::cout << WindowsConsole::Colors::RESET;
    std::cout << "\n\nESC para volver\n";
}






void drawMenuBorder() {
        std::cout << WindowsConsole::Colors::BRIGHT_CYAN;
        std::string border = "╔" + std::string(CONSOLE_WIDTH - 2, '═') + "╗";
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
            "                     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"
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