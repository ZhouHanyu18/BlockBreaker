#include "bar.h"
Bar::Bar()
{
	Reset();
}

void Bar::Reset()
{
	color = { 1, 0, 1 };
	nLength = WINDOW_WIDE / 3;
	nBarX = -nLength / 2;
	nBarY = INITHIGHT;
	nWide = 5;
	nSpeed = 20;
}

void Bar::SetColor(INTCOLOR pColor)
{
	color = pColor;
	//copy(pColor,pColor+3,color);
}

void Bar::ChangeLength(int length)
{
	if (nLength + length <= 2)
		nLength = 3;
	else
		nLength += length;
}

void Bar::ChangeSpeed(int speed)
{
	nSpeed += speed;
}

void Bar::ChangeY(int y)
{
	if (nBarY + y < -WINDOW_HIGN / 2)
		nBarY = -WINDOW_HIGN / 2;
	else
		nBarY += y;
}

void Bar::Move(int left_or_right)
{
	if (left_or_right == LEFT)
	{
		if (nBarX - nSpeed <= -WINDOW_WIDE / 2)
		{
			nBarX = -WINDOW_WIDE / 2;
		}
		else
		{
			nBarX -= nSpeed;
		}
	}
	else
	{
		if (nBarX + nSpeed + nLength >= WINDOW_WIDE / 2)
		{
			nBarX = WINDOW_WIDE / 2 - nLength;
		}
		else
		{
			nBarX += nSpeed;
		}
	}
}

void Bar::Draw()
{
	glColor3f(color[0], color[1], color[2]);
	float x1 = (float)nBarX / (float)WINDOW_WIDE * 2;
	float y1 = (float)nBarY / (float)WINDOW_HIGN * 2;
	float x2 = (float)(nBarX + nLength) / (float)WINDOW_WIDE * 2;
	float y2 = (float)(nBarY - nWide) / (float)WINDOW_HIGN * 2;
	glRectf(x1, y1, x2, y2);
}

void Bar::SetX(int x)
{
	nBarX = x;
}