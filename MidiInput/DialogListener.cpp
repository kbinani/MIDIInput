#include <iostream>
#include <sstream>
#include "DialogListener.h"
#include "MidiInput.h"

using namespace std;

DialogListener::DialogListener(){
}

void DialogListener::inputStartRequired( int channel ){
    this->clearQueue();
    this->channel = channel;
    MidiInput::setReceiver( this );
    MidiInput::start( this->channel );
}

void DialogListener::inputStopRequired(){
    MidiInput::stop( this->channel );
    MidiInput::setReceiver( NULL );
}

void DialogListener::send( unsigned char b1, unsigned char b2, unsigned char b3 ){
    ostringstream oss;
    oss << hex << "0x" << (int)b1 << " 0x" << (int)b2 << " 0x" << (int)b3;
    this->queue.push( oss.str() );
}

void DialogListener::clearQueue(){
    while( !this->queue.empty() ){
        this->queue.pop();
    }
}

std::string DialogListener::get(){
    if( this->queue.empty() ){
        return "";
    }else{
        string result = this->queue.front();
        this->queue.pop();
        return result;
    }
}

bool DialogListener::hasNext(){
    return false == this->queue.empty();
}
