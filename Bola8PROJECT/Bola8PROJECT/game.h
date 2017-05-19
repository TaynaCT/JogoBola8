#pragma once

#include <string>
#include <vector>
#include <gl/freeglut.h>
#include "MainWindow.h"


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