#include <vector>
#include <iostream>
#include "MidiInput.h"
#include "WindowFinder.h"

using namespace std;

MidiInputReceiver *MidiInput::receiver = NULL;
HMIDIIN MidiInput::deviceHandle = NULL;

int MidiInput::getDeviceCount(){
    return (int)midiInGetNumDevs();
}

const string MidiInput::getDeviceName( int index ){
    MIDIINCAPSA caps;
    memset( &caps, 0, sizeof( MIDIINCAPSA ) );
    midiInGetDevCapsA( index, &caps, sizeof( MIDIINCAPSA ) );
    string result = caps.szPname;
    return result;
}

void MidiInput::start( int index ){
    if( !MidiInput::deviceHandle ){
        midiInOpen( &MidiInput::deviceHandle, index, (DWORD_PTR)MidiInput::receive, NULL, CALLBACK_FUNCTION );
    }
    midiInStart( MidiInput::deviceHandle );
}

void MidiInput::setReceiver( MidiInputReceiver *receiver ){
    MidiInput::receiver = receiver;
}

void CALLBACK MidiInput::receive( HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2 ){
    switch( wMsg ){
        case MM_MIM_OPEN:{
            return;
        }
        case MM_MIM_CLOSE:{
            return;
        }
        case MM_MIM_DATA:{
            int receive = dwParam1;
            switch( receive & 0xF0 ){
                case 0x80:
                case 0x90:
                case 0xa0:
                case 0xb0:
                case 0xe0:{
                    if( MidiInput::receiver ){
                        MidiInput::receiver->send(
                            (uint8_t)(receive & 0xff),
                            (uint8_t)((receive & 0xffff) >> 8),
                            (uint8_t)((receive & ((2 << 24) - 1)) >> 16)
                        );
                    }
                    break;
                }
                case 0xc0:
                case 0xd0:{
                    if( MidiInput::receiver ){
                        MidiInput::receiver->send(
                            (uint8_t)( receive & 0xff ),
                            (uint8_t)((receive & 0xffff) >> 8)
                        );
                    }
                    break;
                }
            }
            return;
        }
        case MM_MIM_LONGDATA:{
            return;
        }
        case MM_MIM_ERROR:{
            return;
        }
        case MM_MIM_LONGERROR:{
            return;
        }
    }
}
