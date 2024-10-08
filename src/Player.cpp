#include "Player.hpp"

#define PI 3.1415926535

// Construtor
Player::Player(float start_x, float start_y, float start_delta_x, float start_delta_y, float start_angle) 
:   player_x(start_x), player_y(start_y), 
    player_delta_x(start_delta_x), player_delta_y(start_delta_y),
    player_angle(start_angle) {}

// Função de movimentação do jogador
void Player::move(char direction) {
    switch (direction) {
        case 'w': 
            player_x += player_delta_x;
            player_y += player_delta_y;
            break;
        case 's': 
            player_x -= player_delta_x;
            player_y -= player_delta_y;
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
}

// Função para desenhar o jogador na tela
void Player::draw() const {
    // Pixel de representação do jogador
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player_x, player_y);
    glEnd();

    // Linha de representação da direção que o jogador observa
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(player_x, player_y);
    glVertex2i(player_x + player_delta_x * 5, player_y + player_delta_y * 5);
    glEnd();
}
