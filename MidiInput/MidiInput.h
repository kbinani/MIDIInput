#ifndef __midiinput_MidiInput_h__
#define __midiinput_MidiInput_h__

#include <QString>
#include <string>
#include "MidiInputReceiver.h"

class MidiInput{
public:
    /**
     * MIDI 入力ポートの個数を取得する
     */
    static int getDeviceCount();

    /**
     * 指定した番号の MIDI 入力ポートのデバイス名を取得する
     */
    static const QString getDeviceName( int index );

    static void setReceiver( MidiInputReceiver *receiver );

    static void start( int index );

    static void stop();
};

#endif
