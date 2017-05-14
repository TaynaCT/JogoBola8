#pragma once
#include "Game.h"
#include "glm.h"
#include "Vector.h"

using namespace std;

GLMmodel* pmodel = NULL;

static float angle = 0.0;
static float red = 1.0, blue = 1.0, green = 1.0;
double motionScale = 0.00001;

//load model é tambem chamada no main!!!
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

//desenho das bolas
void drawBalls() {
	//bolas

	float ballSize = 0.05;
	float x = -0.16;
	float y = 1.25;
	float z = -0.16;
	float d = 0.15;

	for (int j = 1; j <= 5; j += 1)
	{
		z += d;
		for (int i = 1; i <= 5; i += 1)
		{
			
			if (j == 1 && i == 3) {
				glPushMatrix();
				glTranslatef(x, y, z);
				glutSolidSphere(ballSize, 10, 10);
				glPopMatrix();
				x -= d;
			}

			if (j == 2 && (i == 2 || i == 3)) {
				glPushMatrix();
				glTranslatef(x + 0.5F, y, z + 0.5);
				glutSolidSphere(ballSize, 10, 10);
				glPopMatrix();
				x += d;
			}

			if ((j == 3 && i != 1) || (j == 3 &&i != 5)) {
				glPushMatrix();
				glTranslatef(x, y, z);
				glutSolidSphere(ballSize, 10, 10);
				glPopMatrix();
				x -= d;
			}

			if (j == 4 && i != 5) {
				glPushMatrix();
				glTranslatef(x + 0.5F, y, z + 0.5F);
				glutSolidSphere(ballSize, 10, 10);
				glPopMatrix();
				x += d;
			}

			if (j == 5) {
				glPushMatrix();
				glTranslatef(x, y, z);
				glutSolidSphere(ballSize, 10, 10);
				glPopMatrix();
				x -= d;
			}
		}
	}
	//end
}

//Taco
//recebe o array com a posição do taco
void  drawTaco(double *camPos) {

	glPushMatrix();  //Set current matrix on the stack
	glColor3f(1.0f, 0.5f, 0.5f); // transformation 1
	glTranslatef(camPos[0], camPos[1], camPos[2]);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glutSolidCylinder(0.015f, 1, 6, 6);
	glPopMatrix();// Pop the old matrix without the transformations.

	std::cout << "----------------camPos[0] = " << camPos[0] << '\n';
	std::cout << "----------------camPos[1] = " << camPos[1] << '\n';
	std::cout << "----------------camPos[2] = " << camPos[2] << '\n';
}

//Coisas q vão ser apresentadas na tela
void drawSceneGame1(void) {

	glPushMatrix();
	glTranslatef(0, 1, 0);
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();

	/*glPushMatrix();  Set current matrix on the stack
	glColor3f(1.0f, 0.5f, 0.5f);  transformation 1 --> cor do objeto
	glTranslatef(0.5f, 1, 0.5f); transformation 2
	glRotatef(0.5, 0.0f, 0.0f, 1.0f); 
	glutSolidSphere(1, 10, 10);
	glPopMatrix();*/// Pop the old matrix without the transformations.

	//Vector coisa = Vector(10, 2, 1);
	

	drawBalls();
	
}

class Game1 : public Game { public: void gameSetWindowCallbacks(int windowID); };

