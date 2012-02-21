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
