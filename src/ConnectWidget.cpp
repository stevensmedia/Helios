#include "Application.h"
#include "ConnectWidget.h"

#include <QtDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

ConnectWidget::ConnectWidget(QWidget * parent)
	: Dialog(parent)
{
	setWindowTitle(tr("Settings"));

	/* Widgets */
	QListWidget *pageList = new QListWidget(this);

	QPushButton *newButton = new QPushButton("New Profile", this);
	QPushButton *connectButton = new QPushButton("Connect", this);
	QPushButton *closeButton = new QPushButton("Close", this);

	std::function<QTextEdit*()> lbl = [this]() -> QTextEdit * {
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
	QTextEdit *urlLabel = lbl();
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
	buttonLayout->addWidget(connectButton);
	buttonLayout->addWidget(closeButton);

	auto row = [this, pageLayout](const QString &name, QWidget *widget) {
		QHBoxLayout *l = new QHBoxLayout;
		l->addWidget(new QLabel(name, this));
		l->addWidget(widget);
		pageLayout->addLayout(l);
	};
	row(tr("Profile Name"), nameLabel);
	row(tr("URL"), urlLabel);
	row(tr("User name"), userLabel);
	row(tr("Password"), passLabel);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	setLayout(mainLayout);
	mainLayout->addLayout(windowLayout);
	mainLayout->addLayout(buttonLayout);

	/* Events */
	connect(newButton, &QPushButton::clicked, [this]() {
	});

	connect(connectButton, &QPushButton::clicked, [this]() {
	});

	connect(closeButton, &QPushButton::clicked, [this]() {
		this->hide();
	});

	std::function<void()> updateConnection = [&]() {
		QListWidgetItem *current = pageList->currentItem();
		QVector<QWidget *> widgets {
			nameLabel,
			urlLabel,
			userLabel,
			passLabel
		};

		for(QWidget *i: widgets) {
			i->setEnabled(!!current);
		}
	};

	connect(pageList, &QListWidget::itemSelectionChanged, updateConnection);
	updateConnection();
}
