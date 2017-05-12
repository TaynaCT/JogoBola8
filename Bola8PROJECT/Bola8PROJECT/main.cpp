#include <gl/freeglut.h>
#include <iostream>
#include "Camera.h"

using namespace std;

GLMmodel* pmodel = NULL;


void loadmodel(void)
{
	if(pmodel == NULL)
	{
        pmodel = glmReadOBJ("modelos/PoolTableWithoutUVW.obj");
		if(pmodel == NULL) {exit(0);}
		else
		{
			glmUnitize(pmodel);
			glmLinearTexture(pmodel);
			glmScale(pmodel, 1.0);
			glmFacetNormals(pmodel);
			glmVertexNormals(pmodel, 90.0);
		}
    }
}



void renderScene(void) {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	
	glFlush();
	
}

int main(int argc, char **argv) {
	Camera cam;

	// Inicializar o GLUT e a janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Programa-01");
	// Registar funções para processar eventos (callbacks)
	glutDisplayFunc(renderScene);
	// Entrar no ciclo de processamento do GLUT
	glutMainLoop();
	
	return 0;
}