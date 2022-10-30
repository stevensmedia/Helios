#include "MainWindow.h"
#include "TerminalView.h"

#include <QtDebug>
#include <QAction>
#include <QDesktopServices>
#include <QDir>
#include <QFontMetrics>
#include <QFrame>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Helios"));

	auto a = [this](const QString &text, const QString &name, QMenu *menu) -> QAction * {
		QAction *action = new QAction(text);
		action->setObjectName(name);
		actions.append(action);
		menu->addAction(action);
		return action;
	};

	sunMenu = menuBar()->addMenu(tr("☼"));
	a(tr("&About..."), "About", sunMenu);
	a(tr("&Preferences..."), "Preferences", sunMenu);

	serverMenu = menuBar()->addMenu(tr("Server"));
	a(tr("&Connect..."), "Connect", serverMenu);
	a(tr("&Disconnect"), "Disonnect", serverMenu);

	editMenu = menuBar()->addMenu(tr("Edit"));
	a(tr("Undo"), "Undo", editMenu);
	a(tr("Redo"), "Redo", editMenu);
	editMenu->addSeparator();
	a(tr("Cut"), "Cut", editMenu);
	a(tr("Copy"), "Copy", editMenu);
	a(tr("Paste"), "Paste", editMenu);

	helpMenu = menuBar()->addMenu(tr("Help"));
	a(tr("&Help..."), "Help", helpMenu);

	outputView = new TerminalView(this);

	inputView = new QTextEdit(this);
	inputView->setLineWrapMode(QTextEdit::WidgetWidth);

	// Make the input view change height according to its contents
	connect(inputView, &QTextEdit::textChanged, [this]() {
		const int margin = inputView->contentsMargins().top() +
		                   inputView->contentsMargins().bottom() + 10;
		const int fontHeight = QFontMetrics(inputView->currentFont()).boundingRect("Testing").height();
		const int lines = inputView->document()->lineCount();
		const int height = (lines ? lines : 1) * fontHeight;
		inputView->setMaximumHeight(height + margin);
		inputView->setMinimumHeight(height + margin);
	});

	inputView->clear();

	QFrame *central = new QFrame;
	QLayout *layout = new QVBoxLayout(central);
	layout->addWidget(outputView);
	layout->addWidget(inputView);

	setCentralWidget(central);

	QSettings settings;
	restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
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
