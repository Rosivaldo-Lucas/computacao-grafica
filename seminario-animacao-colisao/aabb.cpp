#include <GL/glut.h>
#include <iostream>

struct Rect {
    float x, y;     // Coordenadas do canto superior esquerdo
    float width, height;  // Largura e altura
};

float rect1X = 0.2f, rect1Y = 0.2f; // Posição inicial do Retângulo 1
float rect2X = 0.6f, rect2Y = 0.6f; // Posição inicial do Retângulo 2
float rectSize = 0.1f;              // Tamanho inicial dos retângulos (proporcional à tela)

bool collision = false;

bool AABBIntersect(const Rect &rect1, const Rect &rect2) {
    // Verifique a colisão nas coordenadas x (eixo horizontal)
    bool xOverlap = (rect1.x < rect2.x + rect2.width) && (rect1.x + rect1.width > rect2.x);

    // Verifique a colisão nas coordenadas y (eixo vertical)
    bool yOverlap = (rect1.y < rect2.y + rect2.height) && (rect1.y + rect1.height > rect2.y);

    // Se houver colisão nas coordenadas x e y, então há colisão AABB
    return xOverlap && yOverlap;
}

void drawRect(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    if (collision) {
        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde se houver colisão
    } else {
        glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha se não houver colisão
    }
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Verifique a colisão
    Rect rect1 = {rect1X, rect1Y, rectSize, rectSize};
    Rect rect2 = {rect2X, rect2Y, rectSize, rectSize};
    collision = AABBIntersect(rect1, rect2);

    // Desenhe os retângulos
    drawRect(rect1X, rect1Y, rectSize, rectSize);
    drawRect(rect2X, rect2Y, rectSize, rectSize);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    float step = 0.02f; // Tamanho do passo para mover os quadrados

    switch (key) {
        case 'w': // Mover para cima
            rect1Y += step;
            break;
        case 's': // Mover para baixo
            rect1Y -= step;
            break;
        case 'a': // Mover para a esquerda
            rect1X -= step;
            break;
        case 'd': // Mover para a direita
            rect1X += step;
            break;
    }

    glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Quadrados Colidindo");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
