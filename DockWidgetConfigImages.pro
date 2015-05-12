#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T13:02:52
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DockWidgetConfigImages
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dockwidgetconfig.cpp \
    dockwidgetimages.cpp

HEADERS  += mainwindow.h \
    dockwidgetconfig.h \
    dockwidgetimages.h

FORMS    += mainwindow.ui
