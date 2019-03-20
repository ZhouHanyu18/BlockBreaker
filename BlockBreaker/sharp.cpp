#include "sharp.h"
void Arrow::show()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
	glVertex2f((float)x / (float)WINDOW_WIDE * 2, (float)y / (float)WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size*cos(deg)) / WINDOW_WIDE * 2, (float)(y + (float)size*sin(deg)) / WINDOW_HIGN * 2);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f((float)(x + (float)size*cos(deg)) / WINDOW_WIDE * 2, (float)(y + (float)size*sin(deg)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size * 2 / 3 * cos(deg + 0.3)) / WINDOW_WIDE * 2, (float)(y + (float)size * 2 / 3 * sin(deg + 0.3)) / WINDOW_HIGN * 2);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f((float)(x + (float)size*cos(deg)) / WINDOW_WIDE * 2, (float)(y + (float)size*sin(deg)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size * 2 / 3 * cos(deg - 0.3)) / WINDOW_WIDE * 2, (float)(y + (float)size * 2 / 3 * sin(deg - 0.3)) / WINDOW_HIGN * 2);
	glEnd();
}

void Triangle::show()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_LOOP);
	glVertex2f((float)(x + size / 2 * (float)cos(deg + 0.3)) / WINDOW_WIDE * 2, (float)(y + size / 2 * (float)sin(deg + 0.3)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + size / 2 * (float)cos(deg + 0.3 + PI)) / WINDOW_WIDE * 2, (float)(y + size / 2 * (float)sin(deg + 0.3 + PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + size / 2 * (float)cos(deg + 0.3 + PI / 2)) / WINDOW_WIDE * 2, (float)(y + size / 2 * (float)sin(deg + 0.3 + PI / 2)) / WINDOW_HIGN * 2);
	glEnd();
}

void Star::show()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_STRIP);
	glVertex2f((float)(x + (float)size*cos((float)deg / 180 * PI)) / WINDOW_WIDE * 2,
		(float)(y + (float)size*sin((float)deg / 180 * PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size*cos((float)(144 + deg) / 180 * PI)) / WINDOW_WIDE * 2,
		(float)(y + (float)size*sin((float)(144 + deg) / 180 * PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size*cos((float)(288 + deg) / 180 * PI)) / WINDOW_WIDE * 2,
		(float)(y + (float)size*sin((float)(288 + deg) / 180 * PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size*cos((float)(72 + deg) / 180 * PI)) / WINDOW_WIDE * 2,
		(float)(y + (float)size*sin((float)(72 + deg) / 180 * PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size*cos((float)(216 + deg) / 180 * PI)) / WINDOW_WIDE * 2,
		(float)(y + (float)size*sin((float)(216 + deg) / 180 * PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + (float)size*cos((float)deg / 180 * PI)) / WINDOW_WIDE * 2,
		(float)(y + (float)size*sin((float)deg / 180 * PI)) / WINDOW_HIGN * 2);
	glEnd();
}

void NewBall::show()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_POLYGON);
	int nsize = size / 3;
	for (int i = 0; i < 50; ++i)
	{
		glVertex2f((float)nsize / (float)CurrentW * 2 * cos(2 * PI / 50 * i)
			+ (float)x / (float)CurrentW * 2,
			(float)nsize / (float)CurrentH * 2 * sin(2 * PI / 50 * i)
			+ (float)y / (float)CurrentH * 2);
	}
	glEnd();
}