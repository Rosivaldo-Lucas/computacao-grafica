#include <GL/glut.h>
#include <deque>
#include <ctime>
#include <iostream>

/**
 * Definição das estruturas utilizadas
 * 
*/
struct VERTICE {
  int x;
  int y;
};

struct OBJETO {
  VERTICE *vertices;

  int num_vertices;
};

struct SNAKE {
  OBJETO *objetos;

  int tam;
};

enum Direcao {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

/**
 * Definição das variáveis globais
 * 
*/
int LARGURA = 600;
int ALTURA = 600;
int tamanhoObjetos = 20;
int velSnake = 100;   // Em milissegundos

SNAKE *snake;

Direcao direcao = Direcao::RIGHT;

int comidaX, comidaY;
bool gameOver = false;

/**
 * Definição das funções utilizadas
 * 
*/
void initGlut(int *argc, char **argv) {
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(LARGURA, ALTURA);
  glutCreateWindow("Snake Game");
}

void inicializacao(GLvoid) {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, LARGURA, 0, ALTURA);

  // Inicializa a cobra e a posição da comida
  snake = (SNAKE *) malloc(sizeof(SNAKE));
  snake->tam = 1;
  snake->objetos = (OBJETO *) malloc(sizeof(OBJETO));
  snake->objetos[0].num_vertices = 1;
  snake->objetos[0].vertices = (VERTICE *)malloc(sizeof(VERTICE));
  snake->objetos[0].vertices[0] = {LARGURA / 2, ALTURA / 2};

  srand(time(nullptr)); // Inicializa a semente do gerador de números aleatórios
  comidaX = rand() % (LARGURA / tamanhoObjetos) * tamanhoObjetos;
  comidaY = rand() % (ALTURA / tamanhoObjetos) * tamanhoObjetos;
}

void drawSnake() {
  glColor3f(0.0, 1.0, 0.0);
  
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;

  for (int i = 0; i < snake->tam; i++) {
    for (int j = 0; j < snake->objetos[i].num_vertices; j++) {
      x1 = snake->objetos[i].vertices[j].x;
      y1 = snake->objetos[i].vertices[j].y;
      x2 = snake->objetos[i].vertices[j].x + tamanhoObjetos;
      y2 = snake->objetos[i].vertices[j].y + tamanhoObjetos;

      glRecti(x1, y1, x2, y2);
    }
  }
}

void drawComida() {
  glColor3f(1.0, 0.0, 0.0);

  glRecti(comidaX, comidaY, comidaX + tamanhoObjetos, comidaY + tamanhoObjetos);
}

bool AABB(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  // Verifica se os retângulos não se sobrepõem nas coordenadas x e y
  if (x1 + w1 <= x2 || x1 >= x2 + w2 || y1 + h1 <= y2 || y1 >= y2 + h2) {
    return false; // Não há colisão
  } else {
    return true; // Há colisão
  }
}

bool verificaColisaoSnakeComida() {
  // Tamanho dos retângulos da cobra e da comida
  int snakeLARGURA = tamanhoObjetos;
  int snakeALTURA = tamanhoObjetos;
  int comidaLARGURA = tamanhoObjetos;
  int comidaALTURA = tamanhoObjetos;

  // Posições dos retângulos da cobra e da comida
  int snakeX = snake->objetos[0].vertices[0].x;
  int snakeY = snake->objetos[0].vertices[0].y;

  // Verifica a colisão entre a cabeça da cobra e a comida
  return AABB(snakeX, snakeY, snakeLARGURA, snakeALTURA, comidaX, comidaY, comidaLARGURA, comidaALTURA);
}

bool verificaColisaoBordasTela(VERTICE novaSnakeHead) {
  return novaSnakeHead.x < 0 || novaSnakeHead.x >= LARGURA || novaSnakeHead.y < 0 || novaSnakeHead.y >= ALTURA;
}

