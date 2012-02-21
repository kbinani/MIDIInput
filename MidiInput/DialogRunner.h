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

class DialogRunner : public QThread
{
private:
    std::string eventText;
    std::string timesigText;

public:
    explicit DialogRunner( const std::string eventText, const std::string timesigText );

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
