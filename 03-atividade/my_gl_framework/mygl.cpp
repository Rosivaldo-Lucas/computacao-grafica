#include "definitions.h"
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

void showPutPixels();
void showLineOctants();
void showTriangle();

//-----------------------------------------------------------------------------
void MyGlDraw(void) {
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************	
	// PutPixel();
	// DrawLine();

	showLineOctants();
	showPutPixels();
	showTriangle();
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
	/**
	 * Calcula o índice no array FBptr com base nas coordenadas x e y,
	 * assim acessando na coordenada (p.x, p.y). 
	*/
  int indiceInicioPixel = (p.y * IMAGE_WIDTH + p.x) * 4;

	// Escreve os valores das componentes de cor no array FBptr
	FBptr[indiceInicioPixel] = p.R;   		// componente R
	FBptr[indiceInicioPixel + 1] = p.G; 	// componente G
	FBptr[indiceInicioPixel + 2] = p.B; 	// componente B
	FBptr[indiceInicioPixel + 3] = 255; 	// componente A
}

void myDrawLine(Ponto pi, Ponto pf) {
	int dx = pf.x - pi.x;
	int dy = pf.y - pi.y;
	int x = pi.x;
	int y = pi.y;
	float e = 0.0f;

	Ponto p;
	p.R = pi.R;
	p.G = pi.G;
	p.B = pi.B;

	int stepX = dx >= 0 ? 1 : -1; // passo a ser utilizado em x
	int stepY = dy >= 0 ? 1 : -1; // passo a ser utilizado em y

	dx *= stepX; // garante que dx seja positivo
	dy *= stepY; // garante que dy seja positivo

	// realiza a rasterização para todos os 8 octantes
	if (dx >= dy) {
		while (x != pf.x) {
			p.x = x;
			p.y = y;
			myPutPixel(p);

			x += stepX;
			e += 2 * dy;

			if (e >= dx) {
				y += stepY;
				e -= 2 * dx;
			}
		}
	} else {
		while (y != pf.y) {
			p.x = x;
			p.y = y;
			myPutPixel(p);

			y += stepY;
			e += 2 * dx;

			if (e >= dy) {
				x += stepX;
				e -= 2 * dy;
			}
		}
	}
}

void myDrawLineOctant1(Ponto pi, Ponto pf) {
	int dx = pf.x - pi.x;
	int dy = pf.y - pi.y;
	int x = pi.x;
	int y = pi.y;
	float e = 0.0f;

	Ponto p;

	while (x < pf.x) {
		p.x = x;
		p.y = y;
		p.R = pi.R;
		p.G = pi.G;
		p.B = pi.B;

		myPutPixel(p);

		x = x + 1;
		e = e + 2 * dy;

		if (e >= dy) {
			y = y + 1;
			e = e - 2 * dx;
		}
	}
}

void myDrawTriangle(Ponto pa, Ponto pb, Ponto pc) {
	myDrawLine(pa, pb);
	myDrawLine(pa, pc);
	myDrawLine(pb, pc);
}

void showPutPixels() {
	Ponto p1;
	p1.x = 256;
	p1.y = 256;
	p1.R = 255;
	p1.G = 0;
	p1.B = 0;

	Ponto p2;
	p2.x = 257;
	p2.y = 256;
	p2.R = 255;
	p2.G = 0;
	p2.B = 0;

	Ponto p3;
	p3.x = 258;
	p3.y = 256;
	p3.R = 0;
	p3.G = 255;
	p3.B = 0;

	Ponto p4;
	p4.x = 259;
	p4.y = 256;
	p4.R = 0;
	p4.G = 255;
	p4.B = 0;

	Ponto p5;
	p5.x = 260;
	p5.y = 256;
	p5.R = 0;
	p5.G = 0;
	p5.B = 255;

	Ponto p6;
	p6.x = 261;
	p6.y = 256;
	p6.R = 0;
	p6.G = 0;
	p6.B = 255;

	myPutPixel(p1);
	myPutPixel(p2);
	myPutPixel(p3);
	myPutPixel(p4);
	myPutPixel(p5);
	myPutPixel(p6);
}

