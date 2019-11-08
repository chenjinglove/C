#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
HWND hwnd = NULL;   //标识窗口
struct pos_xy 
{
	int x;
	int y;
};
struct snackinfo 
{
	int num;	//蛇的节数
	struct pos_xy xy[100];//蛇的最大节数
	char position;//蛇前进方向
}snack;
struct foodinfo
{
	struct pos_xy xy;//食物坐标
	int flag;//食物标记
	int grade;//经验值
}food;
//方向的枚举
enum snackPosition{right,left,down,up};
void initsnack()
{
	snack.xy[2].x = 0;
	snack.xy[2].y = 0;

	snack.xy[1].x = 10;
	snack.xy[1].y = 0;

	snack.xy[0].x = 20;
	snack.xy[0].y = 0;

	snack.num = 3;
	snack.position = right;
	food.grade = 0;
}
void drawsnack()
{
	for (int i = 0; i < snack.num; i++)
	{
		setfillcolor(RGB(rand()%255, rand() % 255, rand() % 255, ));//设置填充颜色
		fillrectangle(snack.xy[i].x, snack.xy[i].y, snack.xy[i].x + 10, snack.xy[i].y + 10);
		rectangle(1, 1, 799, 599);
		setlinecolor(BLACK);
	}

}
void movesnack()
{
	for (int i = snack.num - 1; i > 0; i--)
	{
		snack.xy[i].x = snack.xy[i - 1].x;
		snack.xy[i].y = snack.xy[i - 1].y;
	}
	switch (snack.position)
	{
	case right:
		snack.xy[0].x += 10;
			break;
	case left:
		snack.xy[0].x -= 10;
			break;
	case up:
		snack.xy[0].y -= 10;
			break;
	case down:
		snack.xy[0].y += 10;
			break;

	}
}

void keybored()
{
	BeginBatchDraw();
	char ch = 0;
	ch = _getch();
	switch (ch)
	{
	case 'w':
	case 72:
		if (snack.position != down)
		{
			snack.position = up;
		}
		break;
	case 'a':
	case 75:
		if (snack.position != right)
		{
			snack.position = left;
		}
		break;
	case 's':
	case 80:
		if (snack.position != up)
		{
			snack.position = down;
		}
		break;
	case 'd':
	case 77:
		if (snack.position != left)
		{
			snack.position = right;
		}
		break;
	}
	EndBatchDraw();
}

void initfood()
{
	srand((unsigned int)time(NULL));//用到rand函数就附带使用srand函数
	food.xy.x = rand() % 80 * 10;
	food.xy.y = rand() % 60 * 10;
	food.flag = 1;
	for (int i = 0; i < snack.num; i++)
	{
		if (food.xy.x == snack.xy[i].x&&food.xy.y == snack.xy[i].y)
		{
			food.xy.x = rand() % 80 * 10;
			food.xy.y = rand() % 60 * 10;
		}
	}
	
}
void drawfood()
{
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255, ));
	fillrectangle(food.xy.x, food.xy.y, food.xy.x+10, food.xy.y+10);
}
void eatfood()
{
	if (food.xy.x == snack.xy[0].x&&food.xy.y == snack.xy[0].y)
	{
		snack.num++;
		food.grade += 10;
		food.flag = 0;
	}

}
void judgesnack()     //判断蛇是否越界
{
	char grade[100] = { 0 };
	sprintf(grade, "%d", food.grade);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 30, "得分：");
	outtextxy(740,30,grade);
	if (snack.xy[0].x < 0 || snack.xy[0].y < 0 || snack.xy[0].x>800 || snack.xy[0].y>600)
	{
		MessageBox(hwnd, "游戏结束", "撞墙死亡",0);
		initsnack();
	}
	//判断是否撞障碍物
	if (snack.xy[0].x  == 500)
	{
		if (snack.xy[0].y < 250 && snack.xy[0].y>0)
		{
			MessageBox(hwnd, "游戏结束", "撞障碍物死亡", 0);
			initsnack();
		}
	}
	if (snack.xy[0].y == 240)
	{
		if (snack.xy[0].x < 700 && snack.xy[0].x>500)
		{
			MessageBox(hwnd, "游戏结束", "撞障碍物死亡", 0);
			initsnack();
		}
	}
	if (snack.xy[0].y == 300)
	{
		if (snack.xy[0].x < 400 && snack.xy[0].x>0)
		{
			MessageBox(hwnd, "游戏结束", "撞障碍物死亡", 0);
			initsnack();
		}
	}
	if (snack.xy[0].x == 390)
	{
		if (snack.xy[0].y < 500 && snack.xy[0].y>300)
		{
			MessageBox(hwnd, "游戏结束", "撞障碍物死亡", 0);
			initsnack();
		}
	}
	//判断是否撞自己
	for (int i = 1; i < snack.num; i++)
	{
		if (snack.xy[0].x == snack.xy[i].x&&snack.xy[0].y == snack.xy[i].y)
		{
			MessageBox(hwnd, "游戏结束", "自杀死亡", 0);
			initsnack();
		}
	}
	
}
void initwindows()
{
	outtextxy(340, 5, "程序员专属小游戏");
	settextcolor(BLACK);
	line(500, 0, 500, 250);
	line(500, 250, 700, 250);
	line(0, 300, 400, 300);
	line(400, 300, 400, 500);
	line(510, 0, 510, 250);
	line(510, 240, 700, 240);
	line(700,240,700,250);
	line(0, 310, 400, 310);
	line(390, 310, 390, 500);
	line(390, 500, 400, 500);
}


int main()
{
	hwnd=initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();

	initsnack();
	while (1)
	{
		cleardevice();
		if (food.flag == 0)
		{
			initfood();
		}
		drawfood();
		drawsnack();
		initwindows();
		movesnack();
		judgesnack();
		eatfood();
		if (_kbhit())
		{
			keybored();
		}
		Sleep(1000);
	}
	
	closegraph();
	return 0;
}