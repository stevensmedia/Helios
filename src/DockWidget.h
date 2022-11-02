#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QWidget>

class DockWidget : public QWidget
{
	Q_OBJECT

public:
	DockWidget(QWidget * = 0);

protected:
	void showEvent(QShowEvent *);
};

#endif
