#include "Block.h"

Block::Block()
{
	Reset();
}

Block::~Block()
{
}

void Block::Reset()
{
	pBlock.resize(nBlockH);
	for (int i = 0; i < nBlockH; ++i)
	{
		pBlock[i].resize(0);
		pBlock[i].insert(pBlock[i].begin(), nBlockW, 0);
	}

	srand(time(NULL));
	nBlock = 0;
	for (int i = 0; i < 50; ++i)
	{
		int x = rand() % nBlockH / 2;
		int y = rand() % nBlockW;
		if (pBlock[x][y] == 0)
		{
			pBlock[x][y] = 1;
			nBlock++;
		}
	}
	//cout << nBlock << endl;
}

void Block::Draw()
{
	glColor3f(1, 0, 1);
	glPolygonMode(GL_BACK, GL_LINE);
	for (int i = 0; i < nBlockH; ++i)
	{
		for (int j = 0; j < nBlockW; ++j)
		{
			if (pBlock[i][j] == 1)
			{
				float x1 = -1 + nWide * (float)j / (float)WINDOW_WIDE * 2;
				float y1 = 1 - nHigh * (float)i / (float)WINDOW_HIGN * 2;
				float x2 = -1 + nWide * (float)(j + 1) / (float)WINDOW_WIDE * 2;
				float y2 = 1 - nHigh * (float)(i + 1) / (float)WINDOW_HIGN * 2;
				glRectf(x1, y1, x2, y2);
			}
		}
	}
}
