#include "MidiInputReceiver.h"
#include <iostream>

using namespace std;

void MidiInputReceiver::send( uint8_t b1, uint8_t b2, uint8_t b3 ){
    {//TODO:
        cout << "MidiInputReceiver::send; 0x" << hex << (int)b1 << ", 0x" << (int)b2 << ", 0x" << (int)b3 << dec << endl;
    }
}
