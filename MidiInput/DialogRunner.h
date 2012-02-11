#ifndef __DialogRunner_h__
#define __DialogRunner_h__

#include <QtGui>
#include "DialogListener.h"

class DialogRunner : public QThread{
private:
    DialogListener *listener;

public:
    DialogRunner( DialogListener *listener );

    void run();
};

#endif
