/*贪食蛇游戏用QT实现*/
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();
}
