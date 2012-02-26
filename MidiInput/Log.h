/**
 * Log.h
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
#ifndef __DebugDialog_h__
#define __DebugDialog_h__

#include <fstream>
#include <QDialog>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QDebug>
#include <QTextStream>

class Log
{
private:
    static Log *logger;

    std::ofstream buffer;

public:
    Log() :
        buffer( "midiinput.log" )
    {
    }

    static Log &stream()
    {
        if( logger == NULL ){
            logger = new Log();
        }
        return *logger;
    }

    inline Log &operator << ( const char* t )
    {
        buffer << t;
        buffer.flush();
        return *this;
    }

    inline Log &operator << ( int i )
    {
        buffer << i;
        buffer.flush();
        return *this;
    }
};

#endif
