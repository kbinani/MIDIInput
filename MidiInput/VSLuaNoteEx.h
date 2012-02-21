#ifndef __VSLuaNoteEx_h__
#define __VSLuaNoteEx_h__

#include <string>
#include <vsqglobal.h>

class VSLuaNoteEx
{
public:
    VSQ_NS::tick_t posTick;
    VSQ_NS::tick_t durTick;
    int noteNum;
    int velocity;
    std::string lyric;
    std::string phonemes;
    int bendDepth;
    int bendLength;
    bool risePort;
    bool fallPort;
    int decay;
    int accent;
    int opening;
    int vibratoLength;
    int vibratoType;

public:
    explicit VSLuaNoteEx( const std::string = "" );

    const std::string toString();

protected:
    /**
     * @brief 文字列の前後についている空白文字" "を削除する
     * @param text
     */
    static void chomp( std::string &text );
};

#endif
