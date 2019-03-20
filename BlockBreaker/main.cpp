#include "Block.h"
#include <windows.h>


Block block;
Bar bar;
Ball ball;

vector <Sharp*> list;

Star star_show1(-100, -270, 10, RED);
Triangle star_show2(-50, -270, 20, GREEN);
Arrow star_show3(0, -270, 30, RED);
Triangle star_show4(50, -270, 40, YELLOW);
Star star_show5(100, -270, 50, GREEN);

void Init()
{
	//block.Reset();
	ball.Reset();
	bar.Reset();
	SPEED = 20;
	STOP = TRUE;
	list.clear();
	//��ʼ��
}

void BuildSharp(int x, int y)
{
	int rd = rand() % 14;
	//int rd = 6;
	switch (rd)
	{
	case 0:
	{
			  Sharp *arrow = new Arrow(x, y, 0, YELLOW);
			  list.insert(list.begin(), arrow);
			  break;
	}
	case 1:
	{
			  Sharp *tri = new Triangle(x, y, 0, GREEN);
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
	case 6:
	{
			  Sharp *star = new NewBall(x, y, 0, CYAN);
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

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
		// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
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
	//��ʾλ��
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.99, -0.75);
	drawString("Notice:");

	glRasterPos2f(-0.95, -0.8);
	drawString("Start/Stop: S Speed: 1,2,3,4 L<- R:-> Cheat: F1 Restart: R");

	glRasterPos2f(-0.9, -0.9);
	drawString("");

	glRasterPos2f(-0.94, -0.92);
	drawString("GRADE: ");

	glRasterPos2f(-0.70, -0.92);
	char str[10];
	sprintf_s(str, "%d", Grade);
	drawString(str);

	glFlush();
	glutSwapBuffers();
}

void Timer()
{
	if (STOP)
		return;
	star_show1.deg += 3;
	star_show2.deg += 2;
	star_show3.deg += 2;
	star_show4.deg += 2;
	star_show5.deg += 3;

	//���--->
	if (bCheat)
	{
		int place;
		if (ball.GetX() + bar.GetL() > WINDOW_WIDE / 2)
			place = WINDOW_WIDE / 2 - bar.GetL();
		else
			place = ball.GetX() - ball.GetR();
		bar.SetX(place);
	}

	//���<---

	if (ball.GetX() + ball.GetR() >= WINDOW_WIDE / 2)//��ǽ
	{
		ball.ChangeDirection(PI - ball.GetDirection());
	}
	if (ball.GetX() - ball.GetR() <= -WINDOW_WIDE / 2)//��ǽ
	{
		ball.ChangeDirection(PI - ball.GetDirection());
	}
	if (ball.GetY() + ball.GetR() >= WINDOW_HIGN / 2)//��ǽ
	{
		ball.ChangeDirection(PI * 2 - ball.GetDirection());
	}
	if (ball.GetY() - ball.GetR() <= -WINDOW_HIGN / 2)//��ǽ
	{
		char str[10];
		sprintf_s(str, "%d", Grade);
		string Sout = "�ܱ�Ǹ�������ֵ÷֣�";
		Sout += str;
		MessageBox(0, Sout.c_str(), ">_<", 0);
		Init();
		Grade = 0;
		myDisplay();
		return;
	}

	if (ball.GetX() >= bar.GetX() && ball.GetX() <= bar.GetX() + bar.GetL()
		&& ball.GetY() - ball.GetR() <= bar.GetY() && bar.GetL() &&
		ball.GetY() - ball.GetR() + ball.GetS() >= bar.GetY())
	{
		ball.ChangeDirection(PI * 2 - ball.GetDirection());
		bar.ChangeY(-1);
	}


	//�ж�С����ש�����ײ
	int x = ball.GetX();
	int y = ball.GetY();
	int r = ball.GetR();

	if (y + r >= -WINDOW_WIDE + WINDOW_HIGN / 2)//����ש������
	{
		//������ת������������ש��
		int j = (x + WINDOW_WIDE / 2) / block.GetW();
		int i = (-y + WINDOW_HIGN / 2 - r) / block.GetH();

		if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI * 2 - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
			Grade++;
		}


		//������ת������������ש��
		j = (x + WINDOW_WIDE / 2) / block.GetW();
		i = (-y + WINDOW_HIGN / 2 + r) / block.GetH();

		if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI * 2 - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
			Grade++;
		}

		//������ת������������ש��
		j = (x + WINDOW_WIDE / 2 - r) / block.GetW();
		i = (-y + WINDOW_HIGN / 2) / block.GetH();

		if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
			Grade++;
		}

		//������ת������������ש��
		j = (x + WINDOW_WIDE / 2 + r) / block.GetW();
		i = (-y + WINDOW_HIGN / 2) / block.GetH();

		if (i >= 0 && i<block.nBlockH && j >= 0 && j<block.nBlockW)
		if (block.pBlock[i][j] == 1)
		{
			ball.ChangeDirection(PI - ball.GetDirection());
			block.pBlock[i][j] = 0;
			BuildSharp(x, y);
			block.Decrease();
			Grade++;
		}
	}

	for (auto i = list.begin(); i != list.end(); ++i)
	{
		(*i)->y -= 3;
		if ((*i)->y < -WINDOW_HIGN / 2 * 9 / 10)
		{
			list.erase(i);
			--i;
			continue;
		}
		if ((*i)->x >= bar.GetX() && (*i)->x <= bar.GetX() + bar.GetL()
			&& (*i)->y >= bar.GetY() && (*i)->y - (*i)->size <= bar.GetY())//��������
		{
			int type = (*i)->getType();
			switch (type)
			{
			case 0:
				if ((*i)->color == RED)
					bar.ChangeY(+10);
				else
					bar.ChangeY(-10);
				bar.SetColor((*i)->color);
				list.erase(i);
				--i;

				continue;
				break;
			case 1:
				if ((*i)->color == RED)
					ball.ChangeSize(-4);
				else
					ball.ChangeSize(+6);
				bar.SetColor((*i)->color);
				list.erase(i);
				--i;
				continue;
				break;
			case 2:
				if ((*i)->color == RED)
					bar.ChangeLength(-20);
				else
					bar.ChangeLength(30);
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
		char str[10];
		sprintf_s(str, "%d", Grade);
		string Sout = "��ϲ�����ˣ����ܹ���ȡ�����ǣ�";
		Sout += str;
		MessageBox(0, Sout.c_str(), "^_^", 1);
		Init();
		block.Reset();
		myDisplay();
		return;
		//��ʼ��
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
		MessageBox(0, 0, 0, 0);
	}
	if (w == VK_RIGHT)
	{
		bar.Move(RIGHT);
		MessageBox(0, 0, 0, 0);

	}
	return FALSE;
}

void SpecialKey(int key, int x, int y)
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
		if (SPEED < 2)
			SPEED = 2;
		SPEED--;
	}
	if (key == '2')
	{
		SPEED++;
	}
	if (key == '3')
	{
		SPEED = 8;
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
		Grade = 0;
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
	glutCreateWindow("��ש��");
	srand(time(NULL));
	//SetTimer(NULL, 1, 100, TimeProc);//��Ҫ������Ϣ���ͳ�ȥ
	//SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);//������Ӧ����
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