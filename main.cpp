#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Player.hpp"
#include "Map.hpp"

#define WIDTH 1024
#define HEIGHT 724

// Definição do formato mapa
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

Player player(111, 555, 0, 0, 0);
Map map(13, 9, 72, map_data);

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    map.draw();
    player.draw();
    glutSwapBuffers();
}

void movement(unsigned char key, int x, int y) {
    player.move(key, map);
    glutPostRedisplay();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("ICG_Project");
    init();
    glutKeyboardFunc(movement);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
