#include <iostream>
#include <math.h>
#include <stdio.h>

#include <GL/glut.h>

GLint LARGURA = 600, ALTURA = 600;

int tx = 0, ty = 0;
int angulo = 1;
int sx = 1, sy = 1;

int flagTeclado = 0;

struct VERTICE {
	int x;
	int y;
};

struct OBJETO {
	VERTICE *vertices;
	int num_vertices;
};

OBJETO *objeto;

OBJETO* criar_objeto() {
	OBJETO *obj = (OBJETO*) malloc(sizeof(OBJETO));
	obj->num_vertices = 3;
	obj->vertices = (VERTICE*) malloc(sizeof(VERTICE) * obj->num_vertices);
	obj->vertices[0].x = 300;
	obj->vertices[0].y = 200;
	obj->vertices[1].x = 350;
	obj->vertices[1].y = 275;
	obj->vertices[2].x = 250;
	obj->vertices[2].y = 275;

	return obj;
}

void initGlut(int *argc, char **argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LARGURA, ALTURA);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Transformacoes Geometricas 2D");
}

void inicializacao(GLvoid) {
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION); //esquerda, direita, baixo, cima
	gluOrtho2D(0, LARGURA, ALTURA, 0);

	objeto = criar_objeto();
}

VERTICE calcular_centroide(OBJETO *obj) {
	VERTICE centroide;

	centroide.x = 0;
	centroide.y = 0;

	for (int i = 0; i < obj->num_vertices; i++) {
		centroide.x += obj->vertices[i].x;
		centroide.y += obj->vertices[i].y;
	}

	centroide.x /= obj->num_vertices;
	centroide.y /= obj->num_vertices;

	return centroide;
}

VERTICE rotacao2d(VERTICE v, VERTICE centroide) {
	double s = sin(((angulo) * M_PI / 180.0));
	double c = cos(((angulo) * M_PI / 180.0));
	
	double matriz_rotacao[3][3] = {
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	};

	int matriz_translacao_origem[3][3] = {
		1, 0, -centroide.x,
		0, 1, -centroide.y,
		0, 0, 1
	};

	int matriz_translacao[3][3] = {
		1, 0, centroide.x,
		0, 1, centroide.y,
		0, 0, 1
	};

	int coord_homogeneas[3] = {v.x, v.y, 1};
	int coord_temp[3] = {0, 0, 0};
	int coord_finais[3] = {0, 0, 0};

	// coloca o ponto na origem

	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j++) {
			coord_temp[i] += matriz_translacao_origem[i][j] * coord_homogeneas[j];
		}
	}

	// rotaciona o objeto em torno da origem

	int temp[3] = {0, 0, 0};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i] += matriz_rotacao[i][j] * coord_temp[j];
		}
	}

	// translada o objeto para o ponto orinal

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			coord_finais[i] += matriz_translacao[i][j] * temp[j];
		}
	}

	VERTICE vertice_final;
	vertice_final.x = coord_finais[0];
	vertice_final.y = coord_finais[1];

	return vertice_final;
}

VERTICE translacao2d(VERTICE v, VERTICE centroide) {
	VERTICE v_transladado;

	int coord_homogeneas[3] = {v.x, v.y, 1};
	int coord_finais[3] = {0, 0, 0};
	int coord_temp[3] = {0, 0, 0};

	int matriz_translacao_origem[3][3] = {
		1, 0, -centroide.x,
		0, 1, -centroide.y,
		0, 0, 1
	};

	int matriz_translacao_original[3][3] = {
		1, 0, centroide.x,
		0, 1, centroide.y,
		0, 0, 1
	};

	// coloca o ponto na origem
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			coord_temp[i] += matriz_translacao_origem[i][j] * coord_homogeneas[j];
		}
	}

	// translada o objeto

	int matriz_translacao[3][3] = {
		1, 0, tx,
		0, 1, ty,
		0, 0, 1
	};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			coord_finais[i] += matriz_translacao[i][j] * coord_temp[j];
		}
	}

	// volta o objeto pra posição original

	int coord[3] = {0, 0, 0};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			coord[i] += matriz_translacao_original[i][j] * coord_finais[j];
		}
	}

	v_transladado.x = coord[0];
	v_transladado.y = coord[1];

	return v_transladado;
}

