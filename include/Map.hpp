#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Map {
public:
    int width;
    int height;
    int tileSize;
    int* data;

    Map(int mapWidth, int mapHeight, int tileSize, int* mapData);

    void draw() const;

    bool isWall(int x, int y) const;
};

#endif
