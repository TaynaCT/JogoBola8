#include <gl/freeglut.h>
#include <iostream>
#include "Camera.h"
#include "glm.h"

using namespace std;


void renderScene(void) {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.5f, 0, 0.5f);
	 glutWireSphere(1, 10, 10);
	
	glFlush();
	
}

int main(int argc, char **argv) {
	Camera cam;

	// Inicializar o GLUT e a janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 600);
	//Criação da janela principal
	int wId = glutCreateWindow("******* BOLA 8 ******");
	cam.cameraSetPosition(0.0, 1.0, 5.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	cam.cameraUpdate(0,0,0);
	// Registar funções para processar eventos (callbacks)
	glutDisplayFunc(renderScene);
	// Entrar no ciclo de processamento do GLUT
	glutMainLoop();
	
	return 0;
}