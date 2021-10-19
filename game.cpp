#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>

#define width 500
#define heigh 500
#define max_snake 100 //�ߵ������

enum DIR
{
	up,
	down,
	left,
	right
};

struct XY
{
	int x = -10;
	int y = -10;
};

struct Food
{
	POINT fd;
	int size = 10;
	int flag = 1;
};

struct Food food;
struct Snake  //�ߵĽṹ��
{
	int num;
	DIR dir; //�ߵķ���
	int score; //�ߵķ�����
	XY coor[max_snake]; //����
	int size = 10; //һ������ĳ�������(������������)��

};

struct Snake sanke;



void draw();
void initgame();
void snake_move();
void key_control();
void eatfood();


int main()
{
	initgraph(width,heigh,SHOWCONSOLE);//��ʼ�����ڣ�
	initgame();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	BeginBatchDraw(); //��ʼ��������
	while (1)
	{
		if (t2 - t1 > 120)
		{
			snake_move();
			t1 = t2;
		}
		t2 = GetTickCount();
		key_control();
		FlushBatchDraw(); 
		draw();
		eatfood();
		
	}
	return 0;
}

//�߳�ʳ�ﶯ��
void eatfood()
{
	if (sanke.coor[0].x == food.fd.x && sanke.coor[0].y == food.fd.y && food.flag == 1)
	{
		sanke.score += 10;
		sanke.num += 1;
		food.flag = 0;
	}

	if (food.flag == 0)
	{
		food.fd.x = (rand() % width) / 10 * 10;
		food.fd.y = (rand() % heigh) / 10 * 10;
		food.flag = 1;
	}

}

//��������
void key_control()
{
	//ʹ��win32��ȡ������Ϣ
	if (GetAsyncKeyState(VK_UP)&&sanke.dir!=down)
	{
		sanke.dir = up;
	}
	if (GetAsyncKeyState(VK_DOWN) && sanke.dir != up)
	{
		sanke.dir = down;
	}
	if (GetAsyncKeyState(VK_LEFT) && sanke.dir != right)
	{
		sanke.dir = left;
	}
	if (GetAsyncKeyState(VK_RIGHT) && sanke.dir != left)
	{
		sanke.dir = right;
	}
}
//���߶�����

void snake_move()
{
	for (int i = sanke.num - 1; i > 0; i--)
	{
		sanke.coor[i].x = sanke.coor[i - 1].x;
		sanke.coor[i].y = sanke.coor[i - 1].y;
	}
	switch (sanke.dir)
	{
		case up:sanke.coor[0].y -= sanke.size;
			if (sanke.coor[0].y + 10 <= 0)
			{
				sanke.coor[0].y = heigh;
			}
				break;
		case down:sanke.coor[0].y += sanke.size;
			if (sanke.coor[0].y >= heigh)
			{
				sanke.coor[0].y = 0;
			}
			break;
		case left:sanke.coor[0].x -= sanke.size;
			if (sanke.coor[0].x + 10 <= 0)
			{
				sanke.coor[0].x = width;
			}
			break;
		case right:sanke.coor[0].x += sanke.size; 
			if (sanke.coor[0].x >= width)
			{
				sanke.coor[0].x = 0;
			}
			break;
		default:
			break;
	}
}

//��ʼ����Ϸ��
void initgame()
{
	sanke.num = 3;
	sanke.dir = right;
	sanke.score = 0;
	sanke.coor[2].x = 0;
	sanke.coor[2].y = 0;
	sanke.coor[1].x = sanke.size;
	sanke.coor[1].y = 0;
	sanke.coor[0].x = sanke.size*2;
	sanke.coor[0].y = 0;
	srand(100);

	food.fd.x = (rand() % width)/10*10;
	food.fd.y = (rand() % heigh)/10*10;


	
}

//���ƻ���
void draw()
{
	setbkcolor(WHITE);
	cleardevice();	
	
	for (int i=0; i < sanke.num; i++)
	{
		//�����ߵ�λ��
		setlinecolor(BLACK);
		setfillcolor(YELLOW);
		fillrectangle(sanke.coor[i].x,sanke.coor[i].y, sanke.coor[i].x+sanke.size, sanke.coor[i].y+sanke.size);

	}
	if (food.flag == 1)
	{
		setlinecolor(BLACK);
		setfillcolor((61, 240, 82));
		fillellipse(food.fd.x, food.fd.y, food.fd.x + food.size, food.fd.y + food.size);

	}

}