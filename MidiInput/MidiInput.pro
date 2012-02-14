#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T00:38:14
#
#-------------------------------------------------

TARGET = MidiInput
TEMPLATE = app

QT       += core gui

SOURCES += \
    Dialog.cpp \
    DialogRunner.cpp \
    Robot.cpp \
    MidiInput.cpp \
    WindowFinder.cpp \
    main.cpp \
    DialogListener.cpp \
    PianorollItem.cpp \
    Pianoroll.cpp

HEADERS += \
    Dialog.h \
    DialogRunner.h \
    MidiInputReceiver.h \
    MidiInput.h \
    WindowFinder.h \
    Robot.h \
    DialogListener.h \
    PianorollItem.h \
    Pianoroll.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    Dialog.ui \
    Pianoroll.ui

win32:LIBS += \
    -L"C:\lua5_1_4_Sources\lua5.1\lib\static" \
    -lwinmm \
    -luser32 \
    -llua5.1

unix:LIBS += -llua

win32:INCLUDEPATH += \
    "C:\lua5_1_4_Sources\lua5.1\include"

RESOURCES += \
    MidiInput.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cadencii/vsq/release/ -lvsq
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../cadencii/vsq/debug/ -lvsq
else:symbian: LIBS += -lvsq
else:unix: LIBS += -L$$PWD/../../cadencii/vsq/ -lvsq

INCLUDEPATH += $$PWD/../../cadencii/vsq
DEPENDPATH += $$PWD/../../cadencii/vsq

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/release/vsq.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/debug/vsq.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/libvsq.a
