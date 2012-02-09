#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T00:38:14
#
#-------------------------------------------------

TARGET = MidiInputUi
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    Dialog.cpp \
    MidiInputUi.cpp

HEADERS += \
    Dialog.h \
    MidiInputUi.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    Dialog.ui
