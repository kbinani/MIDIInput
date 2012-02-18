extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <stdio.h>
#include <iostream>
#include "WindowFinder.h"
#include "MidiInput.h"
#include "DialogRunner.h"
#include "Dialog.h"

using namespace std;

DialogRunner *dialogRunner = NULL;
DialogListener *dialogListener = NULL;

/**
 * 次のコマンドがあるかどうかを取得する
 */
extern "C"{
    Q_DECL_EXPORT int hasNext( lua_State *state ){
        if( !dialogRunner || !dialogListener ){
            if( dialogRunner ){
                delete dialogRunner;
            }
            if( dialogListener ){
                delete dialogListener;
            }
            dialogRunner = new DialogRunner();
            dialogRunner->start();
        }
        bool isFinished = dialogRunner->isFinished();

        if( isFinished ){
            delete dialogListener;
            delete dialogRunner;
            dialogListener = NULL;
            dialogRunner = NULL;
        }

        lua_pushboolean( state, isFinished ? FALSE : TRUE );
        return 1;
    }

    /**
     * 次のコマンド文字列を取得する
     */
    Q_DECL_EXPORT int next( lua_State *state ){
        while( !dialogListener->hasNext() && !dialogRunner->isFinished() ){
            QThread::currentThread()->wait( 5 );
        }
        string command = dialogListener->get();
        lua_pushstring( state,  command.c_str() );
        return 1;
    }
}

int main( int argc, char *argv[] ){
    QApplication app( argc, argv );
    Dialog d( NULL );
    d.show();
    return app.exec();
}
