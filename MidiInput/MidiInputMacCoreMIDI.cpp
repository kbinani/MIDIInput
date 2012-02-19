#include <Qt>
#include "MidiInput.h"

#ifdef QT_ARCH_MACOSX

#include <CoreMIDI/MIDIServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <string>
#include <QString>
#include <sstream>

using namespace std;

MidiInputReceiver *MidiInput::receiver = NULL;

void MidiInput::setReceiver( MidiInputReceiver *aReceiver ){
    receiver = aReceiver;
}

int MidiInput::getDeviceCount()
{
    return MIDIGetNumberOfDevices();
}

const QString MidiInput::getDeviceName( int index ){
    MIDIDeviceRef device = MIDIGetDevice( index );
    CFStringRef name;
    MIDIObjectGetStringProperty( device, CFSTR( "name" ), &name );

    const char *str = CFStringGetCStringPtr( name, kCFStringEncodingUTF16LE );
    const int BUFFER_LENGTH = 1024;
    char buffer[BUFFER_LENGTH];
    ::memset( buffer, 0, sizeof( char ) * BUFFER_LENGTH );
    if( str == NULL ){
        if( CFStringGetCString( name, buffer, BUFFER_LENGTH, kCFStringEncodingUTF16LE ) ){
            str = buffer;
        }
    }

    if( str ){
        ushort unicode[BUFFER_LENGTH];
        int size = 0;
        for( int i = 0; i < BUFFER_LENGTH; i += 2 ){
            char lo = str[i];
            char hi = str[i + 1];
            if( hi == 0 && lo == 0 ){
                break;
            }
            unicode[i / 2] = (0xFF00 & ((int)hi << 8)) | (0xFF & lo);
            size++;
        }
        QString result;
        result.setUtf16( unicode, size );
        return result;
    }else{
        return "";
    }
}

void MidiInput::stop( int index ){
    //TODO:
}

void MidiInput::start( int index ){
    //TODO:
}

#endif
