#ifndef __DialogListener_h__
#define __DialogListener_h__

#include "MidiInputReceiver.h"

class DialogListener : public MidiInputReceiver{
public:
    explicit DialogListener();

    /**
     * MIDI 入力開始が要求されたとき呼ばれる
     * @param channel MIDI 入力ポート番号
     */
    void inputStartRequired( int channel );

    /**
     * MIDI 入力終了が要求されたとき呼ばれる
     */
    void inputStopRequired();

    /**
     * MidiInputReceiver の実装
     */
    void send( unsigned char b1, unsigned char b2, unsigned char b3 = 0 );
};

#endif
