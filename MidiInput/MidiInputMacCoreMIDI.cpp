#include <Qt>
#include "MidiInput.h"

#ifdef QT_ARCH_MACOSX

#include <CoreMIDI/MIDIServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <string>
#include <QString>

using namespace std;

MidiInputReceiver *MidiInput::receiver = NULL;

void MidiInput::setReceiver( MidiInputReceiver *aReceiver ){
    receiver = aReceiver;
}

int MidiInput::getDeviceCount()
{
    return MIDIGetNumberOfDevices();
}

const string MidiInput::getDeviceName( int index ){
    MIDIDeviceRef device = MIDIGetDevice( index );
    CFStringRef name;
    MIDIObjectGetStringProperty( device, CFSTR( "name" ), &name );
QString::codecForCStrings;
    const char *str = CFStringGetCStringPtr( name, CFStringGetSystemEncoding() );
    const int BUFFER_LENGTH = 1024;
    char buffer[BUFFER_LENGTH];
    ::memset( buffer, 0, sizeof( char ) * BUFFER_LENGTH );
    if( str == NULL ){
        if( CFStringGetCString( name, buffer, BUFFER_LENGTH, CFStringGetSystemEncoding() ) ){
            str = buffer;
        }
    }

    if( str ){
        return string( str );
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
