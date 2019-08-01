#-------------------------------------------------
#
# Project created by QtCreator 2019-07-31T08:36:03
#
#-------------------------------------------------

QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetWorkInterfaceTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"
