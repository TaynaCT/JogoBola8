#include <iostream>
#include <gl/freeglut.h>
#include "MainWindow.h"

namespace std {

	int MainWindow::countWindows = 1;

	MainWindow::MainWindow(int x, int y, int width, int height, std::string windowName) : x(x), y(x), screenWidth(width), screenHeight(height), windowName(windowName) {
		if (windowName.empty()) {
			std::ostringstream stringStream;
			stringStream << "Game Window #" << countWindows++;
			windowName = stringStream.str();
		}

		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(x, y);
		glutInitWindowSize(screenWidth, screenHeight);
		windowId = glutCreateWindow(windowName.c_str());

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		std::cout << "[MainWindow] Create Main Window " << windowId << std::endl;
	}

	MainWindow::~MainWindow() {
		std::cout << "[MainWindow] Destroy Main Window " << windowId << std::endl;
	}
}