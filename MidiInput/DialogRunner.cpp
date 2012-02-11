#include "DialogRunner.h"

#include "QtGui"
#include "Dialog.h"
#include "DialogListener.h"
#include "Pianoroll.h"

DialogRunner::DialogRunner( DialogListener *listener ){
    this->listener = listener;
}

void DialogRunner::run(){
    int argc;
    QApplication application( argc, NULL );
    Dialog dialog( this->listener );
    dialog.exec();
}
