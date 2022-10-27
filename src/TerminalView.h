#include <QTextEdit>

class TerminalView : public QTextEdit
{
	Q_OBJECT

public:
	TerminalView(QWidget *parent = 0);
	~TerminalView();
};