void showLineOctants() {
	Ponto pi;
	pi.x = 256;
	pi.y = 256;
	pi.R = 255;
	pi.G = 0;
	pi.B = 0;

	Ponto pf1;
	pf1.x = 512;
	pf1.y = 256;
	pf1.R = 255;
	pf1.G = 0;
	pf1.B = 0;

	Ponto pf1_1;
	pf1_1.x = 512;
	pf1_1.y = 384;
	pf1_1.R = 255;
	pf1_1.G = 0;
	pf1_1.B = 0;

	Ponto pf2;
	pf2.x = 512;
	pf2.y = 512;
	pf2.R = 255;
	pf2.G = 0;
	pf2.B = 0;

	Ponto pf2_2;
	pf2_2.x = 384;
	pf2_2.y = 512;
	pf2_2.R = 255;
	pf2_2.G = 0;
	pf2_2.B = 0;

	Ponto pf3;
	pf3.x = 256;
	pf3.y = 512;
	pf3.R = 255;
	pf3.G = 0;
	pf3.B = 0;

	Ponto pf3_3;
	pf3_3.x = 128;
	pf3_3.y = 512;
	pf3_3.R = 255;
	pf3_3.G = 0;
	pf3_3.B = 0;

	Ponto pf4;
	pf4.x = 0;
	pf4.y = 512;
	pf4.R = 255;
	pf4.G = 0;
	pf4.B = 0;

	Ponto pf4_4;
	pf4_4.x = 0;
	pf4_4.y = 384;
	pf4_4.R = 255;
	pf4_4.G = 0;
	pf4_4.B = 0;

	Ponto pf5;
	pf5.x = 0;
	pf5.y = 256;
	pf5.R = 255;
	pf5.G = 0;
	pf5.B = 0;

	Ponto pf5_5;
	pf5_5.x = 0;
	pf5_5.y = 128;
	pf5_5.R = 255;
	pf5_5.G = 0;
	pf5_5.B = 0;

	Ponto pf6;
	pf6.x = 0;
	pf6.y = 0;
	pf6.R = 255;
	pf6.G = 0;
	pf6.B = 0;

	Ponto pf6_6;
	pf6_6.x = 128;
	pf6_6.y = 0;
	pf6_6.R = 255;
	pf6_6.G = 0;
	pf6_6.B = 0;

	Ponto pf7;
	pf7.x = 256;
	pf7.y = 0;
	pf7.R = 255;
	pf7.G = 0;
	pf7.B = 0;

	Ponto pf7_7;
	pf7_7.x = 384;
	pf7_7.y = 0;
	pf7_7.R = 255;
	pf7_7.G = 0;
	pf7_7.B = 0;

	Ponto pf8;
	pf8.x = 512;
	pf8.y = 0;
	pf8.R = 255;
	pf8.G = 0;
	pf8.B = 0;

	Ponto pf8_8;
	pf8_8.x = 512;
	pf8_8.y = 128;
	pf8_8.R = 255;
	pf8_8.G = 0;
	pf8_8.B = 0;

	myDrawLine(pi, pf1);
	myDrawLine(pi, pf1_1);
	myDrawLine(pi, pf2);
	myDrawLine(pi, pf2_2);
	myDrawLine(pi, pf3);
	myDrawLine(pi, pf3_3);
	myDrawLine(pi, pf4);
	myDrawLine(pi, pf4_4);
	myDrawLine(pi, pf5);
	myDrawLine(pi, pf5_5);
	myDrawLine(pi, pf6);
	myDrawLine(pi, pf6_6);
	myDrawLine(pi, pf7);
	myDrawLine(pi, pf7_7);
	myDrawLine(pi, pf8);
	myDrawLine(pi, pf8_8);
}

void showTriangle() {
	Ponto pa;
	pa.x = 256;
	pa.y = 0;
	pa.R = 255;
	pa.G = 0;
	pa.B = 0;

	Ponto pb;
	pb.x = 0;
	pb.y = 256;
	pb.R = 255;
	pb.G = 0;
	pb.B = 0;

	Ponto pc;
	pc.x = 512;
	pc.y = 256;
	pc.R = 255;
	pc.G = 0;
	pc.B = 0;

	myDrawTriangle(pa, pb, pc);
}
