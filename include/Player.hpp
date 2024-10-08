#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

class Player {
public:
    float player_x, player_y;
    float player_delta_x, player_delta_y;
    float player_angle;
    
    Player(float startX, float startY, float player_delta_x, float player_delta_y, float player_angle);

    void move(char direction);
    void draw() const;
};

#endif
