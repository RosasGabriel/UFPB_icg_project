#include "Player.hpp"

// Construtor
Player::Player(float startX, float startY) : x(startX), y(startY) {}

// Função de movimentação do jogador
void Player::move(char direction) {
    switch (direction) {
        case 'w': y -= 5; break;
        case 's': y += 5; break;
        case 'a': x -= 5; break;
        case 'd': x += 5; break;
    }
}

// Função para desenhar o jogador na tela
void Player::draw() const {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
