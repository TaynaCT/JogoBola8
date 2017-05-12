#include <gl/freeglut.h>
#include <iostream>
#include "Camera.h"
#include "glm.h"

using namespace std;

GLMmodel* pmodel = NULL;
int wId;

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


//Criação dos objetos !!!!! 
void renderScene(void) {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.5f, 0, 0.5f);
	glutWireSphere(1, 10, 10);
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	//glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHTING);
	//glFlush();
	glutSwapBuffers();
	
}

void changeSize(int w, int h)
{
	float ratio;

	if (h == 0) h = 1;
	ratio = 1.0f * w / h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	Camera cam;

	// Inicializar o GLUT e a janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 600);
	//Criação da janela principal
	wId = glutCreateWindow("******* BOLA 8 ******");
	cam.cameraSetPosition(0.0, 1.0, 5.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	cam.cameraUpdate(0,0,0);

	// Registar funções para processar eventos (callbacks)
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	//glutReshapeFunc(changeSize);
	
	/*glutSetWindowData(WinMain)
*/
	//carrega o modelo
	loadmodel();

	// Entrar no ciclo de processamento do GLUT
	glutMainLoop();

	return 0;
}

