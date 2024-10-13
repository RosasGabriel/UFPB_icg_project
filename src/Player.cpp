#include "Player.hpp"

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 // Equivalente à 1 Grau em Radianos
#define DOF_VALUE 13
#define NUM_RAYS 120
#define MAX_DEPTH 1000000

// Construtor
Player::Player(float start_x, float start_y, float start_delta_x, float start_delta_y, float start_angle) 
:   player_x(start_x), player_y(start_y), 
    player_delta_x(start_delta_x), player_delta_y(start_delta_y),
    player_angle(start_angle) {}

// Método de movimentação do jogador
void Player::move(char direction, const Map& map) {
    float new_x = player_x;
    float new_y = player_y;

    switch (direction) {
        case 'w': 
            new_x += player_delta_x;
            new_y += player_delta_y;
            break;
        case 's': 
            new_x -= player_delta_x;
            new_y -= player_delta_y;
            break;
        case 'a': 
            player_angle -= 0.1;
            if(player_angle < 0) {
                player_angle += 2 * PI;
            }
            player_delta_x = cos(player_angle) * 5;
            player_delta_y = sin(player_angle) * 5;
            break;
        case 'd': 
            player_angle += 0.1;
            if(player_angle > 2 * PI) {
                player_angle -= 2 * PI;
            }
            player_delta_x = cos(player_angle) * 5;
            player_delta_y = sin(player_angle) * 5;
            break;
    }

    // Checagem se a posição que o jogador irá se mover é válida
    if(isValidPosition(new_x, new_y, map)) {
        player_x = new_x;
        player_y = new_y;
    }
}

// Método para desenhar o jogador na tela
void Player::draw() const {
    // Pixel de representação do jogador
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player_x, player_y);
    glEnd();
}

// Função auxiliar para calcular a distância entre dois pontos no mapa
float distance (float ax, float ay, float bx, float by, float ang) {
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

// Método para desenhar o Ray Casting
void Player::drawRays(const Map& map, const RayCaster& ray_caster) {
    ray_caster.castRays(player_x, player_y, player_angle, map);
}

// Método para verificar se a posição do jogador é válida
bool Player::isValidPosition(float new_x, float new_y, const Map& map) const{
    // Verificar se as novas coordenadas estão dentro dos limites do mapa
    if (new_x < 0 || new_x >= map.width * map.tile_size || new_y < 0  || new_y >= map.height * map.tile_size) {
        return false;
    }

    // Obter a célula correspondente ao novo ponto
    int cell_x = static_cast<int>(new_x) / map.tile_size;
    int cell_y = static_cast<int>(new_y) / map.tile_size;

    // Verificar se a célula está colidindo com uma parede
    if (map.isWall(cell_x, cell_y)) {
        return false; // Colidiu com uma parede
    }

    return true;
}