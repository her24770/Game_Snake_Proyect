#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

namespace InputHandler {
    const int KEY_NONE = 0;
    const int KEY_UP = 1;
    const int KEY_DOWN = 2;
    const int KEY_LEFT = 3;
    const int KEY_RIGHT = 4;
    const int KEY_ENTER = 5;
    const int KEY_ESC = 6;
    const int KEY_W = 7;
    const int KEY_A = 8;
    const int KEY_S = 9;
    const int KEY_D = 10;
    
    int getUserInput();
    int getUserInputNonBlocking();
}

#endif