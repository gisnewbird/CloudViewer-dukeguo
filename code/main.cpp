#include "cloudviewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CloudViewer w;
	w.setWindowTitle(u8"��ľ������ȡϵͳ");
	w.show();
	return a.exec();
}
