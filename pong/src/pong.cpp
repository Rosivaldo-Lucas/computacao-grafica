#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <thread>

#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../includes/Jogador.hpp"
#include "../includes/Bola.hpp"
#include "../includes/Placar.hpp"
#include "../includes/Jogo.hpp"
#include "../includes/GerenciadorSom.hpp"

/**
 * VARIAVEIS GLOBAIS
*/

GLfloat xstep = 2.0f;
GLfloat ystep = 2.0f;

Jogador *jogador11;
Jogador *jogador22;
Bola *bola;
Placar *placar;
Jogo *jogo;
GerenciadorSom gerenciadorSom;

bool jogoPausado = false;
bool jogadorPontuou1 = false;
bool jogadorPontuou2 = false;
bool flag = true;
bool vencedor = false;

const int PONTUACAO_VENCEDOR = 2;

void initGlut(int *argc, char **argv) {
  jogo = new Jogo(800, 800);

  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(jogo->getLargura(), jogo->getAltura());
  glutCreateWindow("PONG");
}

void inicializacao(GLvoid) {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, jogo->getLargura(), 0, jogo->getAltura());

  placar = new Placar();

  bola = new Bola(300.0f, 80.0f, 20.0f);

  jogador11 = new Jogador("Jogador 1", 20, jogo->getAltura() / 2);
  jogador22 = new Jogador("Jogador 2", jogo->getLargura() - 50, jogo->getAltura() / 2);

  srand(time(nullptr));
}

/**
 * FUNCAO QUE REPOSICIONA A BOLA EM JOGO
*/
void reposicionarBola() { 
  if (jogadorPontuou1) {
    bola->setCx(jogador11->getX() + jogador11->getLargura() + bola->getRaio());

    jogadorPontuou1 = false;
  } else if (jogadorPontuou2) {
    bola->setCx(jogador22->getX() - bola->getRaio());

    jogadorPontuou2 = false;
  }

  // Redefina as velocidades da bola para zero
  xstep = 1.5f;
  ystep = 1.5f;
}

/**
 * FUNCAO QUE ATUALIZA A POSICAO DO JOGADOR, EH POSSIVEL MOVER PARA CIMA E PARA BAIXO.
 * FUNCAO TAMBEM EH RESPONSAVEL POR VERIFICAR SE O JOGADOR PONTUOU, SE SIM, POSICIONA A BOLA NO CENTRO DO RETANGULO DO JOGADOR QUE PONTUOU.
 * 
 * EH UTILIZADO A FLAG jogadorPontuou1/2 PARA VERIFICAR.
*/
void atualizaPosicaoJogadores() {
  if (jogador11->isPosicaoParaCima()) {
    if (!jogo->verificarColiscaoJogadorTela(jogador11)) {
      jogador11->moverParaCima();

      if (jogadorPontuou1) {
        bola->setCx(jogador11->getLargura() + 20);
        bola->setCy(jogador11->getAltura() - 100);
      }

    }
  }
  
  if (jogador11->isPosicaoParaBaixo()) {
    if (!jogo->verificarColiscaoJogadorTela(jogador11)) {
      jogador11->moverParaBaixo();

      if (jogadorPontuou1) {
        bola->setCx(jogador11->getLargura() + 20);
        bola->setCy(jogador11->getAltura() - 100);
      }
    }
  }
  
  if (jogador22->isPosicaoParaCima()) {
    if (!jogo->verificarColiscaoJogadorTela(jogador22)) {
      jogador22->moverParaCima();

      if (jogadorPontuou2) {
        bola->setCx(jogador22->getLargura() - 40);
        bola->setCy(jogador22->getAltura() - 100);
      }
    }
  }
  
  if (jogador22->isPosicaoParaBaixo()) {
    if (!jogo->verificarColiscaoJogadorTela(jogador22)) {
      jogador22->moverParaBaixo();

      if (jogadorPontuou2) {
        bola->setCx(jogador22->getLargura() - 40);
        bola->setCy(jogador22->getAltura() - 100);
      }
    }
  }
}

