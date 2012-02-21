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
