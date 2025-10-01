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

        if (c == 'w' || c == 'W') return KEY_W;
        if (c == 'a' || c == 'A') return KEY_A;
        if (c == 's' || c == 'S') return KEY_S;
        if (c == 'd' || c == 'D') return KEY_D;
        return KEY_NONE;
    }

    int getUserInputNonBlocking() {
        fd_set readfds;
        struct timeval timeout;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000; // muy pequeño, loop rápido

        if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0) {
            char c;
            if (read(STDIN_FILENO, &c, 1) == 1) {
                if (c == 27) { // secuencia flecha o ESC
                    char seq[2];
                    if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                        if (seq[0] == '[') {
                            if (seq[1] == 'A') return InputHandler::KEY_UP;
                            if (seq[1] == 'B') return InputHandler::KEY_DOWN;
                            if (seq[1] == 'C') return InputHandler::KEY_RIGHT;
                            if (seq[1] == 'D') return InputHandler::KEY_LEFT;
                        }
                    }
                    return InputHandler::KEY_ESC;
                }

                // WASD
                if (c == 'w' || c == 'W') return InputHandler::KEY_W;
                if (c == 'a' || c == 'A') return InputHandler::KEY_A;
                if (c == 's' || c == 'S') return InputHandler::KEY_S;
                if (c == 'd' || c == 'D') return InputHandler::KEY_D;

                if (c == '\n' || c == '\r') return InputHandler::KEY_ENTER;
            }
        }
        return InputHandler::KEY_NONE;
    }
}