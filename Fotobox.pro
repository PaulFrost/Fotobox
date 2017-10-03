#-------------------------------------------------
#
# Project created by QtCreator 2017-10-02T22:36:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fotobox
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        fotoboxwidget.cpp \
    camcontroller.cpp

HEADERS  += fotoboxwidget.h \
    camcontroller.h

#LIBS += -L/usr/local/lib -lgphoto2.6

LIBS += "/usr/local/lib/libgphoto2.dylib"
LIBS += "/usr/local/lib/libgphoto2_port.12.dylib"

#win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lgphoto2.6
#else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lgphoto2.6
#else:unix: LIBS += -L/usr/local/lib/ -lgphoto2.6

INCLUDEPATH += /usr/local/include/gphoto2
DEPENDPATH += /usr/local/include/gphoto2
