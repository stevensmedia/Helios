TARGET = Helios

QT += core widgets websockets

CONFIG += c++latest

VERSION = 0.1

SOURCES = \
	src/main.cpp \
	src/AboutWidget.cpp \
	src/ConnectWidget.cpp \
	src/Dialog.cpp \
	src/MainWindow.cpp \
	src/TerminalView.cpp

HEADERS = \
	src/AboutWidget.h \
	src/ConnectWidget.h \
	src/Dialog.h \
	src/MainWindow.h \
	src/TerminalView.h

DESTDIR = dist/

MOC_DIR = build/
OBJECTS_DIR = build/
UI_DIR = build/

VERSION_FLAGS = -DVERSION=\\\"$$VERSION\\\"
QMAKE_CFLAGS += $$VERSION_FLAGS
QMAKE_CXXFLAGS += $$VERSION_FLAGS

wasm {
CONFIG += feature-thread
QMAKE_LFLAGS += -sASYNCIFY -Os
}
