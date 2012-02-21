/**
 * Robot.cpp
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
#include <vector>
#include "Robot.h"
#include "WindowFinder.h"

using namespace std;

void Robot::forward()
{
#ifdef WIN32
    HWND editor = WindowFinder::getEditorWindow();
    HWND button = WindowFinder::getForwardToolButton( editor );
    WPARAM wParam = MK_LBUTTON;
    LPARAM lParam = MAKELONG( 13, 18 );
    PostMessage( button, WM_LBUTTONDOWN, wParam, lParam );
    PostMessage( button, WM_LBUTTONUP, wParam, lParam );
#endif
}

void Robot::backward()
{
#ifdef WIN32
    HWND editor = WindowFinder::getEditorWindow();
    HWND button = WindowFinder::getBackwardToolButton( editor );
    WPARAM wParam = MK_LBUTTON;
    LPARAM lParam = MAKELONG( 13, 18 );
    PostMessage( button, WM_LBUTTONDOWN, wParam, lParam );
    PostMessage( button, WM_LBUTTONUP, wParam, lParam );
#endif
}

void Robot::disablePluginCancelButton()
{
#ifdef WIN32
    HWND button = WindowFinder::getPluginCancelButton();
    EnableWindow( button, FALSE );
#endif
}

const string Robot::getSongPosition()
{
#ifdef WIN32
    HWND editor = WindowFinder::getEditorWindow();
    HWND toolbar = WindowFinder::getTransportToolBar( editor );
    vector<HWND> windows;
    WindowFinder::getWindows( toolbar, windows );
    for( vector<HWND>::iterator i = windows.begin(); i != windows.end(); i++ ){
        HWND item = (*i);
        string title = WindowFinder::getTitle( item );
        string::size_type index = title.find( " : " );
        if( index != string::npos ){
            index = title.find( " : ", index + 1 );
            if( index != string::npos ){
                return title;
            }
        }
    }
    return "";
#else
    return "";
#endif
}

int Robot::getPreMeasure()
{
#ifdef WIN32
    // HKEY_CURRENT_USER\Software\VOCALOID3\VOCALOID Editor\System\PreMeasure
    HKEY key;
    RegOpenKeyEx(
        HKEY_CURRENT_USER,
        TEXT( "Software\\VOCALOID3\\VOCALOID Editor\\System" ),
        0,
        KEY_READ,
        &key );
    DWORD valueType;
    const int LENGTH = 10;
    char value[LENGTH];
    DWORD valueSize = LENGTH;
    RegQueryValueEx( key, TEXT( "PreMeasure" ), NULL, &valueType, (LPBYTE)value, &valueSize );
    int result = 4;
    if( valueType == REG_SZ ){
        if( 1 != ::sscanf_s( value, "%d", &result ) ){
            result = 4;
        }
    }
    RegCloseKey( key );
    return result;
#else
    return 4;
#endif
}
