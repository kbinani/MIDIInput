#-------------------------------------------------
#
# Project created by QtCreator 2012-02-10T00:38:14
#
#-------------------------------------------------

TARGET = MidiInput

CONFIG(release, debug|release):TEMPLATE = lib
else:TEMPLATE = app

QT       += core gui

SOURCES += \
    Dialog.cpp \
    Robot.cpp \
    WindowFinder.cpp \
    main.cpp \
    PianorollItem.cpp \
    Pianoroll.cpp \
    PianorollContent.cpp \
    PianorollKeyboard.cpp \
    PianorollContentScroller.cpp \
    MidiInputWin32WinMM.cpp \
    MidiInputMacCoreMIDI.cpp \
    DialogRunner.cpp \
    Parser.cpp \
    VSLuaNoteEx.cpp \
    Log.cpp \
    Settings.cpp

HEADERS += \
    Dialog.h \
    MidiInputReceiver.h \
    MidiInput.h \
    WindowFinder.h \
    Robot.h \
    PianorollItem.h \
    Pianoroll.h \
    PianorollContent.h \
    PianorollKeyboard.h \
    PianorollContentScroller.h \
    DialogRunner.h \
    Parser.h \
    StringUtil.h \
    VSLuaNoteEx.h \
    Log.h \
    Settings.h
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
    -llua5.1 \
    -ladvapi32

unix:LIBS += -llua

win32:INCLUDEPATH += \
    "C:\lua5_1_4_Sources\lua5.1\include"

unix:INCLUDEPATH += \
    /usr/include/lua5.1

mac:LIBS += -framework CoreFoundation -framework CoreMidi

RESOURCES += \
    MidiInput.qrc

win32:CONFIG(release, debug|release):          LIBS += -L$$PWD/../../cadencii/vsq/build/win32/release/ -lvsq
else:win32:CONFIG(debug, debug|release):       LIBS += -L$$PWD/../../cadencii/vsq/build/win32/debug/ -lvsq
else:unix:!mac:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cadencii/vsq/build/linux/release/ -lvsq
else:unix:!mac:CONFIG(debug, debug|release):   LIBS += -L$$PWD/../../cadencii/vsq/build/linux/debug/ -lvsq
else:unix:CONFIG(release, debug|release):      LIBS += -L$$PWD/../../cadencii/vsq/build/macosx/release/ -lvsq
else:unix:CONFIG(debug, debug|release):        LIBS += -L$$PWD/../../cadencii/vsq/build/macosx/debug/ -lvsq

INCLUDEPATH += $$PWD/../../cadencii/vsq
DEPENDPATH += $$PWD/../../cadencii/vsq

win32:CONFIG(release, debug|release):          PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/win32/release/vsq.lib
else:win32:CONFIG(debug, debug|release):       PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/win32/debug/vsq.lib
else:unix:!mac:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/linux/release/libvsq.a
else:unix:!mac:CONFIG(debug, debug|release):   PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/linux/debug/libvsq.a
else:unix:CONFIG(release, debug|release):      PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/macosx/release/libvsq.a
else:unix:CONFIG(debug, debug|release):        PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/macosx/debug/libvsq.a

OTHER_FILES += \
    ../MidiInput.lua \
    ../README.markdown
