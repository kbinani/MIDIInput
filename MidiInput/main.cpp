extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <QApplication>
#include "WindowFinder.h"
#include "MidiInput.h"
#include "Dialog.h"
#include "DialogRunner.h"

using namespace std;

/**
 * @brief ダイアログを表示し、ダイアログが閉じるのを待つ
 */
extern "C" Q_DECL_EXPORT int start( lua_State *state ){
    int argc = lua_gettop( state );
    if( argc != 2 ){
        return 0;
    }

    const char *eventText = lua_tostring( state, 1 );
    const char *timesigText = lua_tostring( state, 2 );
    string eventTextString( eventText );
    string timesigTextString( timesigText );
    DialogRunner runner( eventTextString, timesigTextString );
    runner.start();
    runner.wait();

    string result = runner.getEventText();

    lua_pushstring( state, result.c_str() );
    return 1;
}

#ifdef QT_DEBUG
int main( int argc, char *argv[] ){
    QApplication app( argc, argv );

    ostringstream oss;
    oss << "{posTick=0,noteNum=62,lyric='a',phonemes='w a',durTick=480}";
    oss << "\x0A";
    oss << "{posTick=480,noteNum=64,lyric='ra',phonemes='4 a',durTick=480}";
    string eventText = oss.str();

    oss.str( "" );
    oss.clear( ostringstream::goodbit );
    oss << "0,4,4";
    oss << "\x0A";
    oss << "1920,3,4";
    string timesigText = oss.str();

    Dialog d( eventText, timesigText, NULL );
    d.show();
    eventText = d.getEventText();
    int result = app.exec();
    qDebug( eventText.c_str() );
    return result;
}
#endif

