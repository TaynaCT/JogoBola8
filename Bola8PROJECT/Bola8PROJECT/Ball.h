#pragma once

namespace std {

	class  Ball
	{
	public:
		Ball( int flag, float x, float y, float z, float size) : // construtor
			ballFlag(flag), posX(x), posY(y), posZ(z), ballSize(size) {};
		~Ball() {};
		void drawBall(GLUquadric *mySolid);
		void move(float dx, float dy, float dz);
		int getFlag();
	private:
		float posX, posY, posZ, ballSize;
		int ballFlag; //flag para distinguir a numeração das bolas
	};

	

}