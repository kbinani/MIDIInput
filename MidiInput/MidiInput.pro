#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T00:38:14
#
#-------------------------------------------------

TARGET = MidiInputUi
TEMPLATE = lib

SOURCES += \
    Dialog.cpp \
    DialogRunner.cpp \
    Robot.cpp \
    MidiInputReceiver.cpp \
    MidiInput.cpp \
    WindowFinder.cpp \
    main.cpp

HEADERS += \
    Dialog.h \
    DialogRunner.h \
    MidiInputReceiver.h \
    MidiInput.h \
    WindowFinder.h \
    Robot.h
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

LIBS += \
    -L"C:\lua5_1_4_Sources\lua5.1\lib\static" \
    -lwinmm \
    -luser32 \
    -llua5.1

INCLUDEPATH += \
    "C:\lua5_1_4_Sources\lua5.1\include"