#include "Block.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>

#define LEFT			1
#define RIGHT			2
#define INITHIGHT		-WINDOW_HIGN / 3
#define MAX_CHAR		128
float PI = 3.1415926;

Block block;
Bar bar;
Ball ball;

vector <Sharp*> list;

INTCOLOR RED ={1,0,0};
INTCOLOR GREEN = { 0, 1, 0 };
INTCOLOR BLUE = { 0, 0, 1 };
INTCOLOR YELLOW = { 1, 1, 0 };
INTCOLOR RED2  ={ 1, 0, 1 };
INTCOLOR GREEN2 = { 0, 1, 0 };

Star star_show1(-100, -270, 10, RED);
Triangle star_show2(-50, -270, 20, GREEN);
Arrow star_show3(0, -270, 30, RED);
Triangle star_show4(50, -270, 40, YELLOW);
Star star_show5(100, -270, 50, GREEN);

bool bCheat=FALSE;
bool STOP = TRUE;
int SPEED = 100;
int CurrentW=WINDOW_WIDE;
int CurrentH=WINDOW_HIGN;

void Init()
{
	//block.Reset();
	ball.Reset();
	bar.Reset();
	SPEED = 100;
	STOP = TRUE;
	list.clear();
	//初始化
}

void BuildSharp(int x,int y)
{
	
	int rd = rand()%10;
	switch (rd)
	{
	case 0:
	{
		Sharp *arrow = new Arrow(x, y,0,YELLOW);
		list.insert(list.begin(), arrow);
		break;
	}
		
	case 1:
	{
		Sharp *tri = new Triangle(x, y,0,GREEN);
		list.insert(list.begin(), tri);
		break;
	}
	case 2:
	{
		Sharp *star = new Star(x, y, 0, BLUE);
		list.insert(list.begin(), star);
		break;
	}
	case 3:
	{
			  Sharp *arrow = new Arrow(x, y, 0, RED);
			  list.insert(list.begin(), arrow);
			  break;
	}

	case 4:
	{
			  Sharp *tri = new Triangle(x, y, 0, RED);
			  list.insert(list.begin(), tri);
			  break;
	}
	case 5:
	{
			  Sharp *star = new Star(x, y, 0, RED);
			  list.insert(list.begin(), star);
			  break;
	}
	default:
		break;
	}
}

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // 如果是第一次调用，执行初始化
		// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

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
		pBlock[i].insert(pBlock[i].begin(),nBlockW,0);
	}
	
	srand(time(NULL));
	nBlock = 0;
	for (int i = 0; i < 200; ++i)
	{
		int x = rand() % 40;
		int y = rand() % 20;
		if (pBlock[x][y] ==0)
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
				float x1 = -1 + block.nWide * (float)j / (float)WINDOW_WIDE * 2;
				float y1 = 1 - block.nHigh * (float)i / (float)WINDOW_HIGN * 2;
				float x2 = -1 + block.nWide * (float)(j + 1) / (float)WINDOW_WIDE * 2;
				float y2 = 1 - block.nHigh * (float)(i + 1) / (float)WINDOW_HIGN * 2;
				glRectf(x1,y1,x2,y2);
			}
		}
	}
}

Bar::Bar() 
{
	Reset();
}

void Bar::Reset()
{
	color = {1,0,1};
	nLength = WINDOW_WIDE / 5;
	nBarX = -nLength / 2;
	nBarY = INITHIGHT;
	nWide = 2;
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
		nBarY = -WINDOW_HIGN/2;
	else
		nBarY += y;
}

