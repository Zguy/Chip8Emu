#-------------------------------------------------
#
# Project created by QtCreator 2014-05-01T21:13:59
#
#-------------------------------------------------

QT += core gui widgets multimedia

CONFIG += c++11

TARGET = Chip8Emu
TEMPLATE = app


SOURCES += main.cpp\
	MainWindow.cpp \
	Emulator.cpp \
	CPU.cpp \
	Memory.cpp \
	Log.cpp \
	Display.cpp \
	Random.cpp \
	DisplayWidget.cpp \
	Input.cpp \
	SoundDevice.cpp \
	Sound.cpp

HEADERS += MainWindow.h \
	Emulator.h \
	CPU.h \
	Memory.h \
	Types.h \
	Log.h \
	Display.h \
	Random.h \
	Font.h \
	DisplayWidget.h \
	Input.h \
	SoundDevice.h \
	Sound.h

FORMS += MainWindow.ui
