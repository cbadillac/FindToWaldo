#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T19:53:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        waldogui.cpp

LIBS += `pkg-config --cflags --libs opencv`

HEADERS  += waldogui.h

FORMS    += waldogui.ui
