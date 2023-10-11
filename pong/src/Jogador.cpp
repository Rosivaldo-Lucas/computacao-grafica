#include "../includes/Jogador.hpp"

Jogador::Jogador(std::string nome, int x, int y) {
  this->nome = nome;
  this->x = x;
  this->y = y;
  this->altura = 200;
  this->largura = 20;
  this->pontuacao = 0;
  this->posicao = Posicao::PARADO;
}

void Jogador::moverParaCima() {
  this->y += 3;
}

void Jogador::moverParaBaixo() {
  this->y -= 3;
}

void Jogador::aumentarPontuacao() {
  this->pontuacao += 1;
}

int Jogador::getX() {
  return this->x;
}

int Jogador::getY() {
  return this->y;
}

int Jogador::getAltura() {
  return this->altura + this->y;
}

int Jogador::getLargura() {
  return this->largura + this->x;
}

Posicao Jogador::getPosicao() {
  return this->posicao;
}

void Jogador::setPosicaoParaCima() {
  this->posicao = Posicao::CIMA;
}

void Jogador::setPosicaoParaBaixo() {
  this->posicao = Posicao::BAIXO;
}

void Jogador::setPosicaoParado() {
  this->posicao = Posicao::PARADO;
}

bool Jogador::isPosicaoParaCima() {
  return this->posicao == Posicao::CIMA;
}

bool Jogador::isPosicaoParaBaixo() {
  return this->posicao == Posicao::BAIXO;
}
