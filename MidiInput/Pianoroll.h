/**
 * Pianoroll.h
 * Copyright © 2012 kbinani
 *
 * This file is part of `MIDIInput UG Job Plugin'.
 *
 * `MIDIInput UG Job Plugin' is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License.
 *
 * `MIDIInput UG Job Plugin' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
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

public:
    Ui::Pianoroll *ui;

    explicit Pianoroll( QWidget *parent = 0 );

    void setTrackHeight( int trackHeight );

    /**
     * @brief ソングポジションを設定する
     * @param songPosition ソングポジション
     * @param autoScroll 自動でスクロールするかどうか
     */
    void setSongPosition( VSQ_NS::tick_t songPosition, bool autoScroll );

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
     * @brief ソングポジションの移動に伴って自動スクロールするかどうかを取得する
     * @return 自動スクロールする場合は true を返す
     */
    bool isAutoScroll();

    /**
     * @brief 指定した位置の音符が可視となるようスクロールする
     * @param tick 時刻
     * @param length 音符の長さ
     * @param noteNumber ノート番号
     */
    void ensureNoteVisible( VSQ_NS::tick_t tick, VSQ_NS::tick_t length, int noteNumber );

    /**
     * @brief 曲頭から Musical Part 開始位置のオフセット
     * @param musicalPartOffset オフセット
     */
    void setMusicalPartOffset( VSQ_NS::tick_t musicalPartOffset );

private:
    /**
     * @brief スクロール領域が縦方向にスクロールしたことを PianorollContentScroller -> Pianoroll に通知する
     */
    void notifyVerticalScroll();
};


#endif // PIANOROLL_H
