/**
 * MidiInputReceiver.h
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
#ifndef __MidiInputReceiver_h__
#define __MidiInputReceiver_h__

class MidiInputReceiver{
public:
    virtual void send( unsigned char b1, unsigned char b2, unsigned char b3 = 0 ) = 0;
};

#endif
