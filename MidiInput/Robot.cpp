#include "Robot.h"
#include "WindowFinder.h"

void Robot::forward(){
    HWND editor = WindowFinder::getEditorWindow();
    HWND button = WindowFinder::getForwardToolButton( editor );
    WPARAM wParam = MK_LBUTTON;
    LPARAM lParam = MAKELONG( 13, 18 );
    PostMessage( button, WM_LBUTTONDOWN, wParam, lParam );
    PostMessage( button, WM_LBUTTONUP, wParam, lParam );
}

void Robot::backward(){
    HWND editor = WindowFinder::getEditorWindow();
    HWND button = WindowFinder::getBackwardToolButton( editor );
    WPARAM wParam = MK_LBUTTON;
    LPARAM lParam = MAKELONG( 13, 18 );
    PostMessage( button, WM_LBUTTONDOWN, wParam, lParam );
    PostMessage( button, WM_LBUTTONUP, wParam, lParam );
}