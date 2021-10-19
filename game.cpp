#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>

#define width 500
#define heigh 500
#define max_snake 100 //蛇的最长长度

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
struct Snake  //蛇的结构体
{
	int num;
	DIR dir; //蛇的方向；
	int score; //蛇的分数；
	XY coor[max_snake]; //坐标
	int size = 10; //一段身体的长度与宽度(身体是正方形)；

};

struct Snake sanke;



void draw();
void initgame();
void snake_move();
void key_control();
void eatfood();


int main()
{
	initgraph(width,heigh,SHOWCONSOLE);//初始化窗口；
	initgame();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	BeginBatchDraw(); //开始批量绘制
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

//蛇吃食物动作
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

//监听键盘
void key_control()
{
	//使用win32获取键盘消息
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
//让蛇动起来

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

//初始化游戏；
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

//绘制画面
void draw()
{
	setbkcolor(WHITE);
	cleardevice();	
	
	for (int i=0; i < sanke.num; i++)
	{
		//画出蛇的位置
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