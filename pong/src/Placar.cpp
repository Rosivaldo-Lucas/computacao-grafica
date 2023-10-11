#include "../includes/Placar.hpp"

Placar::Placar() {
  this->pontuacaoJogador1 = 0;
  this->pontuacaoJogador2 = 0;
}

int Placar::getPontuacaoJogador1() {
  return this->pontuacaoJogador1;
}

int Placar::getPontuacaoJogador2() {
  return this->pontuacaoJogador2;
}

void Placar::incrementarPontuacaoJogador1() {
  this->pontuacaoJogador1 += 1;
}

void Placar::incrementarPontuacaoJogador2() {
  this->pontuacaoJogador2 += 1;
}
