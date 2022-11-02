#include "Dialog.h"

#include <QtDebug>

Dialog::Dialog(QWidget * parent)
	: QWidget(parent, Qt::Tool | Qt::WindowStaysOnTopHint)
{
	hide();
}

void Dialog::showEvent(QShowEvent *)
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::WindowStaysOnTopHint);

	QRect geom = geometry();
	geom.moveCenter( parentWidget()->geometry().center() );
	move(geom.topLeft());
}
