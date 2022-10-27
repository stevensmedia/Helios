#include "MainWindow.h"
#include "TerminalView.h"

#include <QDesktopServices>
#include <QDir>
#include <QVBoxLayout>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("Helios");

	QSettings settings;
	restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
	setCentralWidget(new TerminalView);

	restoreState(settings.value("mainWindowState").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent *)
{
	QSettings settings;
	settings.setValue("mainWindowGeometry", saveGeometry());
	settings.setValue("mainWindowState", saveState());
}

MainWindow::~MainWindow()
{
}
