#ifndef __DialogRunner_h__
#define __DialogRunner_h__

#include <QtGui>
#include "DialogListener.h"

class DialogRunner : public QThread{
public:
    void run();
};

#endif
