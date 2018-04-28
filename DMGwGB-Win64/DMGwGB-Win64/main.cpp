#include "MainWindow.h"
#include <QApplication>
#include <QGLFormat>
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	//_CrtDumpMemoryLeaks();

	return a.exec();
}
