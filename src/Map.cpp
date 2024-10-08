#include "Map.hpp"

// Construtor do mapa
Map::Map(int mapWidth, int mapHeight, int tileSize, int* mapData)
    : width(mapWidth), height(mapHeight), tileSize(tileSize), data(mapData) {}

// Método para desenhar o mapa
void Map::draw() const {
    int x_0, y_0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (data[y * width + x] == 1) {
                glColor3f(1, 1, 1);
            } else {
                glColor3f(0, 0, 0);
            }
            x_0 = x * tileSize;
            y_0 = y * tileSize;
            glBegin(GL_QUADS);
            glVertex2i(x_0 + 1, y_0 + 1);
            glVertex2i(x_0 + 1, y_0 + tileSize - 1);
            glVertex2i(x_0 + tileSize - 1, y_0 + tileSize - 1);
            glVertex2i(x_0 + tileSize - 1, y_0 + 1);
            glEnd();
        }
    }
}

// Método para verificar se uma célula é uma parede
bool Map::isWall(int x, int y) const{
    return (x >= 0 && x < width && y >= 0 && y < height) ? data[y * width + x] == 1 : false;
}