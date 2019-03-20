#ifndef BASIC
#define BASIC

#include <GL/glut.h>
#include <vector>

using namespace std;

#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define LEFT			1
#define RIGHT			2
#define INITHIGHT		-WINDOW_HIGN / 3
#define MAX_CHAR		128

typedef vector<int> INTCOLOR;

static const int WINDOW_WIDE = 500;
static const int WINDOW_HIGN = 600;
static float PI = 3.1415926;
static bool bCheat = false;
static bool STOP = true;
static int SPEED = 20;
static int Grade = 0;
static int CurrentW = WINDOW_WIDE;
static int CurrentH = WINDOW_HIGN;

static INTCOLOR RED = { 1, 0, 0 };
static INTCOLOR GREEN = { 0, 1, 0 };
static INTCOLOR BLUE = { 0, 0, 1 };
static INTCOLOR YELLOW = { 1, 1, 0 };
static INTCOLOR RED2 = { 1, 0, 1 };
static INTCOLOR GREEN2 = { 0, 1, 0 };
static INTCOLOR CYAN = { 0, 1, 1 };

#endif