/**
 * FUNCAO RESPONSAVEL POR ATUALIZAR A POSICAO DA BOLA NA TELA.
 * FUNCAO TAMBEM VERIFICA SE A BOLA BATEU NA LATERAL ESQUERDA OU DIREITA DA TELA, SE BATEU, JOGADOR 1/2 PONTUOU, ENTAO EH ATUALIZADO A SUA PONTUACAO NO PLACAR.
 * QUANDO A BOLA BATE EM UMA DAS LATERAIS, EH DISPARADO O SOM DE PONTUACAO DO JOGO.
 * FUNCAO TAMBEM VERIFICA SE A BOLA BATEU NAS BORDAS DA TELA, SE BATEU RECALCULA A POSICAO DA BOLA INVERTENDO A COORDENADA X/Y DA BOLA.
 * QUANDO A BOLA BATE EM UMA DAS LATERAIS, EH DISPARADO O SOM DE COLISAO DO JOGO.
*/
void atualizaPosicaoBola() {
  if (bola->getCx() + bola->getRaio() >= jogo->getAltura()) {
    gerenciadorSom.reproduzirSom("pontuacao.wav");

    placar->incrementarPontuacaoJogador1();

    bola->setCx(jogador11->getLargura() + 20);
    bola->setCy(jogador11->getAltura() - 100);

    // Redefina as velocidades da bola para zero
    xstep = 0;
    ystep = 0;
    
    jogadorPontuou1 = true;
    flag = false;
  }
  
  if (bola->getCx() - bola->getRaio() <= 0) {
    gerenciadorSom.reproduzirSom("pontuacao.wav");

    placar->incrementarPontuacaoJogador2();
  
    bola->setCx(jogador22->getLargura() - 40);
    bola->setCy(jogador22->getAltura() - 100);

    // Redefina as velocidades da bola para zero
    xstep = 0;
    ystep = 0;

    // Marque que um jogador pontuou
    jogadorPontuou2 = true;
    flag = false;
  }

  // Verifique se a bola atingiu as bordas horizontais da tela
  if (bola->getCx() + bola->getRaio() >= jogo->getLargura() || bola->getCx() - bola->getRaio() <= 0) {
    gerenciadorSom.reproduzirSom("colisao-parede.wav");

    xstep = -xstep;
  }

  // Verifique se a bola atingiu as bordas verticais da tela
  if (bola->getCy() + bola->getRaio() >= jogo->getAltura() || bola->getCy() - bola->getRaio() <= 0) {
    gerenciadorSom.reproduzirSom("colisao-parede.wav");

    ystep = -ystep;
  }

  bola->atualizarPosicao(xstep, ystep);
}

/**
 * FUNCAO RESPONSAVEL POR VERIFICAR SE A BOLA BATEU NO JOGADOR.
 * SE A BOLA BATEU, RETORNA TRUE, SE NAO, RETORNA FALSE.
 * 
 * IMPLEMENTACAO DE COLISAO UTILIZANDO O CALCULO DA DISTANCIA EUCLIDIANA ENTRE UM PONTO E UM CIRCULO
 * 
 * @param *jogador - JOGADOR A SER VERIFICADO SE COLIDIU COM A BOLA
 * @param *bola    - BOLA QUE SERA VERIFICADA AS COORDENADAS DA COLISAO
*/
bool colisaoRetanguloCirculo(Jogador *jogador, Bola *bola) {
  float pontoMaisProximoX = std::max((float) jogador->getX(), std::min(bola->getCx(), (float) jogador->getLargura()));
  float pontoMaisProximoY = std::max((float) jogador->getY(), std::min(bola->getCy(), (float) jogador->getAltura()));

  float distancia = std::sqrt(std::pow(pontoMaisProximoX - bola->getCx(), 2) + std::pow(pontoMaisProximoY - bola->getCy(), 2));
  
  return distancia <= bola->getRaio();
}

