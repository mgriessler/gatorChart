
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


SOURCES += main.cpp\
        mainwindow.cpp \
    view.cpp \
    square.cpp \
    model.cpp \
    arrow.cpp \
    diagramitem.cpp \
    trap.cpp \
    diamond.cpp \
    parallelogram.cpp

HEADERS  += mainwindow.h \
    view.h \
    square.h \
    model.h \
    arrow.h \
    diagramitem.h \
    trap.h \
    diamond.h \
    parallelogram.h
