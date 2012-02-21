#include <Qt>
#include "MidiInput.h"

#ifdef QT_ARCH_MACOSX

#include <CoreMIDI/MIDIServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <string>
#include <sstream>
#include <vector>
#include <QString>

using namespace std;

MidiInputReceiver *MidiInput::receiver = NULL;

class MidiInputEndpoint
{
public:
    MIDIDeviceRef device;
    MIDIEntityRef entity;
    MIDIEndpointRef endpoint;

    const QString getName()
    {
        CFStringRef deviceName;
        MIDIObjectGetStringProperty( device, kMIDIPropertyName, &deviceName );
        CFStringRef endpointName;
        MIDIObjectGetStringProperty( endpoint, kMIDIPropertyName, &endpointName );
        if( deviceName && endpointName ){
            QString result = getQStringFromCFStringRef( deviceName ) + " (" + getQStringFromCFStringRef( endpointName ) + ")";
            CFRelease( deviceName );
            CFRelease( endpointName );
            return result;
        }else{
            return "";
        }
    }

private:
    static const QString getQStringFromCFStringRef( CFStringRef stringRef )
    {
        const char *str = CFStringGetCStringPtr( stringRef, kCFStringEncodingUTF16LE );
        const int BUFFER_LENGTH = 1024;
        char buffer[BUFFER_LENGTH];
        ::memset( buffer, 0, sizeof( char ) * BUFFER_LENGTH );
        if( str == NULL ){
            if( CFStringGetCString( stringRef, buffer, BUFFER_LENGTH, kCFStringEncodingUTF16LE ) ){
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
};

/**
 * @brief オンライン状態の MIDI 入力ポートを取得する
 */
vector<MidiInputEndpoint> getOnlineEndpoints()
{
    vector<MidiInputEndpoint> result;
    OSStatus status;
    int devices = MIDIGetNumberOfDevices();
    for( int i = 0; i < devices; i++ ){
        MIDIDeviceRef device = MIDIGetDevice( i );
        int entities = MIDIDeviceGetNumberOfEntities( device );
        for( int j = 0; j < entities; j++ ){
            MIDIEntityRef entity = MIDIDeviceGetEntity( device, j );
            int sources = MIDIEntityGetNumberOfSources( entity );
            for( int k = 0; k < sources; k++ ){
                MIDIEndpointRef endpoint = MIDIEntityGetSource( entity, k );
                SInt32 isOffline;
                status = MIDIObjectGetIntegerProperty( endpoint, kMIDIPropertyOffline, &isOffline );
                if( status == noErr && isOffline != 0 ){
                    MidiInputEndpoint item;
                    item.device = device;
                    item.entity = entity;
                    item.endpoint = endpoint;
                    result.push_back( item );
                }
            }
        }
    }
    return result;
}

void MidiInput::setReceiver( MidiInputReceiver *aReceiver ){
    receiver = aReceiver;
}

int MidiInput::getDeviceCount()
{
    vector<MidiInputEndpoint> endpoints = getOnlineEndpoints();
    return (int)endpoints.size();
}

const QString MidiInput::getDeviceName( int index ){
    vector<MidiInputEndpoint> endpoints = getOnlineEndpoints();
    return endpoints[index].getName();
}

void MidiInput::stop( int index ){
    //TODO:
}

void MidiInput::start( int index ){
    //TODO:
}

#endif
