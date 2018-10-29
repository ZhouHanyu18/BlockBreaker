#ifndef BLOCK
#define BLOCK

#include <GL/glut.h>
#include <vector>

#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace std;

typedef vector<int> INTCOLOR;

const int WINDOW_WIDE = 500;
const int WINDOW_HIGN = 600;
class Block
{
private:
	const int nHigh = 10;
	const int nWide = 25;
	int nBlock;
public:
	Block();
	void Reset();
	~Block();
	const int nBlockH = WINDOW_WIDE / nHigh;
	const int nBlockW = WINDOW_WIDE / nWide;
	//int **pBlock;
	vector <vector <int> >pBlock;
	void Draw();
	void Decrease(){ --nBlock; };
	int GetW(){ return nWide; };
	int GetH(){ return nHigh; };
	int GetN(){ return nBlock; };
};

class Bar
{
private:
	int nBarX, nBarY;
	int nLength;
	int nWide;
	int nSpeed;
	INTCOLOR color;
public:
	Bar();
	void Reset();
	void Draw();
	void SetColor(INTCOLOR pColor);
	void ChangeLength(int length);
	void ChangeY(int y);
	void ChangeSpeed(int speed);
	void Move(int left_or_right);
	void SetX(int x);
	int GetX(){ return nBarX; };
	int GetY(){ return nBarY; };
	int GetL(){ return nLength; };
};


class Ball
{
private:
	int nBallX, nBallY;//Œª÷√
	float nDirection;//∑ΩœÚ
	int nBallR;
	int nSpeed;
public:
	Ball();
	void Reset();
	void Draw();
	void Move();
	
	void ChangeSize(int size);
	void ChangeSpeed(int speed);
	void ChangeDirection(float direction);
	int GetX(){ return nBallX; };
	int GetY(){ return nBallY; };
	int GetR(){ return nBallR; };
	int GetS(){ return nSpeed; };
	float GetDirection(){ return nDirection; };
};

class Sharp
{
public:
	int x=10, y=10;
	int size=10;
	int deg = 0;
	INTCOLOR color;
public:
	virtual void show(){};
	virtual int getType(){ return 0; };

	Sharp(int x1, int y1, int deg1, INTCOLOR col1) :x(x1), y(y1), deg(deg1), color(col1){};
};

class Arrow:public Sharp
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
#endif