/**
 * MidiInput.h
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
