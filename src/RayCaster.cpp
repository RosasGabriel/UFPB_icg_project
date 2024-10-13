#include "RayCaster.hpp"
#include <cmath>

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 // Equivalente a 1 Grau em Radianos

// Construtor do RayCaster
RayCaster::RayCaster() {
}

// Método para desenhar os raios e a cena 3D
void RayCaster::castRays(float player_x, float player_y, float player_angle, const Map& map) const {
    int rays_number = NUM_RAYS;
    float ray_angle_step = (FOV * DR) / rays_number;
    float ray_angle = player_angle - (FOV / 2) * DR;

    for (int ray_index = 0; ray_index < rays_number; ray_index++) {
        float horizontal_ray_x, horizontal_ray_y;
        float vertical_ray_x, vertical_ray_y;

        // Calcular interseções horizontais e verticais
        float horizontal_distance = calculateHorizontalIntersection(ray_angle, player_x, player_y, map, horizontal_ray_x, horizontal_ray_y);
        float vertical_distance = calculateVerticalIntersection(ray_angle, player_x, player_y, map, vertical_ray_x, vertical_ray_y);

        float final_ray_distance;
        float final_ray_x, final_ray_y;

        // Determinar qual interseção está mais próxima
        if (horizontal_distance < vertical_distance) {
            final_ray_distance = horizontal_distance;
            final_ray_x = horizontal_ray_x;
            final_ray_y = horizontal_ray_y;
            glColor3f(0.7, 0, 0);  // Cor para a interseção horizontal
        } else {
            final_ray_distance = vertical_distance;
            final_ray_x = vertical_ray_x;
            final_ray_y = vertical_ray_y;
            glColor3f(0.9, 0, 0);  // Cor para a interseção vertical
        }

        // Desenhar o raio correspondente na cena 2D
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(player_x, player_y);  // Ponto inicial do raio (posição do jogador)
        glVertex2i(final_ray_x, final_ray_y);  // Ponto final do raio (onde colide com a parede)
        glEnd();

        // Corrigir o efeito de distorção "fish-eye"
        float casting_angle = player_angle - ray_angle;
        if (casting_angle > 2 * PI) {
            casting_angle -= 2 * PI;
        }
        final_ray_distance = final_ray_distance * cos(casting_angle);

        // Desenho da cena 3D baseado na distância do raio
        float lineH = (map.tile_size * 320) / final_ray_distance;
        if (lineH > 320) {
            lineH = 320;
        }
        float lineO = 160 - (lineH / 2);
        glLineWidth(9);
        glBegin(GL_LINES);
        glVertex2i(ray_index * 7 + 1024, lineO);  // Desloca a cena 3D para a direita
        glVertex2i(ray_index * 7 + 1024, lineH + lineO);
        glEnd();

        // Desenhar o teto
        glColor3f(0.5, 0.7, 0.9);  // Cor azul claro para o teto
        glBegin(GL_QUADS);
        glVertex2i(ray_index * 7 + 1024, 0);  // Canto superior esquerdo do teto
        glVertex2i(ray_index * 7 + 1024, lineO);  // Limite inferior do teto (parte superior da parede)
        glVertex2i((ray_index + 1) * 7 + 1024, lineO);
        glVertex2i((ray_index + 1) * 7 + 1024, 0);
        glEnd();

        // Desenhar o piso
        glColor3f(0.3, 0.2, 0.1);  // Cor marrom para o piso
        glBegin(GL_QUADS);
        glVertex2i(ray_index * 7 + 1024, lineO + lineH);  // Limite superior do piso (parte inferior da parede)
        glVertex2i(ray_index * 7 + 1024, 320);  // Canto inferior esquerdo do piso
        glVertex2i((ray_index + 1) * 7 + 1024, 320);  // Canto inferior direito do piso
        glVertex2i((ray_index + 1) * 7 + 1024, lineO + lineH);
        glEnd();

        // Ajustar o próximo ângulo
        ray_angle += ray_angle_step;
        if (ray_angle < 0) {
            ray_angle += 2 * PI;
        }
        if (ray_angle > 2 * PI) {
            ray_angle -= 2 * PI;
        }
    }
}

