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
    Log::Log() :
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
