/**
 * DialogRunner.h
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
#ifndef __DialogRunner_h__
#define __DialogRunner_h__

#include <QThread>
#include <vsqglobal.h>

class DialogRunner : public QThread
{
private:
    std::string eventText;
    std::string timesigText;
    VSQ_NS::tick_t musicalPartOffset;

public:
    /**
     * @param eventText 音符情報を格納したテキスト。VSLuaNoteEx でパースできる形式の音符が 0x0A で区切られた形式
     * @param timesigText 拍子変更情報を格納したテキスト
     * @param musicalPartOffset 表示する Musical Part の先頭と、曲頭とのオフセット(tick 単位)
     */
    explicit DialogRunner( const std::string eventText, const std::string timesigText, VSQ_NS::tick_t musicalPartOffset );

    void run();

    /**
     * @brief 編集結果の音符情報を取得する
     * @return 音符情報
     */
    const std::string getEventText();

private:
    DialogRunner(){
    }
};

#endif
