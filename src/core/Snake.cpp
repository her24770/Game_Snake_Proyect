#include "../../include/core/Snake.hpp"
#include "../../include/utils/InputHandler.hpp"
#include <cstddef>

Snake::Snake(int x, int y) : cabeza({x, y}), direccion(1), tamano(3), puntuacion(0) {
    cuerpo.push_back(cabeza);
    cuerpo.push_back({x-1, y});
    cuerpo.push_back({x-2, y});
}

void Snake::mover() {
    // Guarda la posición actual de la cabeza
    std::pair<int, int> prevHead = cabeza;

    // Actualizamos la cabeza según la dirección
    switch (direccion) {
        case 0: // Arriba
        case 7:
            cabeza.second -= 1;
            break;
        case 1: // Derecha
        case 8:
            cabeza.first += 1;
            break;
        case 2: // Abajo
        case 9:
            cabeza.second += 1;
            break;
        case 3: // Izquierda
        case 10:
            cabeza.first -= 1;
            break;
    }

    // Guardamos la posición anterior de cada segmento
    std::pair<int, int> prevPos;
    std::pair<int, int> tempPos;

    if (!cuerpo.empty()) {
        prevPos = cuerpo[0];    // Posición de la cabeza actual
        cuerpo[0] = cabeza;     // La cabeza es el primer elemento
        for (size_t i = 1; i < cuerpo.size(); ++i) {
            tempPos = cuerpo[i];  // Guarda la posición actual del segmento
            cuerpo[i] = prevPos;  // Este segmento sigue al anterior
            prevPos = tempPos;    // Actualiza prevPos para el siguiente segmento
        }
    }

    // Ajustamos el tamaño del vector si la serpiente ha crecido
    while (cuerpo.size() < (size_t)tamano) {
        cuerpo.push_back(prevPos); // Añadimos un segmento al final
    }
}

void Snake::cambiarDireccion(int nuevaDireccion) {
    // Evitar dirección opuesta
    if((direccion + 2) % 4 != nuevaDireccion) {
        direccion = nuevaDireccion;
    }
}

void Snake::crecer() {
    tamano++;
}

std::pair<int, int> Snake::getCabeza() const {
    return cabeza;
}

const std::vector<std::pair<int, int>>& Snake::getCuerpo() const {
    return cuerpo;
}

int Snake::getPuntuacion() const {
    return puntuacion;
}

void Snake::updateDirectionFromKey(int key, int playerId) {
    int nuevaDireccion = -1;

    if(playerId == 1) {
        // Jugador 1: WASD
        switch(key) {
            case InputHandler::KEY_W: nuevaDireccion = 0; break;
            case InputHandler::KEY_D: nuevaDireccion = 1; break;
            case InputHandler::KEY_S:  nuevaDireccion = 2; break;
            case InputHandler::KEY_A:  nuevaDireccion = 3; break;
        }
    } else if(playerId == 2) {
        // Jugador 2: Flechas
        switch(key) {
            case InputHandler::KEY_UP: nuevaDireccion = 0; break;
            case InputHandler::KEY_RIGHT: nuevaDireccion = 1; break;
            case InputHandler::KEY_DOWN:  nuevaDireccion = 2; break;
            case InputHandler::KEY_LEFT:  nuevaDireccion = 3; break;
        }
    }

    if(nuevaDireccion != -1) {
        cambiarDireccion(nuevaDireccion); // Usa la función ya existente que evita dirección opuesta
    }
}