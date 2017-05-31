#include <iostream>
#include <gl/freeglut.h>
#include "Ball.h"

namespace std
{	
	void Ball::drawBall()
	{
		glPushMatrix();
		glTranslatef(posX, posY, posZ);
		glutSolidSphere(ballSize, 10, 10);
		glPopMatrix();		
	}
	void Ball::move(float dx, float dy, float dz)
	{
		posX = dx;
		posY = dy;
		posZ = dz;
	}
}