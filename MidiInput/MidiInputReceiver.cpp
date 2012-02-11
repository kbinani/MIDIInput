#include "MidiInputReceiver.h"
#include <iostream>

using namespace std;

void MidiInputReceiver::send( unsigned char b1, unsigned char b2, unsigned char b3 ){
    {//TODO:
        cout << "MidiInputReceiver::send; 0x" << hex << (int)b1 << ", 0x" << (int)b2 << ", 0x" << (int)b3 << dec << endl;
    }
}
