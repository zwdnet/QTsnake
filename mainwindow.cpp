#include "snake.h"
#include "mainwindow.h"
#include <iostream>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget * parent)
{
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	setWindowTitle(tr("贪食蛇游戏"));
	MenuBarSize = 20;//菜单栏所占的位置
	setFixedSize(510,510+MenuBarSize);
	dealMenu();
	IsDie = false;
	bRun = false; //开始的时侯不开始游戏
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	times = 200;
	timer->start(times);
}

MainWindow::~MainWindow()
{
}

void MainWindow::timeout(void)
{
	if (bRun == false)
	{
		timer->stop();
		return;
	}
	snake.Move();
	IsDie = snake.IsDie();
	if (IsDie)
	{
		//停止计时器，输出游戏结束信息
		timer->stop();
		bRun = false;
		QMessageBox::information(this, tr("游戏结束"),
				tr("你输了，游戏结束!"));
		IsDie = false;
		snake.Clear();
		return;
	}
	update();
}

void MainWindow::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, size().width(), size().height());
	if (IsDie || !bRun)
	{
		return;
	}
	vector<Node> node;
	Node food;
	snake.OutputSnake(node, food);
	//画果子
	painter.setBrush(Qt::red);
	painter.drawEllipse(10*food.x, 10*food.y+MenuBarSize, 10, 10);
	//画墙
	painter.setBrush(Qt::white);
	painter.drawRect(0, 0+MenuBarSize, 510, 10);  //上
	painter.drawRect(0, 500+MenuBarSize, 510, 10); //下
	painter.drawRect(0, 0+MenuBarSize, 10, 510); //左
	painter.drawRect(500, 0+MenuBarSize, 10, 510); //右
	//画蛇，蛇头跟蛇身用不同的颜色
	//蛇头
	painter.setBrush(Qt::yellow);
	painter.drawRect(10*node[0].x, 10*node[0].y+MenuBarSize, 10, 10);
	//蛇身
	painter.setBrush(Qt::blue);
	int n = node.size();
	for (int i = 1; i < n; i++)
	{
		//蛇身比蛇头小一点，这样每节之间有个间隙，看得清楚
		painter.drawRect(10*node[i].x, 10*node[i].y+MenuBarSize, 9, 9);
	}
	node.clear();
	QWidget::paintEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
	int direct = 0;
	switch (event->key())
	{
	case Qt::Key_Up:
		direct = 1;
		break;
	case Qt::Key_Right:
		direct = 2;
		break;
	case Qt::Key_Down:
		direct = 3;
		break;
	case Qt::Key_Left:
		direct = 4;
		break;
	case Qt::Key_U:
		speedUp();
		break;
	case Qt::Key_D:
		speedDown();
		break;
	default:
		break;
	}
	snake.ChangeDirector(direct);
	QWidget::keyPressEvent(event);
}

//处理菜单的函数
void MainWindow::dealMenu(void)
{
	QMenuBar * menuBar = new QMenuBar(this);
	QMenu * gameMenu = new QMenu(tr("游戏"), menuBar);
	QMenu * helpMenu = new QMenu(tr("帮助"), menuBar);
	//添加游戏菜单项
	QAction * startGame = new QAction(tr("开始游戏"), gameMenu);
	QAction * pauseGame = new QAction(tr("暂停游戏"), gameMenu);
	QAction * speedUp = new QAction(tr("游戏加速"), gameMenu);
	QAction * speedDown = new QAction(tr("游戏减速"), gameMenu);
	QAction * quitGame = new QAction(tr("结束游戏"), gameMenu);
	gameMenu->addAction(startGame);
	gameMenu->addAction(pauseGame);
	gameMenu->addAction(speedUp);
	gameMenu->addAction(speedDown);
	gameMenu->addAction(quitGame);
	menuBar->addMenu(gameMenu);
	connect(startGame, SIGNAL(triggered()), this, SLOT(startGame()));
	connect(pauseGame, SIGNAL(triggered()), this, SLOT(pauseGame()));
	connect(speedUp, SIGNAL(triggered()), this, SLOT(speedUp()));
	connect(speedDown, SIGNAL(triggered()), this, SLOT(speedDown()));
	connect(quitGame, SIGNAL(triggered()), this, SLOT(close()));
	//添加帮助和关于菜单项
	QAction * helpGame = new QAction(tr("游戏帮助"), helpMenu);
	QAction * aboutGame = new QAction(tr("关于"), helpMenu);
	helpMenu->addAction(helpGame);
	helpMenu->addAction(aboutGame);
	menuBar->addMenu(helpMenu);
	connect(helpGame, SIGNAL(triggered()), this, SLOT(showHelp()));
	connect(aboutGame, SIGNAL(triggered()), this, SLOT(showAbout()));
	//将菜单加入菜单栏
	menuBar->addMenu(helpMenu);

	//设置菜单栏
	setMenuBar(menuBar);


}

void MainWindow::showAbout(void)
{
	QMessageBox::information(this, tr("关于贪食蛇游戏"),
		           tr("QT程序：贪食蛇游戏1.0。许可协议:GPL3版权所有，侵权必究!"));
}

void MainWindow::showHelp(void)
{
	QMessageBox::information(this, tr("游戏帮助"),
		           tr("还要我告诉你怎么玩？呵呵。"));
}

void MainWindow::startGame(void)
{
	bRun = true;
	timer->start(times);
}

void MainWindow::pauseGame(void)
{
	bRun = false;
	timer->stop();
}

void MainWindow::speedUp(void)
{
	times -= 20;  
	if (times <= 20)
	{
		times = 20;
	}
	timer->stop();
	timer->start(times);
}

void MainWindow::speedDown(void)
{
	times += 20;
	if (times >= 500)
	{
		times = 500;
	}
	timer->stop();
	timer->start(times);
}
