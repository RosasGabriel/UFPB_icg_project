#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 1024
#define HEIGHT 724

float player_x , player_y;

int map_x = 13, map_y = 9, map_s = 72;
int map[] = {
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

void drawMap2D() {
    int x, y;
    int x_0, y_0;

    for(y = 0; y < map_y; y++) {

        for(x = 0; x < map_x; x++) {
            if (map[y*map_x+x] == 1) {
                glColor3f(1,1,1);
            }else {
                glColor3f(0,0,0);
            }
            x_0 = x * map_s;
            y_0 = y * map_s;
            glBegin(GL_QUADS);
            glVertex2i(x_0 + 1, y_0 + 1);
            glVertex2i(x_0 + 1, y_0 + map_s - 1);
            glVertex2i(x_0 + map_s - 1, y_0 + map_s - 1);
            glVertex2i(x_0 + map_s - 1, y_0 + 1);
            glEnd();
        }
    }
}

void drawPlayer() {
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(player_x, player_y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D();
    drawPlayer();
    glutSwapBuffers();
}

void movement(unsigned char key, int x, int y) {
    if(key == 'w') {
        player_y -= 5;
    }
    if(key == 's') {
        player_y += 5;
    }
    if(key == 'a') {
        player_x -= 5;
    }
    if(key == 'd') {
        player_x += 5;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);

    player_x = 300;
    player_y = 300;
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("ICG_Project");
    init();
    glutKeyboardFunc(movement);
    glutDisplayFunc(display);
    glutMainLoop();
}