#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T19:53:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

CONFIG += qt

SOURCES += main.cpp\
        waldogui.cpp \
    filtrosgui.cpp

LIBS += `pkg-config --cflags --libs opencv`

HEADERS  += waldogui.h \
    filtrosgui.h

FORMS    += waldogui.ui \
    filtrosgui.ui
