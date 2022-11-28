#include "Application.h"

#include <QWebSocket>
#include <QtDebug>

Application *Application::app = 0;

Application::Application(int &argc, char **argv)
	: QApplication(argc, argv)
{
	app = this;
}

void Application::connect(const QString &origin)
{
	if(socket) {
		return;
	}

	socket = new QWebSocket(origin);
	QObject::connect(socket, &QWebSocket::connected, [this, origin]() {
		qDebug() << "[Application::connect] Connected";
		emit connected(origin);
	});
	QObject::connect(socket, &QWebSocket::disconnected, [this]() {
		qDebug() << "[Application::connect] Disconnected";
		delete socket;
		socket = 0;
		emit disconnected();
	});
	QObject::connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), [this](QAbstractSocket::SocketError e) {
		qDebug() << "[Application::connect] Socket error: " << e;
	});
	QObject::connect(socket, &QWebSocket::textMessageReceived, [this](const QString &msg) {
		qDebug() << "[Application::connect] textMessageReceived:" << msg;
	});
}

void Application::disconnect(void)
{
	if(!socket) {
		return;
	}

	delete socket;
	socket = 0;
}

bool Application::isConnected(void)
{
	return !!socket;
}
