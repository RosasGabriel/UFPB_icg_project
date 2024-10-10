#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Player.hpp"
#include "Map.hpp"

#define WIDTH 1024
#define HEIGHT 724

// Definição do formato do mapa. Cada valor '1' representa uma parede, e '0' um espaço vazio.
int map_data[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

// Inicialização do jogador e do mapa
Player player(111, 555, 0, 0, 0);
Map map(13, 9, 72, map_data);

// Função responsável para o desenho da cena (mapa, player e raios lançados)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    map.draw();
    player.draw();
    player.drawRays(map);
    glutSwapBuffers();
}

// Função para lidar com o movimento do jogador na cena
void movement(unsigned char key, int x, int y) {
    player.move(key, map);
    glutPostRedisplay();
}

// Inicializa a janela de exibição
void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
}

// Função principal de execução do projeto
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);                          // Inicialização do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   // Configuração do modo de exibição
    glutInitWindowSize(WIDTH, HEIGHT);              // Definição do tamanho da janela de exiibção
    glutCreateWindow("ICG_Project");                // Criação da janela de exibição
    init();                                         // Chamada da função de inicialização
    glutKeyboardFunc(movement);                     // Configuração da entrada do teclado para movimentação
    glutDisplayFunc(display);                       // Chamada da função de exibição
    glutMainLoop();                                 // Loop principal do GLUT
    return 0;
}
