#ifndef __DialogListener_h__
#define __DialogListener_h__

#include <string>
#include <queue>
#include "MidiInputReceiver.h"

class DialogListener : public MidiInputReceiver{
private:
    std::queue<std::string> queue;
    int channel;

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

    /**
     * 入力された音符情報を取得する
     */
    std::string get();

    /**
     * get できる音符情報があるかどうかを取得する
     */
    bool hasNext();

private:
    /**
     * キューを空にする
     */
    void clearQueue();
};

#endif
