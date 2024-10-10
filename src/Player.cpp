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
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo;
    int rays_number = 60;           // Número de linhas para serem desenhadas

    ra = player_angle - DR * 30;    // Ângulo inicial para desenhar as linhas de Ray Casting (30 graus a esquerda do jogador)
    if (ra < 0) {
        ra += 2 * PI;
    }
    if (ra > 2 * PI) {
        ra -= 2 * PI;
    }

    // Para cada raio, calcula interseções horizontais e verticais com as paredes
    for (r=0; r < rays_number; r++) {
        // Checagem de linhas horizontais
        dof = 0;
        float disH = 1000000;
        float hx = player_x; 
        float hy = player_y;

        float aTan=-1/tan(ra);      // Tangente inversa (para calcular as interseções horizontais)

        if (ra > PI) {              // Ray está olhando para cima
            ry = (((int) player_y / map.tileSize) * map.tileSize)-0.0001;
            rx = (player_y - ry) * aTan + player_x;
            yo = -map.tileSize;
            xo = -yo * aTan;
        }

        if (ra < PI) {              // Ray está olhando para baixo
            ry = (((int) player_y / map.tileSize) * map.tileSize) + map.tileSize;
            rx = (player_y - ry) * aTan + player_x;
            yo = map.tileSize;
            xo = -yo * aTan;
        }

        if (ra == 0 || ra == PI) {  // Ray está olhando diretamente para a esquerda ou direita
            ry = player_y;
            rx = player_x;
            dof = DOF_VALUE;
        }

        // Loop que encontra interseções horizontais com as paredes do mapa
        while (dof < DOF_VALUE) {
            mx = (int) (rx) / map.tileSize;
            my = (int) (ry) / map.tileSize;
            mp = my * map.width + mx;                                           // Posição do mapa

            if (mp > 0 && mp < map.width * map.height && map.data[mp] == 1) {   // Colisão com parede
                hx = rx;
                hy = ry;
                disH = distance(player_x, player_y, hx, hy, ra);                // Calcula distância
                dof = DOF_VALUE;                                                // Encerra a busca
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        
        // Checagem de linhas verticais
        dof = 0;
        float disV = 1000000;
        float vx = player_x; 
        float vy = player_y;

        float nTan=-tan(ra);        // Tangente inversa para interseções verticais

        if (ra > P2 && ra < P3) {   // Ray está olhando para a esquerda
            rx = (((int) player_x / map.tileSize) * map.tileSize)-0.0001;
            ry = (player_x - rx) * nTan + player_y;
            xo = -map.tileSize;
            yo = -xo * nTan;
        }

        if (ra < P2 || ra > P3) {   // Ray está olhando para a direita
            rx = (((int) player_x / map.tileSize) * map.tileSize) + map.tileSize;
            ry = (player_x - rx) * nTan + player_y;
            xo = map.tileSize;
            yo = -xo * nTan;
        }

        if (ra == 0 || ra == PI) {
            ry = player_y;
            rx = player_x;
            dof = DOF_VALUE;
        }

        while (dof < DOF_VALUE) {
            mx = (int) (rx) / map.tileSize;
            my = (int) (ry) / map.tileSize;
            mp = my * map.width + mx;
            if (mp > 0 && mp < map.width * map.height && map.data[mp] == 1) {
                vx = rx;
                vy = ry;
                disV = distance(player_x, player_y, vx, vy, ra);
                dof = DOF_VALUE;
            } else {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        
        // Determina qual interseção (horizontal ou vertical) está mais próxima
        if (disV<disH) {
            rx = vx;
            ry = vy;
        }
        if (disH < disV) {
            rx = hx;
            ry = hy;
        }

        // Desenha o raio na tela (da posição do jogador até a interseção)
        glColor3f(1,0,0);               // Cor vermelha para os raios
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(player_x, player_y); // Ponto inicial do raio (posição do jogador)
        glVertex2i(rx, ry);             // Ponto final do raio (onde ele colide com uma parede)
        glEnd();

        ra += DR;                       // Incrementa o ângulo do próximo raio

        if (ra < 0) {
            ra += 2 * PI;
        }
        if (ra > 2 * PI) {
            ra -= 2 * PI;
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