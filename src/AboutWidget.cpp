#include "AboutWidget.h"

#include <QtDebug>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

AboutWidget::AboutWidget(QWidget * parent)
	:DockWidget(parent)
{
	setLayout(new QVBoxLayout);

	layout()->addWidget(new QLabel(tr("Praise Helios!"), this));
	QPushButton *button = new QPushButton("Ok", this);
	layout()->addWidget(button);

	connect(button, &QPushButton::clicked, [this](bool) {
		this->hide();
	});

	setWindowTitle(tr("About"));
}
