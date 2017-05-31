#pragma once
#include "Game.h"
#include "glm.h"
#include "Vector.h"
#include "tinymath.h"
#include"Ball.h"

using namespace std;

GLMmodel* pmodel = NULL;
vector<Ball> gameBalls;

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

//Taco
//recebe o array com a posição do taco
void  drawTaco(double *camPos) {

	glPushMatrix();  //Set current matrix on the stack
	glColor3f(1.0f, 0.5f, 0.5f); // transformation 1
	glTranslatef(camPos[0], camPos[1], camPos[2]);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glutSolidCylinder(0.015f, 1, 6, 6);
	
	glPopMatrix();// Pop the old matrix without the transformations.

}

//desenha as bolas organizadas no centro da mesa
void drawGameBalls() {

	float y = 1.24;
	float size = 0.04;
	float distance = 0.05;

	//primeira bola da lista é a bola branca
	gameBalls.push_back(Ball(0.5, y, 0, size));
	
	for (int x = 0; x < 5; x++)
	{					
			if (x == 0 ) {
				glPushMatrix();
				gameBalls.push_back(Ball(x*distance, y, x*(-distance), size));
				glPopMatrix();
			}	

			if (x == 1) {
				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*(-distance), size));
				glPopMatrix();

			}

			if (x == 2) {
				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*distance, size));
				glPopMatrix();

				//bola 8
				//bola no centro da mesa 
				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, 0, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*-distance, size));
				glPopMatrix();				
			}		

			if (x == 3) {
				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*distance, size));
				glPopMatrix();
				
				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*-distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, -distance, size));
				glPopMatrix();

			}

			if (x == 4) {
				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, x*-distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, 2*distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, 2*-distance, size));
				glPopMatrix();

				glPushMatrix();
				gameBalls.push_back(Ball(x*(-distance), y, 0, size));
				glPopMatrix();
			}
	}
	
}

//função que lêr o texto é apresentado na tela
void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;

	// set position to start drawing fonts
	glRasterPos2f(x, y);

	// loop all the characters in the string
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

//Coisas q vão ser apresentadas na tela
void drawSceneGame1(void) {
	
	for (vector<Ball>::iterator it = gameBalls.begin(); it != gameBalls.end(); it++) {
		glPushMatrix();
		it->drawBall();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL); //modelo 3d
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);	
	glPopMatrix();

	/*glPushMatrix();  Set current matrix on the stack
	glColor3f(1.0f, 0.5f, 0.5f);  transformation 1 --> cor do objeto
	glTranslatef(0.5f, 1, 0.5f); transformation 2
	glRotatef(0.5, 0.0f, 0.0f, 1.0f); 
	glutSolidSphere(1, 10, 10);
	glPopMatrix();*/// Pop the old matrix without the transformations.

	//eixo de x
	glPushMatrix();	
	glBegin(GL_LINE_STRIP);
	glVertex3f(-10, 2, 0);
	glVertex3f(10, 2, 0);
	glEnd();
	glPopMatrix();

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
		
		//TEXTO
		glColor3f(0.0, 1.0, 1.0);

		// switch to projection mode
		glMatrixMode(GL_PROJECTION);
		// save previous matrix which contains the 
		//settings for the perspective projection
		glPushMatrix();
		// reset matrix
		glLoadIdentity();
		// set a 2D orthographic projection
		gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		// invert the y axis, down is positive
		glScalef(1, -1, 1);
		// mover the origin from the bottom left corner
		// to the upper left corner
		glTranslatef(0, -glutGet(GLUT_WINDOW_HEIGHT) / 2, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		//string
		renderBitmapString(10, 10, GLUT_BITMAP_8_BY_13, "JOGO BOLA 8");
		renderBitmapString(10, 20, GLUT_BITMAP_8_BY_13, "Full screen");
		renderBitmapString(10, 30, GLUT_BITMAP_8_BY_13, "Exit - ESC");
		glPopMatrix();

		// set the current matrix to GL_PROJECTION
		glMatrixMode(GL_PROJECTION);
		// restore previous settings
		glPopMatrix();
		// get back to GL_MODELVIEW matrix
		glMatrixMode(GL_MODELVIEW);


		//vista topo
		glPushMatrix();

		glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		glLoadIdentity();
		gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		//ativação de luzes
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

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
