#include <QApplication>

#include "MainWindow.h"

int main(int argc, char **argv) {
	QCoreApplication::setOrganizationName("hakubi.us");
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}
