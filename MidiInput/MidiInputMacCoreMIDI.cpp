/**
 * MidiInputMacCoreMIDI.cpp
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

#ifdef QT_ARCH_MACOSX

#include <CoreMIDI/MIDIServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <string>
#include <sstream>
#include <vector>
#include <QString>

using namespace std;

class MidiInputMacCoreMIDI
{
private:
    class Endpoint{
    public:
        MIDIDeviceRef device;
        MIDIEntityRef entity;
        MIDIEndpointRef endpoint;

        MIDIClientRef client;
        MIDIPortRef port;

    public:
        Endpoint()
        {
            device = 0;
            entity = 0;
            endpoint = 0;
            client = 0;
            port = 0;
        }

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

    static MidiInputReceiver *receiver;

    /**
     * 現在接続中の endpoint 情報
     */
    static Endpoint currentEndpoint;

public:
    static int getDeviceCount()
    {
        vector<Endpoint> endpoints = getOnlineEndpoints();
        return (int)endpoints.size();
    }

    static const QString getDeviceName( int index )
    {
        vector<Endpoint> endpoints = getOnlineEndpoints();
        if( 0 <= index && index < endpoints.size() ){
            return endpoints[index].getName();
        }else{
            return "";
        }
    }

    static void setReceiver( MidiInputReceiver *aReceiver )
    {
        receiver = aReceiver;
    }

    static void receive( const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon )
    {
        MIDIPacket *packet = (MIDIPacket *)&(pktlist->packet[0]);
        UInt32 count = pktlist->numPackets;
        for( int i = 0; i < count; i++ ){
            Byte message = packet->data[0] & 0xF0;
            if( message == 0x90 || message == 0x80 ){
                unsigned char noteNumber = packet->data[1];
                unsigned char velocity = packet->data[2];
                receiver->send( message, noteNumber, velocity );
            }
            packet = MIDIPacketNext( packet );
        }
    }

    static void stop()
    {
        if( currentEndpoint.port ){
            MIDIPortDispose( currentEndpoint.port );
            currentEndpoint.port = 0;
        }
        if( currentEndpoint.client ){
            MIDIClientDispose( currentEndpoint.client );
            currentEndpoint.client = 0;
        }
        currentEndpoint.endpoint = 0;
        currentEndpoint.entity = 0;
        currentEndpoint.device = 0;
    }

    static void start( int index )
    {
        stop();

        vector<Endpoint> endpoints = getOnlineEndpoints();
        if( index < 0 || endpoints.size() <= index ){
            return;
        }

        Endpoint endpoint = endpoints[index];
        currentEndpoint.device = endpoint.device;
        currentEndpoint.entity = endpoint.entity;
        currentEndpoint.endpoint = endpoint.endpoint;

        OSStatus err;

        // client 作成
        err = MIDIClientCreate( CFSTR( "MIDIInputClient" ), NULL, NULL, &currentEndpoint.client );
        if( err != noErr ){
            return;
        }

        // port 作成
        err = MIDIInputPortCreate(
                    currentEndpoint.client, CFSTR( "MIDIInputPort" ),
                    receive, NULL, &currentEndpoint.port );
        if( err != noErr ){
            MIDIClientDispose( currentEndpoint.client );
            currentEndpoint.client = 0;
            return;
        }

        // endpoint と接続
        err = MIDIPortConnectSource( currentEndpoint.port, currentEndpoint.endpoint, NULL );
        if( err != noErr ){
            stop();
        }
    }

private:
    /**
     * @brief オンライン状態の MIDI 入力ポートを取得する
     */
    static vector<Endpoint> getOnlineEndpoints()
    {
        vector<MidiInputMacCoreMIDI::Endpoint> result;
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
                    if( status == noErr && !isOffline ){
                        MidiInputMacCoreMIDI::Endpoint item;
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
};

MidiInputReceiver *MidiInputMacCoreMIDI::receiver = NULL;
MidiInputMacCoreMIDI::Endpoint MidiInputMacCoreMIDI::currentEndpoint;

int MidiInput::getDeviceCount()
{
    return MidiInputMacCoreMIDI::getDeviceCount();
}

const QString MidiInput::getDeviceName( int index )
{
    return MidiInputMacCoreMIDI::getDeviceName( index );
}

void MidiInput::setReceiver( MidiInputReceiver *receiver )
{
    MidiInputMacCoreMIDI::setReceiver( receiver );
}

void MidiInput::start( int index )
{
    MidiInputMacCoreMIDI::start( index );
}

void MidiInput::stop()
{
    MidiInputMacCoreMIDI::stop();
}

#endif
