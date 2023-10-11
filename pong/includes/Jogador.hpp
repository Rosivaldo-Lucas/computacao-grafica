#ifndef __JOGADOR__
#define __JOGADOR__

#include <string>

enum class Posicao {
  CIMA,
  BAIXO,
  PARADO,
};

class Jogador {

  private:
    std::string nome;
    int x;
    int y;
    int altura;
    int largura;
    int pontuacao;
    Posicao posicao;

  public:
    Jogador(std::string nome, int x, int y);

    void moverParaCima();
    void moverParaBaixo();
    void aumentarPontuacao();

    int getX();
    int getY();
    int getAltura();
    int getLargura();
    Posicao getPosicao();
    void setPosicaoParaCima();
    void setPosicaoParaBaixo();
    void setPosicaoParado();
    bool isPosicaoParaCima();
    bool isPosicaoParaBaixo();

};

#endif
