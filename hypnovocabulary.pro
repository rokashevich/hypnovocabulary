DEFINES += "VERSION=\"\\\"$$system(git describe --always)\\\"\""

QT += core gui widgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hypnovocabulary
TEMPLATE = app


SOURCES += main.cpp\
    stripe.cpp \
    mainwidget.cpp

HEADERS  += \
    stripe.h \
    mainwidget.h

RESOURCES += \
    hypnovocabulary.qrc

win32:RC_ICONS += hypnovocabulary.ico

DESTDIR = $$PWD/bundle
