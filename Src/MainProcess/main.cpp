#include "MainProcess.h"
#include <QtWidgets/QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
	QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

	QApplication a(argc, argv);
	MainProcess w;
	w.show();
	return a.exec();
}
