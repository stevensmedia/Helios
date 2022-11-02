#include "AboutWidget.h"

#include <QtDebug>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

AboutWidget::AboutWidget(QWidget * parent)
	:Dialog(parent)
{
	setLayout(new QVBoxLayout);

	layout()->addWidget(new QLabel(tr("Praise Helios!"), this));
	layout()->addWidget(new QLabel(tr("Version") + QString(" " VERSION), this));
	QPushButton *button = new QPushButton("Ok", this);
	layout()->addWidget(button);

	connect(button, &QPushButton::clicked, [this](bool) {
		this->hide();
	});

	setWindowTitle(tr("About"));
}
