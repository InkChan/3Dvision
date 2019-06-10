#include "visionqt_test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	check_sensor();
	visionQT_test w;
	w.show();
	return a.exec();
}
