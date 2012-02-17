#ifndef __PianorollKeyboard_h__
#define __PianorollKeyboard_h__

#include <QWidget>

class Pianoroll;

class PianorollKeyboard : public QWidget
{
    Q_OBJECT

private:
    Pianoroll *pianoroll;

    /**
     * @brief スクロールが現在どの位置にあるか。親からの notifyVerticalScroll の呼び出しで更新される
     */
    int top;

    /**
     * @brief 鍵盤の音の名前(C4など)
     */
    QString *keyNames;

    /**
     * @brief ノートの描画高さ
     */
    int trackHeight;

public:
    explicit PianorollKeyboard( QWidget *parent = 0 );

    ~PianorollKeyboard();

    void paintEvent( QPaintEvent *e );

    /**
     * @brief このインスタンスを持っているピアノロールを設定する
     * @param pianoroll ピアノロール
     */
    void setPianoroll( Pianoroll *pianoroll );

    void notifyVerticalScroll( int y );

    void setTrackHeight( int trackHeight );

private:
    /**
     * @brief 鍵盤を描画する
     */
    void paintKeyboard( QPainter *g );
};

#endif
