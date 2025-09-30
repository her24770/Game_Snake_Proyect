#include "../../include/core/Snake.hpp"

Snake::Snake(int x, int y) : cabeza({x, y}), direccion(1), tamano(3) {
    cuerpo.push_back(cabeza);
    cuerpo.push_back({x-1, y});
    cuerpo.push_back({x-2, y});
}

void Snake::mover() {
    // Implementar lógica de movimiento
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