//callbacks
void Game1::gameSetWindowCallbacks(int windowID) {
	for (int i = 0; i < int(gameMainWindows.size()); i++) {
		if (gameMainWindows[i].windowId == windowID) {
			glutSetWindowData((void *)&gameMainWindows[i]);
			break;
		}
	}

	glutDisplayFunc([](void) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		if (currentWindow->windowId == 1)
			currentWindow->windowId = currentWindow->windowId;

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);
*/
		//ativação de luzes
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		currentWindow->camera.cameraUpdate(0,0,0);

		drawSceneGame1();
		drawTaco(currentWindow->camera.camPos);
		

		//vista topo
		glPushMatrix();
		glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		glLoadIdentity();
		gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		
		drawSceneGame1();
		glPopMatrix(); // Pop the old matrix without the transformations.

		glutSwapBuffers();
	});

	glutReshapeFunc([](int w, int h) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		// Previne a divisão por zero
		if (h == 0) h = 1;
		double ratio = 1.0 * double(w) / double(h);

		// O viewport ocupará toda a janela
		glViewport(0, 0, w, h);

		// Efetua o reset do sistema de coordenadas
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Aplica a perspectiva
		gluPerspective(45.0, ratio, 0.1, 100.0);

		// Altera o sistema de coordenadas, para GL_MODELVIEW
		glMatrixMode(GL_MODELVIEW);
	});

	//INPUT DE TECLAS
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		if (key == 27 /* ESC */) glutLeaveMainLoop();

		if (toupper(key) == 'N') {

			glutSetWindow(currentWindow->windowId);
			glutReshapeWindow(950, 800);
			glutPositionWindow(x - (currentWindow->screenWidth / 2), y + (currentWindow->screenHeight / 2));

		}
		else if (toupper(key) == 'F') {

			glutSetWindow(currentWindow->windowId);
			glutFullScreen();

		}
	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {

	});

	//Quando as teclas são precionadas 
	glutSpecialFunc([](int key, int x, int y) {

		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);


		switch (key) {
		case GLUT_KEY_F1:
			glutSetWindow(currentWindow->windowId);
			glutReshapeWindow(950, 800);
			glutPositionWindow(20, 20);
			break;

		case GLUT_KEY_F2:
			glutSetWindow(currentWindow->windowId);
			glutFullScreen();
			break;
		case GLUT_KEY_UP:
			currentWindow->camera.cameraMove(0.5);
			break;

		case GLUT_KEY_DOWN:
			currentWindow->camera.cameraMove(-0.5);
			break;

		case GLUT_KEY_LEFT:
			currentWindow->camera.cameraPan(-0.5);
			break;
		case GLUT_KEY_RIGHT:
			currentWindow->camera.cameraPan(0.5);
			break;

		}

	});

	//Quando as teclas deixam de ser precionadas 
	glutSpecialUpFunc([](int key, int x, int y) {

		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		if (key == GLUT_KEY_UP) currentWindow->camera.cameraMove(0);
		else if (key == GLUT_KEY_DOWN)currentWindow->camera.cameraMove(0);
		else if (key == GLUT_KEY_LEFT)currentWindow->camera.cameraPan(0);
		else if (key == GLUT_KEY_RIGHT)currentWindow->camera.cameraPan(0);
	});

	//função callback do mouse
	glutMouseFunc([](int button, int state, int x, int y) {

	});

	// Movimento ativo do rato
	//ocorre quando o rato move com um botão pressionado
	glutMotionFunc([](int x, int y) {
		
		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		//Movimento da camera
		if (GLUT_RIGHT_BUTTON/*camFlag*/) {
			int xCenter = glutGet(GLUT_WINDOW_WIDTH) / 2;
			int yCenter = glutGet(GLUT_WINDOW_HEIGHT) / 2;

			double deltaX = (double)(x - xCenter) * motionScale;
			double deltaY = (double)(y - yCenter) * motionScale;

			currentWindow->camera.cameraPan(deltaX);
			currentWindow->camera.cameraTilt(deltaY);

			if (x > glutGet(GLUT_WINDOW_WIDTH) || y > glutGet(GLUT_WINDOW_HEIGHT)) {
				glutWarpPointer(xCenter, yCenter);
			}
			if (x < 0 || y < 0) {
				glutWarpPointer(xCenter, yCenter);
			}
		}

		//Movimento do taco
		if (GLUT_LEFT_BUTTON) {

		}

	});

	//tecção do movimento do mouse
	glutPassiveMotionFunc([](int x, int y) {

		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		//reset das das definições da camera
		currentWindow->camera.cameraPan(0);
		currentWindow->camera.cameraTilt(0);
		currentWindow->camera.cameraMove(0);
	});

	glutEntryFunc([](int state) {

	});

	glutMouseWheelFunc([](int wheel, int direction, int x, int y) {

		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
		glutSetWindow(currentWindow->windowId);

		if (GLUT_MIDDLE_BUTTON) {
			if (direction == 1) {
				currentWindow->camera.cameraMove(0.5);

			}
			else if (direction == -1)
			{
				currentWindow->camera.cameraMove(-0.5);
			}

		}
		/*else currentWindow->camera.cameraMove(0);*/
	});
}
