#include <iostream>
#include <gl/freeglut.h>
#include "Camera.h"

namespace  std {

	Camera::Camera() {
		eyex = 0.0; eyey = 0.0; eyez = -1.0;
		dirx = 0.0; diry = 0.0; dirz = -1.0;
		upx = 0.0; upy = 1.0; upz = 0.0;

		anglePan = 0.0; deltaAnglePan = 0.0;
		angleTilt = 0.0; deltaAngleTilt = 0.0;

		speed = 0.1;
		deltaSpeed = 0.0;
		deltaMove = 0.0;

		std::cout << "[Camera] Create Camera" << std::endl;
	}

	Camera::~Camera() {
		std::cout << "[Camera] Destroy Camera" << std::endl;
	}

	void Camera::cameraSetPosition(double eyex, double eyey, double eyez,
		double dirx, double diry, double dirz,
		double upx, double upy, double upz) {
		this->eyex = eyex; this->eyey = eyey; this->eyez = eyez;
		this->dirx = dirx; this->diry = diry; this->dirz = dirz;
		this->upx = upx; this->upy = upy; this->upz = upz;
		
		anglePan = asin((1.0 * dirx + 0.0 * diry + 0.0 * dirz) / (sqrt(1.0 * 1.0 + 0.0 * 0.0 + 0.0 * 0.0)*sqrt(dirx*dirx + diry*diry + dirz*dirz)));
		anglePan = anglePan * 180.0 / 3.14159265359;
		//std::cout << "anglePan=" << anglePan << '\n';

		// Dados os pontos do plano xz: Po(0,0,0), Px(1,0,0), Py(0,0,1)
		// Obtemos um plano definido pelos dois vetores: PoPx(1,0,0), PoPy(0,0,1)
		// Podemos então calcular o produto vetorial, que nos dará a normal ao plano.
		// Assim, o produto vetorial será calculado por: n = PoPx(1,0,0) x PoPy(0,0,1)
		// n = |PoPx| * |PoPy| * sen(Teta) = (0,1,0)
		// O ângulo entre um vetor (dx,dy,dz) e a normal (0,1,0) é calculado por:
		// alpha = asen(abs(0*dx+1*dy+0*dz)/(abs(sqrt(0*0+1*1+0*0))*abs(dx*dx+dY*dy+dz*dz)))
		angleTilt = asin(fabs(0.0 * dirx + 1.0 * diry + 0.0 * dirz) / (fabs(sqrt(0.0 * 0.0 + 1.0 * 1.0 + 0.0 * 0.0))*fabs(dirx*dirx + diry*diry + dirz*dirz)));
		angleTilt = angleTilt * 180.0 / 3.14159265359;
		//std::cout << "angleTilt=" << angleTilt << '\n';
	}

	void Camera::cameraTilt(double tilt) {
		deltaAngleTilt = tilt;
	}

	void Camera::cameraPan(double pan) {
		deltaAnglePan = pan;
	}

	void Camera::cameraMove(double move) {
		deltaMove = move;
	}
	
	void Camera::cameraUpdate(double targetX, double targetY, double targetZ) {
		if (deltaSpeed) {
			speed += deltaSpeed;
			if (speed < 0.0) speed = 0.0;
		}

		if (deltaMove) {
			// x = x0 + (Amplitude * Direcção) * Velocidade
			eyex = eyex + (deltaMove * dirx) * speed;
			eyey = eyey + (deltaMove * diry) * speed;
			eyez = eyez + (deltaMove * dirz) * speed;
		}

		anglePan += deltaAnglePan;
		angleTilt += deltaAngleTilt;
		dirx = sin(anglePan) * cos(angleTilt);
		diry = sin(angleTilt); //yaw
		dirz = -cos(anglePan) * cos(angleTilt);

		if (cos(angleTilt) < 0.0) upy = -1.0;
		else upy = 1.0;

		/*if (angleTilt > 88)
			diry = 88.0f;
		if(angleTilt < 1)
			diry = 1;*/

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glTranslatef(-eyex, -eyey, -eyez);

		gluLookAt(dirx, diry ,dirz,					// eye
			targetX, targetY, targetZ,	// Target
			upx, upy, upz);							// up
			
	}
		
}