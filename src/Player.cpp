#include "Player.hpp"

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 // Equivalente à 1 Grau em Radianos
#define DOF_VALUE 13

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
void Player::drawRays(const Map& map) {
    int ray_index, map_tile_x, map_tile_y, map_index, depth_of_field;
    float ray_x, ray_y, ray_angle, x_offset, y_offset;
    int rays_number = 60;                   // Número de linhas para serem desenhadas

    ray_angle = player_angle - DR * 30;     // Ângulo inicial para desenhar as linhas de Ray Casting (30 graus a esquerda do jogador)
    if (ray_angle < 0) {
        ray_angle += 2 * PI;
    }
    if (ray_angle > 2 * PI) {
        ray_angle -= 2 * PI;
    }

    // Para cada raio, calcula interseções horizontais e verticais com as paredes
    for (ray_index=0; ray_index < rays_number; ray_index++) {
        // Checagem de linhas horizontais
        depth_of_field = 0;
        float horizontal_distance = 1000000;
        float horizontal_intersection_x = player_x; 
        float horizontal_intersection_y = player_y;

        float inv_tan = -1/tan(ray_angle);          // Tangente inversa (para calcular as interseções horizontais)

        if (ray_angle > PI) {                       // Ray está olhando para cima
            ray_y = (((int) player_y / map.tileSize) * map.tileSize)-0.0001;
            ray_x = (player_y - ray_y) * inv_tan + player_x;
            y_offset = -map.tileSize;
            x_offset = -y_offset * inv_tan;
        }

        if (ray_angle < PI) {                       // Ray está olhando para baixo
            ray_y = (((int) player_y / map.tileSize) * map.tileSize) + map.tileSize;
            ray_x = (player_y - ray_y) * inv_tan + player_x;
            y_offset = map.tileSize;
            x_offset = -y_offset * inv_tan;
        }

        if (ray_angle == 0 || ray_angle == PI) {    // Ray está olhando diretamente para a esquerda ou direita
            ray_y = player_y;
            ray_x = player_x;
            depth_of_field = DOF_VALUE;
        }

        // Loop que encontra interseções horizontais com as paredes do mapa
        while (depth_of_field < DOF_VALUE) {
            map_tile_x = (int) (ray_x) / map.tileSize;
            map_tile_y = (int) (ray_y) / map.tileSize;
            map_index = map_tile_y * map.width + map_tile_x;                                                                            // Posição do mapa

            if (map_index > 0 && map_index < map.width * map.height && map.data[map_index] == 1) {                                      // Colisão com parede
                horizontal_intersection_x = ray_x;
                horizontal_intersection_y = ray_y;
                horizontal_distance = distance(player_x, player_y, horizontal_intersection_x, horizontal_intersection_y, ray_angle);    // Calcula distância
                depth_of_field = DOF_VALUE;                                                                                             // Encerra a busca
            } else {
                ray_x += x_offset;
                ray_y += y_offset;
                depth_of_field += 1;
            }
        }
        
        // Checagem de linhas verticais
        depth_of_field = 0;
        float vertical_distance = 1000000;
        float vertical_intersection_x = player_x; 
        float vertical_intersection_y = player_y;

        float neg_tan = -tan(ray_angle);          // Tangente inversa para interseções verticais

        if (ray_angle > P2 && ray_angle < P3) {   // Ray está olhando para a esquerda
            ray_x = (((int) player_x / map.tileSize) * map.tileSize)-0.0001;
            ray_y = (player_x - ray_x) * neg_tan + player_y;
            x_offset = -map.tileSize;
            y_offset = -x_offset * neg_tan;
        }

        if (ray_angle < P2 || ray_angle > P3) {   // Ray está olhando para a direita
            ray_x = (((int) player_x / map.tileSize) * map.tileSize) + map.tileSize;
            ray_y = (player_x - ray_x) * neg_tan + player_y;
            x_offset = map.tileSize;
            y_offset = -x_offset * neg_tan;
        }

        if (ray_angle == 0 || ray_angle == PI) {
            ray_y = player_y;
            ray_x = player_x;
            depth_of_field = DOF_VALUE;
        }

        while (depth_of_field < DOF_VALUE) {
            map_tile_x = (int) (ray_x) / map.tileSize;
            map_tile_y = (int) (ray_y) / map.tileSize;
            map_index = map_tile_y * map.width + map_tile_x;
            if (map_index > 0 && map_index < map.width * map.height && map.data[map_index] == 1) {
                vertical_intersection_x = ray_x;
                vertical_intersection_y = ray_y;
                vertical_distance = distance(player_x, player_y, vertical_intersection_x, vertical_intersection_y, ray_angle);
                depth_of_field = DOF_VALUE;
            } else {
                ray_x += x_offset;
                ray_y += y_offset;
                depth_of_field += 1;
            }
        }
        
        // Determina qual interseção (horizontal ou vertical) está mais próxima
        if (vertical_distance<horizontal_distance) {
            ray_x = vertical_intersection_x;
            ray_y = vertical_intersection_y;
        }
        if (horizontal_distance < vertical_distance) {
            ray_x = horizontal_intersection_x;
            ray_y = horizontal_intersection_y;
        }

        // Desenha o raio na tela (da posição do jogador até a interseção)
        glColor3f(1,0,0);               // Cor vermelha para os raios
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(player_x, player_y); // Ponto inicial do raio (posição do jogador)
        glVertex2i(ray_x, ray_y);             // Ponto final do raio (onde ele colide com uma parede)
        glEnd();

        ray_angle += DR;                       // Incrementa o ângulo do próximo raio

        if (ray_angle < 0) {
            ray_angle += 2 * PI;
        }
        if (ray_angle > 2 * PI) {
            ray_angle -= 2 * PI;
        }
    }
}

// Método para verificar se a posição do jogador é válida
bool Player::isValidPosition(float new_x, float new_y, const Map& map) const{
    // Verificar se as novas coordenadas estão dentro dos limites do mapa
    if (new_x < 0 || new_x >= map.width * map.tileSize || new_y < 0  || new_y >= map.height * map.tileSize) {
        return false;
    }

    // Obter a célula correspondente ao novo ponto
    int cell_x = static_cast<int>(new_x) / map.tileSize;
    int cell_y = static_cast<int>(new_y) / map.tileSize;

    // Verificar se a célula está colidindo com uma parede
    if (map.isWall(cell_x, cell_y)) {
        return false; // Colidiu com uma parede
    }

    return true;
}