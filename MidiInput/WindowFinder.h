#ifndef __midiinput_WindowFinder_h__
#define __midiinput_WindowFinder_h__

#ifdef WIN32
#include <windows.h>
#include <vector>
#include <string>

class WindowFinder{
public:
    /**
     * ピアノロールの水平スクロールバーのハンドルを取得する
     */
    static HWND getHorizontalScroll();

    /**
     * スクロールの情報を取得する
     */
    static void getScrollInfo( HWND scroll, LPSCROLLINFO info );

    /**
     * エディタウィンドウのハンドルを取得する
     */
    static HWND getEditorWindow();

    /**
     * Musical エディタのハンドルを取得する
     */
    static HWND getMusicalEditor( HWND editorWindow );

    /**
     * Musical エディタ内の ContentPane のハンドルを取得する
     */
    static HWND getMusicalEditorComponent( HWND musicalEditor );

    /**
     * 早送りボタンのハンドルを取得する
     */
    static HWND getForwardToolButton( HWND editorWindow );

    /**
     * 巻き戻しボタンのハンドルを取得する
     */
    static HWND getBackwardToolButton( HWND editorWindow );

    /**
     * @brief プラグインの進捗を表示するウィンドウを取得する
     * @return ウィンドウハンドル
     */
    static HWND getPluginProgressWindow();

    /**
     * @brief プラグインを中断するための"Cancel"ボタンのハンドルを取得する
     * @return Cancel ボタンのウィンドウハンドル
     */
    static HWND getPluginCancelButton();

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

    /**
     * Musical Editor の中に配置されている ContentPane 的なコンポーネントと、
     * 水平スクロールバーのコンポーネントのハンドルを取得する
     */
    static void getComponentAndScroll( HWND musicalEditor, HWND *component, HWND *scroll );

    static HWND getToolButton( HWND editorWindow, std::string title );
};
#endif
#endif
