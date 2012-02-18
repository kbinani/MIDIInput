#include <iostream>
#include <sstream>
#include "DialogListener.h"
#include "MidiInput.h"

using namespace std;

DialogListener::DialogListener(){
}



void DialogListener::send( unsigned char b1, unsigned char b2, unsigned char b3 ){
    int command = (b1 & 0xF0);
    if( command == 0x90 && b3 != 0 ){
        int length = 480;
        int position = 1920;
        bool isRest = false;

        ostringstream oss;
        oss << "PUT " << (isRest ? "REST" : "NOTE") << " LENGTH " << length;
        if( !isRest ){
            oss << " PITCH " << (int)b2;
        }
        oss << " AT " << position;
        this->queue.push( oss.str() );
    }
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
