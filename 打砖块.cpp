///*
//	1.��������
//	2.������ͼ����
//		2.1��ɫ����
//		2.2������
//*/
//#include<graphics.h>
//#include<time.h>
////��ש��
//int map[5][8];//����������ͼ
//void initmap()
//{
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			map[i][j] = rand() % 3 + 1;
//		}
//	}
//}
//void drawmap()
//{
//	setlinestyle(PS_SOLID,2); 
//	setlinecolor(WHITE);
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			int x = 100 * j;
//			int y = 25 * i;
//			switch (map[i][j])
//			{
//			case 0:
//				break;
//			case 1:
//				break;
//			case 2:
//				break;
//			default:
//				break;
//
//
//			}
//		}
//
//
//	}
//
//
//
//}
//struct board {
//	int x;
//	int y;
//	int speed;
//	COLORREF color;
//	int width;
//	int height;
//};
//struct board* creatboard(int x, int y, int speed, COLORREF color, int width, int height) 
//{
//	struct board* pboard = (struct board*)malloc(sizeof(struct board));
//	pboard->x = x;
//	pboard->y = y;
//	pboard->speed = speed;
//	pboard->color = color;
//	pboard->width = width;
//	pboard->height = height;
//	return pboard;
//
//
//}
//void drawboard(struct board* pboard)
//{
//	setfillcolor(pboard->color);
//	fillrectangle(pboard->x,pboard->y,
//	pboard->x + pboard->width,pboard->y + pboard->height);
//}
////ľ�尴������
//
//int main()
//{
//	srand((unsigned int)time(0));  //��������֣���ʱ���
//	initgraph(800, 800);
//	struct board* pboard = creatboard(300, 800 - 25, 1, WHITE, 200, 25);
//	initmap();
//	while (1)
//	{
//		cleardevice();
//		drawmap();
//		drawboard(pboard);
//	}
//	closegraph();
//	return 0;
//}