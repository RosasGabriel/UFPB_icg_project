#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Map.hpp"

class RayCaster {
public:
    RayCaster();  // Construtor

    // Método para desenhar os raios
    void castRays(float player_x, float player_y, float player_angle, const Map& map) const;

private:
    // Métodos auxiliares para calcular interseções
    float calculateHorizontalIntersection(float ray_angle, float player_x, float player_y, const Map& map, float& ray_x, float& ray_y) const;
    float calculateVerticalIntersection(float ray_angle, float player_x, float player_y, const Map& map, float& ray_x, float& ray_y) const;

    // Função auxiliar para calcular distância
    float distance(float ax, float ay, float bx, float by) const;

    // Constantes e parâmetros
    static constexpr int NUM_RAYS = 120;
    static constexpr float FOV = 60.0; // Campo de visão
    static constexpr float MAX_DEPTH = 1000000;
    static constexpr int DOF_VALUE = 13;
};

#endif
