#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include<conio.h>
IMAGE img, blank;	//����ͼƬ  �հ�ͼƬ
int arraymap[4][4];		//4*4ƴͼ
int array[15];
struct mypos 
{
	int i;
	int j;
}searchBlank = {0.0};
//��װ���������������������ֵ���
//�ҵ��׿������
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
void loadResource()			//��ʼ����Դ
{
	srand((unsigned int)time(NULL));
	int length = 15;	//��ʼ��һά���鳤��
	int pos = 0;		//	��ʼ���±�
	int i, j;
	for (i = 0; i < 15; i++)
	{
		array[i] = i;
	}
	//�����һά������ȡֵ����ά����
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
			//��������±�
			for(int k = pos; k < length; k++)		//������ĳ������³�ʼ��
			{
				array[k] = array[k + 1];
			}
			length--;
		}
		if (i == 3 && j == 3)			//break ��������forѭ��
		{
			arraymap[3][3] = 15;
			break;
		}
	}
	loadimage(&img, "m.jpg", 400, 400);		//����ͼƬ��հ�ͼƬ��Դ
	loadimage(&blank, "blank.jpg", 100, 100);

}

void drawmap()				//����ͼ��ʾ����
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
	while (1)		//����ѭ��������������
	{
		drawmap();
		//�ҵ��׿��λ��
		searchBlankPos(arraymap);
		i = searchBlank.i;
		j = searchBlank.j;
		
		m = GetMouseMsg();
		switch (m.uMsg)		//�ж�������λ��
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