VERTICE escala2d(VERTICE v, VERTICE centroide) {
	int matriz_escala[3][3] = {
		sx, 0, 0,
		0, sy, 0,
		0, 0, 1
	};

	int matriz_translacao_origem[3][3] = {
		1, 0, -centroide.x,
		0, 1, -centroide.y,
		0, 0, 1
	};

	int matriz_translacao[3][3] = {
		1, 0, centroide.x,
		0, 1, centroide.y,
		0, 0, 1
	};

	int coord_homogeneas[3] = {v.x, v.y, 1};
	int coord_temp[3] = {0, 0, 0};
	int coord_finais[3] = {0, 0, 0};

	// coloca o ponto na origem

	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j++) {
			coord_temp[i] += matriz_translacao_origem[i][j] * coord_homogeneas[j];
		}
	}

	// escala o objeto em torno da origem

	int temp[3] = {0, 0, 0};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp[i] += matriz_escala[i][j] * coord_temp[j];
		}
	}

	// translada o objeto para o ponto orinal

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			coord_finais[i] += matriz_translacao[i][j] * temp[j];
		}
	}

	VERTICE vertice_final;
	vertice_final.x = coord_finais[0];
	vertice_final.y = coord_finais[1];

	return vertice_final;
}

void desenharObjeto() {
	glColor3f(1.0, 0.0, 0.0);
	
	VERTICE centroide = calcular_centroide(objeto);

	VERTICE v;

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < objeto->num_vertices; i++) {

			if (flagTeclado == 1) {
				v = translacao2d(objeto->vertices[i], centroide);
			} else if (flagTeclado == 2) {
				v = rotacao2d(objeto->vertices[i], centroide);
			} else if (flagTeclado == 3) {
				v = escala2d(objeto->vertices[i], centroide);
			} else {
				v = translacao2d(objeto->vertices[i], centroide);
			}
	
			glVertex2i(v.x, v.y);
		}
	glEnd();
}

void desenha(GLvoid) {
	glClear(GL_COLOR_BUFFER_BIT);
	desenharObjeto();   
	glFlush();
}

void eventoMouse(GLint button, GLint action, GLint x, GLint y) {
  // TO DO...
}

void eventoTeclado(GLubyte key, GLint x, GLint y) {
	if (key == 'w') {
		ty -= 1;
		flagTeclado = 1;
	} else if (key == 's') {
		ty += 1;
		flagTeclado = 1;
	} else if (key == 'a') {
		tx -= 1;
		flagTeclado = 1;
	} else if (key == 'd') {
		tx += 1;
		flagTeclado = 1;
	} else if (key == '4') {
		angulo -= 10;
		flagTeclado = 2;
	} else if (key == '6') {
		angulo += 10;
		flagTeclado = 2;
	}

	glutPostRedisplay();
}

void eventoTecladoEsp(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		int add = sx + 1 == 0 ? 3 : 1;

		flagTeclado = 3;

		sx += add;
	} else if (key == GLUT_KEY_RIGHT) {
		int add = sx - 1 == 0 ? 3 : 1;

		flagTeclado = 3;

		sx -= add;
	} else if (key == GLUT_KEY_UP) {
		int add = sy + 1 == 0 ? 3 : 1;

		flagTeclado = 3;

		sy += add;
	} else if (key == GLUT_KEY_DOWN) {
		int add = sy - 1 == 0 ? 3 : 1;

		flagTeclado = 3;

		sy -= add;
	}

	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	initGlut(&argc, argv);
	inicializacao();
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(desenha);
	glutKeyboardFunc(eventoTeclado);
	glutSpecialFunc(eventoTecladoEsp);
	
	glutMainLoop();

	return 0;
}