// Método para o cálculo da interseção horizontal
float RayCaster::calculateHorizontalIntersection(float ray_angle, float player_x, float player_y, const Map& map, float& ray_x, float& ray_y) const {
    float inv_tan = -1 / tan(ray_angle);  // Tangente inversa
    float horizontal_distance = MAX_DEPTH;
    int map_tile_x, map_tile_y, map_index, depth_of_field = 0;
    float x_offset, y_offset;

    if (ray_angle > PI) {  // Ray está apontando para cima
        ray_y = (((int)player_y / map.tile_size) * map.tile_size) - 0.0001;  // Interseção com linha horizontal superior
        ray_x = (player_y - ray_y) * inv_tan + player_x;
        y_offset = -map.tile_size;
        x_offset = -y_offset * inv_tan;
    } else if (ray_angle < PI) {  // Ray está apontando para baixo
        ray_y = (((int)player_y / map.tile_size) * map.tile_size) + map.tile_size;
        ray_x = (player_y - ray_y) * inv_tan + player_x;
        y_offset = map.tile_size;
        x_offset = -y_offset * inv_tan;
    } else {  // Ray está na direção exata do eixo horizontal
        ray_x = player_x;
        ray_y = player_y;
        depth_of_field = DOF_VALUE;
    }

    // Iterar até encontrar uma parede ou atingir o limite de profundidade
    while (depth_of_field < DOF_VALUE) {
        map_tile_x = (int)(ray_x) / map.tile_size;
        map_tile_y = (int)(ray_y) / map.tile_size;
        map_index = map_tile_y * map.width + map_tile_x;

        if (map_index > 0 && map_index < map.width * map.height && map.data[map_index] == 1) {  // Colisão com parede
            horizontal_distance = distance(player_x, player_y, ray_x, ray_y);
            depth_of_field = DOF_VALUE;  // Parar ao encontrar uma parede
        } else {  // Continuar avançando o raio
            ray_x += x_offset;
            ray_y += y_offset;
            depth_of_field++;
        }
    }

    return horizontal_distance;
}

// Método para o cálculo da interseção vertical
float RayCaster::calculateVerticalIntersection(float ray_angle, float player_x, float player_y, const Map& map, float& ray_x, float& ray_y) const {
    float neg_tan = -tan(ray_angle);  // Tangente negativa
    float vertical_distance = MAX_DEPTH;
    int map_tile_x, map_tile_y, map_index, depth_of_field = 0;
    float x_offset, y_offset;

    if (ray_angle > P2 && ray_angle < P3) {  // Ray está apontando para a esquerda
        ray_x = (((int)player_x / map.tile_size) * map.tile_size) - 0.0001;
        ray_y = (player_x - ray_x) * neg_tan + player_y;
        x_offset = -map.tile_size;
        y_offset = -x_offset * neg_tan;
    } else if (ray_angle < P2 || ray_angle > P3) {  // Ray está apontando para a direita
        ray_x = (((int)player_x / map.tile_size) * map.tile_size) + map.tile_size;
        ray_y = (player_x - ray_x) * neg_tan + player_y;
        x_offset = map.tile_size;
        y_offset = -x_offset * neg_tan;
    } else {  // Ray está na direção exata do eixo vertical
        ray_x = player_x;
        ray_y = player_y;
        depth_of_field = DOF_VALUE;
    }

    // Iterar até encontrar uma parede ou atingir o limite de profundidade
    while (depth_of_field < DOF_VALUE) {
        map_tile_x = (int)(ray_x) / map.tile_size;
        map_tile_y = (int)(ray_y) / map.tile_size;
        map_index = map_tile_y * map.width + map_tile_x;

        if (map_index > 0 && map_index < map.width * map.height && map.data[map_index] == 1) {  // Colisão com parede
            vertical_distance = distance(player_x, player_y, ray_x, ray_y);
            depth_of_field = DOF_VALUE;
        } else {  // Continuar avançando o raio
            ray_x += x_offset;
            ray_y += y_offset;
            depth_of_field++;
        }
    }

    return vertical_distance;
}

// Método auxiliar para calcular distância
float RayCaster::distance(float ax, float ay, float bx, float by) const {
    return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}
