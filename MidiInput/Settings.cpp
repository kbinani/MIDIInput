#include <string>
#include "Settings.h"

using namespace std;

map<Qt::Key, string> Settings::toolButtonShortcut;

map<Qt::Key, string> *Settings::getToolButtonShortcut()
{
    const int BUTTONS = 10;
    const char *toolButtons[BUTTONS] = {
        "toolButtonNote001", "toolButtonNote002", "toolButtonNote004", "toolButtonNote008", "toolButtonNote016",
        "toolButtonRest001", "toolButtonRest002", "toolButtonRest004", "toolButtonRest008", "toolButtonRest016",
    };
    const Qt::Key defaultShortcut[BUTTONS] = {
        Qt::Key_Q, Qt::Key_W, Qt::Key_E, Qt::Key_R, Qt::Key_T,
        Qt::Key_A, Qt::Key_S, Qt::Key_D, Qt::Key_F, Qt::Key_G,
    };

    for( int i = 0; i < BUTTONS; i++ ){
        string name = toolButtons[i];
        Qt::Key shortcut = defaultShortcut[i];
        bool found = false;
        map<Qt::Key, string>::iterator j;
        for( j = toolButtonShortcut.begin(); j != toolButtonShortcut.end(); j++ ){
            if( j->second == name ){
                found = true;
                break;
            }
        }
        if( !found ){
            toolButtonShortcut.insert( make_pair( shortcut, name ) );
        }
    }

    return &toolButtonShortcut;
}