/**
 * FUNCAO RESPONSAVEL POR ATUALIZAR O JOGO.
 * VERIFICA SE O JOGO FOI PAUSADO OU NAO, VERIFICANDO A FLAG jogoPausado. SE ESTIVER PAUSADO SAI DA FUNCAO.
 * VERFICA SE O JOGADOR ATINGIU A PONTUACAO DEFINIDA PARA QUE O JOGADOR GANHE O JOGO. QUANDO UM JOGADOR ATINGIR, HABILITA FLAG vencedor.
 * CHAMA FUNCOES PARA ATUALIZAR POSICAO JOGADORES E ATUALIZAR POSICAO BOLA.
 * VERIFICA A COLISAO DO JOGADOR COM A BOLA, SE COLIDIU, ALTERA O SENTIDO DA BOLA E AUMENTA A VELOCIDADE DO JOGADOR.
*/
void atualizaJogo() {
  if (jogoPausado) {
    return;
  }
  
  if (placar->getPontuacaoJogador1() >= PONTUACAO_VENCEDOR || placar->getPontuacaoJogador2() >= PONTUACAO_VENCEDOR) {
    vencedor = true;

    return;
  }

  atualizaPosicaoJogadores();
  atualizaPosicaoBola();

  if (colisaoRetanguloCirculo(jogador11, bola)) {
    if (flag && !jogadorPontuou1) {
      gerenciadorSom.reproduzirSom("colisao-parede.wav");
    }

    xstep = -xstep;
    // ystep = -ystep;
    xstep *= 1.1f;

    // int numero = rand() % 2;

    // if (numero == 0) {
    //   ystep *= -0.9f;
    // } else {
    //   ystep *= 0.9f;
    // }
  }

  if (colisaoRetanguloCirculo(jogador22, bola)) {
    if (flag && !jogadorPontuou2) {
      gerenciadorSom.reproduzirSom("colisao-parede.wav");
    }

    xstep = -xstep;
    // ystep = -ystep;
    xstep *= 1.1f;

    // int numero = rand() % 2;

    // if (numero == 0) {
    //   ystep *= -0.9f;
    // } else {
    //   ystep *= 0.9f;
    // }
  }

}

/**
 * FUNCAO RESPONSAVEL POR CHAMAR A FUNCAO ATUALIZAR JOGO.
 * FUNCAO TIMER DA A IMPRESSAO DE ANIMACAO AO JOGO, A CADA 1 MILISEGUNDO A FUNCAO EH CHAMADA E ENTAO ATUALIZA O JOGO.
*/
void timer(int value) {
  atualizaJogo();

  glutPostRedisplay();
  
  glutTimerFunc(1, timer, 0);
}

void drawJogadores() {
  glColor3f(0.0f, 1.0f, 0.0f);

  glRecti(jogador11->getX(), jogador11->getY(), jogador11->getLargura(), jogador11->getAltura());

  glRecti(jogador22->getX(), jogador22->getY(), jogador22->getLargura(), jogador22->getAltura());
}

/**
 * FUNCAO QUE DESENHA O PLACAR NA TELA.
*/
void drawPlacar() {
  glColor3f(1.0f, 1.0f, 1.0f);

  glRasterPos2f((jogo->getLargura() / 2) - 50, jogo->getAltura() - 50);

  for (char c : std::to_string(placar->getPontuacaoJogador1()))
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);

  glRasterPos2f((jogo->getLargura() / 2) + 50, jogo->getAltura() - 50);

  for (char c : std::to_string(placar->getPontuacaoJogador2()))
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
}

/**
 * FUNCAO QUE DESENHA A BOLA NA TELA.
*/
void drawCircle() {
  glColor3f(1.0f, 1.0f, 1.0f);

  glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
      float theta = i * 3.1415926 / 180.0;

      float x = bola->getRaio() * cos(theta) + bola->getCx();
      float y = bola->getRaio() * sin(theta) + bola->getCy();

      glVertex2i((int) x, (int) y);
    }
  glEnd();
}

/**
 * FUNCAO QUE MOSTRA A MENSAGEM PAUSE QUANDO O JOGO FOR PAUSADO.
*/
void drawPauseJogo() {
  if (jogoPausado) {
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(jogo->getLargura() / 2, jogo->getAltura() / 2);

    std::string s = "PAUSE";

    for (char c : s)
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
  }
}

/**
 * FUNCAO QUE MOSTRA QUAL FOI O JOGADOR QUE GANHOU. E TOCA UMA MUSICA.
*/
void drawVencedor() {
  if (vencedor) {
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(jogo->getLargura() / 2, jogo->getAltura() / 2);

    std::string v;

    if (placar->getPontuacaoJogador1() >= PONTUACAO_VENCEDOR) {
      v = "JOGADOR 1";
    } else if (placar->getPontuacaoJogador2() >= PONTUACAO_VENCEDOR) {
      v = "JOGADOR 2";
    }

    std::string s = "VENCEDOR ";

    s += v;

    for (char c : s)
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);

    gerenciadorSom.reproduzirSom("UC3CKCR-game-over-a.wav");
  }
}

