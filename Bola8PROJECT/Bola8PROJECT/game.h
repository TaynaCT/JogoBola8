#pragma once

#include <string>
#include <vector>
#include <gl/freeglut.h>
#include "MainWindow.h"

//namespace std {
//
//	class Game
//	{
//	public:
//		Game::Game(int x = 0, int y = 0, int width = 320, int height = 320) : x(x), y(y), screenWidth(width), screenHeight(height) {
//			running = false;
//		}
//		Game::~Game() {}
//		void init();
//		void init(int x, int y, int width, int height);
//		void run(void);
//		static void changeSize(int w, int h);
//		Camera camera;
//	private:
//		static void renderScene(void);									// Funções de callback têm de ser estáticas
//																		// Funções de callback têm de ser estáticas
//		static void processNormalKeys(unsigned char key, int x, int y);	// Funções de callback têm de ser estáticas
//		static void processSpecialKeys(int key, int x, int y);			// Funções de callback têm de ser estáticas
//		static void drawScene(void);
//		static void processMotionFunc(int x, int y);
//
//		bool running;
//		int x, y, screenWidth, screenHeight;
//		int window;
//	};
//}



namespace std {

	class Game
	{
	public:
		Game();
		~Game();
		int gameAddMainWindow(int x, int y, int width, int height, std::string windowName);
		void gameCameraSetPosition(int wID,
			double eyex, double eyey, double eyez,
			double dirx, double diry, double dirz,
			double upx, double upy, double upz);
		virtual void gameSetWindowCallbacks(int windowID) = 0;
		static void gameSetTimerFPS(int fps);
		static void gameTimerRun(int value);
		static void gameRun(void);

	protected:
		static bool gameInit;
		static bool gameRunning;
		static int gameFPS;
		std::vector<MainWindow> gameMainWindows;
	};
}