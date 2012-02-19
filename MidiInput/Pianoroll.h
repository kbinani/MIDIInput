#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <map>
#include <QScrollArea>
#include <QMutex>
#include <MeasureLineIterator.h>
#include <TimesigList.h>
#include "PianorollItem.h"
#include "PianorollContentScroller.h"
#include "PianorollKeyboard.h"

namespace Ui{
    class Pianoroll;
}

class Pianoroll : public QWidget
{
    friend class PianorollContentScroller;

    Q_OBJECT

private:
    /**
     * @brief ソングポジションの移動に伴って自動スクロールするかどうか
     */
    bool autoScroll;

public:
    Ui::Pianoroll *ui;

    explicit Pianoroll( QWidget *parent = 0 );

    void setTrackHeight( int trackHeight );

    /**
     * @brief ソングポジションを設定する
     * @param ソングポジション
     */
    void setSongPosition( VSQ_NS::tick_t songPosition );

    /**
     * @brief ソングポジションを取得する
     * @return ソングポジション
     */
    VSQ_NS::tick_t getSongPosition();

    /**
     * @brief テンポ変更リストを設定する
     * @param timesigList テンポ変更リスト
     */
    void setTimesigList( VSQ_NS::TimesigList *timesigList );

    /**
     * @brief 描画対象のアイテムリストを設定する
     * @param items 描画対象のアイテム
     */
    void setItems( std::map<VSQ_NS::tick_t, PianorollItem *> *items );

    /**
     * @brief オーバーライドする。ピアノロール本体と、鍵盤部分を repaint する処理を追加している。
     */
    void repaint();

    /**
     * @brief ミューテックスを設定する
     * @param mutex ミューテックス
     */
    void setMutex( QMutex *mutex );

    /**
     * @brief ソングポジションの移動に伴って自動スクロールするかどうかを設定する
     * @param autoScroll 自動スクロールする場合は true を設定する
     */
    void setAutoScroll( bool autoScroll );

private:
    /**
     * @brief スクロール領域が縦方向にスクロールしたことを PianorollContentScroller -> Pianoroll に通知する
     */
    void notifyVerticalScroll();
};


#endif // PIANOROLL_H
