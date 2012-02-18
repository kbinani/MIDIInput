#include "DialogRunner.h"

#include "QtGui"
#include "Dialog.h"
#include "DialogListener.h"
#include "Pianoroll.h"

void DialogRunner::run(){
    int argc;
    QApplication application( argc, NULL );
    Dialog dialog;
    dialog.exec();
}
