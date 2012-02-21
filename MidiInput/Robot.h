/**
 * Robot.h
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
#ifndef __Robot_h__
#define __Robot_h__

class Robot{
public:
    /**
     * 早送りボタンを押す
     */
    static void forward();

    /**
     * 巻き戻しボタンを押す
     */
    static void backward();

    /**
     * @brief Job Plugin 実行中に表示される"Running JobPlugin ..."ウィンドウ内の、"Cancel"ボタンを無効化する
     */
    static void disablePluginCancelButton();

private:
    Robot(){
    }
};

#endif
