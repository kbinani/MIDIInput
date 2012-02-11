#ifndef __MidiInputReceiver_h__
#define __MidiInputReceiver_h__

class MidiInputReceiver{
public:
    void send( unsigned char b1, unsigned char b2, unsigned char b3 = 0 );
};

#endif
