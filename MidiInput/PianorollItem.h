#ifndef PIANOROLLITEM_H
#define PIANOROLLITEM_H

#include <string>

class PianorollItem
{
public:
    /**
     * ノート番号
     */
    int noteNumber;

    /**
     * tick 単位の長さ
     */
    int length;

    /**
     * 歌詞
     */
    std::string phrase;

    /**
     * 発音記号
     */
    std::string symbols;

public:
    PianorollItem();
};

#endif // PIANOROLLITEM_H
