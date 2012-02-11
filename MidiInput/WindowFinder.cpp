#include <iostream>
#include "WindowFinder.h"

#ifdef WIN32

using namespace std;

void WindowFinder::getScrollInfo( HWND scroll, LPSCROLLINFO info ){
    info->cbSize = sizeof( SCROLLINFO );
    info->fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
    GetScrollInfo( scroll, SB_CTL, info );
}

HWND WindowFinder::getEditorWindow(){
    return ::FindWindowA( NULL, "VOCALOID3 Editor - TRACK EDITOR" );
}

HWND WindowFinder::getMusicalEditor( HWND editorWindow ){
    /*
     * + VOCALOID3.exe
     *       + MDIClient
     *             + "VOCALOID3 Editor - TRACK EDITOR"
     *                   + (maybe variable)
     *                         + MUSICAL EDITOR - NewPart [VY1V3]
     *                               + (maybe variable)
     *                                     + ScrollBar
     *                                     + ScrollBar
     */
    HWND result = NULL;
    vector<HWND> windows;
    WindowFinder::getWindows( editorWindow, windows );
    vector<HWND>::iterator i = windows.begin();
    for( ; i != windows.end(); i++ ){
        vector<HWND> childWindows;
        WindowFinder::getWindows( (*i), childWindows );
        vector<HWND>::iterator j = childWindows.begin();

        string searchTitle = "MUSICAL EDITOR - ";
        for( ; j != childWindows.end(); j++ ){
            string title = WindowFinder::getTitle( (*j) );
            if( title.length() >= searchTitle.length() && title.substr( 0, searchTitle.length() ) == searchTitle ){
                result = (*j);
                break;
            }
        }
        if( result ){
            break;
        }
    }
    return result;
}

void WindowFinder::getComponentAndScroll( HWND musicalEditor, HWND *component, HWND *scroll ){
    *scroll = NULL;
    *component = NULL;

    vector<HWND> windows;
    WindowFinder::getWindows( musicalEditor, windows );
    vector<HWND>::iterator i = windows.begin();
    for( ; i != windows.end(); i++ ){
        vector<HWND> childWindows;
        WindowFinder::getWindows( (*i), childWindows );
        vector<HWND>::iterator j = childWindows.begin();
        for( ; j != childWindows.end(); j++ ){
            LONG_PTR result = GetWindowLongPtr( (*j), GWL_STYLE );
            if( (result & SBS_VERT) != SBS_VERT ){
                *scroll = (*j);
                *component = (*i);
                return;
            }
        }
    }
    return;
}

HWND WindowFinder::getMusicalEditorComponent( HWND musicalEditor ){
    HWND component, scroll;
    WindowFinder::getComponentAndScroll( musicalEditor, &component, &scroll );
    return component;
}

HWND WindowFinder::getHorizontalScroll(){
    HWND editorWindow = WindowFinder::getEditorWindow();
    HWND musicalEditor = WindowFinder::getMusicalEditor( editorWindow );

    HWND component, scroll;
    WindowFinder::getComponentAndScroll( musicalEditor, &component, &scroll );

    return scroll;
}

void WindowFinder::getWindows( HWND window, vector<HWND> &result ){
    EnumChildWindows( window, WindowFinder::enumerationCallback, (LPARAM)&result );
}

string WindowFinder::getTitle( HWND window ){
    int maxLength = 512;
    char *title = new char[maxLength]();
    int length = GetWindowTextA( window, title, maxLength );
    string result = title;
    delete [] title;
    return result;
}

HWND WindowFinder::getForwardToolButton( HWND editorWindow ){
    return WindowFinder::getToolButton( editorWindow, "tool_forward" );
}

HWND WindowFinder::getBackwardToolButton( HWND editorWindow ){
    return WindowFinder::getToolButton( editorWindow, "tool_backward" );
}

HWND WindowFinder::getToolButton( HWND editor, string title ){
    vector<HWND> level1;
    WindowFinder::getWindows( editor, level1 );
    for( vector<HWND>::iterator i = level1.begin(); i != level1.end(); i++ ){
        vector<HWND> level2;
        WindowFinder::getWindows( (*i), level2 );
        for( vector<HWND>::iterator j = level2.begin(); j != level2.end(); j++ ){
            vector<HWND> level3;
            WindowFinder::getWindows( (*j), level3 );
            for( vector<HWND>::iterator k = level3.begin(); k != level3.end(); k++ ){
                string text = WindowFinder::getTitle( (*k) );
                if( text == title ){
                    return (*k);
                }
            }
        }
    }
    return NULL;
}

/*bool WindowFinder::getHorizontalScrollInfo( HWND scroll, LPSCROLLINFO info ){
    info->cbSize = sizeof( SCROLLINFO );
    info->fMask = SIF_PAGE | SIF_POS | SIF_RANGE | SIF_TRACKPOS;
    if( GetScrollInfo( scroll, SB_HORZ, info ) ){
        return true;
    }else{
        return false;
    }
}*/

BOOL CALLBACK WindowFinder::enumerationCallback( HWND hwnd, LPARAM lParam ){
    vector<HWND> *result = (vector<HWND> *)lParam;
    result->push_back( hwnd );
    return TRUE;
}

#endif
