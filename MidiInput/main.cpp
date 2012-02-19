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

//    string result = dialog.getMetaText();
    string result = eventTextString;

    lua_pushstring( state, "foo" );//result.c_str() );
    return 1;
}

#ifdef QT_DEBUG
int main( int argc, char *argv[] ){
    QApplication app( argc, argv );
    ostringstream oss;
    oss << "0,62,a,w a,480";
    oss << "\x0A";
    oss << "480,64,ra,4 a,480";
    string eventText = oss.str();

    oss.str( "" );
    oss.clear( ostringstream::goodbit );
    oss << "0,4,4";
    oss << "\x0A";
    oss << "1920,3,4";
    string timesigText = oss.str();
    Dialog d( eventText, timesigText, NULL );
    d.show();
    return app.exec();
}
#endif

