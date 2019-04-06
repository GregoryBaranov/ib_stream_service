#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T21:02:32
#
#-------------------------------------------------

QT       += core gui network
QT += core
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DownloadHttp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    downloader.cpp

HEADERS  += widget.h \
    downloader.h

FORMS    += widget.ui
