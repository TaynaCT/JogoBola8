#pragma once

#include "Camera.h"

namespace std {

	class Game
	{
	public:
		Game::Game(int x = 0, int y = 0, int width = 320, int height = 320) : x(x), y(y), screenWidth(width), screenHeight(height) {
			running = false;
		}
		Game::~Game() {}
		void init();
		void init(int x, int y, int width, int height);
		void run(void);
		static void changeSize(int w, int h);
	private:
		static void renderScene(void);									// Funções de callback têm de ser estáticas
																		// Funções de callback têm de ser estáticas
		static void processNormalKeys(unsigned char key, int x, int y);	// Funções de callback têm de ser estáticas
		static void processSpecialKeys(int key, int x, int y);			// Funções de callback têm de ser estáticas
		static void drawScene(void);

		bool running;
		int x, y, screenWidth, screenHeight;
		int window;
	};
}