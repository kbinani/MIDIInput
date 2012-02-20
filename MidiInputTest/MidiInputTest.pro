#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T22:06:38
#
#-------------------------------------------------

QT       += core

TARGET = MidiInputTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../MidiInput/Parser.cpp \
    ../MidiInput/PianorollItem.cpp \
    ../MidiInput/VSLuaNoteEx.cpp \
    ParserTest.cpp \
    VSLuaNoteExTest.cpp \
    StringUtilTest.cpp

HEADERS += \
    Util.h

LIBS += -lcppunit

win32:CONFIG(release, debug|release):          LIBS += -L$$PWD/../../cadencii/vsq/build/win32/release/ -lvsq
else:win32:CONFIG(debug, debug|release):       LIBS += -L$$PWD/../../cadencii/vsq/build/win32/debug/ -lvsq
else:unix:!mac:CONFIG(release, debug|release): LIBS += -L$$PWD/../../cadencii/vsq/build/linux/release/ -lvsq
else:unix:!mac:CONFIG(debug, debug|release):   LIBS += -L$$PWD/../../cadencii/vsq/build/linux/debug/ -lvsq
else:unix:CONFIG(release, debug|release):      LIBS += -L$$PWD/../../cadencii/vsq/build/macosx/release/ -lvsq
else:unix:CONFIG(debug, debug|release):        LIBS += -L$$PWD/../../cadencii/vsq/build/macosx/debug/ -lvsq

INCLUDEPATH += $$PWD/../../cadencii/vsq \
    $$PWD../MidiInput

win32:CONFIG(release, debug|release):          PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/win32/release/vsq.lib
else:win32:CONFIG(debug, debug|release):       PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/win32/debug/vsq.lib
else:unix:!mac:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/linux/release/libvsq.a
else:unix:!mac:CONFIG(debug, debug|release):   PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/linux/debug/libvsq.a
else:unix:CONFIG(release, debug|release):      PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/macosx/release/libvsq.a
else:unix:CONFIG(debug, debug|release):        PRE_TARGETDEPS += $$PWD/../../cadencii/vsq/build/macosx/debug/libvsq.a
