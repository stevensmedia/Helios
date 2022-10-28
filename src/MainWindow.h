#include <QMainWindow>

class QTextEdit;
class TerminalView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent *);

private:
	TerminalView *outputView;
	QTextEdit *inputView;
};
