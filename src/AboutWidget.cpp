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

	QLabel *link = new QLabel("<a href=\"https://heliosmush.org/\">heliosmush.org</a>", this);
	link->setOpenExternalLinks(true);

	layout()->addWidget(new QLabel(tr("Praise Helios!"), this));
	layout()->addWidget(link);
	layout()->addWidget(new QLabel(tr("Version") + QString(" " VERSION), this));
	QPushButton *button = new QPushButton("Ok", this);
	layout()->addWidget(button);

	connect(button, &QPushButton::clicked, [this](bool) {
		this->hide();
	});

	setWindowTitle(tr("About"));
}
