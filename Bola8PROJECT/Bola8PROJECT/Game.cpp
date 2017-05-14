#include <iostream>
#include <vector>
#include <gl/freeglut.h>
#include "Game.h"

//#define NOME_JANELA "BOLA 8"

namespace std {

	bool Game::gameRunning = false;
	bool Game::gameInit = false;
	int Game::gameFPS = 100;

	Game::Game() {
		static int argc = 1;
		static char *argv[] = { "none" };

		if (gameInit == false) {
			glutInit(&argc, argv);
			gameInit = true;
		}

		gameRunning = false;

		std::cout << "[Game] Create Game" << std::endl;
	}

	Game::~Game() {
		std::cout << "[Game] Destroy Game" << std::endl;
	}

	void Game::gameRun(void) {
		if (gameRunning == true) return;
		else gameRunning = true;

		glutMainLoop();
	}

	int Game::gameAddMainWindow(int x, int y, int width, int height, std::string windowName) {
		MainWindow window(x, y, width, height, windowName);
		gameMainWindows.push_back(window);

		return window.windowId;
	}

	void Game::gameCameraSetPosition(int wId,
		double eyex, double eyey, double eyez,
		double dirx, double diry, double dirz,
		double upx, double upy, double upz) {
		for (std::vector<MainWindow>::iterator it = gameMainWindows.begin(); it != gameMainWindows.end(); it++) {
			if (it->windowId == wId) {
				it->camera.cameraSetPosition(eyex, eyey, eyez, dirx, diry, dirz, upx, upy, upz);
			}
		}
	}

	void Game::gameSetTimerFPS(int fps) {
		gameFPS = fps;
	}

	void Game::gameTimerRun(int value) { // Como valor identificador do timer, foi passado o ID da janela
										 //glutPostRedisplay(); // Lança evento de Display na janela que está ativa
		glutPostWindowRedisplay(value); // ID da janela a que se pretende lançar novo evento de Display
		glutTimerFunc((1000 / gameFPS) /*ms*/, gameTimerRun, value); // Estamos a passar como valor identificador do timer, o ID da janela
	}
}