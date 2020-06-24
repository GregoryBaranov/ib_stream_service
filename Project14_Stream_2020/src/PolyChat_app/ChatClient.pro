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
    emojis.cpp \
    listmessagemodel.cpp \
        mainwindow.cpp \
    client.cpp \
    messageviewdelegate.cpp \
    popup.cpp \
    styleapp.cpp

HEADERS  += mainwindow.h \
    client.h \
    emojis.h \
    listmessagemodel.h \
    messageviewdelegate.h \
    popup.h \
    smart_pointer.h \
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

win32 : MOC_DIR = $$OUT_PWD/tmp_moc
win32 : RCC_DIR = $$OUT_PWD/tmp_rcc
win32 : UI_DIR = $$OUT_PWD/tmp_ui
win32 : DESTDIR=bin
win32 : QMAKE_POST_LINK += $$(QTDIR)/bin/windeployqt $$OUT_PWD/$$DESTDIR

win32 : OBJECTS_DIR = $$OUT_PWD/tmp_o/win32
win32 : RC_ICONS = "icon.ico"

#message($$OUT_PWD)
#message($$DESTDIR)
