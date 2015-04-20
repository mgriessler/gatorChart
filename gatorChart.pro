
#-------------------------------------------------
#
# Project created by QtCreator 2015-03-01T00:49:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

TARGET = gatorChart
TEMPLATE = app

CONFIG+= static

SOURCES += main.cpp\
        mainwindow.cpp \
    view.cpp \
    square.cpp \
    model.cpp \
    arrow.cpp \
    trap.cpp \
    diamond.cpp \
    parallelogram.cpp \
    oval.cpp \
    shape.cpp

HEADERS  += mainwindow.h \
    view.h \
    square.h \
    model.h \
    arrow.h \
    trap.h \
    diamond.h \
    parallelogram.h \
    oval.h \
    shape.h

DISTFILES +=
