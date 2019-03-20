#ifndef BAR
#define BAR
#include "basic.h"
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
#endif