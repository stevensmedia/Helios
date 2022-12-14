#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class QAction;
class QLabel;
class QMenu;
class QTextEdit;
class TerminalView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


protected:
	void closeEvent(QCloseEvent *);

private:
	TerminalView *outputView;
	QTextEdit *inputView;

	QMenu *sunMenu;
	QMenu *serverMenu;
	QMenu *editMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;

	QLabel *connectedStatus;

	QList<QAction *> actions;
	QAction *findAction(const QString &);

	QWidget *aboutWidget;
	QWidget *connectWidget;
};

#endif
