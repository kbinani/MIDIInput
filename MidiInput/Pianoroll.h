#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <vector>
#include <QWidget>
#include "PianorollItem.h"

namespace Ui {
    class Pianoroll;
}

class Pianoroll : public QWidget
{
    Q_OBJECT

public:
    static const int DEFAULT_TRACK_HEIGHT = 14;

private:
    Ui::Pianoroll *ui;

    /**
     * 描画されるアイテムの一覧
     */
    std::vector<PianorollItem *> *items;

    /**
     * 鍵盤の表示幅
     */
    int keyWidth;

    /**
     * ノートの描画高さ
     */
    int trackHeight;

    /**
     * 鍵盤の音の名前(C4など)
     */
    QString keyNames[128];

public:
    explicit Pianoroll(QWidget *parent = 0);
    ~Pianoroll();
    void setItems( std::vector<PianorollItem *> *aItems );
    void paintEvent( QPaintEvent *e );

private:
    QRect getVisibleArea();

    void paintBackground( QPainter *g, QRect visibleArea );

    /**
     * 鍵盤を描画する
     */
    void paintKeyboard( QPainter *g, QRect, QRect visibleArea );
};

#endif // PIANOROLL_H
