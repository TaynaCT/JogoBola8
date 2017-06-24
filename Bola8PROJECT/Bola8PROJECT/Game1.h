#pragma once
#include "Game.h"
#include "glm.h"
#include "Vector.h"
#include "tinymath.h"
#include "Ball.h"
#include "tga.h"

using namespace std;

GLMmodel* pmodel = NULL;
vector<Ball> gameBalls;

static float angle = 0.0;
static float red = 1.0, blue = 1.0, green = 1.0;
double motionScale = 0.00001;

tgaInfo *im;
//GLuint texture;
GLuint ballsTexture[15]; // array de texturas
int textIndice = 0;
GLUquadric *mysolid;
GLfloat spin = 0.05;

// Material a aplicar ao objeto
GLfloat mat_ambient_and_diffuse[] = { 0.4, 0.4, 0.4, 1.0 }; // Reflecte 100% todas as componentes de cor
GLfloat mat_specular[] = { 0.9, 0.9, 0.9, 1.0 }; // Reflecte 100% todas as componentes de cor
GLfloat mat_shininess[] = { 6.0 }; // Expoente especular. [0 (mais brilho), 128 (menos brilho)]


								   //Inicializa as propriedades do material, fonte de luz, z-buffer, etc...
void init(void)
{
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; // "acinzentado"
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // Branco
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Branco
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Luz direccional (posicionada no infinito)


 // Permitir iluminação e activar fonte de luz #0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Configurar cor da fonte de luz
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	// Configurar a posição da fonte de luz
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Configurar material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	// Recarcular as normais, após alteração de escala. Melhora a aparência do efeito da iluminação.
	glEnable(GL_NORMALIZE);

	// Outros...
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void load_tga_image(void)
{
	string pathArray[] = { "Texturas/PoolBall1.tga", "Texturas/PoolBall2.tga", "Texturas/PoolBall3.tga", "Texturas/PoolBall4.tga", "Texturas/PoolBall5.tga",
						"Texturas/PoolBall6.tga", "Texturas/PoolBall7.tga", "Texturas/PoolBall8.tga", "Texturas/PoolBall9.tga", "Texturas/PoolBall10.tga",
						"Texturas/PoolBall11.tga", "Texturas/PoolBall12.tga", "Texturas/PoolBall13.tga", "Texturas/PoolBall14.tga", "Texturas/PoolBall5.tga" };

	for (int i = 0; i < 15; i++)
	{
		//const char impathfile[255] = "Texturas/PoolBall2.tga";
		char *impathfile = new char[pathArray[i].length() + 1];
		strcpy(impathfile, pathArray[i].c_str());

		//char impathfile[255] = "earth.tga";
		// Carrega a imagem de textura
		im = tgaLoad(impathfile);

		printf("IMAGE INFO: %s\nstatus: %d\ntype: %d\npixelDepth: %d\nsize%d x %d\n", impathfile, im->status, im->type, im->pixelDepth, im->width, im->height);

		//glGenTextures(1, &texture);
		glGenTextures(15, ballsTexture);

		//glBindTexture(GL_TEXTURE_2D, texture);

		glBindTexture(GL_TEXTURE_2D,ballsTexture[i]);

		mysolid = gluNewQuadric();
		gluQuadricDrawStyle(mysolid, GLU_FILL);
		gluQuadricTexture(mysolid, GL_TRUE);
		gluQuadricNormals(mysolid, GLU_SMOOTH);
		gluQuadricOrientation(mysolid, GLU_OUTSIDE);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, /*GL_ADD*/GL_MODULATE);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // MIPMAP
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, im->width, im->height, GL_RGB, GL_UNSIGNED_BYTE, im->imageData); // MIPMAP
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im->width, im->height, 0, GL_RGB, GL_UNSIGNED_BYTE, im->imageData);

		// Destrói a imagem
		tgaDestroy(im);
	}
}


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
	gameBalls.push_back(Ball(/*mysolid,*/ 0.5, y, 0, size));
	
	for (int x = 0; x < 5; x++)
	{					
			if (x == 0 ) {
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*distance, y, x*(-distance), size));
				
			}	

			if (x == 1) {
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, x*distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, x*(-distance), size));
				

			}

			if (x == 2) {
			
				gameBalls.push_back(Ball(/*mysolid, */x*(-distance), y, x*distance, size));
				
				
				//bola 8
				//bola no centro da mesa 				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, 0, size));
				
				gameBalls.push_back(Ball(/*mysolid, */x*(-distance), y, x*-distance, size));
						
			}		

			if (x == 3) {
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, x*distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, x*-distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, -distance, size));
			
			}

			if (x == 4) {
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, x*distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, x*-distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, 2*distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, 2*-distance, size));
				
				gameBalls.push_back(Ball(/*mysolid,*/ x*(-distance), y, 0, size));
			
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
	
		textIndice++;
		if (textIndice > 15) {
			textIndice = 0;
		}
		glEnable(GL_TEXTURE_2D);
		//glColor4f(1.0, 1.0, 1.0, 1.0);
		//glBindTexture(GL_TEXTURE_2D, texture[]);
		glBindTexture(GL_TEXTURE_2D, ballsTexture[textIndice]);

		// Configurar material
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
		//-----------------------------
		it->drawBall(mysolid);		
	}

	//Desenha mesa
	glPushMatrix();
	glTranslatef(0, 1, 0);	
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL); //modelo 3d	
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
		
		//glEnable(GL_TEXTURE_2D);	
		//glColor4f(1.0, 1.0, 1.0, 1.0);
		//glBindTexture(GL_TEXTURE_2D, texture);

		//// Configurar material
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);



		//iniciação de luzes, buffers etc
		//init();
		//carrega a textura da ser aplicada na imagem 
		//load_tga_image();
		
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
		//Texto da tela
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
		
		//VISTA TOPO
		glPushMatrix();

		glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		glLoadIdentity();
		gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		
		drawSceneGame1();
		glPopMatrix(); // Pop the old matrix without the transformations.
		
		glDisable(GL_TEXTURE_2D);
		glutSwapBuffers();
		glFlush();
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
