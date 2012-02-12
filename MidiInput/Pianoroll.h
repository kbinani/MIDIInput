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
    /**
     * ノート描画高さのデフォルト値(ピクセル単位)
     */
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
     * 1 tick 時刻を何ピクセルで描画するか
     */
    double pixelPerTick;

    /**
     * 鍵盤の音の名前(C4など)
     */
    QString keyNames[128];

public:
    explicit Pianoroll(QWidget *parent = 0);
    ~Pianoroll();

    /**
     * 描画対象のアイテムリストを設定する
     */
    void setItems( std::vector<PianorollItem *> *aItems );

    /**
     * オーバーライドする。ピアノロールの描画処理が追加される
     */
    void paintEvent( QPaintEvent *e );

private:
    /**
     * スクロールされた結果、可視状態となっている領域を取得する
     */
    QRect getVisibleArea();

    /**
     * ピアノロールのバックグラウンドを描画する
     */
    void paintBackground( QPainter *g, QRect visibleArea );

    /**
     * アイテムを描画する
     */
    void paintItems( QPainter *g, QRect visibleArea );

    /**
     * 鍵盤を描画する
     */
    void paintKeyboard( QPainter *g, QRect, QRect visibleArea );

    /**
     * tick 単位の時刻から、描画時の x 座標を取得する
     */
    inline int getXFromTick( long int tick );

    /**
     * ノート番号から、描画時の y 座標を取得する
     */
    inline int getYFromNoteNumber( int noteNumber );
};

#endif // PIANOROLL_H
