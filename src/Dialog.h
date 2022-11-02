#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QWidget>

class Dialog : public QWidget
{
	Q_OBJECT

public:
	Dialog(QWidget * = 0);

protected:
	void showEvent(QShowEvent *);
};

#endif
