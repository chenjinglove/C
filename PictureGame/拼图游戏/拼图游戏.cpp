#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
IMAGE img, blank;	//背景图片  空白图片
int arraymap[4][4];		//4*4拼图
int array[15];
struct mypos 
{
	int i;
	int j;
}searchBlank = {0.0};
//分装函数，避免鼠标操作造成数值溢出
//找到白块的坐标
struct mypos searchBlankPos(int arraymap[][4])
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			if (arraymap[i][j] == 15)
			{
				searchBlank.i = i;
				searchBlank.j = j; 
				return searchBlank;
			}
		}
	}
	return searchBlank;



}
void loadResource()			//初始化资源
{
	srand((unsigned int)time(NULL));
	int length = 15;	//初始化一维数组长度
	int pos = 0;		//	初始化下标
	int i, j;
	for (i = 0; i < 15; i++)
	{
		array[i] = i;
	}
	//随机从一维数组中取值给二维数组
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == 3 && j == 3)
			{
				arraymap[3][3] = 15;
				break;
			}
			pos = rand() % length;
			arraymap[i][j] = array[pos];
			//随机产生下标
			for(int k = pos; k < length; k++)		//将数组的长度重新初始化
			{
				array[k] = array[k + 1];
			}
			length--;
		}
		if (i == 3 && j == 3)			//break 跳出两层for循环
		{
			arraymap[3][3] = 15;
			break;
		}
	}
	loadimage(&img, "m.jpg", 400, 400);		//加载图片与空白图片资源
	loadimage(&blank, "blank.jpg", 100, 100);

}

void drawmap()				//将贴图显示出来
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = j * 100;
			int y = i * 100;
			switch (arraymap[i][j])
			{
			case 0:
			case 1:
			case 2:
			case 3:
				putimage(x, y, 100, 100, &img, arraymap[i][j] * 100, 0);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				putimage(x, y, 100, 100, &img, (arraymap[i][j] - 4) * 100, 100);
				break;
			case 8:
			case 9:
			case 10:
			case 11:
				putimage(x, y, 100, 100, &img, (arraymap[i][j] - 8) * 100, 200);
				break;
			case 12:
			case 13:
			case 14:
				putimage(x, y, 100, 100, &img, (arraymap[i][j] - 12) * 100, 300);
				break;
			case 15:
				putimage(x, y, &blank);
				break;
			}


		}
	}
}
void playgame() 
{
	MOUSEMSG m;
	int i=0, j=0;
	int j_Mouse=0, i_Mouse=0;
	while (1)		//用死循环来进行鼠标操作
	{
		drawmap();
		//找到白块的位置
		searchBlankPos(arraymap);
		i = searchBlank.i;
		j = searchBlank.j;
		
		m = GetMouseMsg();
		switch (m.uMsg)		//判断鼠标相对位置
			{
			case WM_LBUTTONDOWN:
				j_Mouse = m.x / 100;
				i_Mouse = m.y / 100;
				if (i_Mouse == i + 1 && j_Mouse == j)
				{
					arraymap[i][j] = arraymap[i_Mouse][j_Mouse];
					arraymap[i_Mouse][j_Mouse] = 15;
					break;
				}
				if (i_Mouse == i - 1 && j_Mouse == j)
				{
					arraymap[i][j] = arraymap[i_Mouse][j_Mouse];
					arraymap[i_Mouse][j_Mouse] = 15;
					break;
				}
				if (i_Mouse == i && j_Mouse == j - 1)
				{
					arraymap[i][j] = arraymap[i_Mouse][j_Mouse];
					arraymap[i_Mouse][j_Mouse] = 15;
					break;
				}
				if (i_Mouse == i && j_Mouse == j + 1)
				{
					arraymap[i][j] = arraymap[i_Mouse][j_Mouse];
					arraymap[i_Mouse][j_Mouse] = 15;
					break;
				}
				break;
			}
	}
}



int main()
{
	loadResource();
	initgraph(400, 400);
	playgame();
	closegraph();
	return 0;
}