#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T18:59:56
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




TARGET = ChatClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    popup.cpp \
    styleapp.cpp

HEADERS  += mainwindow.h \
    client.h \
    popup.h \
    styleapp.h

FORMS    += mainwindow.ui


QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

RESOURCES += \
    image.qrc
