#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <utility>

class Snake {
private:
    std::pair<int, int> cabeza;
    int direccion; // 0=arriba, 1=derecha, 2=abajo, 3=izquierda
    int tamano;
    std::vector<std::pair<int, int>> cuerpo;
    int puntuacion;
    
public:
    Snake(int x, int y);
    void mover();
    void cambiarDireccion(int nuevaDireccion);
    void crecer();
    std::pair<int, int> getCabeza() const;
    const std::vector<std::pair<int, int>>& getCuerpo() const;
    int getPuntuacion() const;
    void updateDirectionFromKey(int key, int playerId);
    void sumarPuntos(int puntos);
};

#endif