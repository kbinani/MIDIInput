#ifndef __midiinput_MidiInput_h__
#define __midiinput_MidiInput_h__

#include <windows.h>
#include <string>
#include "MidiInputReceiver.h"

class MidiInput{
private:
    static MidiInputReceiver *receiver;

    static HMIDIIN deviceHandle;

public:
    /**
     * MIDI 入力ポートの個数を取得する
     */
    static int getDeviceCount();

    /**
     * 指定した番号の MIDI 入力ポートのデバイス名を取得する
     */
    static const std::string getDeviceName( int index );

    static void setReceiver( MidiInputReceiver *receiver );

    static void start( int index );

    static void stop( int index );

private:
    /**
     * MIDI 入力を受信する
     */
    static void CALLBACK MidiInput::receive( HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2 );
};

#endif
