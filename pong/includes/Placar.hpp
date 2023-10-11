#ifndef __PLACAR__
#define __PLACAR__

class Placar {

  private:
    int pontuacaoJogador1;
    int pontuacaoJogador2;

  public:
    Placar();

    int getPontuacaoJogador1();
    int getPontuacaoJogador2();

    void incrementarPontuacaoJogador1();
    void incrementarPontuacaoJogador2();

};

#endif
