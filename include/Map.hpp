#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Classe Map para representar o mapa com seus métodos e atributos
class Map {
public:
    // Atributos
    int width;
    int height;
    int tileSize;
    int* data;

    // Contrutor
    Map(int mapWidth, int mapHeight, int tileSize, int* mapData);

    // Métodos
    void draw() const;

    bool isWall(int x, int y) const;
};

#endif
