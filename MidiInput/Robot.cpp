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
#include "Robot.h"
#include "WindowFinder.h"


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
