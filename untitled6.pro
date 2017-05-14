#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T10:01:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled6
TEMPLATE = app
CONFIG += C++14
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    progresscircle.cpp \
    timec.cpp

HEADERS  += mainwindow.h \
    progresscircle.h \
    timec.h

FORMS    += mainwindow.ui
