#include "Game1.h"

int main(int argc, char **argv) {	
	drawGameBalls();

	loadmodel();

	//definição da nova janela 
	Game1 game;
	int wId = game.gameAddMainWindow(0, 0, 800, 600, "Bola 8 || F2 - full screen || esc - escape window");
	//posicionamento inicial da camera
	game.gameCameraSetPosition(wId, 0.0, 1.0, 1.0, 1.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	//game.gameCameraSetPosition((double eyex, double eyey, double eyez, ouble dirx, double diry, double dirz, double upx, double upy, double upz)
	//iniciação dos callbacks 
	game.gameSetWindowCallbacks(wId);

	// Esta função é geral para o freeglut
	/*glutIdleFunc([](void) {
	// Colocar aqui o código que se pretenda executar sempre que não existires outros eventos
	});*/

	// Definir o FPS (É comum a todas as janelas)
	Game::gameSetTimerFPS(100);
	// Inicia o lançamento de eventos de display, para cada janela, de acordo com o FPS definido
	Game::gameTimerRun(wId);

	// Entra no ciclo de gestão da aplicação por eventos
	Game::gameRun();

	return 0;
}

