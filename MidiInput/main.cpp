extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <stdio.h>
#include <iostream>
#include <QApplication>
#include "WindowFinder.h"
#include "MidiInput.h"
#include "Dialog.h"

using namespace std;

/**
 * @brief ダイアログを表示し、ダイアログが閉じるのを待つ
 */
extern "C" Q_DECL_EXPORT int start( lua_State *state ){
    int argc = lua_gettop( state );
    if( argc != 1 ){
        return 0;
    }

    size_t length;
    const char* metaText = lua_tostring( state, 1, &length );
    string metaTextString( metaText );
    Dialog dialog( metaTextString );
    dialog.exec();

    string result = dialog.getMetaText();

    lua_pushstring( state, result.c_str() );
    return 1;
}

int main( int argc, char *argv[] ){
    QApplication app( argc, argv );
    Dialog d( string( "" ), NULL );
    d.show();
    return app.exec();
}
