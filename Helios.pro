TARGET = Helios

QT += core widgets websockets

CONFIG += c++latest

VERSION = 0.1

SOURCES = $$files(src/*.c) $$files(src/*.cpp)

HEADERS = $$files(src/*.h)

DESTDIR = dist

MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

VERSION_FLAGS = -DVERSION=\\\"$$VERSION\\\"
QMAKE_CFLAGS += $$VERSION_FLAGS
QMAKE_CXXFLAGS += $$VERSION_FLAGS

wasm {
CONFIG += feature-thread
QMAKE_LFLAGS += -sASYNCIFY -O2 --cache $$OBJECTS_DIR/cache
QMAKE_CXXFLAGS += -O2 --cache $$OBJECTS_DIR/cache
}
