#include "myGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	myGUI w;
	w.show();
	return a.exec();
}