/**
 * FUNCAO QUE CHAMA AS FUNCOES QUE DESENHAM O JOGO.
*/
void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  drawJogadores();
  drawPlacar();
  drawCircle();
  drawPauseJogo();
  drawVencedor();

  glutSwapBuffers();
}

/**
 * FUNCAO PARA AS TECLAS DE CIMA E BAIXO DO TECLADO, ESSAS TECLAS MOVIMENTAM O JOGADOR 2.
 * CADA MOVIMENTO INCREMENTA A COMPONETE Y DO JOGADOR.
*/
void specialKeyboard(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      jogador22->setPosicaoParaCima();
      
      break;
    case GLUT_KEY_DOWN:
      jogador22->setPosicaoParaBaixo();
      
      break;
  }

}

/**
 * FUNCAO QUE VERIFICA SE TELA CIMA/BAIXO DO TECLADO FOI SOLTA, SE FOI, SETA A POSICAO DO JOGADOR PARA PARADO.
*/
void specialKeyboardUpFunc(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      jogador22->setPosicaoParado();
      
      break;
    case GLUT_KEY_DOWN:
      jogador22->setPosicaoParado();
      
      break;
  }
}

/**
 * FUNCAO QUE VERIFICA AS TECLAS w E s DO TECLADO, ESSAS TECLAS MOVIMENTAM O JOGADOR 1.
 * CADA MOVIMENTO INCREMENTA A COMPONENTE Y DO JOGADOR.
 * 
 * FUNCAO TAMBEM VERIFICA SE A TECLA ESPACO FOI PRESSIONADA, SE FOI PRESSIONADA E O JOGADOR1/2 PONTUOU, ENTAO
 * CHAMA FUNCAO DE REPOR A BOLA, INDICANDO QUE O JOGADOR REPOSICIONOU A BOLA NO JOGO E SETA A FLAG flag PARA TRUE.
 * 
 * SE O JOGADOR1/2 NAO PONTUOU, SIGNIFICA QUE O JOGO IRA SER PAUSADO, ENTAO HABILITA A PAUSA SE ESTIVER DESABILITADA E DESABILITA SE A PAUSA
 * JA ESTIVER HABILITADA. PAUSA E DESPAUSA O JOGO MANTENDO O ESTADO DO JOGO NO MOMENTO DA PAUSA.
*/
void keyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      jogador11->setPosicaoParaCima();
      
      break;
    case 's':
      jogador11->setPosicaoParaBaixo();
      
      break;
  }

  if (key == ' ' && jogadorPontuou1) {
    reposicionarBola();

    flag = true;
  } else if (key == ' ' && jogadorPontuou2) {
    reposicionarBola();

    flag = true;
  } else if (key == ' ') {
    jogoPausado = jogoPausado == true ? false : true;
  }
}

/**
 * FUNCAO QUE VERIFICA SE TELA w/s DO TECLADO FOI SOLTA, SE FOI, SETA A POSICAO DO JOGADOR PARA PARADO.
*/
void keyboardUpFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      jogador11->setPosicaoParado();
      
      break;
    case 's':
      jogador11->setPosicaoParado();
      
      break;
  }
}

/**
 * FUNCAO QUE INICIALIZA OS SONS UTILIZADOS NO JOGO.
 * CARREGA ANTES DO JOGO COMECAR, PARA NAO DEMORAR CARREGANDO ARQUIVO DA MEMORIA DURANTE O JOGO.
*/
void inicializarSons() {
  if (!gerenciadorSom.carregarSom("colisao-parede.wav")) {
    exit(0);
  }

  if (!gerenciadorSom.carregarSom("pontuacao.wav")) {
    exit(0);
  }

  if (!gerenciadorSom.carregarSom("UC3CKCR-game-over-a.wav")) {
    exit(0);
  }
}

/**
 * FUNCAO MAIN, DEIXA O JOGO EM LOOP.
 * CHAMA FUNCAO PARA INICIALIZAR OS SONS DO JOGO.
*/
int main(int argc, char **argv) {
  initGlut(&argc, argv);

  glutDisplayFunc(display);

  glutKeyboardFunc(keyboardFunc);
  glutKeyboardUpFunc(keyboardUpFunc);

  glutSpecialFunc(specialKeyboard);
  glutSpecialUpFunc(specialKeyboardUpFunc);
  
  inicializacao();

  inicializarSons();

  glutTimerFunc(1, timer, 0);

  glutMainLoop();

  SDL_Quit();

  return 0;
}
