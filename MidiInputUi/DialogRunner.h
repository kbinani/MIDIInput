#ifndef __DialogRunner_h__
#define __DialogRunner_h__

#include <QtGui>
#include "Dialog.h"

class DialogRunner : public QThread{
public:
    void run();
};

#endif
