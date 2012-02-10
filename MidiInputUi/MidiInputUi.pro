#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T00:38:14
#
#-------------------------------------------------

TARGET = MidiInputUi
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    MidiInputUi.cpp \
    Dialog.cpp \
    DialogRunner.cpp

HEADERS += \
    MidiInputUi.h \
    Dialog.h \
    DialogRunner.h
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
