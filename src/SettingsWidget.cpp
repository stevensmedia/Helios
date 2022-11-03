#include "SettingsWidget.h"

#include <QtDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

SettingsWidget::SettingsWidget(QWidget * parent)
	: Dialog(parent)
{
	setWindowTitle(tr("Settings"));

	/* Widgets */
	QListWidget *pageList = new QListWidget(this);

	QPushButton *newButton = new QPushButton("New Profile", this);
	QPushButton *closeButton = new QPushButton("Close", this);

	auto lbl = [this]() -> QTextEdit * {
		QTextEdit *widget = new QTextEdit(this);
		const int height = QFontMetrics(widget->currentFont()).boundingRect("Testing").height() + 10;
		widget->setMaximumHeight(height);
		widget->setMinimumHeight(height);
		widget->setLineWrapMode(QTextEdit::NoWrap);
		widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		return widget;
	};

	QTextEdit *nameLabel = lbl();
	QTextEdit *hostLabel = lbl();
	QTextEdit *portLabel = lbl();
	QTextEdit *userLabel = lbl();
	QTextEdit *passLabel = lbl();

	/* Layouts */
	QHBoxLayout *windowLayout = new QHBoxLayout;
	QVBoxLayout *pageLayout = new QVBoxLayout;
	windowLayout->addWidget(pageList);
	windowLayout->setStretchFactor(pageList, 0);
	windowLayout->addLayout(pageLayout);
	windowLayout->setStretchFactor(pageLayout, 2);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(newButton);
	buttonLayout->addStretch(2);
	buttonLayout->addWidget(closeButton);

	auto row = [this, pageLayout](const QString &name, QWidget *widget) {
		QHBoxLayout *l = new QHBoxLayout;
		l->addWidget(new QLabel(name, this));
		l->addWidget(widget);
		pageLayout->addLayout(l);
	};
	row(tr("Profile Name"), nameLabel);
	row(tr("Host"), hostLabel);
	row(tr("Port"), portLabel);
	row(tr("User name"), userLabel);
	row(tr("Password"), passLabel);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	setLayout(mainLayout);
	mainLayout->addLayout(windowLayout);
	mainLayout->addLayout(buttonLayout);

	/* Events */
	connect(newButton, &QPushButton::clicked, [this](bool) {
	});

	connect(closeButton, &QPushButton::clicked, [this](bool) {
		this->hide();
	});
}
