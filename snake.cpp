/*贪食蛇类的实现*/

#include <cstdlib>
#include <ctime>
#include "snake.h"

Snake::Snake(int  w, int  h)
{
	if (h > 0 || w > 0)
	{
		height = h;
		width = w;
	}
	else
	{
		height = 50;
		width = 50;
	}
	
	length = 0;
	AddNode(w/2, h/2);
	PutFood();
	die = false;
	director = 1;  //初始方向向上
}

Snake::~Snake(void)
{
	SnakeNode.clear();
}

void Snake::AddNode(const int & w, const int & h)
{
	Node * newNode = new Node;
	newNode->x = w;
	newNode->y = h;
	SnakeNode.push_back(*newNode);
	length++;
}


void Snake::Judge(void)
{
	//判断是否撞墙
	if (SnakeNode[0].x == 0 || SnakeNode[0].x == width ||
	    SnakeNode[0].y == 0 || SnakeNode[0].y == height)
	{
		die = true;
		return;
	}
	//判断蛇是否跟自己相撞
	for (int i = 1; i < length; i++)
	{
		if (SnakeNode[0].x == SnakeNode[i].x &&
		    SnakeNode[0].y == SnakeNode[i].y)
		{
			die = true;
			return;
		}
	}
	//若两种情况均未发生，说明还活着。
	die = false;
}

//返回蛇的生死状态
bool Snake::IsDie(void)
{
	return die;
}

void Snake::Move(void)
{
	//记录蛇尾的位置，用来在吃到果子的时侯增加长度
	int lastX = SnakeNode[length-1].x;
	int lastY = SnakeNode[length-1].y;
	//从尾部开始处理除蛇头以外的蛇身的移动
	for (int i = length - 1; i > 0; i--)
	{
		SnakeNode[i].x = SnakeNode[i-1].x;
		SnakeNode[i].y = SnakeNode[i-1].y;
	}
	//根据当前方向处理蛇头
	switch (director)
	{
	case 1: //向上
		SnakeNode[0].y--;
		break;
	case 2: //向右
		SnakeNode[0].x++;
		break;
	case 3: //向下
		SnakeNode[0].y++;
		break;
	case 4: //向左
		SnakeNode[0].x--;
		break;
	default:
		break;
	}
	//看移动后的蛇是否吃到果子了，如果吃到，增加蛇的长度
	if (SnakeNode[0].x == Food.x && SnakeNode[0].y == Food.y)
	{
		AddNode(lastX, lastY);
		PutFood();
	}
	Judge();  //每次移动后调用判断函数更新蛇的生死状态
}

void Snake::ChangeDirector(const int & NewDirector)
{
	//如果新的方向与原方向相同或者相反，原方向不变
	if (director == NewDirector || director - NewDirector == 2 ||
	    director - NewDirector == -2)
	{
		return;
	}
	director = NewDirector;
}

void Snake::PutFood(void)
{
	int x, y;
	bool empty = false;
	srand(time(NULL));
	do
	{
		empty = true;
		x = rand()%(width-2) + 1;
		y = rand()%(height-2) + 1;
		for (int i = 0; i < length; i++)
		{
			if (SnakeNode[i].x == x &&
			    SnakeNode[i].y == y)
			{
				empty = false;
				break;
			}
		}
	}while (empty == false);
	Food.x = x; 
	Food.y = y;
}

void Snake::OutputSnake(vector<Node> & node,
		         Node & food)
{
	node.resize(SnakeNode.size());
	node = SnakeNode;
	food = Food;
}

void Snake::Clear(void)
{
	SnakeNode.clear();
	length = 0;
	AddNode(25, 25);
	director = 1;
}
