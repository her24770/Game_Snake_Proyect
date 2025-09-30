#include "../../include/utils/InputHandler.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

namespace InputHandler {
    int getUserInput() {
        char c = getchar();
        
        if (c == 27) {
            char next = getchar();
            if (next == '[') {
                c = getchar();
                if (c == 'A') return KEY_UP;
                if (c == 'B') return KEY_DOWN;
                if (c == 'C') return KEY_RIGHT;
                if (c == 'D') return KEY_LEFT;
            }
            return KEY_ESC;
        }
        
        if (c == '\n' || c == '\r') return KEY_ENTER;
        return KEY_NONE;
    }

    int getUserInputNonBlocking() {
        fd_set readfds;
        struct timeval timeout;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 10000;
        
        if(select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0) {
            return getUserInput();
        }
        return KEY_NONE;
    }
}