#ifndef BLOCK
#define BLOCK
#include <iostream>
#include <math.h>
#include <time.h>

#include "sharp.h"
#include "bar.h"
#include "ball.h"
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

#endif