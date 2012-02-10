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
     * MIDI ���̓|�[�g�̌����擾����
     */
    static int getDeviceCount();

    /**
     * �w�肵���ԍ��� MIDI ���̓|�[�g�̃f�o�C�X�����擾����
     */
    static const std::string getDeviceName( int index );

    static void setReceiver( MidiInputReceiver *receiver );

    static void start( int index );

    static void stop( int index );

private:
    /**
     * MIDI ���͂���M����
     */
    static void CALLBACK MidiInput::receive( HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2 );
};

#endif
