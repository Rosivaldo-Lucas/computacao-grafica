#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include <iostream>

GLint LARGURA = 600, ALTURA = 600;

GLfloat x_ini = 100.0f;
GLfloat y_ini = 150.0f;
GLsizei rsize = 50;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat vel = 0.1f;

struct VERTICE {
  float x;
  float y;
};

struct OBJETO {
  VERTICE *vertices;

  int num_vertices;
};

OBJETO *objeto;

OBJETO *criar_objeto() {
  objeto = (OBJETO *) malloc(sizeof(OBJETO));

  objeto->num_vertices = 4;

  objeto->vertices = (VERTICE *) malloc(sizeof(VERTICE) * objeto->num_vertices);
  objeto->vertices[0].x = x_ini;
  objeto->vertices[0].y = y_ini + rsize;

  objeto->vertices[1].x = x_ini;
  objeto->vertices[1].y = y_ini;

  objeto->vertices[2].x = x_ini + rsize;
  objeto->vertices[2].y = y_ini;

  objeto->vertices[3].x = x_ini + rsize;
  objeto->vertices[3].y = (y_ini + rsize);

  return objeto;
}

void initGlut(int *argc, char **argv) {
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400, 350);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Transformacoes Geometricas 2D");
}

void inicializacao(GLvoid) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, LARGURA, ALTURA, 0);

  objeto = criar_objeto();
}

void desenharObjeto() {
  glBegin(GL_QUADS);

    for (int i = 0; i < objeto->num_vertices; i++) {
      if (i == 0) {
        glVertex2i(objeto->vertices[i].x, objeto->vertices[i].y + rsize);
      } else if (i == 1) {
        glVertex2i(objeto->vertices[i].x, objeto->vertices[i].y);
      } else if (i == 2) {
        glVertex2i(objeto->vertices[i].x + rsize, objeto->vertices[i].y);
      } else if (i == 3) {
        glVertex2i(objeto->vertices[i].x + rsize, objeto->vertices[i].y + rsize);
      }

      glColor3f(0.0f, 0.0f, 1.0f);
    }

  glEnd();
}

void desenha(GLvoid) {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(0.0f, 1.0f, 0.0f);

  desenharObjeto();

  glFlush();
  glutSwapBuffers();
}

void timer(int value) {
  // Muda a direção quando chega na borda esquerda ou direita
  if (x_ini > LARGURA - rsize || x_ini < 0)
    xstep = -xstep;

  // Muda a direção quando chega na borda superior ou inferior
  if (y_ini > ALTURA - rsize || y_ini < 0)
    ystep = -ystep;

  // Verifica as bordas.  Se a window for menor e o
  // quadrado sair do volume de visualização
  if (x_ini > LARGURA - rsize)
    x_ini = LARGURA - rsize - 1;

  if (y_ini > ALTURA - rsize)
    y_ini = ALTURA - rsize - 1;

  x_ini += xstep;
  y_ini += ystep;

  // Move os certices do quadrado
  for (int i = 0; i < objeto->num_vertices; i++) {
    objeto->vertices[i].x = x_ini + vel;
    objeto->vertices[i].y = y_ini + vel;
  }

  // Redesenha o quadrado com as novas coordenadas
  glutPostRedisplay();
  glutTimerFunc(1, timer, 1);
}

void keyboardSpecialFunc(GLint key, GLint x, GLint y) {
  if (key == GLUT_KEY_UP) {
    vel += 1;
  } else if (key == GLUT_KEY_DOWN) {
    vel -= 1;
  }
}

void alteraTamanhoJanela(GLsizei w, GLsizei h) {
  // Evita a divisao por zero
  if (h == 0)
    h = 1;

  // Especifica as dimensões da Viewport
  glViewport(0, 0, w, h);

  // Inicializa o sistema de coordenadas
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Estabelece a janela de seleção (left, right, bottom, top)
  if (w <= h) {
    ALTURA = 250.0f * h / w;
    LARGURA = 250.0f;
  } else {
    LARGURA = 250.0f * w / h;
    ALTURA = 250.0f;
  }

  gluOrtho2D(0.0f, LARGURA, 0.0f, ALTURA);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  initGlut(&argc, argv);
  inicializacao();
  glClear(GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(desenha);
  glutReshapeFunc(alteraTamanhoJanela);

  glutSpecialFunc(keyboardSpecialFunc);

  glutTimerFunc(1, timer, 1);

  glutMainLoop();

  return 0;
}
