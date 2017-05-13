#include <iostream>
#include <gl/freeglut.h>
#include "Game.h"
//#include "SnowMan.h"

#define NOME_JANELA "BOLA 8"

namespace std {

	void Game::changeSize(int w, int h) {
		// Previne a divisão por zero
		if (h == 0) h = 1;
		double ratio = 1.0 * double(w) / double(h);

		// O viewport ocupará toda a janela
		glViewport(0, 0, w, h);

		// Efetua o reset do sistema de coordenadas
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Aplica a perspectiva
		gluPerspective(45.0, ratio, 1.0, 100.0);

		// Altera o sistema de coordenadas, para GL_MODELVIEW
		glMatrixMode(GL_MODELVIEW);
	}

	void Game::renderScene(void)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glLoadIdentity();
		gluLookAt(5.0, 5.0, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);

		drawScene();

		glutSwapBuffers();
	}

	void Game::run(void) {
		if (running == true) return;
		else running = true;

		glutDisplayFunc(this->renderScene);
		glutIdleFunc(this->renderScene);
		glutReshapeFunc(this->changeSize);
		glutKeyboardFunc(this->processNormalKeys);
		glutSpecialFunc(this->processSpecialKeys);

		glutMainLoop();
	}

	void Game::init() {
		int argc = 1;
		char *argv[1] = { (char*) "none" };

		if (running == true) return;

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(x, y);
		glutInitWindowSize(screenWidth, screenHeight);
		window = glutCreateWindow(NOME_JANELA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

	void Game::init(int x, int y, int width, int height) {
		Game::x = x;
		Game::y = y;
		screenWidth = width;
		screenHeight = height;

		init();
	}
}