#include "Game1.h"

int main(int argc, char **argv) {	
	drawGameBalls();

	loadmodel();

	//defini��o da nova janela 
	Game1 game;
	int wId = game.gameAddMainWindow(0, 0, 800, 600, "Bola 8 || F2 - full screen || esc - escape window");
	//posicionamento inicial da camera
	game.gameCameraSetPosition(wId, 0.0, 1.0, 1.0, 1.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	//game.gameCameraSetPosition((double eyex, double eyey, double eyez, ouble dirx, double diry, double dirz, double upx, double upy, double upz)
	//inicia��o dos callbacks 
	game.gameSetWindowCallbacks(wId);

	// Esta fun��o � geral para o freeglut
	/*glutIdleFunc([](void) {
	// Colocar aqui o c�digo que se pretenda executar sempre que n�o existires outros eventos
	});*/

	// Definir o FPS (� comum a todas as janelas)
	Game::gameSetTimerFPS(100);
	// Inicia o lan�amento de eventos de display, para cada janela, de acordo com o FPS definido
	Game::gameTimerRun(wId);

	// Entra no ciclo de gest�o da aplica��o por eventos
	Game::gameRun();

	return 0;
}

