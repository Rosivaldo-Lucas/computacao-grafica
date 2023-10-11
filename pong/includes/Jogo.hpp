#ifndef __JOGO__
#define __JOGO__

#include "Jogador.hpp"

class Jogo {

  private:
    int largura;
    int altura;
    bool isGameOver;


  public:
    Jogo(int largura, int altura);

    bool verificarColiscaoJogadorTela(Jogador *jogador);

    int getLargura();
    int getAltura();

};

#endif
