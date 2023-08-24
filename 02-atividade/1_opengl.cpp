#include <iostream>
#include <cmath>
#include <GL/glut.h>

GLint WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

GLint xi, yi;
GLint xf, yf;

int qtdClicks = 0;
int currentOption = 0;
bool isMenuOpen = false;

void initializeGlut(int argc, char *argv[]) {
	//Inicializa a biblioteca GLUT e negocia uma 
	//seção com o sistema de janelas
	glutInit(&argc, argv);

	//Define qual será o modo inicial de display
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Definir a posição inicial da janela, passando 
	//canto superior esquerdp
	glutInitWindowPosition(100,100);

	//Define a largura e altura da janela
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Cria a janela, passando o titulo
	glutCreateWindow("Meu primeiro programa OpenGL");
}

void initialize() {
	//Define a cor de fundo
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//Matriz que usaremos para opperacoes
	glMatrixMode(GL_MODELVIEW);

	//erquerdo, direito, baixo, cima
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

void handle_menu(int option) {
	if (option == 5) {
		glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
	} else {
  	currentOption = option;
	}
}

void inicializeMenu() {
	int submenu = glutCreateMenu(handle_menu);
	glutAddMenuEntry("Ponit", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Rectangle", 3);
	glutAddMenuEntry("Circle", 4);

	int menu = glutCreateMenu(handle_menu);
	glutAddSubMenu("Drawing", submenu);
	glutAddMenuEntry("Clean", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawPoint(GLfloat x, GLfloat y) {
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
	glFlush();
}

void drawLine(GLfloat xi, GLfloat yi, GLfloat xf, GLfloat yf) {
	glBegin(GL_LINES);
		glVertex2f(xi, yi);
		glVertex2f(xf, yf);
	glEnd();
}

void drawRectangle(GLfloat xi, GLfloat yi, GLfloat xf, GLfloat yf) {
	glBegin(GL_LINES);
		glVertex2f(xi, yi);
		glVertex2f(xi, yf);

		glVertex2f(xi, yf);
		glVertex2f(xf, yf);

		glVertex2f(xf, yf);
		glVertex2f(xf, yi);

		glVertex2f(xf, yi);
		glVertex2f(xi, yi);
	glEnd();
}

void drawCircle(GLfloat xi, GLfloat yi, GLfloat xf, GLfloat yf) {
	GLfloat centerX = xi;
	GLfloat centerY = yi;
	GLfloat radius = sqrt((xf - xi) * (xf - xi) + (yf - yi) * (yf - yi));

	int numSegments = 50;
	
	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < numSegments; i++) {
			float angle = 2.0 * 3.1415926 * float(i) / float(numSegments);
			
			GLfloat x = centerX + radius * cos(angle);
			GLfloat y = centerY + radius * sin(angle);
			
			glVertex2f(x, y);
		}
	glEnd();
}

void draw() {
	if (!isMenuOpen) {
		glClear(GL_COLOR_BUFFER_BIT);

		glPointSize(5.0);
		glColor3f(1.0f, 0.0f, 0.0f);
		// glBegin(GL_LINE_LOOP);
		//     glVertex2f(10.0, 10.0);
		//     glVertex2f(100.0, 10.0);
		//     glColor3f(0.0f, 0.0f, 1.0f);
		//     glVertex2f(10.0, 50.0);
		//     glVertex2f(100.0, 50.0);
		// glEnd();

		glFlush();
	}
}

void handle_mouse(GLint button, GLint action, GLint x, GLint y) {
	if (currentOption == 1) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			drawPoint(x, y);
		}
	} else if (currentOption == 2) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			if (qtdClicks == 0) {
				xi = x;
				yi = y;

				qtdClicks = 1;
			} else if (qtdClicks == 1) {
				xf = x;
				yf = y;

				qtdClicks = 0;

				drawLine(xi, yi, xf, yf);
			}

			drawPoint(x, y);
		}
	} else if (currentOption == 3) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			if (qtdClicks == 0) {
				xi = x;
				yi = y;

				qtdClicks = 1;
			} else if (qtdClicks == 1) {
				xf = x;
				yf = y;

				qtdClicks = 0;

				drawRectangle(xi, yi, xf, yf);
			}

			drawPoint(x, y);
		}
	} else if (currentOption == 4) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			if (qtdClicks == 0) {
				xi = x;
				yi = y;

				qtdClicks = 1;
			} else if (qtdClicks == 1) {
				xf = x;
				yf = y;

				qtdClicks = 0;

				drawCircle(xi, yi, xf, yf);
			}

			drawPoint(x, y);
		}
	}
}

void handle_keyboard(unsigned char key, GLint x, GLint y) {
	if (key == 'R' || key == 'r') {
		glColor3f(1.0f, 0.0f, 0.0f);
	} else if (key == 'G' || key == 'g') {
		glColor3f(0.0f, 1.0f, 0.0f);
	} else if (key == 'B' || key == 'b') {
		glColor3f(0.0f, 0.0f, 1.0f);
	}
}

void handle_mouse_motion(GLint x, GLint y) {
  drawPoint(x, y);
}

int main(int argc, char *argv[]) {   
	initializeGlut(argc, argv);
	initialize();
	inicializeMenu();

	glutDisplayFunc(draw);
	glutMouseFunc(handle_mouse);
	glutKeyboardFunc(handle_keyboard);
	glutMotionFunc(handle_mouse_motion);

	glutMainLoop();
	
	return EXIT_SUCCESS;
}
