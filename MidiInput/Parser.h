#ifndef __Parser_h__
#define __Parser_h__

#include <map>
#include <string>
#include <vsqglobal.h>
#include <TimesigList.h>
#include "PianorollItem.h"

class Parser{
public:
    /**
     * @brief イベント情報が記録されたテキストを parse する
     * @param eventText イベントが記録されたテキスト
     *     480,60,あ,a,480
     *     940,62,わ,w a,480
     *     {tick},{noteNumber},{phrase},{symbol},{length}
     */
    std::map<VSQ_NS::tick_t, PianorollItem *> *getEvent( const std::string eventText );

    /**
     * @brief 拍子変更情報が記録されたテキスト
     * @param timesigText 拍子変更情報が記録されたテキスト
     *     0,4,4
     *     {tick},{numerator},{denominator}
     */
    VSQ_NS::TimesigList *getTimesig( const std::string timesigText );

    /**
     * @brief イベント情報をテキストに変換する。getEvent の逆の処理を行うメソッド
     */
    const std::string toString( std::map<VSQ_NS::tick_t, PianorollItem *> *items );
};

#endif
