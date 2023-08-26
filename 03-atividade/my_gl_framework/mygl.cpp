#include "definitions.h"
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

//-----------------------------------------------------------------------------
void MyGlDraw(void) {
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************	
	// PutPixel();
	// DrawLine();

	// myPutPixel(ponto);
	// myPutPixel(512, 256, 255, 0, 0);
}

void PutPixel(void) {
	// Escreve um pixel vermelho na posicao (0,0) da tela:
	FBptr[0] = 255; // componente R
	FBptr[1] = 0;   // componente G
	FBptr[2] = 0;   // componente B
	FBptr[3] = 255; // componente A

	// Escreve um pixel verde na posicao (1,0) da tela:
	FBptr[4] = 0;   // componente R
	FBptr[5] = 255; // componente G
	FBptr[6] = 0;   // componente B
	FBptr[7] = 255; // componente A

	// Escreve um pixel azul na posicao (2,0) da tela:
	FBptr[8] = 0;    // componente R
	FBptr[9] = 0;    // componente G
	FBptr[10] = 255; // componente B
	FBptr[11] = 255; // componente A
}

void DrawLine(void) {
	for (unsigned int i = 0; i < 250; ++i) {
		FBptr[4 * i + 4 * i * IMAGE_WIDTH + 0] = 255;
		FBptr[4 * i + 4 * i * IMAGE_WIDTH + 1] = 0;
		FBptr[4 * i + 4 * i * IMAGE_WIDTH + 2] = 255;
		FBptr[4 * i + 4 * i * IMAGE_WIDTH + 3] = 255;
	}
}

void myPutPixel(Ponto p) {
	// Calcula o índice no array FBptr com base nas coordenadas x e y, assim escrevendo na coordenada (p.x, p.y)
  int indiceInicioPixel = (p.y * IMAGE_WIDTH + p.x) * 4;

	// Escreve os valores das componentes de cor no array FBptr
	FBptr[indiceInicioPixel] = p.R;   		// componente R
	FBptr[indiceInicioPixel + 1] = p.G; 	// componente G
	FBptr[indiceInicioPixel + 2] = p.B; 	// componente B
	FBptr[indiceInicioPixel + 3] = 255; 	// componente A
}

void myDrawLine(Ponto pi, Ponto pf) {
	int dx = abs(pf.x - pi.x);
	int dy = abs(pf.y - pi.y);
	int x = pi.x;
	int y = pi.y;
	int sx = pf.x >= pi.x ? 1 : -1;
	int sy = pf.y >= pi.y ? 1 : -1;
	int err = dx - dy;

	Ponto ponto;

	while (true) {	
		ponto.x = x;
		ponto.y = y;
		ponto.R = 255;
		ponto.G = 0;
		ponto.B = 0;

		myPutPixel(ponto);

		if (x == pf.x && y == pf.y) {
			break;
		}

		int e2 = 2 * err;

		if (e2 > -dy) {
			err -= dy;
			x += sx;
		}

		if (e2 < dx) {
			err += dx;
			y += sy;
		}
	}
}

void myDrawTriangle(Ponto pa, Ponto pb, Ponto pc) {
	myDrawLine(pa, pb);
	myDrawLine(pa, pc);
	myDrawLine(pb, pc);
}
