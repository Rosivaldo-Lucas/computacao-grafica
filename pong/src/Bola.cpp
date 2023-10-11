#include "../includes/Bola.hpp"

Bola::Bola(float cx, float cy, float raio) {
  this->cx = cx;
  this->cy = cy;
  this->raio = raio;
}

float Bola::getCx() {
  return this->cx;
}

void Bola::setCx(float cx) {
  this->cx = cx;
}

float Bola::getCy() {
  return this->cy;
}

void Bola::setCy(float cy) {
  this->cy = cy;
}

float Bola::getRaio() {
  return this->raio;
}

void Bola::atualizarPosicao(float passoX, float passoY) {
  this->cx += passoX;
  this->cy += passoY;
}
