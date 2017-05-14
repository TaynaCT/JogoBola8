#include "Game1.h"



//Game game;
//GLMmodel* pmodel = NULL;
//int wId;
//
//double motionScale = 0.00001; // velocidade do movimento da camera

//void loadmodel(void)
//{
//	if(pmodel == NULL)
//	{
//        pmodel = glmReadOBJ("modelos/PoolTableWithoutUVW.obj");
//		if(pmodel == NULL) {exit(0);}
//		else
//		{
//			glmUnitize(pmodel);
//			glmLinearTexture(pmodel);
//			glmScale(pmodel, 1.0);
//			glmFacetNormals(pmodel);
//			glmVertexNormals(pmodel, 90.0);
//		}
//    }
//}


//Criação dos objetos !!!!! 
//void renderScene(void) {
//
//	glClearColor(0, 0, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	glTranslatef(0.5f, 0, 0.5f);
//	glutWireSphere(1, 10, 10);
//	/*glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);*/
//	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
//	//glDisable(GL_LIGHT0);
//	//glDisable(GL_LIGHTING);
//	//glFlush();
//	glutSwapBuffers();
//	
//}


//Coisas que devem aparecer na tela
//void drawScene() {
//	//glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
//	glTranslatef(0.5f, 0, 0.5f);
//	glutWireSphere(1, 10, 10);
//}
//
////void Game::processNormalKeys(unsigned char key, int x, int y) {
////	if (key == 27 /* ESC */) glutLeaveMainLoop(); //exit(0);
////
////}
//void changeSize(int w, int h)
//{
//	float ratio;
//
//	if (h == 0) h = 1;
//	ratio = 1.0f * w / h;
//
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45, ratio, 1, 1000);
//
//	glMatrixMode(GL_MODELVIEW);
//}

//void Game::processSpecialKeys(int key, int x, int y) {
//	switch (key) {
//	case GLUT_KEY_F1:
//		glutSetWindow(game.window);
//		game.changeSize(250, 100);
//		glutPositionWindow(20, 20);
//		break;
//
//	case GLUT_KEY_F2:
//		glutSetWindow(game.window);
//		glutFullScreen();
//		break;
//	case GLUT_KEY_F3:
//		//red = 0.0; green = 0.0; blue = 1.0;
//		break;
//	}
//
//}
//
//
//
//void Game::processMotionFunc(int x, int y) {
//	
//	//Game *currentWindow = (Game *)glutGetWindowData();
//	glutSetWindow(game.window);
//	
//	//Movimento da camera
//	if (GLUT_RIGHT_BUTTON/*camFlag*/) {
//
//		
//		int xCenter = glutGet(GLUT_WINDOW_WIDTH) / 2;
//		int yCenter = glutGet(GLUT_WINDOW_HEIGHT) / 2;
//
//		double deltaX = (double)(x - xCenter) * motionScale;
//		double deltaY = (double)(y - yCenter) * motionScale;
//
//		game.camera.cameraPan(deltaX);
//		game.camera.cameraTilt(deltaY);
//
//		if (x > glutGet(GLUT_WINDOW_WIDTH) || y > glutGet(GLUT_WINDOW_HEIGHT)) {
//			glutWarpPointer(xCenter, yCenter);
//		}
//		if (x < 0 || y < 0) {
//			glutWarpPointer(xCenter, yCenter);
//		}
//	}
//}


//void Game::gameSetWindowCallbacks(int windowID) {
//
//	for (int i = 0; i < int(gameMainWindows.size()); i++) {
//		if (gameMainWindows[i].windowId == windowID) {
//			glutSetWindowData((void *)&gameMainWindows[i]);
//			break;
//		}
//	}
//
//	glutDisplayFunc([](void) {
//		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
//		glutSetWindow(currentWindow->windowId);
//
//		if (currentWindow->windowId == 1)
//			currentWindow->windowId = currentWindow->windowId;
//
//		glClearColor(0.0, 0.0, 0.0, 0.0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		currentWindow->camera.cameraUpdate(0,0,0);
//
//		drawScene();
//
//		glutSwapBuffers();
//	});
//
//
//	glutReshapeFunc([](int w, int h) {
//		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
//		glutSetWindow(currentWindow->windowId);
//
//		// Previne a divisão por zero
//		if (h == 0) h = 1;
//		double ratio = 1.0 * double(w) / double(h);
//
//		// O viewport ocupará toda a janela
//		glViewport(0, 0, w, h);
//
//		// Efetua o reset do sistema de coordenadas
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//
//		// Aplica a perspectiva
//		gluPerspective(45.0, ratio, 0.1, 100.0);
//
//		// Altera o sistema de coordenadas, para GL_MODELVIEW
//		glMatrixMode(GL_MODELVIEW);
//	});
//
//
//	glutSpecialFunc([](int key, int x, int y) {
//		
//		MainWindow *currentWindow = (MainWindow *)glutGetWindowData();
//		glutSetWindow(currentWindow->windowId);
//
//		switch (key) {
//		case GLUT_KEY_F1:
//			glutSetWindow(currentWindow->windowId);
//			game.changeSize(250, 100);
//			glutPositionWindow(20, 20);
//			break;
//
//		case GLUT_KEY_F2:
//			glutSetWindow(currentWindow->windowId);
//			glutFullScreen();
//			break;
//		}
//	
//	});
//
//}


int main(int argc, char **argv) {	
//	Camera cam;
//	// Inicializar o GLUT e a janela
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
//	glutInitWindowPosition(10, 10);
//	glutInitWindowSize(800, 600);
//	//Criação da janela principal
//	wId = glutCreateWindow("******* BOLA 8 ******");
//	cam.cameraSetPosition(0.0, 1.0, 5.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
//
//	cam.cameraUpdate(0,0,0);
//
//	// Registar funções para processar eventos (callbacks)
//	glutDisplayFunc(renderScene);
//	glutIdleFunc(renderScene);
//	//glutReshapeFunc(changeSize);
//	
//	/*glutSetWindowData(WinMain)
//*/
//	//carrega o modelo
//	loadmodel();
//
//	// Entrar no ciclo de processamento do GLUT
//	glutMainLoop();
//



	//createGameCharacters();

	/*game.init(0, 0, 600, 600);*/

	/*game.run();*/

	loadmodel();
	//definição da nova janela 
	Game1 game;
	int wId = game.gameAddMainWindow(0, 0, 800, 600, "Main Window 1");
	//posicionamento inicial da camera
	game.gameCameraSetPosition(wId, 0.0, 1.0, 5.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
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

