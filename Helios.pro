TARGET = Helios

QT += core widgets websockets

CONFIG += c++latest

VERSION = 0.1

SOURCES = src/main.cpp src/MainWindow.cpp src/TerminalView.cpp

HEADERS = src/MainWindow.h src/TerminalView.h

DESTDIR = dist/

MOC_DIR = build/
OBJECTS_DIR = build/
UI_DIR = build/
