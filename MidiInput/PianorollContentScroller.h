#ifndef __PianorollContentScroller_h__
#define __PianorollContentScroller_h__

#include <QScrollArea>

class Pianoroll;

class PianorollContentScroller : public QScrollArea
{
    Q_OBJECT

private:
    Pianoroll *pianoroll;

public:
    explicit PianorollContentScroller( QWidget *parent = 0 );

    /**
     * @brief このインスタンスを持っているピアノロールを設定する
     * @param pianoroll ピアノロール
     */
    void setPianoroll( Pianoroll *pianoroll );

    void scrollContentsBy( int dx, int dy );
};

#endif
