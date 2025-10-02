#include "../../include/core/Snake.hpp"
#include "../../include/utils/InputHandler.hpp"
#include <cstddef>

Snake::Snake(int x, int y) : cabeza({x, y}), direccion(1), tamano(3), puntuacion(0) {
    cuerpo.push_back(cabeza);
    cuerpo.push_back({x-1, y});
    cuerpo.push_back({x-2, y});
}

void Snake::mover() {
    std::pair<int, int> prevHead = cabeza;

    // Actualizamos la cabeza según la dirección (solo 0-3)
    switch (direccion) {
        case 0: // Arriba
            cabeza.second -= 1;
            break;
        case 1: // Derecha
            cabeza.first += 1;
            break;
        case 2: // Abajo
            cabeza.second += 1;
            break;
        case 3: // Izquierda
            cabeza.first -= 1;
            break;
    }

    std::pair<int, int> prevPos;
    std::pair<int, int> tempPos;

    if (!cuerpo.empty()) {
        prevPos = cuerpo[0];
        cuerpo[0] = cabeza;
        for (size_t i = 1; i < cuerpo.size(); ++i) {
            tempPos = cuerpo[i];
            cuerpo[i] = prevPos;
            prevPos = tempPos;
        }
    }

    while (cuerpo.size() < (size_t)tamano) {
        cuerpo.push_back(prevPos);
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
        // Jugador 1: Flechas (lee de getKey donde se escriben flechas)
        switch(key) {
            case InputHandler::KEY_UP: nuevaDireccion = 0; break;
            case InputHandler::KEY_RIGHT: nuevaDireccion = 1; break;
            case InputHandler::KEY_DOWN: nuevaDireccion = 2; break;
            case InputHandler::KEY_LEFT: nuevaDireccion = 3; break;
        }
    } else if(playerId == 2) {
        // Jugador 2: WASD (lee de getKey2 donde se escribe WASD)
        switch(key) {
            case InputHandler::KEY_W: nuevaDireccion = 0; break;
            case InputHandler::KEY_D: nuevaDireccion = 1; break;
            case InputHandler::KEY_S: nuevaDireccion = 2; break;
            case InputHandler::KEY_A: nuevaDireccion = 3; break;
        }
    }

    if(nuevaDireccion != -1) {
        cambiarDireccion(nuevaDireccion);
    }
}

void Snake::sumarPuntos(int puntos) {
    puntuacion += puntos;
}