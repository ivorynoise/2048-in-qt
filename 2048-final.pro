#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T20:39:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048-final
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
    core/board.cpp \
    core/subject.cpp \
    core/observer.cpp \
    core/tile.cpp \
    core/game.cpp \
    gui/qgameboard.cpp \
    gui/qtile.cpp \
    gui/qgameoverwindow.cpp \
    gui/qresetbutton.cpp \
    gui/mainwindow.cpp

HEADERS  += \
    core/board.h \
    core/subject.h \
    core/observer.h \
    core/tile.h \
    core/game.h \
    gui/qgameboard.h \
    gui/qtile.h \
    gui/qgameoverwindow.h \
    gui/qresetbutton.h \
    gui/mainwindow.h