void Bar::Move(int left_or_right)
{
	if (left_or_right == LEFT)
	{
		if (nBarX-nSpeed <= -WINDOW_WIDE/2)
		{
			nBarX = -WINDOW_WIDE/2;
		}
		else
		{
			nBarX -= nSpeed;
		}
	}
	else
	{
		if (nBarX + nSpeed + nLength >= WINDOW_WIDE/2)
		{
			nBarX = WINDOW_WIDE/2-nLength;
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
	float x2 = (float)(nBarX+nLength) / (float)WINDOW_WIDE * 2;
	float y2 = (float)(nBarY+nWide) / (float)WINDOW_HIGN * 2;
	glRectf(x1, y1, x2, y2);
}

void Bar::SetX(int x)
{
	nBarX = x;
}

Ball::Ball()
{
	Reset();
}

void Ball::Reset()
{
	nDirection = PI / 4;//方向
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
	glVertex2f((float)(x + size / 2 * (float)cos(deg + 0.3+PI)) / WINDOW_WIDE * 2, (float)(y + size / 2 * (float)sin(deg + 0.3+PI)) / WINDOW_HIGN * 2);
	glVertex2f((float)(x + size / 2 * (float)cos(deg + 0.3 + PI / 2)) / WINDOW_WIDE * 2, (float)(y + size / 2 * (float)sin(deg + 0.3 + PI / 2)) / WINDOW_HIGN * 2);
	glEnd();
}

void Star::show()
{
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_STRIP);
		glVertex2f((float)(x + (float)size*cos((float)deg / 180 * PI)) / WINDOW_WIDE * 2, 
			(float)(y + (float)size*sin((float)deg / 180 * PI)) / WINDOW_HIGN * 2);
		glVertex2f((float)(x + (float)size*cos((float)(144+deg) / 180 * PI)) / WINDOW_WIDE * 2, 
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

void myDisplay(void)
{
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		block.Draw();
		bar.Draw();
		ball.Draw();

		for each (auto pSharp in list)
		{
			pSharp->show();
		}

		star_show1.show();
		star_show2.show();
		star_show3.show();
		star_show4.show();
		star_show5.show();
		//提示位置
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2f(-0.99, -0.75);
		drawString("Notice:");

		glRasterPos2f(-0.95, -0.8);
		drawString("Start/Stop: S Speed: 1,2,3,4 L<- R:-> Cheat: F1 Restart: R");

		glRasterPos2f(-0.9, -0.9);
		drawString("");

		glFlush();
		glutSwapBuffers();
}

void Timer()
{
	if (STOP)
		return;
	star_show1.deg+=5;
	star_show2.deg+=5;
	star_show3.deg+=5;
	star_show4.deg+=5;
	star_show5.deg+=5;

	//外挂--->
	if (bCheat)
	{
		int place;
		if (ball.GetX() + bar.GetL() > WINDOW_WIDE / 2)
			place = WINDOW_WIDE / 2 - bar.GetL();
		else
			place = ball.GetX() - ball.GetR();
		bar.SetX(place);
	}
	
	//外挂<---

	if (ball.GetX() + ball.GetR() >= WINDOW_WIDE/2)//右墙
	{
		ball.ChangeDirection(PI-ball.GetDirection());
	}
	if (ball.GetX() - ball.GetR() <= -WINDOW_WIDE / 2)//左墙
	{
		ball.ChangeDirection(PI - ball.GetDirection());
	}
	if (ball.GetY() + ball.GetR() >= WINDOW_HIGN / 2)//上墙
	{
		ball.ChangeDirection(PI * 2 - ball.GetDirection());
	}
	if (ball.GetY() - ball.GetR() <= -WINDOW_HIGN / 2)//下墙
	{
		MessageBox(0,L"GameOver",L">_<",0);
		Init();
		myDisplay();
		return;
	}

	if (ball.GetX() >= bar.GetX() && ball.GetX() <= bar.GetX() +bar.GetL() 
		&& ball.GetY() - ball.GetR() <= bar.GetY() && bar.GetL() &&
		ball.GetY() - ball.GetR()+ball.GetS() >= bar.GetY())
	{
		ball.ChangeDirection(PI * 2 - ball.GetDirection());
	}


	//判断小球与砖块的碰撞
	int x = ball.GetX();
	int y = ball.GetY();
	int r = ball.GetR();
	
	if (y+r >= -WINDOW_WIDE + WINDOW_HIGN/2)//进入砖块区域
	{
		//球坐标转换，向上遇到砖块
		int j = (x + WINDOW_WIDE / 2) / block.GetW();
		int i = (-y + WINDOW_HIGN / 2-r) / block.GetH();

		if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI * 2 - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x,y);
			block.Decrease();
		}


		//球坐标转换，向下遇到砖块
		 j = (x + WINDOW_WIDE / 2) / block.GetW();
		 i = (-y + WINDOW_HIGN / 2 + r) / block.GetH();

		 if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI * 2 - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
		}

		//球坐标转换，向左遇到砖块
		 j = (x + WINDOW_WIDE / 2 -r) / block.GetW();
		 i = (-y + WINDOW_HIGN / 2 ) / block.GetH();

		 if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
		}

		//球坐标转换，向右遇到砖块
		 j = (x + WINDOW_WIDE / 2 + r) / block.GetW() ;
		 i = (-y + WINDOW_HIGN / 2) / block.GetH() ;

		 if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
		}
	}
	
	for (auto i=list.begin(); i != list.end(); ++i)
	{
		(*i)->y -= 2;
		if ((*i)->y < -WINDOW_HIGN / 2*9/10)
		{
			list.erase(i);
			--i;
			continue;
		}
		if ((*i)->x >= bar.GetX() && (*i)->x <= bar.GetX() + bar.GetL() 
			&& (*i)->y >= bar.GetY() && (*i)->y - (*i)->size<=bar.GetY())//碰到板子
		{
			int type = (*i)->getType();
			switch (type)
			{
			case 0:
				if ((*i)->color == RED)
					bar.ChangeY(+4);
				else
					bar.ChangeY(-4);
				bar.SetColor((*i)->color);
				list.erase(i);
				--i;
				
				continue;
				break;
			case 1:
				if ((*i)->color == RED)
					ball.ChangeSize(-4);
				else
					ball.ChangeSize(+4);
				bar.SetColor((*i)->color);
				list.erase(i);
				--i;
				continue;
				break;
			case 2:
				if ((*i)->color == RED)
					bar.ChangeLength(-20);
				else
					bar.ChangeLength(20);
				bar.SetColor((*i)->color);
				list.erase(i);
				--i;
				continue;
				break;
			
			default:
				break;
			}
		}
	}

	if (block.GetN() <= 0)
	{
		MessageBox(0,L"You Win",L"^_^",1);
		Init();
		block.Reset();
		myDisplay();
		return;
		//初始化
	}

	Sleep(SPEED);
	ball.Move();
	myDisplay();
}

