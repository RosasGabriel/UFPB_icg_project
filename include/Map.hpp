#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Map {
private:
    int width, height, tileSize;
    int* data;

public:
    Map(int mapWidth, int mapHeight, int tileSize, int* mapData);

    void draw() const;
};

#endif
