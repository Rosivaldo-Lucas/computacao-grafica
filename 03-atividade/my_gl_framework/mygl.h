#ifndef _MYGL_H_
#define _MYGL_H_
#endif

#include "definitions.h"

// estrutura para encapsular os dados da coordenada e cor do ponto
typedef struct Ponto Ponto;
struct Ponto {
  int x;
  int y;
  int R;
  int G;
  int B;
};

//-----------------------------------------------------------------------------
void MyGlDraw(void);

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
void PutPixel(void);
void DrawLine(void);

void myPutPixel(Ponto p);
void myDrawLine(Ponto pi, Ponto pf);
void myDrawTriangle(Ponto pa, Ponto pb, Ponto pc);

void myDrawLineOctant1(Ponto pi, Ponto pf);