void CALLBACK TimeProc(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
{
	//cout << i << endl;
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM w, LPARAM l)
{
	if (w == VK_LEFT)
	{
		bar.Move(LEFT);
		MessageBox(0,0,0,0);
	}
	if (w == VK_RIGHT)
	{
		bar.Move(RIGHT);
		MessageBox(0, 0, 0, 0);

	}
	return FALSE;
}

void SpecialKey(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		bar.Move(LEFT);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		bar.Move(RIGHT);
	}
	if (key == GLUT_KEY_F1)
	{
		bCheat = !bCheat;
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		SPEED =60;
	}
	if (key == '2')
	{
		SPEED = 40;
	}
	if (key == '3')
	{
		SPEED = 10;
	}
	if (key == '4')
	{
		SPEED = 0;
	}

	if (key == 's' || key == 'S')
	{
		STOP = !STOP;
	}

	if (key == 'r' || key == 'R')
	{
		block.Reset();
		list.clear();
		myDisplay();
	}
}

void ChangeSize(int w, int h)
{
	
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDE, WINDOW_HIGN);
	glutCreateWindow("打砖块");
	srand(time(NULL));
	//SetTimer(NULL, 1, 100, TimeProc);//需要跟着消息发送出去
	//SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);//钩子响应按键
	/*MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		glutDisplayFunc(&myDisplay);
		glutMainLoop();
	}*/

	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&Timer);
	glutSpecialFunc(&SpecialKey);
	glutKeyboardFunc(&Keyboard);
	//glutReshapeFunc(ChangeSize);
	glutMainLoop();
	
	return 0;
}
