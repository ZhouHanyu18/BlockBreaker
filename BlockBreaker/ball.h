#ifndef BALL
#define BALL
#include "basic.h"
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
#endif