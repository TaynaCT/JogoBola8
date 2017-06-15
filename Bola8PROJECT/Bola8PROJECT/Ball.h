#pragma once

namespace std {

	class  Ball
	{
	public:
		Ball( float x, float y, float z, float size) : // construtor
			posX(x), posY(y), posZ(z), ballSize(size) {};
		~Ball() {};
		void drawBall(GLUquadric *mySolid);
		void move(float dx, float dy, float dz);

	private:
		float posX, posY, posZ, ballSize;		
	};

	

}