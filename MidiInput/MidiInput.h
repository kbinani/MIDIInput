#ifndef __midiinput_MidiInput_h__
#define __midiinput_MidiInput_h__

#ifdef WIN32
#include <windows.h>
#endif
#include <QString>
#include <string>
#include "MidiInputReceiver.h"

class MidiInput{
private:
    static MidiInputReceiver *receiver;

#ifdef WIN32
    static HMIDIIN deviceHandle;
#endif

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

    static void stop( int index );

private:
#ifdef WIN32
    /**
     * MIDI 入力を受信する
     */
    static void CALLBACK MidiInput::receive( HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2 );
#endif
};

#endif
