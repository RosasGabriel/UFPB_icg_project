#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Player {
public:
    float x, y;
    
    Player(float startX, float startY);

    void move(char direction);
    void draw() const;
};

#endif
