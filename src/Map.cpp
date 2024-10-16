#include "Map.hpp"

// Construtor do mapa
Map::Map(int mapWidth, int mapHeight, int tileSize, int* mapData)
    : width(mapWidth), height(mapHeight), tile_size(tileSize), data(mapData) {}

// Método para desenhar o mapa
void Map::draw() const {
    int x_0, y_0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (data[y * width + x] == 1) { // Verifica se a célula for uma parede
                glColor3f(1, 1, 1);         // Cor branca para as paredes
            } else {
                glColor3f(0, 0, 0);         // Cor preta para os espaços vazios
            }
            x_0 = x * tile_size;
            y_0 = y * tile_size;
            glBegin(GL_QUADS);
            glVertex2i(x_0 + 1, y_0 + 1);
            glVertex2i(x_0 + 1, y_0 + tile_size - 1);
            glVertex2i(x_0 + tile_size - 1, y_0 + tile_size - 1);
            glVertex2i(x_0 + tile_size - 1, y_0 + 1);
            glEnd();
        }
    }
}

// Método para verificar se uma célula é uma parede
bool Map::isWall(int x, int y) const{
    return (x >= 0 && x < width && y >= 0 && y < height) ? data[y * width + x] == 1 : false;
}