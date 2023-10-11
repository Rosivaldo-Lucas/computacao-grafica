#ifndef __BOLA__
#define __BOLA__

class Bola {
  private:
    float cx;
    float cy;
    float raio;

  public:
    Bola(float cx, float cy, float raio);

    float getCx();
    void setCx(float cx);

    float getCy();
    void setCy(float cy);

    float getRaio();

    void atualizarPosicao(float passoX, float passoY);

};

#endif
