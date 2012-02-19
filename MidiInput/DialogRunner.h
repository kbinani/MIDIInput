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

private:
    DialogRunner(){
    }
};

#endif
