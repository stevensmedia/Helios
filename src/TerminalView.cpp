#include "TerminalView.h"

TerminalView::TerminalView(QWidget *parent)
	: QTextEdit(parent)
{
	setStyleSheet("background-color: black; color: white; selection-color: black; selection-background-color: white;");
}

TerminalView::~TerminalView()
{
}
