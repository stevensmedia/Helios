#include "SettingsWidget.h"

#include <QtDebug>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>

SettingsWidget::SettingsWidget(QWidget * parent)
	:DockWidget(parent)
{
	setLayout(new QVBoxLayout);

	QPushButton *button = new QPushButton("Ok", this);
	layout()->addWidget(button);

	connect(button, &QPushButton::clicked, [this](bool) {
		this->hide();
	});

	setWindowTitle(tr("Settings"));
}
