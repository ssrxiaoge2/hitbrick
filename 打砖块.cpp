/*
	1. 创建窗口
	2. 基本绘图函数
		2.1 颜色设置
		2.2 画填充矩形和圆
*/
#include <graphics.h>
#include <time.h>
//画砖块
int  map[5][8];				//描述整个地图
HWND hwnd = NULL;
//用1-3 给数组赋值
void initMap() 
{
	for (int i = 0; i < 5; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			map[i][j] = rand() % 3 + 1;
		}
	}
}
void drawMap() 
{
	setlinestyle(PS_SOLID, 2);
	setlinecolor(WHITE);
	for (int i = 0; i < 5; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			int x = 100*j ;		//j=x/100
			int y = 25*i ;		//i=y/i
			switch (map[i][j])   //map[i][j]!=0
			{
			case 0:			//做消除用的
				break;
			case 1:
				setfillcolor(YELLOW);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 2:
				setfillcolor(LIGHTBLUE);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 3:
				setfillcolor(LIGHTGREEN);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			}
		}
	}
}
//木板的过程
struct Board 
{
	int x;
	int y;
	int speed;
	COLORREF color;
	int width;
	int height;
};
//struct Board board = { 300, 800 - 25,1, WHITE, 200, 25 };
struct Board* createBoard(int x, int y, int  speed, COLORREF color, int width, int height) 
{
	struct Board* pBoard = (struct Board*)malloc(sizeof(struct Board));
	//结构体指针->成员   ->指针指向运算符
	//(*指针).成员;
	pBoard->x = x;
	pBoard->y = y;
	pBoard->speed = speed;
	pBoard->color = color;
	//结构体变量.成员
	(*pBoard).width = width;
	(*pBoard).height = height;
	return pBoard;
}
void drawBoard(struct Board* pBoard) 
{
	setfillcolor(pBoard->color);
	fillrectangle(pBoard->x, pBoard->y,
		pBoard->x + pBoard->width, pBoard->y + pBoard->height);
}
//木板的按键操作
void keyDown(struct Board* pBoard)
{
	//C语言: scanf函数 getch() getchar() gets()
	//异步的按键操作
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)&&pBoard->x>=0) 
	{
		pBoard->x -= pBoard->speed;
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)&&pBoard->x<=800-200) 
	{
		pBoard->x += pBoard->speed;
	}
}
//球：
struct Ball 
{
	int x;
	int y;
	int r;				//半径
	int dx;
	int dy;
	COLORREF color;
};
struct Ball* createBall(int x, int y, int r, int dx, int dy, COLORREF color)
{
	struct Ball* pBall = (struct Ball*)malloc(sizeof(struct Ball));
	pBall->x = x;
	pBall->y = y;
	pBall->r = r;
	pBall->dx = dx;
	pBall->dy = dy;
	pBall->color = color;
	return pBall;
}
void drawBall(struct Ball* pBall)
{
	setfillcolor(pBall->color);
	solidcircle(pBall->x, pBall->y, pBall->r);
}
//1.反射
//2.撞击木板
int hitBoard(struct Ball* pBall, struct Board* pBoard) 
{
	if (pBall->y + pBall->r == pBoard->y) //y满足
	{
		if (pBall->x >= pBoard->x && pBall->x <= pBoard->x + pBoard->width) 
		{
			return 1;
		}
	}
	return 0;
}
int die(struct Ball* pBall) 
{
	if (pBall->y > 800 - 25)
	{
		return 1;
	}
	return 0;
}
//3.撞击砖块
int hitBricks(struct Ball* pBall) 
{
	//1.算出球的行的列是属于地图
	int ballJ = pBall->x / 100;
	int ballI = (pBall->y - pBall->r) / 25;
	//2.当前下标下，数组中不等于表示有砖块需要反射
	if (ballJ < 8 && ballI < 5 && map[ballI][ballJ] != 0) 
	{
		map[ballI][ballJ] = 0;
		return 1;
	}
	return 0;
}
void moveBall(struct Ball* pBall,struct Board* pBoard) 
{
	if (pBall->x - pBall->r <= 0 || pBall->x + pBall->r >= 800) 
	{
		pBall->dx = -pBall->dx;
	}
	if (pBall->y - pBall->r <= 0 || hitBoard(pBall,pBoard)|| hitBricks(pBall))
	{
		pBall->dy = -pBall->dy;
	}
	pBall->x += pBall->dx;
	pBall->y += pBall->dy;
}
//4.收尾工作 ：游戏结束
//5.定时器
int Timer(time_t num, int id) 
{
	static time_t start[10];
	time_t end = clock();
	if (end - start[id]>num) 
	{
		start[id] = end;
		return 1;
	}
	return 0;
}
int gameOver() 
{
	for (int i = 0; i < 5; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			if (map[i][j] != 0) 
			{
				return 0;
			}
		}
	}
	return 1;
}
int main() 
{
	srand((unsigned int)time(0));			//设置随机数的范围跟随时间改变而改变
	hwnd=initgraph(800, 700);
	struct Board* pBoard = createBoard(300, 700 - 25,2, WHITE, 200, 25);
	struct Ball* pBall = createBall(400, 600, 15, 2, -5, RED);
	initMap();
	BeginBatchDraw();
	while (1) 
	{
		cleardevice();
		drawMap();
		drawBoard(pBoard);
		drawBall(pBall);
		if(Timer(10,0))
			moveBall(pBall,pBoard);
		keyDown(pBoard);
		if (die(pBall)) 
		{
			MessageBox(hwnd, "you die", "gameOver", MB_OK);
			exit(0);
		}
		if (gameOver()) 
		{
			MessageBox(hwnd, "win game", "gameOver", MB_OK);
			exit(0);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
