#include "../../include/utils/InputHandler.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

namespace InputHandler {
    int getUserInput() {
        char c = getchar();
        
        if (c == 27) { // ESC sequence
            getchar(); // skip '['
            c = getchar();
            if (c == 'A') return KEY_UP;
            if (c == 'B') return KEY_DOWN;
        }
        
        if (c == '\n' || c == '\r') return KEY_ENTER;
        if (c == 27) return KEY_ESC;
        
        return KEY_NONE;
    }
}