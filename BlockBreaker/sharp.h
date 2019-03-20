#ifndef SHARP
#define SHARP
#include "basic.h"

class Sharp
{
public:
	int x = 10, y = 10;
	int size = 10;
	int deg = 0;
	INTCOLOR color;
public:
	virtual void show(){};
	virtual int getType(){ return 0; };

	Sharp(int x1, int y1, int deg1, INTCOLOR col1) :x(x1), y(y1), deg(deg1), color(col1){};
};

class Arrow :public Sharp
{
public:
	virtual void show();
	virtual int getType(){ return 0; };
	Arrow(int x, int y, int deg, INTCOLOR col) :Sharp(x, y, deg, col){};
};

class Triangle :public Sharp
{
public:
	virtual void show();
	virtual int getType(){ return 1; };
	Triangle(int x, int y, int deg, INTCOLOR col) :Sharp(x, y, deg, col){};
};

class Star :public Sharp
{
public:
	virtual void show();
	virtual int getType(){ return 2; };
	Star(int x, int y, int deg, INTCOLOR col) :Sharp(x, y, deg, col){};

};
class NewBall : public Sharp
{
public:
	virtual void show();
	virtual int getType(){ return 3; };
	NewBall(int x, int y, int deg, INTCOLOR col) :Sharp(x, y, deg, col){};
};
#endif