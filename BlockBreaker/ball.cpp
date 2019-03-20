#include "ball.h"
Ball::Ball()
{
	Reset();
}

void Ball::Reset()
{
	nDirection = PI / 4;//·½Ïò
	nBallR = 6;
	nSpeed = 5;
	nBallX = 0;
	nBallY = INITHIGHT + nBallR;
}

void Ball::ChangeDirection(float direction)
{
	nDirection = direction;
}

void Ball::ChangeSize(int size)
{
	if (nBallR + size <= 2)
		nBallR = 2;
	else if (nBallR + size > 80)
		nBallR = 70;
	else
		nBallR += size;
}

void Ball::Move()
{
	nBallX += (float)nSpeed*cos(nDirection);
	nBallY += (float)nSpeed*sin(nDirection);
}

void Ball::ChangeSpeed(int speed)
{
	if (nSpeed + speed < 5)
		nSpeed = 5;
	else
		nSpeed += speed;
}

void Ball::Draw()
{
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; ++i)
	{
		glVertex2f((float)nBallR / (float)CurrentW * 2 * cos(2 * PI / 50 * i)
			+ (float)nBallX / (float)CurrentW * 2,
			(float)nBallR / (float)CurrentH * 2 * sin(2 * PI / 50 * i)
			+ (float)nBallY / (float)CurrentH * 2);
	}
	glEnd();
}