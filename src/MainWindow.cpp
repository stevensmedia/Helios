#include "AboutWidget.h"
#include "Application.h"
#include "ConnectWidget.h"
#include "MainWindow.h"
#include "TerminalView.h"

#include <QtDebug>
#include <QAction>
#include <QDesktopServices>
#include <QDir>
#include <QFontMetrics>
#include <QFrame>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QStatusBar>
#include <QTextEdit>
#include <QVBoxLayout>

template <typename T> T find(QList<T> list, T none, std::function<bool(T)> cb)
{
	for(qsizetype i = 0; i < list.size(); ++i) {
		if(cb(list[i])) {
			return list[i];
		}
	}
	return none;
}

QAction *MainWindow::findAction(const QString &name)
{
	return find<QAction *>(actions, 0, [name](QAction *a) -> bool {
		return a->objectName() == name;
	});
}

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
	a(tr("&Settings..."), "Settings", sunMenu);

	serverMenu = menuBar()->addMenu(tr("Server"));
	a(tr("&Connect..."), "Connect", serverMenu);
	a(tr("&Disconnect"), "Disconnect", serverMenu);

	editMenu = menuBar()->addMenu(tr("Edit"));
	a(tr("Undo"), "Undo", editMenu);
	a(tr("Redo"), "Redo", editMenu);
	editMenu->addSeparator();
	a(tr("Cut"), "Cut", editMenu);
	a(tr("Copy"), "Copy", editMenu);
	a(tr("Paste"), "Paste", editMenu);

	helpMenu = menuBar()->addMenu(tr("Help"));
	a(tr("&Help..."), "Help", helpMenu);

	aboutWidget = new AboutWidget(this);
	connectWidget = new ConnectWidget(this);

	connect(findAction("About"), &QAction::triggered, [this]() {
		aboutWidget->show();
		aboutWidget->activateWindow();
	});

	connect(findAction("Disconnect"), &QAction::triggered, [this]() {
		qDebug() << "[MainWindow Disconnect] activated";
		Application::app->disconnect();
	});

	connect(findAction("Connect"), &QAction::triggered, [this]() {
		qDebug() << "[MainWindow Connect] activated";
		connectWidget->show();
		connectWidget->activateWindow();
	});

	std::function<void (const QString &)> onConnect = [this](const QString &s) {
		findAction("Connect")->setEnabled(false);
		findAction("Disconnect")->setEnabled(true);
		connectedStatus->setText(QString("Connected to ") + s);
		qDebug() << "[MainWindow onConnect]";
	};

	std::function<void ()> onDisconnect = [this]() {
		findAction("Connect")->setEnabled(true);
		findAction("Disconnect")->setEnabled(false);
		connectedStatus->setText("Disconnected");
		qDebug() << "[MainWindow onDisconnect]";
	};

	connect(Application::app, &Application::connected, onConnect);
	connect(Application::app, &Application::disconnected, onDisconnect);

	connectedStatus = new QLabel(this);
	connectedStatus->setMargin(5);
	setStatusBar(new QStatusBar);
	statusBar()->addPermanentWidget(connectedStatus);

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
		inputView->setMaximumHeight(height + margin + 5);
		inputView->setMinimumHeight(height + margin + 5);
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

	onDisconnect();
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
