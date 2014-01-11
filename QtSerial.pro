#-------------------------------------------------
#
# Project created by QtCreator 2014-01-07T20:16:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = QtSerial
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

RESOURCES += \
    icon/icon.qrc
