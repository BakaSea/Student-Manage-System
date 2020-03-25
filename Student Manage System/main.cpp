#include "LoginWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);
	LoginWidget w;
	w.show();
	return a.exec();
}
