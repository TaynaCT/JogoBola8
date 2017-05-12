#pragma once

namespace std {

	class Camera {
	public:
		Camera();
		~Camera();
		void cameraSetPosition(double eyex, double eyey, double eyez,
			double dirx, double diry, double dirz,
			double upx, double upy, double upz);
		void cameraTilt(double tilt);
		void cameraPan(double pan);
		void cameraMove(double move);
		void cameraUpdate(double targetX, double targetY, double targetZ);


	private:
		double eyex, eyey, eyez;	// Posição da câmara (centro-de-massa)
		double dirx, diry, dirz;	// Vector do sentido de deslocamento da câmara
		double upx, upy, upz;		// Vector que indica a parte superior da câmara

		double anglePan, angleTilt;	// Ângulos de Pan e Tilt
		double deltaAnglePan, deltaAngleTilt;

		double deltaMove;			// Move para a frente e para trás
		double deltaSpeed;			// Aumenta ou diminui a velocidade
		double speed;				// Constante de velocidade de deslocamento

	};
}