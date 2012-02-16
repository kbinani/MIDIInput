#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <vector>
#include <QWidget>
#include "PianorollItem.h"
#include <TimesigList.h>
#include <MeasureLineIterator.h>

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

    static const int NOTE_MIN = 0;

    static const int NOTE_MAX = 127;

private:
    Ui::Pianoroll *ui;

    /**
     * 描画されるアイテムの一覧
     */
    std::vector<PianorollItem *> *items;

    /**
     * 拍ごとの線を描画するための、拍子変更情報
     */
    cadencii::vsq::TimesigList *timesigList;

    /**
     * @brief デフォルトの拍子変更情報
     */
    cadencii::vsq::TimesigList defaultTimesigList;

    /**
     * @brief 拍ごとの線を描画するために、timesigList から作成した反復子
     */
    cadencii::vsq::MeasureLineIterator *measureLineIterator;

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
    QString *keyNames;

public:
    /**
     * @brief ウィジェットの、スクリーン上での座標を取得する
     * @param widget ウィジェット
     * @return スクリーン上での座標
     */
    static QPoint getPositionOnScreen( QWidget *widget );

    explicit Pianoroll( QWidget *parent = 0 );

    ~Pianoroll();

    /**
     * 描画対象のアイテムリストを設定する
     */
    void setItems( std::vector<PianorollItem *> *items, cadencii::vsq::TimesigList *timesigList );

    /**
     * オーバーライドする。ピアノロールの描画処理が追加される
     */
    void paintEvent( QPaintEvent *e );

    /**
     * オーバーライドする。再描画処理が追加される
     */
    void mouseMoveEvent( QMouseEvent *e );

    /**
     * @brief ノートの描画高さを設定する
     * @param trackHeight ノートの描画高さ
     */
    void setTrackHeight( int trackHeight );

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
    void paintKeyboard( QPainter *g, QRect visibleArea );

    /**
     * 1拍ごとの線を描画する
     */
    void paintMeasureLines( QPainter *g, QRect visibleArea );

    /**
     * tick 単位の時刻から、描画時の x 座標を取得する
     */
    inline int getXFromTick( cadencii::vsq::tick_t tick );

    /**
     * @brief x 座標から、tick 単位の時刻を取得する
     */
    inline double getTickFromX( int x );

    /**
     * ノート番号から、描画時の y 座標を取得する
     */
    inline int getYFromNoteNumber( int noteNumber );

    /**
     * @brief y 座標からノート番号を取得する
     * @param y 座標
     * @return ノート番号
     */
    inline int getNoteNumberFromY( int y );

    /**
     * @brief 最小高さを取得する
     */
    inline int getMinimumHeight();

    /**
     * @brief ノート番号から、音名を表す番号を取得する。Cであれば0, C#であれば1など
     * @param noteNumber ノート番号
     * @return 音名を表す番号
     */
    inline int getNoteModuration( int noteNumber );

    /**
     * @brief ノート番号から、その音高が何オクターブめかを取得する。
     * @param noteNumber ノート番号
     * @return 何オクターブめかを表す番号
     */
    inline int getNoteOctave( int noteNumber );

    /**
     * @brief widget の親の位置を取得し、引数 p の座標値に加算する
     * @param widget ウィジェット
     * @param p 座標
     */
    static void getPosition( QWidget *widget, QPoint &p );
};

#endif // PIANOROLL_H
