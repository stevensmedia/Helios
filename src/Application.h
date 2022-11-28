#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class QWebSocket;

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int &, char **);

	void connect(const QString &origin);
	void disconnect(void);
	bool isConnected(void);

	static Application *app;

signals:
	void connected(const QString &origin);
	void disconnected(void);

private:
	QWebSocket *socket;
};

#endif
