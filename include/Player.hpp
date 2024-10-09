#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

#include "Map.hpp"

class Player {
public:
    float player_x, player_y;
    float player_delta_x, player_delta_y;
    float player_angle;
    
    Player(float start_x, float start_y, float player_delta_x, float player_delta_y, float player_angle);

    void move(char direction, const Map& map);
    void draw() const;
    void drawRays(const Map& map);

private:
    bool isValidPosition(float new_x, float new_y, const Map& map) const;
};

#endif
