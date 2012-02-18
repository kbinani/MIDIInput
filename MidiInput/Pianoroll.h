#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <vector>
#include <QScrollArea>
#include <MeasureLineIterator.h>
#include <TimesigList.h>
#include "PianorollItem.h"
#include "PianorollContent.h"
#include "PianorollKeyboard.h"

namespace Ui{
    class Pianoroll;
}

class Pianoroll : public QWidget
{
    Q_OBJECT

public:
    Ui::Pianoroll *ui;

    explicit Pianoroll( QWidget *parent = 0 );

    /**
     * スクロール領域が縦方向にスクロールしたことを子→親に通知する
     */
    void notifyVerticalScroll();

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
     * @brief オーバーライドする。ピアノロール本体と、鍵盤部分を repaint する処理を追加している。
     */
    void repaint();
};


#endif // PIANOROLL_H
