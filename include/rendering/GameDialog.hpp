#ifndef GAME_DIALOG_HPP
#define GAME_DIALOG_HPP

#include <string>

namespace GameDialog {
    // Funciones para diálogos del juego
    bool showSaveDialog();
    std::string getPlayerName();
    void showSaveConfirmation();
}

#endif // GAME_DIALOG_HPP