void atualizaPosicaoSnake(VERTICE *novaSnakeHead) {
  switch (direcao) {
    case Direcao::UP:
      novaSnakeHead->y += tamanhoObjetos;

      break;
    case Direcao::DOWN:
      novaSnakeHead->y -= tamanhoObjetos;

      break;
    case Direcao::LEFT:
      novaSnakeHead->x -= tamanhoObjetos;

      break;
    case Direcao::RIGHT:
      novaSnakeHead->x += tamanhoObjetos;

      break;
  }
}

void moveSnake() {
  if (gameOver)
    return;

  // Crie a nova cabeça da cobra
  VERTICE novaSnakeHead;
  novaSnakeHead.x = snake->objetos[0].vertices[0].x; 
  novaSnakeHead.y = snake->objetos[0].vertices[0].y;

  atualizaPosicaoSnake(&novaSnakeHead);

  if (verificaColisaoBordasTela(novaSnakeHead)) {
    gameOver = true;

    return;
  }

  // Verifica colisão consigo mesma
  for (int i = 1; i < snake->tam; i++) {
    for (int j = 0; j < snake->objetos[i].num_vertices; j++) {
      if (snake->objetos[i].vertices[j].x == snake->objetos[0].vertices[0].x && snake->objetos[i].vertices[j].y == snake->objetos[0].vertices[0].y) {
        gameOver = true;

        return;
      }
    }
  }

  // Verifique se a cobra comeu a comida
  if (verificaColisaoSnakeComida()) {
    // Aumenta o tamanho da cobra
    snake->tam++;

    // Aloca memória para o novo objeto da cobra
    snake->objetos = (OBJETO *) realloc(snake->objetos, snake->tam * sizeof(OBJETO));

    // Crie um novo objeto para a nova cabeça
    snake->objetos[snake->tam - 1].num_vertices = 1;
    snake->objetos[snake->tam - 1].vertices = (VERTICE *) malloc(sizeof(VERTICE));
    snake->objetos[snake->tam - 1].vertices[0] = novaSnakeHead;

    // Gera uma nova posição para a comida
    comidaX = rand() % (LARGURA / tamanhoObjetos) * tamanhoObjetos;
    comidaY = rand() % (ALTURA / tamanhoObjetos) * tamanhoObjetos;
  } else {
    // Atualize o restante do corpo da cobra movendo cada segmento para a posição do segmento anterior
    VERTICE verticeTemp = snake->objetos[0].vertices[0];
    
    for (int i = 1; i < snake->tam; i++) {
      VERTICE verticeAtual = snake->objetos[i].vertices[0];

      snake->objetos[i].vertices[0] = verticeTemp;
      
      verticeTemp = verticeAtual;
    }

    snake->objetos[0].vertices[0] = novaSnakeHead;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  drawSnake();
  drawComida();

  glutSwapBuffers();
}

void specialKeyboard(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      if (direcao != Direcao::DOWN)
        direcao = Direcao::UP;
      
      break;
    case GLUT_KEY_DOWN:
      if (direcao != Direcao::UP)
        direcao = Direcao::DOWN;
      
      break;
    case GLUT_KEY_LEFT:
      if (direcao != Direcao::RIGHT)
        direcao = Direcao::LEFT;
      
      break;
    case GLUT_KEY_RIGHT:
      if (direcao != Direcao::LEFT)
        direcao = Direcao::RIGHT;
      
      break;
    case 27: // Tecla Esc
      exit(0);
      
      break;
  }
}

void animcaoSnake(int value) {
  moveSnake();

  glutPostRedisplay();
  
  glutTimerFunc(velSnake, animcaoSnake, 0);
}

int main(int argc, char **argv) {
  initGlut(&argc, argv);

  glutDisplayFunc(display);
  glutSpecialFunc(specialKeyboard);
  
  inicializacao();

  glutTimerFunc(velSnake, animcaoSnake, 0);

  glutMainLoop();

  // Libera a memória alocada
  for (int i = 0; i < snake->tam; ++i) {
    free(snake->objetos[i].vertices);
  }

  free(snake->objetos);
  free(snake);

  return 0;
}
