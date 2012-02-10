#ifndef __MidiInputReceiver_h__
#define __MidiInputReceiver_h__

#include <stdint.h>

class MidiInputReceiver{
public:
    void send( uint8_t b1, uint8_t b2, uint8_t b3 = 0 );
};

#endif
