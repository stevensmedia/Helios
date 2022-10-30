#include "TerminalView.h"

TerminalView::TerminalView(QWidget *parent)
	: QTextEdit(parent)
{
	setStyleSheet("font-family: DejaVu Sans Mono; background-color: black; color: white; selection-color: black; selection-background-color: white;");
}

TerminalView::~TerminalView()
{
}
