#pragma comment( lib, "lua5.1.lib" )
#pragma comment( lib, "QtCore4.lib" )
#pragma comment( lib, "QtGui4.lib" )
#include <windows.h>

extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <stdio.h>
#include <iostream>
#include "WindowFinder.h"
#include "../MidiInputUi/MidiInputUi.h"

using namespace std;

#ifdef _DEBUG
    void main(){
		MidiInputUi::doSomething();
        HWND scroll = WindowFinder::getHorizontalScroll();

        /*Type SCROLLINFO
    cbSize As Long
    fMask As Long
    nMin As Long
    nMax As Long
    nPage As Long
    nPos As Long
    nTrackPos As Long
End Type*/
        SCROLLINFO info;
        memset( &info, 0, sizeof( SCROLLINFO ) );
        WindowFinder::getScrollInfo( scroll, &info );
        cout << "main; info={nMin=" << info.nMin << ", nMax=" << info.nMax << ", nPage=" << info.nPage << ", nPos=" << info.nPos << ", nTrackPos=" << info.nTrackPos << "}" << endl;

        info.nPos = info.nPos + 100;
        info.nTrackPos = info.nPos;
        //SetScrollInfo( scroll, SB_CTL, &info, FALSE );

        HWND editorWindow = WindowFinder::getEditorWindow();
        HWND musicalEditor = WindowFinder::getMusicalEditor( editorWindow );
        HWND musicalEditorComponent = WindowFinder::getMusicalEditorComponent( musicalEditor );
        cout << "main; musicalEditorComponent=0x" << hex << (int)musicalEditorComponent << dec << endl;

        /*LRESULT SendMessage(
          HWND hWnd,      // 送信先ウィンドウのハンドル
          UINT Msg,       // メッセージ
          WPARAM wParam,  // メッセージの最初のパラメータ
          LPARAM lParam   // メッセージの 2 番目のパラメータ
        );*/

        //SB_THUMBTRACK
        WPARAM wParam = MAKELONG( /*SB_THUMBTRACK*/SB_THUMBPOSITION, info.nTrackPos );
        LPARAM lParam = (LPARAM)scroll;
        SendMessage( musicalEditorComponent, WM_HSCROLL, wParam, lParam );

        return;
    }
#endif

extern "C"{
    int test_func_a( lua_State *state )
    {
		MidiInputUi::doSomething();

		HWND editorWindow = WindowFinder::getHorizontalScroll();

        int length = 100;
        char *foo = new char[length]();
        sprintf( foo, "%d", (int)editorWindow );
        lua_pushstring( state, (const char *)foo );
        delete [] foo;
        return 1;
    }

    BOOL APIENTRY DllMain( HMODULE hModule,
                           DWORD  ul_reason_for_call,
                           LPVOID lpReserved
                         )
    {
        switch (ul_reason_for_call)
        {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
        }
        return TRUE;
    }
}
