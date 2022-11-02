#include "DockWidget.h"

#include <QtDebug>

DockWidget::DockWidget(QWidget * parent)
	: QWidget(parent, Qt::Tool | Qt::WindowStaysOnTopHint)
{
	hide();
}

void DockWidget::showEvent(QShowEvent *)
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::WindowStaysOnTopHint);

	QRect geom = geometry();
	geom.moveCenter( parentWidget()->geometry().center() );
	move(geom.topLeft());
}
