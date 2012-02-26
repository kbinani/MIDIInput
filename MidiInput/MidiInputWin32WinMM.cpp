/**
 * MidiInputWin32WinMM.cpp
 * Copyright © 2012 kbinani
 *
 * This file is part of `MIDIInput UG Job Plugin'.
 *
 * `MIDIInput UG Job Plugin' is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License.
 *
 * `MIDIInput UG Job Plugin' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <Qt>
#include "MidiInput.h"

#ifdef QT_ARCH_WINDOWS

#include <windows.h>

using namespace std;

class MidiInputWin32WinMM
{
private:
    static HMIDIIN deviceHandle;

    static MidiInputReceiver *receiver;

public:
    static int getDeviceCount()
    {
        return (int)midiInGetNumDevs();
    }

    static const QString getDeviceName( int index )
    {
        MIDIINCAPSA caps;
        memset( &caps, 0, sizeof( MIDIINCAPSA ) );
        midiInGetDevCapsA( index, &caps, sizeof( MIDIINCAPSA ) );
        return QString::fromStdString( string( caps.szPname ) );
    }

    static void start( int index )
    {
        if( !deviceHandle ){
            midiInOpen( &deviceHandle, index, (DWORD_PTR)receive, NULL, CALLBACK_FUNCTION );
        }
        midiInStart( deviceHandle );
    }

    static void stop()
    {
        midiInStop( deviceHandle );
        midiInClose( deviceHandle );
        deviceHandle = NULL;
    }

    static void setReceiver( MidiInputReceiver *aReceiver )
    {
        receiver = aReceiver;
    }

private:
    MidiInputWin32WinMM()
    {
    }

    /**
     * @brief MIDI 入力を受信する
     */
    static void CALLBACK receive( HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2 )
    {
        if( wMsg == MM_MIM_DATA ){
            int receive = dwParam1;
            int message = receive & 0xF0;
            if( message == 0x80 || message == 0x90 ){
                if( receiver ){
                    receiver->send(
                        (unsigned char)(receive & 0xff),
                        (unsigned char)((receive & 0xffff) >> 8),
                        (unsigned char)((receive & ((2 << 24) - 1)) >> 16)
                    );
                }
            }
        }
    }
};

MidiInputReceiver *MidiInputWin32WinMM::receiver = NULL;
HMIDIIN MidiInputWin32WinMM::deviceHandle = NULL;

int MidiInput::getDeviceCount(){
    return MidiInputWin32WinMM::getDeviceCount();
}

const QString MidiInput::getDeviceName( int index ){
    return MidiInputWin32WinMM::getDeviceName( index );
}

void MidiInput::setReceiver( MidiInputReceiver *aReceiver ){
    MidiInputWin32WinMM::setReceiver( aReceiver );
}

void MidiInput::start( int index ){
    MidiInputWin32WinMM::start( index );
}

void MidiInput::stop(){
    MidiInputWin32WinMM::stop();
}

#endif
