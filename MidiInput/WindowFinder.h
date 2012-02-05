#ifndef __midiinput_WindowFinder_h__
#define __midiinput_WindowFinder_h__

#include <windows.h>
#include <vector>
#include <string>

class WindowFinder{
public:
    static HWND getHorizontalScroll();

    static void getScrollInfo( HWND scroll, LPSCROLLINFO info );

    static HWND getEditorWindow();

    static HWND getMusicalEditor( HWND editorWindow );

    static HWND getMusicalEditorComponent( HWND musicalEditor );

private:
    WindowFinder(){
    }

    /**
     * 指定されたウィンドウの子ウィンドウを列挙する
     */
    static void getWindows( HWND window, std::vector<HWND> &result );

    /**
     * ウィンドウのタイトルを取得する
     */
    static std::string getTitle( HWND window );

    static BOOL CALLBACK enumerationCallback( HWND hwnd, LPARAM lParam );
};
#endif
