#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

namespace InputHandler {
    
    // Constantes para códigos de teclas
    const int KEY_NONE = 0;
    const int KEY_UP = 1;
    const int KEY_DOWN = 2;
    const int KEY_LEFT = 3;
    const int KEY_RIGHT = 4;
    const int KEY_ENTER = 5;
    const int KEY_ESC = 6;
    const int KEY_SPACE = 7;
    
    // Función principal para capturar entrada de teclado
    int getUserInput();
    
    // Funciones auxiliares
    bool isKeyPressed();
    void flushInputBuffer();
    char getChar();
}

#endif // INPUT_HANDLER_HPP