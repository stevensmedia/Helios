#include "Application.h"
#include "MainWindow.h"

int main(int argc, char **argv) {
	QCoreApplication::setOrganizationName("hakubi.us");
	QCoreApplication::setOrganizationDomain("hakubi.us");
	QCoreApplication::setApplicationName("Helios");
	Application app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}
