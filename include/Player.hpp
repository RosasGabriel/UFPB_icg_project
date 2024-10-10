#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

#include "Map.hpp"

// Classe Player para representar o jogador com seus métodos e atributos
class Player {
public:
    // Atributos
    float player_x, player_y;
    float player_delta_x, player_delta_y;
    float player_angle;
    
    // Construtor
    Player(float start_x, float start_y, float player_delta_x, float player_delta_y, float player_angle);

    // Métodos públicos
    void move(char direction, const Map& map);
    void draw() const;
    void drawRays(const Map& map);

private:
    // Métodos privados
    bool isValidPosition(float new_x, float new_y, const Map& map) const;
};

#endif
