#include "DialogRunner.h"

#include "QtGui"
#include "Dialog.h"

void DialogRunner::run(){
    int argc;
    QApplication application( argc, NULL );
    Dialog dialog;
    dialog.exec();
}
