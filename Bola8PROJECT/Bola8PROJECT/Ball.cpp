#include <iostream>
#include <gl/freeglut.h>
#include "Ball.h"

namespace std
{	
	void Ball::drawBall(GLUquadric *mySolid)
	{
		glPushMatrix();
		
		glTranslatef(posX, posY, posZ);
		//glutSolidSphere(ballSize, 10, 10);
				
		gluSphere(mySolid, ballSize, 50, 50);
		glPopMatrix();
		int a = 0;
	}
	void Ball::move(float dx, float dy, float dz)
	{
		posX = dx;
		posY = dy;
		posZ = dz;
	}

	int Ball::getFlag() {
		return ballFlag;
	}
}