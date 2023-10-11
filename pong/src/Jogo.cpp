#include "../includes/Jogo.hpp"

Jogo::Jogo(int largura, int altura) {
  this->largura = largura;
  this->altura = altura;
}

bool Jogo::verificarColiscaoJogadorTela(Jogador *jogador) {
  if ((jogador->getY() <= 0 && jogador->isPosicaoParaBaixo())) {
    return true;
  }

  if ((jogador->getY() >= this->getAltura() - 200 && jogador->isPosicaoParaCima())) {
    return true;
  }

  return false;
}

int Jogo::getLargura() {
  return this->largura;
}

int Jogo::getAltura() {
  return this->altura;
}
