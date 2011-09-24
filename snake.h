#ifndef SNAKE_H
#define SNAKE_H
/*贪食蛇模型的类定义*/

#include <iostream>
#include <vector>

using namespace std;

//蛇的结点
class Node
{
public:
	int x;
	int y;
};

class Snake
{
private:
	vector<Node> SnakeNode;  //蛇的数据结构，座标范围为(1,100)
	Node Food;               //蛇吃的食物的座标
	int director;            //蛇头的前进方向 1-4:从上开始顺时针
	int length;              //蛇的全长
	bool die;                //是否死了
	int height;              //游戏区域的高度（y值)
	int width;               //游戏区域的宽度(x值)

public:
	Snake(int w = 50, int h = 50);
	~Snake(void);
	void ChangeDirector(const int & NewDirector); //改变蛇的前进方向
	void Move(void);                             //蛇头向当前方向前进1
	bool IsDie(void);                           //判断蛇是否死了
	void OutputSnake(vector<Node> & node,
			 Node & food);  //将当前的蛇的数据结构复制
	                                //到node及food中供其以各种形式输出
	void Clear();  //将数据结构清空

private:
	void Judge(void);                //蛇每前进一步，对蛇的状态进行判断
	void AddNode(const int & w, const int & h); //将蛇的长度加1
	void PutFood(void);              //随机放置食物
};

#endif
